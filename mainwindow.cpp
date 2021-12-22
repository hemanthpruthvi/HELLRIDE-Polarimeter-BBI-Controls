#define HandleError(Error, ErrorLocation) if (Error!=0) { printf("Error %s (%d) \n", ErrorLocation, Error);}
#define PrintStatus(Error, ErrorLocation) {printf("%s (%d) \n", ErrorLocation, Error);}

#include "mainwindow.h"
#include "ui_mainwindow.h"

/***
Initialize the global variables
***/
Camera *DetectorPCh1;
Camera *DetectorPCh2;
Camera *DetectorBBCh;
QSettings *Settings;
QSettings *obsSettings;
QSettings *chrSettings;
std::vector<double> XData, YData;
std::vector<double> XData2, YData2;
//QThread *ThreadAcquisition;
//QThread *ThreadCAM1;
//QThread *ThreadCAM2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (!QDir("./Logs").exists()) QDir().mkdir("./Logs");
    std::ofstream DevLog("./Logs/HELLRIDE_" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss").toStdString() + "_log.txt");
    //
    DataDetails = new Details();
    obsSettings = new QSettings("./obsSettings.ini", QSettings::IniFormat);
    Settings = new QSettings("./coreSettings.ini", QSettings::IniFormat);
    showSettings();
    addLog("Core settings loaded from coreSettings.ini");
    addLog("Observation settings loaded from obsSettings.ini");
    ui->lineEditSettings->setText("./obsSettings.ini");
    ui->lineEditAutoSave->setText(Settings->value("Common/AutoSaveDir").toString());
    //
    FilterMatrix = new TwoStages();
    ETStages = new TwoStages();
    PolarimeterStages = new TwoStages();
    ET50 = new Etalon();
    ET70 = new Etalon();
    LCVRPolarimeter = new Polarimeter();
    VTTControls = new VTT();
    VTTServer = new VTTNet();
    //
    DetectorBBCh = new Camera();
    DetectorPCh1 = new Camera();
    DetectorPCh2 = new Camera();
    //
    Display0 = new imageview();
    Display1 = new imageview();
    Display2 = new imageview();
    DisplayPlot = new plotview();
    //
    ui->toolBoxAcquisition->setCurrentIndex(OBS_MODE_SCIE);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (ui->pushButtonOpenFMS->isChecked()) delete FilterMatrix;
    if (ui->pushButtonOpenETS->isChecked()) delete ETStages;
    if (ui->pushButtonOpenPLS->isChecked()) delete PolarimeterStages;
    if (ui->pushButtonOpenVTTServer->isChecked()) delete VTTServer;
    if (ui->pushButtonOpenVTT->isChecked()) delete VTTControls;
    if (ui->pushButtonOpenCWP->isChecked()) delete CWPMount;
    if (ui->pushButtonOpenET1->isChecked()) delete ET50;
    if (ui->pushButtonOpenET2->isChecked()) delete ET70;
    if (ui->pushButtonOpenLCVR->isChecked()) delete LCVRPolarimeter;
    if (ui->pushButtonOpenCAM0->isChecked()) delete DetectorBBCh;
    if (ui->pushButtonOpenCAM1->isChecked()) delete DetectorPCh1;
    if (ui->pushButtonOpenCAM2->isChecked()) delete DetectorPCh2;
    if (DevLog.is_open()) DevLog.close();
    if (Display0->isVisible()) Display0->close();
    if (Display1->isVisible()) Display1->close();
    if (Display2->isVisible()) Display2->close();
    if (DisplayPlot->isVisible()) DisplayPlot->close();
    event->accept();
}

void MainWindow::addLog(QString Log)
{
//    QString Temp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz   ") + Log;
    ui->plainTextEditLog->appendPlainText(Log);
    DevLog << Log.toStdString() << std::endl;
    std::cout << Log.toStdString() << std::endl;
}

