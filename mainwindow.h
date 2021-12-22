#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFileDialog>
#include <QThread>
//
#include "vtt.h"
#include "vttnet.h"
#include "common.h"
#include "etalon.h"
#include "camera.h"
#include "rotmount.h"
#include "twostages.h"
#include "polarimeter.h"
#include "acquisition.h"
#include "imageview.h"
#include "plotview.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void closeEvent(QCloseEvent *event);

    std::ofstream DevLog;

    Details *DataDetails;

    QSettings *newSettings;

    // Acquisition related

    QThread *ThreadAcquisition;

    Acquisition *Live;

    Acquisition *Observation;

    Acquisition *Characterization;

    // Component controls

    TwoStages *PolarimeterStages;

    TwoStages *FilterMatrix;

    TwoStages *ETStages;

    Polarimeter *LCVRPolarimeter;

    Etalon *ET50;

    Etalon *ET70;

    VTT *VTTControls;

    VTTNet *VTTServer;

    RotMount *CWPMount;

    // Other windows

    imageview *Display0;

    imageview *Display1;

    imageview *Display2;

    plotview *DisplayPlot;

private slots:

    void addLog(QString Log);

    void prepareAcquisition();

    void finishAcquisition();

    void applyDetectorSettings();

    void prepareDisplay(bool CAM0, bool CAM1, bool CAM2);

    void plotData(int Index);

    void doObservation();

    void doCharacterization();

    void showSettings();

    void saveSettings();

    //

    void on_pushButtonSettings_clicked();

    void on_pushButtonAutoSave_clicked();

    void on_pushButtonAcquisition_clicked(bool checked);

    void on_lineEditComment_returnPressed();

    void on_pushButtonGetValues_clicked();

    void on_pushButtonClearLog_clicked();

    void on_comboBoxStepResolution_currentIndexChanged(int index);

    // Filter matrix functions

    void on_pushButtonOpenFMS_clicked(bool checked);

    void on_pushButtonResetFMS_clicked();

    void on_lineEditCommandFMS_returnPressed();

    void on_spinBoxFilterPosition_valueChanged(int arg1);

    void on_doubleSpinBoxFMSXmm_valueChanged(double arg1);

    void on_doubleSpinBoxFMSYmm_valueChanged(double arg1);

    // Etalon stages functions

    void on_pushButtonOpenETS_clicked(bool checked);

    void on_pushButtonResetETS_clicked();

    void on_lineEditCommandETS_returnPressed();

    void on_pushButtonRemoveET1_clicked(bool checked);

    void on_pushButtonRemoveET2_clicked(bool checked);

    void on_doubleSpinBoxETS1mm_valueChanged(double arg1);

    void on_doubleSpinBoxETS2mm_valueChanged(double arg1);

    // Polarimeter stages functions

    void on_pushButtonOpenPLS_clicked(bool checked);

    void on_pushButtonResetPLS_clicked();

    void on_lineEditCommandPLS_returnPressed();

    void on_pushButtonRemoveAnalyzer_clicked(bool checked);

    void on_doubleSpinBoxFSmm_valueChanged(double arg1);

    void on_doubleSpinBoxANSmm_valueChanged(double arg1);

    // Etalon-1 (50) controls

    void on_pushButtonOpenET1_clicked(bool checked);

    void on_pushButtonResetET1_clicked();

    void on_lineEditCommandET1_returnPressed();

    void on_spinBoxET1Counts_valueChanged(int arg1);

    // Etalon-2 (ET70) controls

    void on_pushButtonOpenET2_clicked(bool checked);

    void on_pushButtonResetET2_clicked();

    void on_lineEditCommandET2_returnPressed();

    void on_spinBoxET2Counts_valueChanged(int arg1);

    // LCVR controls

    void on_pushButtonOpenLCVR_clicked(bool checked);

    void on_lineEditCommandLCVR_returnPressed();

    void on_spinBoxLCVR1mV_valueChanged(int arg1);

    void on_spinBoxLCVR2mV_valueChanged(int arg1);

    void on_pushButtonStartModulation_clicked(bool checked);

    // VTT instrument calibration unit controls

    void on_pushButtonOpenVTT_clicked(bool checked);

    void on_lineEditCommandVTT_returnPressed();

    void on_pushButtonInsertICU_clicked(bool checked);

    void on_doubleSpinBoxICUPdeg_editingFinished();

    void on_doubleSpinBoxICURdeg_editingFinished();

    void on_comboBoxVTTStopWheel_currentIndexChanged(int index);

    void on_pushButtonOpenVTTServer_clicked(bool checked);

    void on_lineEditCommandVTTServer_returnPressed();

    void on_pushButtonHomeICU_clicked();

    // Calibration wave plate/polarizer functions

    void on_pushButtonOpenCWP_clicked(bool checked);

    void on_pushButtonHomeCWP_clicked();

    void on_doubleSpinBoxCWPdeg_editingFinished();

    // Detectors' controls

    void on_comboBoxTrigger_currentIndexChanged(int index);

    void on_pushButtonLive_clicked(bool checked);

    void on_pushButtonOpenCAM0_clicked(bool checked);

    void on_pushButtonOpenCAM1_clicked(bool checked);

    void on_pushButtonOpenCAM2_clicked(bool checked);

    void on_comboBoxBinning_currentIndexChanged(const QString &arg1);

    void on_comboBoxROI_currentIndexChanged(const QString &arg1);

    void on_toolBoxAcquisition_currentChanged(int index);




    void on_pushButtonReloadObsSettings_clicked();

    void on_pushButtonReloadCoreSettings_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void stopAcquisition();
};

#endif // MAINWINDOW_H