void MainWindow::showSettings()
{
    QString Value;
    QTableWidgetItem *TableItem = new QTableWidgetItem;
    //
    int i=0;
    ui->tableWidgetCoreSettings->setRowCount(0);
    ui->tableWidgetCoreSettings->setColumnCount(2);
    ui->tableWidgetCoreSettings->setColumnWidth(0,280);
    ui->tableWidgetCoreSettings->setColumnWidth(1,170);
    //
    foreach (const QString &Key, Settings->allKeys()){
        ui->tableWidgetCoreSettings->insertRow(i);
        TableItem = new QTableWidgetItem;
        TableItem->setText(Key);
        TableItem->setFlags(TableItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidgetCoreSettings->setItem(i, 0, TableItem);
        TableItem = new QTableWidgetItem;
        if (Settings->value(Key).type() == QVariant::StringList) Value = Settings->value(Key).toStringList().join(",");
        else Value = Settings->value(Key).toString();
        TableItem->setText(Value);
        TableItem->setFlags(TableItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidgetCoreSettings->setItem(i, 1, TableItem);
        i++;
    }
    //
    i=0;
    ui->tableWidgetObsSettings->setRowCount(0);
    ui->tableWidgetObsSettings->setColumnCount(2);
    ui->tableWidgetObsSettings->setColumnWidth(0,280);
    ui->tableWidgetObsSettings->setColumnWidth(1,170);
    //
    foreach (const QString &Key, obsSettings->allKeys()){
        ui->tableWidgetObsSettings->insertRow(i);
        TableItem = new QTableWidgetItem;
        TableItem->setText(Key);
        TableItem->setFlags(TableItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidgetObsSettings->setItem(i, 0, TableItem);
        TableItem = new QTableWidgetItem;
        if (obsSettings->value(Key).type() == QVariant::StringList) Value = obsSettings->value(Key).toStringList().join(",");
        else Value = obsSettings->value(Key).toString();
        TableItem->setText(Value);
        TableItem->setFlags(TableItem->flags() & ~Qt::ItemIsEditable);
        ui->tableWidgetObsSettings->setItem(i, 1, TableItem);
        i++;
    }
    //
}
//

void MainWindow::on_pushButtonSettings_clicked()
{
    QString SettingsFileName = QFileDialog::getOpenFileName(this, "Select settings file for the observations...", "./", "*.ini");
    ui->lineEditSettings->setText(SettingsFileName);
    delete obsSettings;
    obsSettings = new QSettings(SettingsFileName, QSettings::IniFormat);
    showSettings();
}

void MainWindow::on_pushButtonAutoSave_clicked()
{
    QString AutoSaveDir = QFileDialog::getExistingDirectory(this, "Select auto-save directory for the observations...", "./");
    std::string Temp = AutoSaveDir.toStdString();
    if (Temp.back() == '/') AutoSaveDir.chop(1);
    ui->lineEditAutoSave->setText(AutoSaveDir);
}

void MainWindow::on_lineEditComment_returnPressed()
{
    addLog("[COMMENT] " + ui->lineEditComment->text());
    ui->lineEditComment->clear();
}

void MainWindow::on_pushButtonReloadObsSettings_clicked()
{
    QString SettingsFileName = ui->lineEditSettings->text();
    delete obsSettings;
    obsSettings = new QSettings(SettingsFileName, QSettings::IniFormat);
    showSettings();
    addLog("Observation settings reloaded from " + SettingsFileName);
}

void MainWindow::on_pushButtonReloadCoreSettings_clicked()
{
    QString SettingsFileName = "./coreSettings.ini";
    delete Settings;
    Settings = new QSettings(SettingsFileName, QSettings::IniFormat);
    showSettings();
    addLog("Core settings reloaded from " + SettingsFileName);
}

// FilterMatrix

void MainWindow::on_pushButtonOpenFMS_clicked(bool checked)
{
    if(checked) {
        FilterMatrix = new TwoStages();
        connect(FilterMatrix, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        FilterMatrix->initTwoStages("FilterMatrix");
        if (FilterMatrix->Error) {
            ui->pushButtonOpenFMS->setChecked(false);
        }
        else {
            ui->pushButtonOpenFMS->setText("Close Filter Matrix Stages Controls");
            ui->pushButtonResetFMS->setEnabled(true);
            ui->lineEditCommandFMS->setEnabled(true);
            ui->spinBoxFilterPosition->setEnabled(true);
            ui->doubleSpinBoxFMSXmm->setEnabled(true);
            ui->doubleSpinBoxFMSYmm->setEnabled(true);
        }
    }
    else {
        delete FilterMatrix;
        ui->pushButtonOpenFMS->setText("Open Filter Matrix Stages Controls");
        ui->pushButtonResetFMS->setEnabled(false);
        ui->lineEditCommandFMS->setEnabled(false);
        ui->spinBoxFilterPosition->setEnabled(false);
        ui->doubleSpinBoxFMSXmm->setEnabled(false);
        ui->doubleSpinBoxFMSYmm->setEnabled(false);
    }
}

void MainWindow::on_pushButtonResetFMS_clicked()
{
    addLog("Doing calibration/home run for Filter Matrix, please wait...");
    FilterMatrix->calibrateTwoStages();
    addLog("Filter Matrix calibration finished.");
}

void MainWindow::on_lineEditCommandFMS_returnPressed()
{
    FilterMatrix->Command = ui->lineEditCommandFMS->text().toStdString();
    FilterMatrix->sendCommand();
}

void MainWindow::on_spinBoxFilterPosition_valueChanged(int arg1)
{
    addLog("Selecting pre-filter: " + ui->spinBoxFilterPosition->text());
    FilterMatrix->iPreFilter = arg1;
    FilterMatrix->selectPreFilter();
}

void MainWindow::on_doubleSpinBoxFMSXmm_valueChanged(double arg1)
{
    FilterMatrix->Position2 = arg1;
    FilterMatrix->moveStage2();
}

void MainWindow::on_doubleSpinBoxFMSYmm_valueChanged(double arg1)
{
    FilterMatrix->Position1 = arg1;
    FilterMatrix->moveStage1();
}

// Etalon Stages (ETS)

void MainWindow::on_pushButtonOpenETS_clicked(bool checked)
{
    if(checked) {
        ETStages = new TwoStages();
        connect(ETStages, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        ETStages->initTwoStages("EtalonStages");
        if (ETStages->Error) {
            ui->pushButtonOpenETS->setChecked(false);
        }
        else {
            ui->pushButtonOpenETS->setText("Close Etalon Stages Controls");
            ui->pushButtonResetETS->setEnabled(true);
            ui->lineEditCommandETS->setEnabled(true);
            ui->pushButtonRemoveET1->setEnabled(true);
            ui->pushButtonRemoveET2->setEnabled(true);
            ui->doubleSpinBoxETS1mm->setEnabled(true);
            ui->doubleSpinBoxETS2mm->setEnabled(true);
        }
    }
    else {
        delete ETStages;
        ui->pushButtonOpenETS->setText("Open Etalon Stages Controls");
        ui->pushButtonResetETS->setEnabled(false);
        ui->lineEditCommandETS->setEnabled(false);
        ui->pushButtonRemoveET1->setEnabled(false);
        ui->pushButtonRemoveET2->setEnabled(false);
        ui->doubleSpinBoxETS1mm->setEnabled(false);
        ui->doubleSpinBoxETS2mm->setEnabled(false);
    }
}

void MainWindow::on_pushButtonResetETS_clicked()
{
    addLog("Doing calibration/home run for the Etalon Stages, please wait...");
    ETStages->calibrateTwoStages();
    addLog("Etalon Stages calibration finished.");
}

void MainWindow::on_lineEditCommandETS_returnPressed()
{
    ETStages->Command = ui->lineEditCommandETS->text().toStdString();
    ETStages->sendCommand();
}

void MainWindow::on_pushButtonRemoveET1_clicked(bool checked)
{
    if (checked) {
        addLog("Removing etalon-1 from the optical path...");
        ETStages->Position1 = ETStages->ZeroPosition1;
        ETStages->moveStage1();
        ui->pushButtonRemoveET1->setText("Insert ET50");
    }
    else {
        addLog("Inserting etalon-1 into the optical path...");
        ETStages->Position1 = ETStages->DefaultPosition1;
        ETStages->moveStage1();
        ui->pushButtonRemoveET1->setText("Remove ET50");
    }
}

void MainWindow::on_pushButtonRemoveET2_clicked(bool checked)
{
    if (checked) {
        addLog("Removing etalon-2 from the optical path...");
        ETStages->Position2 = ETStages->ZeroPosition2;
        ETStages->moveStage2();
        ui->pushButtonRemoveET2->setText("Insert ET70");
    }
    else {
        addLog("Inserting etalon-2 into the optical path...");
        ETStages->Position2 = ETStages->DefaultPosition2;
        ETStages->moveStage2();
        ui->pushButtonRemoveET2->setText("Remove ET70");
    }
}

void MainWindow::on_doubleSpinBoxETS1mm_valueChanged(double arg1)
{
    ETStages->Position1 = arg1;
    ETStages->moveStage1();
}

void MainWindow::on_doubleSpinBoxETS2mm_valueChanged(double arg1)
{
    ETStages->Position2 = arg1;
    ETStages->moveStage2();
}

// PolarimeterStages

void MainWindow::on_pushButtonOpenPLS_clicked(bool checked)
{
    if(checked) {
        PolarimeterStages = new TwoStages();
        connect(PolarimeterStages, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        PolarimeterStages->initTwoStages("PolarimeterStages");
        if (PolarimeterStages->Error) {
            ui->pushButtonOpenPLS->setChecked(false);
        }
        else{
            ui->pushButtonOpenPLS->setText("Close Polarimeter Stages Controls");
            ui->pushButtonResetPLS->setEnabled(true);
            ui->lineEditCommandPLS->setEnabled(true);
            ui->pushButtonRemoveAnalyzer->setEnabled(true);
            ui->doubleSpinBoxFSmm->setEnabled(true);
            ui->doubleSpinBoxANSmm->setEnabled(true);
        }
    }
    else {
        delete PolarimeterStages;
        ui->pushButtonOpenPLS->setText("Open Polarimeter Stages Controls");
        ui->pushButtonResetPLS->setEnabled(false);
        ui->lineEditCommandPLS->setEnabled(false);
        ui->pushButtonRemoveAnalyzer->setEnabled(false);
        ui->doubleSpinBoxFSmm->setEnabled(false);
        ui->doubleSpinBoxANSmm->setEnabled(false);
    }
}

void MainWindow::on_pushButtonResetPLS_clicked()
{
    addLog("Doing calibration/home run for the focus and analyzer stages, please wait...");
    PolarimeterStages->calibrateTwoStages();
    addLog("Polarimeter stages calibration finished.");
}

void MainWindow::on_lineEditCommandPLS_returnPressed()
{
    PolarimeterStages->Command = ui->lineEditCommandPLS->text().toStdString();
    PolarimeterStages->sendCommand();
}

void MainWindow::on_pushButtonRemoveAnalyzer_clicked(bool checked)
{
    if (checked) {
        addLog("Removing analyzer from the optical path...");
        PolarimeterStages->Position2 = 0.0;
        PolarimeterStages->moveStage2();
        ui->pushButtonRemoveAnalyzer->setText("Insert Analyzer");
    }
    else {
        addLog("Inserting analyzer into the optical path...");
        PolarimeterStages->Position2 = PolarimeterStages->DefaultPosition2;
        PolarimeterStages->moveStage2();
        ui->pushButtonRemoveAnalyzer->setText("Remove Analyzer");
    }
}

void MainWindow::on_doubleSpinBoxFSmm_valueChanged(double arg1)
{
    PolarimeterStages->Position1 = arg1 - PolarimeterStages->ZeroPosition1;
    PolarimeterStages->moveStage1();
}

void MainWindow::on_doubleSpinBoxANSmm_valueChanged(double arg1)
{
    PolarimeterStages->Position2 = arg1 - PolarimeterStages->ZeroPosition2;
    PolarimeterStages->moveStage2();
}

// ET1

void MainWindow::on_pushButtonOpenET1_clicked(bool checked)
{
    if(checked) {
        ET50 = new Etalon();
        connect(ET50, SIGNAL(addLog(QString)), this, SLOT(addLog(QString)));
        ET50->initEtalon("Etalon_1");
        if (ET50->Error) {
            ui->pushButtonOpenET1->setChecked(false);
        }
        else {
            ui->pushButtonOpenET1->setText("Close ET50 Controls");
            ui->pushButtonResetET1->setEnabled(true);
            ui->lineEditCommandET1->setEnabled(true);
            ui->spinBoxET1Counts->setEnabled(true);
        }
    }
    else {
        delete ET50;
        ui->pushButtonOpenET1->setText("Open ET50 Controls");
        ui->pushButtonResetET1->setEnabled(false);
        ui->lineEditCommandET1->setEnabled(false);
        ui->spinBoxET1Counts->setEnabled(false);
    }
}

void MainWindow::on_pushButtonResetET1_clicked()
{
    addLog("Resetting " + QString::fromStdString(ET50->Label));
    ET50->resetEtalon();
    Sleep(LDELAY);
    ET50->resetXYParallelism();
    Sleep(MDELAY);
}

void MainWindow::on_lineEditCommandET1_returnPressed()
{
    ET50->Command = ui->lineEditCommandET1->text().toStdString();
    ET50->sendCommand();
}

void MainWindow::on_spinBoxET1Counts_valueChanged(int arg1)
{
    ET50->ZCounts = arg1;
    ET50->tuneWavelength();
}

// ET2

void MainWindow::on_pushButtonOpenET2_clicked(bool checked)
{
    if(checked) {
        ET70 = new Etalon();
        connect(ET70, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        ET70->initEtalon("Etalon_2");
        if (ET70->Error) {
            ui->pushButtonOpenET2->setChecked(false);
        }
        else {
            ui->pushButtonOpenET2->setText("Close ET70 Controls");
            ui->pushButtonResetET2->setEnabled(true);
            ui->lineEditCommandET2->setEnabled(true);
            ui->spinBoxET2Counts->setEnabled(true);
        }
    }
    else {
        delete ET70;
        ui->pushButtonOpenET2->setText("Open ET70 Controls");
        ui->pushButtonResetET2->setEnabled(false);
        ui->lineEditCommandET2->setEnabled(false);
        ui->spinBoxET2Counts->setEnabled(false);
    }
}

void MainWindow::on_pushButtonResetET2_clicked()
{
    addLog("Resetting " + QString::fromStdString(ET70->Label));
    ET70->resetEtalon();
    Sleep(LDELAY);
    ET70->resetXYParallelism();
    Sleep(MDELAY);
}

void MainWindow::on_lineEditCommandET2_returnPressed()
{
    ET70->Command = ui->lineEditCommandET2->text().toStdString();
    ET70->sendCommand();
}

void MainWindow::on_spinBoxET2Counts_valueChanged(int arg1)
{
    ET70->ZCounts = arg1;
    ET70->tuneWavelength();
}

// CWP mount

void MainWindow::on_pushButtonOpenCWP_clicked(bool checked)
{
    if(checked) {
        CWPMount = new RotMount();
        connect(CWPMount, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        CWPMount->initDevice("CWPMount");
        if (CWPMount->Error) {
            ui->pushButtonOpenCWP->setChecked(false);
        }
        else {
            ui->pushButtonOpenCWP->setText("Close Cal-Polarizer Mount Controls");
            ui->pushButtonHomeCWP->setEnabled(true);
            ui->doubleSpinBoxCWPdeg->setEnabled(true);
        }
    }
    else {
        delete CWPMount;
        ui->pushButtonOpenCWP->setText("Open Cal-Polarizer Mount Controls");
        ui->pushButtonHomeCWP->setEnabled(false);
        ui->doubleSpinBoxCWPdeg->setEnabled(false);
    }
}

void MainWindow::on_pushButtonHomeCWP_clicked()
{
    CWPMount->moveHome();
}

void MainWindow::on_doubleSpinBoxCWPdeg_editingFinished()
{
    CWPMount->Position = ui->doubleSpinBoxCWPdeg->value();
    CWPMount->movePosition();
}

// LCVR

void MainWindow::on_pushButtonOpenLCVR_clicked(bool checked)
{
    if(checked) {
        LCVRPolarimeter = new Polarimeter();
        connect(LCVRPolarimeter, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        if (LCVRPolarimeter->Error) {
            ui->pushButtonOpenLCVR->setChecked(false);
        }
        else {
            ui->pushButtonOpenLCVR->setText("Close LCVR Controls");
            ui->pushButtonStartModulation->setEnabled(true);
            ui->lineEditCommandLCVR->setEnabled(true);
            ui->lineEditVoltagesLCVR1->setEnabled(true);
            ui->lineEditVoltagesLCVR2->setEnabled(true);
            ui->lineEditDurationLCVR->setEnabled(true);
            ui->spinBoxSyncLCVR->setEnabled(true);
            ui->spinBoxLCVR1mV->setEnabled(true);
            ui->spinBoxLCVR2mV->setEnabled(true);
        }
    }
    else {
        delete LCVRPolarimeter;
        ui->pushButtonOpenLCVR->setText("Open LCVR Controls");
        ui->pushButtonStartModulation->setEnabled(false);
        ui->lineEditCommandLCVR->setEnabled(false);
        ui->lineEditVoltagesLCVR1->setEnabled(false);
        ui->lineEditVoltagesLCVR2->setEnabled(false);
        ui->lineEditDurationLCVR->setEnabled(false);
        ui->spinBoxSyncLCVR->setEnabled(false);
        ui->spinBoxLCVR1mV->setEnabled(false);
        ui->spinBoxLCVR2mV->setEnabled(false);
    }
}

void MainWindow::on_lineEditCommandLCVR_returnPressed()
{
    LCVRPolarimeter->Command = ui->lineEditCommandLCVR->text().toStdString();
    LCVRPolarimeter->sendCommand();
}

void MainWindow::on_spinBoxLCVR1mV_valueChanged(int arg1)
{
    LCVRPolarimeter->LCVR1Voltage = arg1;
    LCVRPolarimeter->setVoltages();
}

void MainWindow::on_spinBoxLCVR2mV_valueChanged(int arg1)
{
    LCVRPolarimeter->LCVR2Voltage = arg1;
    LCVRPolarimeter->setVoltages();
}

void MainWindow::on_pushButtonStartModulation_clicked(bool checked)
{
    if (checked) {
        LCVRPolarimeter->startModulation();
        ui->pushButtonStartModulation->setText("Stop Modulation");
        ui->pushButtonOpenLCVR->setEnabled(false);
    }
    else {
        LCVRPolarimeter->stopModulation();
        ui->pushButtonStartModulation->setText("Start Modulation");
        ui->pushButtonOpenLCVR->setEnabled(true);
    }
}

// VTTControls

void MainWindow::on_pushButtonOpenVTT_clicked(bool checked)
{
    if(checked) {
        VTTControls = new VTT();
        connect(VTTControls, SIGNAL(addLog(QString)), this, SLOT(addLog(QString)));
        VTTControls->initVTT("VTTControls");
        if (VTTControls->Error) {
            ui->pushButtonOpenVTT->setChecked(false);
        }
        else {
            ui->pushButtonOpenVTT->setText("Close VTT Controls");
            ui->lineEditCommandVTT->setEnabled(true);
            ui->pushButtonInsertICU->setEnabled(true);
            ui->doubleSpinBoxICUPdeg->setEnabled(true);
            ui->doubleSpinBoxICURdeg->setEnabled(true);
        }
    }
    else {
        delete VTTControls;
        ui->lineEditCommandVTT->setEnabled(false);
        ui->pushButtonInsertICU->setEnabled(false);
        ui->doubleSpinBoxICUPdeg->setEnabled(false);
        ui->doubleSpinBoxICURdeg->setEnabled(false);
        ui->pushButtonOpenVTT->setText("Open VTT Controls");
    }
}

void MainWindow::on_lineEditCommandVTT_returnPressed()
{
    VTTControls->Command = ui->lineEditCommandVTT->text().toStdString();
    VTTControls->sendCommand();
}

void MainWindow::on_pushButtonInsertICU_clicked(bool checked)
{
    if (checked) {
        addLog("Inserting VTT-ICU into the optical path...");
        VTTControls->insertICU();
        ui->pushButtonInsertICU->setText("Remove ICU");
    }
    else {
        addLog("Removing VTT-ICU from the optical path...");
        VTTControls->removeICU();
        ui->pushButtonInsertICU->setText("Insert ICU");
    }
}

void MainWindow::on_doubleSpinBoxICUPdeg_editingFinished()
{
    double arg1 = ui->doubleSpinBoxICUPdeg->value();
    VTTControls->PolarizerAngle = arg1;
    VTTControls->rotateICUPolarizer();
}


void MainWindow::on_doubleSpinBoxICURdeg_editingFinished()
{
    double arg1 = ui->doubleSpinBoxICURdeg->value();
    VTTControls->RetarderAngle = arg1;
    VTTControls->rotateICURetarder();
}

void MainWindow::on_pushButtonHomeICU_clicked()
{
}


// VTTServer

void MainWindow::on_pushButtonOpenVTTServer_clicked(bool checked)
{
    if(checked) {
        VTTServer = new VTTNet();
        connect(VTTServer, SIGNAL(addLog(QString)), this, SLOT(addLog(QString)));
        VTTServer->initVTTNet("VTTServer");
        if (VTTServer->Error) {
            ui->pushButtonOpenVTTServer->setChecked(false);
        }
        else {
            ui->pushButtonOpenVTTServer->setText("Close VTTServer Controls");
            ui->lineEditCommandVTTServer->setEnabled(true);
            ui->comboBoxVTTStopWheel->setEnabled(true);
        }
    }
    else {
        delete VTTServer;
        ui->lineEditCommandVTTServer->setEnabled(false);
        ui->comboBoxVTTStopWheel->setEnabled(false);
        ui->pushButtonOpenVTT->setText("Open VTTServer Controls");
    }
}

void MainWindow::on_comboBoxVTTStopWheel_currentIndexChanged(int index)
{
    VTTServer->StopWheelPosition = index+1;
    VTTServer->positionStopWheel();
}

void MainWindow::on_lineEditCommandVTTServer_returnPressed()
{
    VTTServer->Command = ui->lineEditCommandVTTServer->text().toStdString();
    VTTServer->sendCommand();
}

// ALL controls

void MainWindow::on_comboBoxStepResolution_currentIndexChanged(int index)
{
    switch(index) {
    case 0:
        ui->doubleSpinBoxFMSXmm->setSingleStep(1);
        ui->doubleSpinBoxFMSYmm->setSingleStep(1);
        ui->doubleSpinBoxETS1mm->setSingleStep(0.5);
        ui->doubleSpinBoxETS2mm->setSingleStep(0.5);
        ui->doubleSpinBoxFSmm->setSingleStep(0.1);
        ui->doubleSpinBoxANSmm->setSingleStep(0.1);
        ui->doubleSpinBoxICUPdeg->setSingleStep(0.1);
        ui->doubleSpinBoxICURdeg->setSingleStep(0.1);
        ui->doubleSpinBoxCWPdeg->setSingleStep(0.1);
        ui->spinBoxET1Counts->setSingleStep(1);
        ui->spinBoxET2Counts->setSingleStep(1);
        ui->spinBoxLCVR1mV->setSingleStep(100);
        ui->spinBoxLCVR2mV->setSingleStep(100);
        break;
    case 1:
        ui->doubleSpinBoxFMSXmm->setSingleStep(5);
        ui->doubleSpinBoxFMSYmm->setSingleStep(5);
        ui->doubleSpinBoxETS1mm->setSingleStep(2);
        ui->doubleSpinBoxETS2mm->setSingleStep(2);
        ui->doubleSpinBoxFSmm->setSingleStep(0.5);
        ui->doubleSpinBoxANSmm->setSingleStep(0.5);
        ui->doubleSpinBoxICUPdeg->setSingleStep(0.5);
        ui->doubleSpinBoxICURdeg->setSingleStep(0.5);
        ui->doubleSpinBoxCWPdeg->setSingleStep(0.5);
        ui->spinBoxET1Counts->setSingleStep(5);
        ui->spinBoxET2Counts->setSingleStep(5);
        ui->spinBoxLCVR1mV->setSingleStep(500);
        ui->spinBoxLCVR2mV->setSingleStep(500);
        break;
    case 2:
        ui->doubleSpinBoxFMSXmm->setSingleStep(20);
        ui->doubleSpinBoxFMSYmm->setSingleStep(20);
        ui->doubleSpinBoxETS1mm->setSingleStep(10);
        ui->doubleSpinBoxETS2mm->setSingleStep(10);
        ui->doubleSpinBoxFSmm->setSingleStep(2);
        ui->doubleSpinBoxANSmm->setSingleStep(2);
        ui->doubleSpinBoxICUPdeg->setSingleStep(2);
        ui->doubleSpinBoxICURdeg->setSingleStep(2);
        ui->doubleSpinBoxCWPdeg->setSingleStep(2);
        ui->spinBoxET1Counts->setSingleStep(20);
        ui->spinBoxET2Counts->setSingleStep(20);
        ui->spinBoxLCVR1mV->setSingleStep(2000);
        ui->spinBoxLCVR2mV->setSingleStep(2000);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButtonGetValues_clicked()
{
    if (ui->pushButtonOpenFMS->isChecked()) {
        // X, axis - 2
        FilterMatrix->Command = "2 np";
        FilterMatrix->sendCommand();
        Sleep(SDELAY);
        ui->lineEditFMSX->setText(QString::fromStdString(FilterMatrix->Response));
        // Y, axis - 1
        FilterMatrix->Command = "1 np";
        FilterMatrix->sendCommand();
        Sleep(SDELAY);
        ui->lineEditFMSY->setText(QString::fromStdString(FilterMatrix->Response));
    }
    if (ui->pushButtonOpenETS->isChecked()) {
        // ET1 stage, axis - 1
        ETStages->Command = "1 np";
        ETStages->sendCommand();
        Sleep(SDELAY);
        ui->lineEditETS1mm->setText(QString::fromStdString(ETStages->Response));
        // ET2 stage, axis - 2
        ETStages->Command = "2 np";
        ETStages->sendCommand();
        Sleep(SDELAY);
        ui->lineEditETS2mm->setText(QString::fromStdString(ETStages->Response));
    }
    if (ui->pushButtonOpenET1->isChecked()) {
        // ET1
        ET50->getCurrentStatus();
        Sleep(MDELAY);
        ui->lineEditET1Counts->setText(QString::fromStdString(ET50->Response));
    }
    if (ui->pushButtonOpenET2->isChecked()) {
        // ET2
        ET70->getCurrentStatus();
        Sleep(MDELAY);
        ui->lineEditET2Counts->setText(QString::fromStdString(ET70->Response));
    }
    if (ui->pushButtonOpenPLS->isChecked()) {
        // Focus stage, axis - 1
        PolarimeterStages->Command = "1 np";
        PolarimeterStages->sendCommand();
        Sleep(SDELAY);
        ui->lineEditFSmm->setText(QString::fromStdString(PolarimeterStages->Response));
        // Analyzer stage, axis - 2
        PolarimeterStages->Command = "2 np";
        PolarimeterStages->sendCommand();
        Sleep(SDELAY);
        ui->lineEditFSmm->setText(QString::fromStdString(PolarimeterStages->Response));
    }
    if (ui->pushButtonOpenCWP->isChecked()) {
        ui->lineEditCWPdeg->setText(QString::number(CWPMount->Position));
    }
}

// Acquisition

void MainWindow::on_toolBoxAcquisition_currentChanged(int index)
{
    if (index>CHR_MODE_ET1_MATCH) {
        ui->comboBoxBinning->setCurrentText("1");
        ui->comboBoxROI->setCurrentText("1280");
    }
    else {
        ui->comboBoxBinning->setCurrentText("1");
        ui->comboBoxROI->setCurrentText("512");
    }
}

void MainWindow::saveSettings()
{
    QString TempSettingsName = QString::fromStdString(Observation->AutoSaveSubDir) + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz") + "_settings.ini";
    QSettings *TempSettings = new QSettings(TempSettingsName, QSettings::IniFormat);
    //
    foreach (const QString &Key, Settings->allKeys()){
        TempSettings->setValue(Key, Settings->value(Key));
    }
    TempSettings->sync();
    //
    foreach (const QString &Key, obsSettings->allKeys()){
        TempSettings->setValue(Key, obsSettings->value(Key));
    }
    TempSettings->sync();
    //
    TempSettings->setValue("Common/AutoSaveDir", QString::fromStdString(Observation->AutoSaveDir));
    TempSettings->setValue("Common/ArcsecX0", ui->doubleSpinBoxXArcsec->value());
    TempSettings->setValue("Common/ArcsecY0", ui->doubleSpinBoxYArcsec->value());
    TempSettings->setValue("Common/AtmR0", ui->doubleSpinBoxR0->value());
    TempSettings->setValue("Common/PAngle", ui->doubleSpinBoxPAngle->value());
    TempSettings->setValue("Common/Observers", ui->lineEditObservers->text());
    TempSettings->setValue("Common/Investigators", ui->lineEditPlanners->text());
    TempSettings->setValue("Common/DataTags", ui->lineEditDataTags->text());
    TempSettings->sync();
    //
    if (ui->lineEditOtherSettings->text().toStdString() != "") {
        QStringList OtherSettings, KeyValues;
        QString Key, Value;
        OtherSettings = ui->lineEditOtherSettings->text().split(",");
        foreach (const QString &OtherSetting, OtherSettings) {
            KeyValues = OtherSetting.split("=");
            Key = KeyValues[0];
            Value = KeyValues[1];
            TempSettings->setValue("Common/"+Key, Value);
        }
    }
    addLog("Settings saved as: " + TempSettingsName);
}

void MainWindow::on_pushButtonAcquisition_clicked(bool checked)
{
    int Mode = ui->toolBoxAcquisition->currentIndex();
    if (Mode >= OBS_MODE_TARG) {
        if (checked) {
            Observation = new Acquisition();
            Observation->Mode = Mode;
            doObservation();
        }
        else {
            Observation->Interrupt();
            ui->pushButtonAcquisition->setChecked(true);
        }
    }
    else {
        if (checked) {
            Characterization = new Acquisition();
            Characterization->Mode = Mode;
            doCharacterization();
        }
        else {
            Characterization->Interrupt();
            ui->pushButtonAcquisition->setChecked(true);
        }
    }
    ui->pushButtonAcquisition->setText("Stop Acquisition");
}

void MainWindow::doObservation()
{
    ThreadAcquisition = new QThread();
    Observation->moveToThread(ThreadAcquisition);
    Observation->AutoSaveDir = ui->lineEditAutoSave->text().toStdString();
    switch (Observation->Mode) {
    case OBS_MODE_SCIE:
        Observation->NCycles = ui->spinBoxObsScienceCyc->value();
        // Sub-dir for science data
        Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/Science";
        if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
        }
        //
        connect(ThreadAcquisition, SIGNAL(started()),
                Observation, SLOT(getScienceData()));
        break;
    case OBS_MODE_FLAT:
        Observation->NCycles = ui->spinBoxObsFlatsCyc->value();
        // Sub-dir for flats data
        Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/Flats";
        if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
        }
        //
        connect(ThreadAcquisition, SIGNAL(started()),
                Observation, SLOT(getFlatsData()));
        break;
    case OBS_MODE_PCAL:
        Observation->NICUPolCalib = ui->spinBoxObsPCalPol->value();
        Observation->NICURetCalib = ui->spinBoxObsPCalRet->value();
        Observation->NCycles = Observation->NICUPolCalib*Observation->NICURetCalib;
        Observation->AutoSaveDir = ui->lineEditAutoSave->text().toStdString();
        // Sub-dir for science data
        Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/PCalibration";
        if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
        }
        //
        connect(ThreadAcquisition, SIGNAL(started()),
                Observation, SLOT(getCalibrationData()));
        break;
    case OBS_MODE_DARK:
        Observation->NCycles = ui->spinBoxObsDarksFrames->value();
        // Sub-dir for darks data
        Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/Darks";
        if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
        }
        //
        connect(ThreadAcquisition, SIGNAL(started()),
                Observation, SLOT(getDarksData()));
        break;
    case OBS_MODE_TARG:
        Observation->NCycles = ui->spinBoxObsTargetFrames->value();
        // Sub-dir for darks data
        Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/Targetplate";
        if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
        }
        //
        connect(ThreadAcquisition, SIGNAL(started()),
                Observation, SLOT(getTargetplateData()));
        break;
    case OBS_MODE_PINH:
        Observation->NCycles = ui->spinBoxObsPinholeFrames->value();
        // Sub-dir for darks data
        Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/Pinhole";
        if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
        }
        //
        connect(ThreadAcquisition, SIGNAL(started()),
                Observation, SLOT(getPinholeData()));
        break;
    default:
        if (ThreadAcquisition->isRunning()) ThreadAcquisition->exit();
        break;
    }
    // Sub-dir for the day
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/yyyyMMdd").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Sub-dir for the time
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/hhmm").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()) {
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Log file name
    std::string TempName = Observation->AutoSaveSubDir + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz").toStdString() + "_log.txt";
    DevLog = std::ofstream(TempName);
    addLog("Observation log will be saved as: " + QString::fromStdString(TempName));
    // Settings file
    saveSettings();
    // Connect observation signals
    connect(this, SIGNAL(stopAcquisition()),
            Observation, SLOT(Interrupt()));
    connect(Observation, SIGNAL(Finished()),
            ThreadAcquisition, SLOT(quit()));
    connect(ThreadAcquisition, SIGNAL(finished()),
            ThreadAcquisition, SLOT(deleteLater()));
    connect(ThreadAcquisition, SIGNAL(finished()),
            this, SLOT(finishAcquisition()));
    connect(Observation, SIGNAL(addLog(QString)),
            this, SLOT(addLog(QString)));
    connect(Observation, SIGNAL(updateProgress(int)),
            ui->progressBarStatus, SLOT(setValue(int)));
    connect(Observation, SIGNAL(updateOProgress(int)),
            ui->progressBarOStatus, SLOT(setValue(int)));
    // Start Acquisition
    prepareAcquisition();
    prepareDisplay(1, 1, 1);
    ThreadAcquisition->start();
}

void MainWindow::doCharacterization()
{
    ThreadAcquisition = new QThread();
    Characterization->moveToThread(ThreadAcquisition);
    Characterization->AutoSaveDir = ui->lineEditAutoSave->text().toStdString();
    Characterization->AutoSaveSubDir = Characterization->AutoSaveDir + "/Characterization";
    if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
        QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
    }
    prepareAcquisition();
    switch (Characterization->Mode) {
    case CHR_MODE_ET1_MATCH:
        Characterization->ET1Start = ui->spinBoxCharET1MatchStart->value();
        Characterization->ET1Step = ui->spinBoxCharET1MatchStep->value();
        Characterization->ET1Stop = ui->spinBoxCharET1MatchStop->value();
        Characterization->iPreFilter = ui->spinBoxCharET1MatchPF->value();
        //
        Characterization->AutoSaveSubDir += "/ET50Match";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(0, 1, 0);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(matchET1Passband()));
        break;
    case CHR_MODE_ET2_MATCH:
        Characterization->ET1Zero = ui->spinBoxCharET2MatchET1->value();
        Characterization->ET2Start = ui->spinBoxCharET2MatchStart->value();
        Characterization->ET2Step = ui->spinBoxCharET2MatchStep->value();
        Characterization->ET2Stop = ui->spinBoxCharET2MatchStop->value();
        Characterization->iPreFilter = ui->spinBoxCharET1MatchPF->value();
        //
        Characterization->AutoSaveSubDir += "/ET70Match";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(0, 1, 0);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(matchET2Passband()));
        break;
    case CHR_MODE_LINE_PROF:
        Characterization->ET1Zero = ui->spinBoxCharETLineET1->value();
        Characterization->ET2Zero = ui->spinBoxCharETLineET2->value();
        Characterization->Wavelength = ui->doubleSpinBoxCharETLineCenter->value();
        Characterization->WaveRange = ui->doubleSpinBoxCharETLineRange->value();
        Characterization->WaveStep = ui->doubleSpinBoxCharETLineStep->value();
        Characterization->iPreFilter = ui->spinBoxCharETLinePF->value();
        //
        Characterization->AutoSaveSubDir += "/ETLineMatch";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(0, 1, 0);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(matchETPassbandsLine()));
        break;
    case CHR_MODE_CAM_FOCUS:
        Characterization->FocusStart = ui->doubleSpinBoxCharFocusStart->value();
        Characterization->FocusStep = ui->doubleSpinBoxCharFocusStep->value();
        Characterization->FocusStop = ui->doubleSpinBoxCharFocusStop->value();
        Characterization->iPreFilter = ui->spinBoxCharFocusPF->value();
        Characterization->ET1Zero = ui->spinBoxCharFocusET1->value();
        Characterization->ET2Zero = ui->spinBoxCharFocusET2->value();
        //
        Characterization->AutoSaveSubDir += "/FocusTest";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(1, 1, 1);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(examineBestFocus()));
        break;
    case CHR_MODE_LCVR1_PROF:
        Characterization->LCVR1Start = ui->spinBoxCharLCVR1Start->value();
        Characterization->LCVR1Step = ui->spinBoxCharLCVR1Step  ->value();
        Characterization->LCVR1Stop = ui->spinBoxCharLCVR1Stop->value();
        Characterization->iPreFilter = ui->spinBoxCharLCVR1PF->value();
        Characterization->BiasCounts = ui->spinBoxCharLCVR1Bias->value();
        Characterization->NPolarizer = ui->comboBoxCharLCVR1PolPos->currentText().toInt();
        //
        Characterization->AutoSaveSubDir += "/LCVR1";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(0, 1, 1);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(doLCVR1Characterization()));
        break;
    case CHR_MODE_LCVR2_PROF:
        Characterization->LCVR2Start = ui->spinBoxCharLCVR2Start->value();
        Characterization->LCVR2Step = ui->spinBoxCharLCVR2Step  ->value();
        Characterization->LCVR2Stop = ui->spinBoxCharLCVR2Stop->value();
        Characterization->iPreFilter = ui->spinBoxCharLCVR2PF->value();
        Characterization->BiasCounts = ui->spinBoxCharLCVR2Bias->value();
        Characterization->NPolarizer = ui->comboBoxCharLCVR2PolPos->currentText().toInt();
        //
        Characterization->AutoSaveSubDir += "/LCVR2";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(0, 1, 1);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(doLCVR2Characterization()));
        break;
    case CHR_MODE_ET1_PROF:
        Characterization->ET1Start = ui->spinBoxCharET1ProfStart->value();
        Characterization->ET1Step = ui->spinBoxCharET1ProfStep->value();
        Characterization->ET1Stop = ui->spinBoxCharET1ProfStop->value();
        //
        Characterization->AutoSaveSubDir += "/ET50Prof";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(0, 1, 0);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(doET1Profiling()));
        break;
    case CHR_MODE_ET2_PROF:
        Characterization->ET2Start = ui->spinBoxCharET2ProfStart->value();
        Characterization->ET2Step = ui->spinBoxCharET2ProfStep->value();
        Characterization->ET2Stop = ui->spinBoxCharET2ProfStop->value();
        //
        Characterization->AutoSaveSubDir += "/ET70Prof";
        if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
            QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
            addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
        }
        //
        prepareDisplay(0, 1, 0);
        connect(ThreadAcquisition, SIGNAL(started()),
                Characterization, SLOT(doET2Profiling()));
        break;
    default:
        if (ThreadAcquisition->isRunning()) ThreadAcquisition->exit();
        break;
    }
    // Sub-dir for the day
    Characterization->AutoSaveSubDir += QDateTime::currentDateTime().toString("/yyyyMMdd").toStdString();
    if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
        QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
    }
    // Sub-dir for the time
    Characterization->AutoSaveSubDir += QDateTime::currentDateTime().toString("/hhmm").toStdString();
    if (!QDir(QString::fromStdString(Characterization->AutoSaveSubDir)).exists()) {
        QDir().mkdir(QString::fromStdString(Characterization->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Characterization->AutoSaveSubDir));
    }
    // Log file name
    std::string TempName = Characterization->AutoSaveSubDir + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz").toStdString() + "_log.txt";
    DevLog = std::ofstream(TempName);
    addLog("Observation log will be saved as: " + QString::fromStdString(TempName));
    // Connect signals
    connect(Characterization, SIGNAL(plotData(int)),
            this, SLOT(plotData(int)));
    connect(Characterization, SIGNAL(Finished()),
            ThreadAcquisition, SLOT(quit()));
    connect(ThreadAcquisition, SIGNAL(finished()),
            ThreadAcquisition, SLOT(deleteLater()));
    connect(ThreadAcquisition, SIGNAL(finished()),
            this, SLOT(finishAcquisition()));
    connect(Characterization, SIGNAL(addLog(QString)),
            this, SLOT(addLog(QString)));
    connect(Characterization, SIGNAL(updateProgress(int)),
            ui->progressBarStatus, SLOT(setValue(int)));
    connect(Characterization, SIGNAL(updateOProgress(int)),
            ui->progressBarOStatus, SLOT(setValue(int)));
    //
    ThreadAcquisition->start();
}

void MainWindow::prepareAcquisition()
{
    // Kill the component objects in current thread because :
    // Qt doesn't allow using TCP sockets from different threads.
    DataDetails->Observers = ui->lineEditObservers->text().toStdString();
    DataDetails->Planners = ui->lineEditPlanners->text().toStdString();
    DataDetails->DataTags = ui->lineEditDataTags->text().toStdString();
    DataDetails->OtherSettings = ui->lineEditOtherSettings->text().toStdString();
    DataDetails->XArcsec = ui->doubleSpinBoxXArcsec->value();
    DataDetails->YArcsec = ui->doubleSpinBoxYArcsec->value();
    DataDetails->PAngle = ui->doubleSpinBoxPAngle->value();
    DataDetails->AtmosR0 = ui->doubleSpinBoxR0->value();
    //
    if (ui->pushButtonOpenFMS->isChecked()) {
        ui->pushButtonOpenFMS->setChecked(false);
        on_pushButtonOpenFMS_clicked(false);
    }
    if (ui->pushButtonOpenETS->isChecked()) {
        ui->pushButtonOpenETS->setChecked(false);
        on_pushButtonOpenETS_clicked(false);
    }
    if (ui->pushButtonOpenPLS->isChecked()) {
        ui->pushButtonOpenPLS->setChecked(false);
        on_pushButtonOpenPLS_clicked(false);
    }
    if (ui->pushButtonOpenET1->isChecked()) {
        ui->pushButtonOpenET1->setChecked(false);
        on_pushButtonOpenET1_clicked(false);
    }
    if (ui->pushButtonOpenET2->isChecked()) {
        ui->pushButtonOpenET2->setChecked(false);
        on_pushButtonOpenET2_clicked(false);
    }
    if (ui->pushButtonOpenLCVR->isChecked()) {
        ui->pushButtonOpenLCVR->setChecked(false);
        on_pushButtonOpenLCVR_clicked(false);
    }
    if (ui->pushButtonOpenVTT->isChecked()) {
        ui->pushButtonOpenVTT->setChecked(false);
        on_pushButtonOpenVTT_clicked(false);
    }
    if (ui->pushButtonOpenVTTServer->isChecked()) {
        ui->pushButtonOpenVTTServer->setChecked(false);
        on_pushButtonOpenVTTServer_clicked(false);
    }
    if (ui->pushButtonLive->isChecked()) {
        ui->pushButtonLive->setChecked(false);
        on_pushButtonLive_clicked(false);
    }
    //
    if (!ui->pushButtonOpenCAM0->isChecked()) {
        ui->pushButtonOpenCAM0->setChecked(true);
        on_pushButtonOpenCAM0_clicked(true);
    }
    if (!ui->pushButtonOpenCAM1->isChecked()) {
        ui->pushButtonOpenCAM1->setChecked(true);
        on_pushButtonOpenCAM1_clicked(true);
    }
    if (!ui->pushButtonOpenCAM2->isChecked()) {
        ui->pushButtonOpenCAM2->setChecked(true);
        on_pushButtonOpenCAM2_clicked(true);
    }
    applyDetectorSettings();
    //
    DetectorBBCh->MainThread = QThread::currentThread();
    DetectorPCh1->MainThread = QThread::currentThread();
    DetectorPCh2->MainThread = QThread::currentThread();
//    DetectorBBCh->moveToThread(ThreadAcquisition);
//    DetectorPCh1->moveToThread(ThreadAcquisition);
//    DetectorPCh2->moveToThread(ThreadAcquisition);
    //
    ui->groupBoxInit->setEnabled(false);
    ui->groupBoxBrowse->setEnabled(false);
    ui->groupBoxDetector->setEnabled(false);
    ui->groupBoxFITSHeader->setEnabled(false);
    ui->toolBoxAcquisition->setEnabled(false);
}

void MainWindow::finishAcquisition()
{
    addLog("Acquisition finished");
    ui->pushButtonAcquisition->setChecked(false);
    ui->progressBarStatus->setValue(0);
    ui->progressBarOStatus->setValue(0);
//    ui->lineEditCycles->setText("0/" + QString::number(ui->spinBoxObsScienceCyc->value()));
    //
    DevLog.close();
    std::string TempName = "./Logs/HELLRIDE_" + QDateTime::currentDateTime().toString("yyyyMMmm_hhmmss").toStdString() + "_log.txt";
    DevLog = std::ofstream(TempName);
    Sleep(MDELAY);
    ui->groupBoxInit->setEnabled(true);
    ui->groupBoxBrowse->setEnabled(true);
    ui->groupBoxDetector->setEnabled(true);
    ui->groupBoxFITSHeader->setEnabled(true);
    ui->toolBoxAcquisition->setEnabled(true);
    ui->pushButtonAcquisition->setChecked(false);
    ui->pushButtonAcquisition->setText("Start Acquisition");
}

// Cameras

void MainWindow::applyDetectorSettings()
{
    DetectorBBCh->ExposureTime = ui->spinBoxExposureCAM0->value();
    DetectorBBCh->ROI = ui->comboBoxROI->currentText().toInt();
    DetectorBBCh->Binning = ui->comboBoxBinning->currentText().toInt();
    //
    DetectorPCh1->ExposureTime = ui->spinBoxExposureCAM1->value();
    DetectorPCh1->ROI = ui->comboBoxROI->currentText().toInt();
    DetectorPCh1->Binning = ui->comboBoxBinning->currentText().toInt();
    //
    DetectorPCh2->ExposureTime = ui->spinBoxExposureCAM2->value();
    DetectorPCh2->ROI = ui->comboBoxROI->currentText().toInt();
    DetectorPCh2->Binning = ui->comboBoxBinning->currentText().toInt();
}

void MainWindow::on_pushButtonLive_clicked(bool checked)
{
    DetectorBBCh->ROI = ui->comboBoxROI->currentText().toInt();
    DetectorPCh1->ROI = ui->comboBoxROI->currentText().toInt();
    DetectorPCh2->ROI = ui->comboBoxROI->currentText().toInt();
    DetectorBBCh->Binning = ui->comboBoxBinning->currentText().toInt();
    DetectorPCh1->Binning = ui->comboBoxBinning->currentText().toInt();
    DetectorPCh2->Binning = ui->comboBoxBinning->currentText().toInt();
    DetectorBBCh->Trigger = ui->comboBoxTrigger->currentIndex();
    DetectorPCh1->Trigger = ui->comboBoxTrigger->currentIndex();
    DetectorPCh2->Trigger = ui->comboBoxTrigger->currentIndex();
    if(checked){
        //
        applyDetectorSettings();
        ThreadAcquisition = new QThread;
        Live = new Acquisition();
        Live->moveToThread(ThreadAcquisition);
        Live->CAM0_LIVE_FLAG = ui->pushButtonOpenCAM0->isChecked() && ui->checkBoxLiveCAM0->isChecked();
        Live->CAM1_LIVE_FLAG = ui->pushButtonOpenCAM1->isChecked() && ui->checkBoxLiveCAM1->isChecked();
        Live->CAM2_LIVE_FLAG = ui->pushButtonOpenCAM2->isChecked() && ui->checkBoxLiveCAM2->isChecked();
        Live->LiveMode = ui->comboBoxLiveMode->currentIndex();
        if (!Live->CAM0_LIVE_FLAG && !Live->CAM1_LIVE_FLAG && !Live->CAM2_LIVE_FLAG) {
            ui->pushButtonLive->setChecked(false);
            addLog("No detector is open/selected!");
            return;
        }
        connect(ThreadAcquisition, SIGNAL(started()),
                Live, SLOT(startLive()));
        connect(Live, SIGNAL(Finished()),
                ThreadAcquisition, SLOT(quit()));
        connect(ThreadAcquisition, SIGNAL(finished()),
                ThreadAcquisition, SLOT(deleteLater()));
        connect(ThreadAcquisition, SIGNAL(finished()),
                Live, SLOT(deleteLater()));
        //
        DetectorBBCh->FileNameModeSuffix = ui->lineEditSuffixCAM0->text().toStdString();
        DetectorPCh1->FileNameModeSuffix = ui->lineEditSuffixCAM1->text().toStdString();
        DetectorPCh2->FileNameModeSuffix = ui->lineEditSuffixCAM2->text().toStdString();
        prepareDisplay(Live->CAM0_LIVE_FLAG, Live->CAM1_LIVE_FLAG, Live->CAM2_LIVE_FLAG);
        //
        ThreadAcquisition->start();
        ui->pushButtonLive->setText("Stop Live Preview");
        ui->pushButtonOpenCAM0->setEnabled(false);
        ui->pushButtonOpenCAM1->setEnabled(false);
        ui->pushButtonOpenCAM2->setEnabled(false);
    }
    else {
        Live->Interrupt();
        ui->pushButtonOpenCAM0->setEnabled(true);
        ui->pushButtonOpenCAM1->setEnabled(true);
        ui->pushButtonOpenCAM2->setEnabled(true);
        ui->pushButtonLive->setText("Start Live Preview");
    }

//    if(checked) {
//        applyDetectorSettings();
//        if (ui->pushButtonOpenCAM0->isChecked() && ui->checkBoxLiveCAM0->isChecked()) {
//            DetectorBBCh->SAVE_IMAGE_FLAG = ui->checkBoxSaveframes->isChecked();
//            //
//            QThread *LiveThreadCAM0 = new QThread;
//            DetectorBBCh->moveToThread(LiveThreadCAM0);
//            connect(LiveThreadCAM0, SIGNAL(started()),
//                    DetectorBBCh, SLOT(startLive()));
//            connect(DetectorBBCh, SIGNAL(Finished()),
//                    LiveThreadCAM0, SLOT(quit()));
//            connect(DetectorBBCh, SIGNAL(Finished()),
//                    LiveThreadCAM0, SLOT(deleteLater()));
//            //
//            imageview *DisplayCAM0 = new imageview();
//            DisplayCAM0->setWindowTitle("Broadband Channel Detector");
//            connect(DetectorBBCh, SIGNAL(displayImage(QPixmap,int,int,int)),
//                 DisplayCAM0, SLOT(displayImage(QPixmap,int,int,int)));
//            connect(DetectorBBCh, SIGNAL(Finished()),
//                    DisplayCAM0, SLOT(deleteLater()));
//            DisplayCAM0->show();
//            //
//            LiveThreadCAM0->start();
//        }
//        //
//        if (ui->pushButtonOpenCAM1->isChecked() && ui->checkBoxLiveCAM1->isChecked()) {
//            DetectorPCh1->SAVE_IMAGE_FLAG = ui->checkBoxSaveframes->isChecked();
//            //
//            QThread *LiveThreadCAM1 = new QThread;
//            DetectorPCh1->moveToThread(LiveThreadCAM1);
//            connect(LiveThreadCAM1, SIGNAL(started()),
//                    DetectorPCh1, SLOT(startLive()));
//            connect(DetectorPCh1, SIGNAL(Finished()),
//                    LiveThreadCAM1, SLOT(quit()));
//            connect(DetectorPCh1, SIGNAL(Finished()),
//                    LiveThreadCAM1, SLOT(deleteLater()));
//            //
//            imageview *DisplayCAM1 = new imageview();
//            DisplayCAM1->setWindowTitle("Polarimeter Channel-1 Detector");
//            connect(DetectorPCh1, SIGNAL(displayImage(QPixmap,int,int,int)),
//                 DisplayCAM1, SLOT(displayImage(QPixmap,int,int,int)));
//            connect(DetectorPCh1, SIGNAL(Finished()),
//                    DisplayCAM1, SLOT(deleteLater()));
//            DisplayCAM1->show();
//            //
//            LiveThreadCAM1->start();
//        }
//        //
//        if (ui->pushButtonOpenCAM2->isChecked() && ui->checkBoxLiveCAM2->isChecked()) {
//            DetectorPCh2->SAVE_IMAGE_FLAG = ui->checkBoxSaveframes->isChecked();
//            //
//            QThread *LiveThreadCAM2 = new QThread;
//            DetectorPCh2->moveToThread(LiveThreadCAM2);
//            connect(LiveThreadCAM2, SIGNAL(started()),
//                    DetectorPCh2, SLOT(startLive()));
//            connect(DetectorPCh2, SIGNAL(Finished()),
//                    LiveThreadCAM2, SLOT(quit()));
//            connect(DetectorPCh2, SIGNAL(Finished()),
//                    LiveThreadCAM2, SLOT(deleteLater()));
//            //
//            imageview *DisplayCAM2 = new imageview();
//            DisplayCAM2->setWindowTitle("Broadband Channel Detector");
//            connect(DetectorPCh2, SIGNAL(displayImage(QPixmap,int,int,int)),
//                 DisplayCAM2, SLOT(displayImage(QPixmap,int,int,int)));
//            connect(DetectorPCh2, SIGNAL(Finished()),
//                    DisplayCAM2, SLOT(deleteLater()));
//            DisplayCAM2->show();
//            //
//            LiveThreadCAM2->start();
//        }

//        ui->pushButtonLive->setText("Stop Live");
//        ui->pushButtonOpenCAM0->setEnabled(false);
//        ui->pushButtonOpenCAM1->setEnabled(false);
//        ui->pushButtonOpenCAM2->setEnabled(false);
//    }
//    else {
//    DetectorBBCh->stopAcquisition();
//    DetectorPCh1->stopAcquisition();
//    DetectorPCh2->stopAcquisition();
//    ui->pushButtonOpenCAM0->setEnabled(true);
//    ui->pushButtonOpenCAM1->setEnabled(true);
//    ui->pushButtonOpenCAM2->setEnabled(true);
//    ui->pushButtonLive->setText("Start Live");
//    }

}

void MainWindow::on_pushButtonOpenCAM0_clicked(bool checked)
{
    if(checked){
        DetectorBBCh = new Camera();
        connect(DetectorBBCh, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        DetectorBBCh->initDetector("Camera_0");
        if (DetectorBBCh->Error) {
            ui->pushButtonOpenCAM0->setChecked(false);
        }
        else {
            ui->pushButtonOpenCAM0->setText("Stop Boradband Detector");
        }
    }
    else {
        delete DetectorBBCh;
        ui->pushButtonOpenCAM0->setText("Open Boradband Detector");
    }
}

void MainWindow::on_pushButtonOpenCAM1_clicked(bool checked)
{
    if(checked){
        DetectorPCh1 = new Camera();
        connect(DetectorPCh1, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        DetectorPCh1->initDetector("Camera_1");
        if (DetectorPCh1->Error) {
            ui->pushButtonOpenCAM1->setChecked(false);
        }
        else {
            ui->pushButtonOpenCAM1->setText("Stop Polarimeter Detector-1");
        }
    }
    else {
        delete DetectorPCh1;
        ui->pushButtonOpenCAM1->setText("Open Polarimeter Detector-1");
    }
}

void MainWindow::on_pushButtonOpenCAM2_clicked(bool checked)
{
    if(checked){
        DetectorPCh2 = new Camera();
        connect(DetectorPCh2, SIGNAL(addLog(QString)),
                this, SLOT(addLog(QString)));
        DetectorPCh2->initDetector("Camera_2");
        if (DetectorPCh2->Error) {
            ui->pushButtonOpenCAM2->setChecked(false);
        }
        else {
            ui->pushButtonOpenCAM2->setText("Stop Polarimeter Detector-2");
        }
    }
    else {
        delete DetectorPCh2;
        ui->pushButtonOpenCAM2->setText("Open Polarimeter Detector-2");
    }
}

void MainWindow::on_comboBoxTrigger_currentIndexChanged(int index)
{
    DetectorBBCh->Trigger = index;
    DetectorPCh1->Trigger = index;
    DetectorPCh2->Trigger = index;
}

void MainWindow::on_comboBoxBinning_currentIndexChanged(const QString &arg1)
{
    int Binning = arg1.toInt();
    DetectorBBCh->Binning = Binning;
    DetectorPCh1->Binning = Binning;
    DetectorPCh2->Binning = Binning;
    //
    switch(Binning) {
    case 1:
        ui->comboBoxROI->clear();
        ui->comboBoxROI->addItem("2048");
        ui->comboBoxROI->addItem("1920");
        ui->comboBoxROI->addItem("1800");
        ui->comboBoxROI->addItem("1600");
        ui->comboBoxROI->addItem("1536");
        ui->comboBoxROI->addItem("1280");
        ui->comboBoxROI->addItem("1200");
        ui->comboBoxROI->addItem("1024");
        ui->comboBoxROI->addItem("800");
        ui->comboBoxROI->addItem("768");
        ui->comboBoxROI->addItem("600");
        ui->comboBoxROI->addItem("512");
        ui->comboBoxROI->addItem("384");
        ui->comboBoxROI->addItem("256");
        break;
    case 2:
        ui->comboBoxROI->clear();
        ui->comboBoxROI->addItem("1024");
        ui->comboBoxROI->addItem("960");
        ui->comboBoxROI->addItem("900");
        ui->comboBoxROI->addItem("800");
        ui->comboBoxROI->addItem("768");
        ui->comboBoxROI->addItem("640");
        ui->comboBoxROI->addItem("600");
        ui->comboBoxROI->addItem("512");
        ui->comboBoxROI->addItem("400");
        ui->comboBoxROI->addItem("384");
        ui->comboBoxROI->addItem("300");
        ui->comboBoxROI->addItem("256");
        ui->comboBoxROI->addItem("192");
        ui->comboBoxROI->addItem("128");
        break;
    case 4:
        ui->comboBoxROI->clear();
        ui->comboBoxROI->addItem("512");
        ui->comboBoxROI->addItem("480");
        ui->comboBoxROI->addItem("450");
        ui->comboBoxROI->addItem("400");
        ui->comboBoxROI->addItem("384");
        ui->comboBoxROI->addItem("320");
        ui->comboBoxROI->addItem("300");
        ui->comboBoxROI->addItem("256");
        ui->comboBoxROI->addItem("200");
        ui->comboBoxROI->addItem("192");
        ui->comboBoxROI->addItem("150");
        ui->comboBoxROI->addItem("128");
        ui->comboBoxROI->addItem("96");
        ui->comboBoxROI->addItem("64");
        break;
    default:
        break;
    }
}

void MainWindow::on_comboBoxROI_currentIndexChanged(const QString &arg1)
{
    int ROI = arg1.toInt();
    DetectorBBCh->ROI = ROI;
    DetectorPCh1->ROI = ROI;
    DetectorPCh2->ROI = ROI;
}

void MainWindow::prepareDisplay(bool CAM0, bool CAM1, bool CAM2)
{
    delete Display0;
    delete Display1;
    delete Display2;
    Display0 = new imageview();
    Display1 = new imageview();
    Display2 = new imageview();
    if (CAM0) {
        Display0->setWindowTitle("Broadband Channel Detector");
        connect(DetectorBBCh, SIGNAL(displayImage(QPixmap,int,int,int)),
                Display0, SLOT(displayImage(QPixmap,int,int,int)));
        Display0->show();
    }
    if (CAM1) {
        Display1->setWindowTitle("Polarimeter Channel-1 Detector");
        connect(DetectorPCh1, SIGNAL(displayImage(QPixmap,int,int,int)),
                Display1, SLOT(displayImage(QPixmap,int,int,int)));
        Display1->show();
    }
    if (CAM2) {
        Display2->setWindowTitle("Polarimeter Channel-2 Detector");
        connect(DetectorPCh2, SIGNAL(displayImage(QPixmap,int,int,int)),
                Display2, SLOT(displayImage(QPixmap,int,int,int)));
        Display2->show();
    }
}

void MainWindow::plotData(int Mode)
{
    DisplayPlot = new plotview();
    DisplayPlot->setWindowTitle("Characterization Plot Window");
    DisplayPlot->AutoSaveDir = Characterization->AutoSaveSubDir;
    DisplayPlot->Mode = Mode;
    DisplayPlot->plotData();
    DisplayPlot->show();
}

void MainWindow::on_pushButtonClearLog_clicked()
{
    ui->plainTextEditLog->clear();
}

/***
void MainWindow::getScienceData()
{
    Observation = new AcqObservation();
    ThreadAcquisition = new QThread();
    Observation->Mode = ui->toolBoxAcquisition->currentIndex();
    Observation->NCycles = ui->spinBoxObsScienceCyc->value();
    Observation->AutoSaveDir = ui->lineEditAutoSave->text().toStdString();
    // Sub-dir for science data
    Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/Science";
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Sub-dir for the day
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/yyyyMMdd").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Sub-dir for the time
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/hhmm").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Log file name
    std::string TempName = Observation->AutoSaveSubDir + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz").toStdString() + "_log.txt";
    DevLog = std::ofstream(TempName);
    addLog("Observation log will be saved as: " + QString::fromStdString(TempName));
    QString TempSettingsName = QString::fromStdString(Observation->AutoSaveSubDir) + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz") + "_settings.ini";
    QSettings *TempSettings = new QSettings(TempSettingsName, QSettings::IniFormat);
    foreach (const QString &Key, obsSettings->allKeys()){
        TempSettings->setValue(Key, obsSettings->value(Key));
    }
    TempSettings->sync();
    addLog("Settings will be saved as: " + TempSettingsName);
    //
    Observation->moveToThread(ThreadAcquisition);
    connect(ThreadAcquisition, SIGNAL(started()),
            Observation, SLOT(getScienceData()));
    connect(this, SIGNAL(stopAcquisition()),
            Observation, SLOT(Interrupt()));
    connect(Observation, SIGNAL(Finished()),
            ThreadAcquisition, SLOT(quit()));
    connect(ThreadAcquisition, SIGNAL(finished()),
            ThreadAcquisition, SLOT(deleteLater()));
    connect(ThreadAcquisition, SIGNAL(finished()),
            this, SLOT(finishAcquisition()));
    connect(Observation, SIGNAL(addLog(QString)),
            this, SLOT(addLog(QString)));
    connect(Observation, SIGNAL(updateProgress(int)),
            ui->progressBarStatus, SLOT(setValue(int)));
    connect(Observation, SIGNAL(updateOProgress(int)),
            ui->progressBarOStatus, SLOT(setValue(int)));
    //
    prepareAcquisition();
    prepareDisplay(1, 1, 1);
    ThreadAcquisition->start();
    ui->pushButtonAcquisition->setText("Stop Acquisition");
}

void MainWindow::getFlatsData()
{
    Observation = new AcqObservation();
    AcquisitionThread = new QThread();
    Observation->Mode = ui->toolBoxAcquisition->currentIndex();
    Observation->NCycles = ui->spinBoxObsFlatsCyc->value();
    Observation->AutoSaveDir = ui->lineEditAutoSave->text().toStdString();
    // Sub-dir for science data
    Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/Flats";
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Sub-dir for the day
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/yyyyMMdd").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Sub-dir for the time
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/hhmm").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Log file name
    std::string TempName = Observation->AutoSaveSubDir + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz").toStdString() + "_log.txt";
    DevLog = std::ofstream(TempName);
    addLog("Observation log will be saved as: " + QString::fromStdString(TempName));
    QString TempSettingsName = QString::fromStdString(Observation->AutoSaveSubDir) + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz") + "_settings.ini";
    QSettings *TempSettings = new QSettings(TempSettingsName, QSettings::IniFormat);
    foreach (const QString &Key, obsSettings->allKeys()){
        TempSettings->setValue(Key, obsSettings->value(Key));
    }
    TempSettings->sync();
    addLog("Settings will be saved as: " + TempSettingsName);
    //
    Observation->moveToThread(AcquisitionThread);
    connect(AcquisitionThread, SIGNAL(started()),
            Observation, SLOT(getFlatsData()));
    connect(this, SIGNAL(stopAcquisition()),
            Observation, SLOT(Interrupt()));
    connect(Observation, SIGNAL(Finished()),
            AcquisitionThread, SLOT(quit()));
    connect(AcquisitionThread, SIGNAL(finished()),
            AcquisitionThread, SLOT(deleteLater()));
    connect(AcquisitionThread, SIGNAL(finished()),
            this, SLOT(finishAcquisition()));
    connect(Observation, SIGNAL(addLog(QString)),
            this, SLOT(addLog(QString)));
    connect(Observation, SIGNAL(updateProgress(int)),
            ui->progressBarStatus, SLOT(setValue(int)));
    connect(Observation, SIGNAL(updateOProgress(int)),
            ui->progressBarOStatus, SLOT(setValue(int)));
    //
    prepareDisplay(1, 1, 1);
    prepareAcquisition();
    AcquisitionThread->start();
    ui->pushButtonAcquisition->setText("Stop Acquisition");
}

void MainWindow::getCalibrationData()
{
    Observation = new AcqObservation();
    AcquisitionThread = new QThread();
    Observation->Mode = ui->toolBoxAcquisition->currentIndex();
    addLog("Beginning acquisition of calibration frames");
    Observation->NICUPolCalib = ui->spinBoxObsPCalPol->value();
    Observation->NICURetCalib = ui->spinBoxObsPCalRet->value();
    Observation->NCycles = Observation->NICUPolCalib*Observation->NICURetCalib;
    Observation->AutoSaveDir = ui->lineEditAutoSave->text().toStdString();
    // Sub-dir for science data
    Observation->AutoSaveSubDir = Observation->AutoSaveDir + "/PCalibration";
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Sub-dir for the day
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/yyyyMMdd").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Sub-dir for the time
    Observation->AutoSaveSubDir += QDateTime::currentDateTime().toString("/hhmm").toStdString();
    if (!QDir(QString::fromStdString(Observation->AutoSaveSubDir)).exists()){
        QDir().mkdir(QString::fromStdString(Observation->AutoSaveSubDir));
        addLog("Creating directory : " + QString::fromStdString(Observation->AutoSaveSubDir));
    }
    // Log file name
    std::string TempName = Observation->AutoSaveSubDir + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz").toStdString() + "_log.txt";
    DevLog = std::ofstream(TempName);
    addLog("Observation log will be saved as: " + QString::fromStdString(TempName));
    QString TempSettingsName = QString::fromStdString(Observation->AutoSaveSubDir) + "/HELLRIDE_" +
                            QDateTime::currentDateTime().toString("yyyyMMmm_hhmmsszzz") + "_settings.ini";
    QSettings *TempSettings = new QSettings(TempSettingsName, QSettings::IniFormat);
    foreach (const QString &Key, obsSettings->allKeys()){
        TempSettings->setValue(Key, obsSettings->value(Key));
    }
    TempSettings->sync();
    addLog("Settings will be saved as: " + TempSettingsName);
    //
    Observation->moveToThread(AcquisitionThread);
    connect(AcquisitionThread, SIGNAL(started()),
            Observation, SLOT(getFlatsData()));
    connect(this, SIGNAL(stopAcquisition()),
            Observation, SLOT(Interrupt()));
    connect(Observation, SIGNAL(Finished()),
            AcquisitionThread, SLOT(quit()));
    connect(AcquisitionThread, SIGNAL(finished()),
            AcquisitionThread, SLOT(deleteLater()));
    connect(AcquisitionThread, SIGNAL(finished()),
            this, SLOT(finishAcquisition()));
    connect(Observation, SIGNAL(addLog(QString)),
            this, SLOT(addLog(QString)));
    connect(Observation, SIGNAL(updateProgress(int)),
            ui->progressBarStatus, SLOT(setValue(int)));
    connect(Observation, SIGNAL(updateOProgress(int)),
            ui->progressBarOStatus, SLOT(setValue(int)));
//    connect(Observation, SIGNAL(updateCycles(QString)),
//            ui->lineEditCycles, SLOT(setText(QString)));
    //
    prepareAcquisition();
    prepareDisplay(1, 1, 1);
    AcquisitionThread->start();
    ui->pushButtonAcquisition->setText("Stop Acquisition");
}
***/

