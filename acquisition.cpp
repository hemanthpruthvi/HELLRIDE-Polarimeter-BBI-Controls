# include "acquisition.h"

Acquisition::Acquisition(QObject *parent) : QObject(parent)
{
}

Acquisition::~Acquisition()
{
}

void Acquisition::addLog(std::string Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Log)));
}

void Acquisition::addLog(const char* Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Log)));
}

void Acquisition::initAcquisition()
{
    FilterMatrix = new TwoStages();
    PolarimeterStages = new TwoStages();
    VTTControls = new VTT();
    VTTServer = new VTTNet();
    CWPMount = new RotMount();
    LCVRPolarimeter = new Polarimeter();
    ET50 = new Etalon();
    ET70 = new Etalon();
    //
    connect(FilterMatrix, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    connect(ET50, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    connect(ET70, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    connect(PolarimeterStages, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    connect(LCVRPolarimeter, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    connect(VTTControls, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    connect(VTTServer, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    connect(CWPMount, SIGNAL(addLog(QString)), this, SIGNAL(addLog(QString)));
    //
    switch(Mode) {
    case OBS_MODE_SCIE:
        FilterMatrix->initTwoStages("FilterMatrix");
        PolarimeterStages->initTwoStages("PolarimeterStages");
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        TimeStamps = std::ofstream(AutoSaveSubDir + "/HELLRIDE_" +
                                   QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss").toStdString() + "_timestamps.csv");
        break;
    case OBS_MODE_FLAT:
        FilterMatrix->initTwoStages("FilterMatrix");
        PolarimeterStages->initTwoStages("PolarimeterStages");
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        TimeStamps = std::ofstream(AutoSaveSubDir + "/HELLRIDE_" +
                                   QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss").toStdString() + "_timestamps.csv");
        break;
    case OBS_MODE_PCAL:
        FilterMatrix->initTwoStages("FilterMatrix");
        PolarimeterStages->initTwoStages("PolarimeterStages");
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        VTTControls->initVTT("VTTControls");
        TimeStamps = std::ofstream(AutoSaveSubDir + "/HELLRIDE_" +
                                   QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss").toStdString() + "_timestamps.csv");        break;
    case OBS_MODE_DARK:
        VTTServer->initVTTNet("VTTServer");
        break;
    case OBS_MODE_TARG:
        FilterMatrix->initTwoStages("FilterMatrix");
        PolarimeterStages->initTwoStages("PolarimeterStages");
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        VTTServer->initVTTNet("VTTServer");
        break;
    case OBS_MODE_PINH:
        FilterMatrix->initTwoStages("FilterMatrix");
        PolarimeterStages->initTwoStages("PolarimeterStages");
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        VTTServer->initVTTNet("VTTServer");
        break;
    case CHR_MODE_ET1_MATCH:
        FilterMatrix->initTwoStages("FilterMatrix");
        ET50->initEtalon("Etalon_1");
        break;
    case CHR_MODE_ET2_MATCH:
        FilterMatrix->initTwoStages("FilterMatrix");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        break;
    case CHR_MODE_LINE_PROF:
        FilterMatrix->initTwoStages("FilterMatrix");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        break;
    case CHR_MODE_CAM_FOCUS:
        FilterMatrix->initTwoStages("FilterMatrix");
        PolarimeterStages->initTwoStages("PolarimeterStages");
        ET50->initEtalon("Etalon_1");
        ET70->initEtalon("Etalon_2");
        break;
    case CHR_MODE_LCVR1_PROF:
        FilterMatrix->initTwoStages("FilterMatrix");
        CWPMount->initDevice("CWPMount");
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        break;
    case CHR_MODE_LCVR2_PROF:
        FilterMatrix->initTwoStages("FilterMatrix");
        CWPMount->initDevice("CWPMount");
        LCVRPolarimeter->initPolarimeter("Polarimeter");
        break;
    case CHR_MODE_ET1_PROF:
        ET50->initEtalon("Etalon_1");
        break;
    case CHR_MODE_ET2_PROF:
        ET70->initEtalon("Etalon_2");
        break;
    default: break;
    }
    //
    DetectorBBCh->Mode = Mode;
    DetectorPCh1->Mode = Mode;
    DetectorPCh2->Mode = Mode;

    DetectorBBCh->prepareAcquisition();
    DetectorPCh1->prepareAcquisition();
    DetectorPCh2->prepareAcquisition();
    //
    NLines = obsSettings->childGroups().count();
    ACQ_RUN_FLAG = true;
}

void Acquisition::finishAcquisition()
{
    switch(Mode) {
    case OBS_MODE_SCIE:
        delete FilterMatrix;
        delete PolarimeterStages;
        delete LCVRPolarimeter;
        delete ET50;
        delete ET70;
        TimeStamps.close();
        break;
    case OBS_MODE_FLAT:
        delete FilterMatrix;
        delete PolarimeterStages;
        delete LCVRPolarimeter;
        delete ET50;
        delete ET70;
        TimeStamps.close();
        break;
    case OBS_MODE_PCAL:
        delete FilterMatrix;
        delete PolarimeterStages;
        delete LCVRPolarimeter;
        delete ET50;
        delete ET70;
        delete VTTControls;
        TimeStamps.close();
        break;
    case OBS_MODE_DARK:
        delete VTTServer;
        break;
    case OBS_MODE_TARG:
        delete FilterMatrix;
        delete PolarimeterStages;
        delete LCVRPolarimeter;
        delete ET50;
        delete ET70;
        delete VTTServer;
        break;
    case OBS_MODE_PINH:
        delete FilterMatrix;
        delete PolarimeterStages;
        delete LCVRPolarimeter;
        delete ET50;
        delete ET70;
        delete VTTServer;
        break;
    case CHR_MODE_ET1_MATCH:
        delete FilterMatrix;
        delete ET50;
        break;
    case CHR_MODE_ET2_MATCH:
        delete FilterMatrix;
        delete ET50;
        delete ET70;
        break;
    case CHR_MODE_LINE_PROF:
        delete FilterMatrix;
        delete ET50;
        delete ET70;;
        break;
    case CHR_MODE_CAM_FOCUS:
        delete FilterMatrix;
        delete PolarimeterStages;
        delete ET50;
        delete ET70;
        break;
    case CHR_MODE_LCVR1_PROF:
        delete FilterMatrix;
        delete CWPMount;
        delete LCVRPolarimeter;
        break;
    case CHR_MODE_LCVR2_PROF:
        delete FilterMatrix;
        delete CWPMount;
        delete LCVRPolarimeter;
        break;
    case CHR_MODE_ET1_PROF:
        delete ET50;
        break;
    case CHR_MODE_ET2_PROF:
        delete ET70;
        break;
    default: break;
    }
    //
    emit(Finished());
    emit(updateProgress(0));
    emit(updateOProgress(0));
//    DetectorBBCh->moveToThread(DetectorBBCh->MainThread);
//    DetectorPCh1->moveToThread(DetectorPCh1->MainThread);
//    DetectorPCh2->moveToThread(DetectorPCh2->MainThread);
    addLog(std::string("Acquisition finished."));
}

void Acquisition::startLive()
{
    ACQ_RUN_FLAG = true;
    if (LiveMode == LIVE_MODE_SAVE_ONLY || LiveMode == LIVE_MODE_VIEW_SAVE) SAVE_LIVE_FLAG = true;
    else SAVE_LIVE_FLAG = false;
    //
    if(CAM0_LIVE_FLAG) DetectorBBCh->prepareLive(SAVE_LIVE_FLAG);
    if(CAM1_LIVE_FLAG) DetectorPCh1->prepareLive(SAVE_LIVE_FLAG);
    if(CAM2_LIVE_FLAG) DetectorPCh2->prepareLive(SAVE_LIVE_FLAG);
    //
    switch(LiveMode) {
    case LIVE_MODE_VIEW_ONLY:
        while (ACQ_RUN_FLAG) {
            if (CAM0_LIVE_FLAG) DetectorBBCh->viewImage();
            if (CAM1_LIVE_FLAG) DetectorPCh1->viewImage();
            if (CAM2_LIVE_FLAG) DetectorPCh2->viewImage();
        }
        break;
    case LIVE_MODE_SAVE_ONLY:
        while (ACQ_RUN_FLAG) {
            if (CAM0_LIVE_FLAG) DetectorBBCh->saveImage();
            if (CAM1_LIVE_FLAG) DetectorPCh1->saveImage();
            if (CAM2_LIVE_FLAG) DetectorPCh2->saveImage();
        }
        break;
    case LIVE_MODE_VIEW_SAVE:
        while (ACQ_RUN_FLAG) {
            if (CAM0_LIVE_FLAG) DetectorBBCh->recordImage();
            if (CAM1_LIVE_FLAG) DetectorPCh1->recordImage();
            if (CAM2_LIVE_FLAG) DetectorPCh2->recordImage();
        }
        break;
    default: break;
    }
    //
    if(CAM0_LIVE_FLAG) DetectorBBCh->finishAcquisition();
    if(CAM1_LIVE_FLAG) DetectorPCh1->finishAcquisition();
    if(CAM2_LIVE_FLAG) DetectorPCh2->finishAcquisition();
}

void Acquisition::Interrupt() {
    ACQ_RUN_FLAG = false;
    addLog(std::string("Acquisition is interrupted..."));
}

// Observation subroutines---------------------------------------------------------------

void Acquisition::getScienceData()
{
    addLog("Observation mode: Science");
    initAcquisition();
    for (int c=0; c<NCycles; c++) {
        addLog("Cycle number: " + std::to_string(c+1));
        for (int i=0; i<NLines; i++) {
            emit(updateOProgress(100*(c*NLines+1+i)/(NCycles*NLines)));
            if (ACQ_RUN_FLAG) {
                loadLineSettings(QString::fromStdString("Line_"+std::to_string(i+1)));
                addLog("Number of accumulations per modulation state: " + std::to_string(NAccumulations));
                addLog("Number of modulations per wave point: " + std::to_string(NModulations));
                addLog("Number of wave points per spectral line: " + std::to_string(NWavePoints));
                int NFramesPerWave = NAccumulations*NModulations;
                int NFramesPerLine = NFramesPerWave*NWavePoints;
                int NMissedCAM0 = 0;
                int NMissedCAM1 = 0;
                int NMissedCAM2 = 0;
                addLog("Total frames to be recorded: " + std::to_string(NFramesPerLine));
                //
                addLog("Filter matrix moving to: " + std::to_string(FilterMatrix->iPreFilter));
                FilterMatrix->selectPreFilter();
                addLog("Focus stage moving to: " + std::to_string(PolarimeterStages->Position1));
                PolarimeterStages->moveStage1();
                addLog("Etalons tuning to line start: " + std::to_string(ET50->ZZero) + ", " + std::to_string(ET70->ZZero));
                ET50->gotoScanStartPosition();
                ET70->gotoScanStartPosition();
                addLog("Applying the LCVRs' settings...");
                LCVRPolarimeter->setModulation(POLARIMETRY);
                addLog("Applying the detectors' settings...");
                DetectorBBCh->NFrames = DetectorPCh1->NFrames = DetectorPCh2->NFrames = NFramesPerLine;
                DetectorBBCh->initAcquisition();
                DetectorPCh1->initAcquisition();
                DetectorPCh2->initAcquisition(); 
                Sleep(SDELAY);
                // Acquisition
                addLog("Starting acquisition...");
                LCVRPolarimeter->startModulation();
                for (int f=0; f<NFramesPerLine; f++) {
                    DetectorBBCh->saveImage();
                    DetectorPCh1->saveImage();
                    DetectorPCh2->saveImage();
                    if (DetectorBBCh->Error || DetectorPCh1->Error || DetectorPCh2->Error) {
                        addLog("Detector Error! Finishing acquisition!");
                        ACQ_RUN_FLAG = false;
                        break;
                    }
                    if (f == 0) {
                        NMissedCAM0 = -DetectorBBCh->Image.nframe;
                        NMissedCAM1 = -DetectorPCh1->Image.nframe;
                        NMissedCAM2 = -DetectorPCh2->Image.nframe;

                    }
                    if (f == NFramesPerLine-1) {
                        NMissedCAM0 += DetectorBBCh->Image.nframe;
                        NMissedCAM1 += DetectorPCh1->Image.nframe;
                        NMissedCAM2 += DetectorPCh2->Image.nframe;
                    }
                    if ((f+1)%NFramesPerWave == 1) {
                        ET50->scanWavelength();
                        ET70->scanWavelength();
                        emit(updateProgress(100*(1+f)/NFramesPerLine));
                    }
                    TimeStamps << c+1 << "," << i+1 << "," << f+1 << "," <<
                                  DetectorBBCh->Image.nframe << "," << DetectorBBCh->Image.tsSec << "," << DetectorBBCh->Image.tsUSec << "," <<
                                  DetectorPCh1->Image.nframe << "," << DetectorPCh1->Image.tsSec << "," << DetectorPCh1->Image.tsUSec << "," <<
                                  DetectorPCh2->Image.nframe << "," << DetectorPCh2->Image.tsSec << "," << DetectorPCh2->Image.tsUSec << std::endl;
                }
                addLog("Stopping modulation and acquisition...");
                if (!DetectorBBCh->Error) DetectorBBCh->displayImage();
                if (!DetectorPCh1->Error) DetectorPCh1->displayImage();
                if (!DetectorPCh2->Error) DetectorPCh2->displayImage();
                DetectorBBCh->finishAcquisition();
                DetectorPCh1->finishAcquisition();
                DetectorPCh2->finishAcquisition();
                LCVRPolarimeter->stopModulation();
                addLog("Total frames to be recorded: " + std::to_string(NFramesPerLine));
                addLog(DetectorBBCh->Label + " frames missed: " + std::to_string(NMissedCAM0+1 - NFramesPerLine));
                addLog(DetectorPCh1->Label + " frames missed: " + std::to_string(NMissedCAM1+1 - NFramesPerLine));
                addLog(DetectorPCh2->Label + " frames missed: " + std::to_string(NMissedCAM2+1 - NFramesPerLine));
                // Reset etalons if there is an error
                if (!ET50->Operating || !ET70->Operating) {
                    addLog(std::string("Etalon error! resetting both the etalons..."));
                    ET50->resetEtalon();
                    ET70->resetEtalon();
                    addLog("Deleting bad data file : " + DetectorPCh1->DATFileName);
                    std::remove(DetectorPCh1->DATFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorPCh2->DATFileName);
                    std::remove(DetectorPCh2->DATFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorBBCh->DATFileName);
                    std::remove(DetectorBBCh->DATFileName.c_str());
                }
            }
            else {
                finishAcquisition();
                return;
            }
        }
    }
    finishAcquisition();
}

void Acquisition::getFlatsData()
{
    addLog("Observation mode: Flats");
    initAcquisition();
    for (int i=0; i<NLines; i++) {
        loadLineSettings(QString::fromStdString("Line_"+std::to_string(i+1)));
        addLog("Number of accumulations per modulation state: " + std::to_string(NAccumulations));
        addLog("Number of modulations per wave point: " + std::to_string(NModulations));
        addLog("Number of wave points per spectral line: " + std::to_string(NWavePoints));
        int NFramesPerWave = NAccumulations*LCVRPolarimeter->NModulations;
        int NFramesPerLine = NFramesPerWave*ET50->NWavePoints;
        int NMissedCAM0 = 0;
        int NMissedCAM1 = 0;
        int NMissedCAM2 = 0;
        addLog("Total frames to be recorded: " + std::to_string(NFramesPerLine));
        //
        addLog("Filter matrix moving to: " + std::to_string(FilterMatrix->iPreFilter));
        FilterMatrix->selectPreFilter();
        addLog("Focus stage moving to: " + std::to_string(PolarimeterStages->Position1));
        PolarimeterStages->moveStage1();
        addLog("Applying LCVR settings...");
        LCVRPolarimeter->setModulation(POLARIMETRY=false);
        for (int c=0; c<NCycles; c++) {
            emit(updateOProgress(100*(c+1+i*NCycles)/(NCycles*NLines)));
            if (ACQ_RUN_FLAG) {
                // Setup components
                addLog("Cycle number: " + std::to_string(c+1));
                addLog("Etalons tuning to line start: " + std::to_string(ET50->ZZero) + ", " + std::to_string(ET70->ZZero));
                ET50->gotoScanStartPosition();
                ET70->gotoScanStartPosition();
                addLog("Applying detector settings...");
                DetectorBBCh->NFrames = DetectorPCh1->NFrames = DetectorPCh2->NFrames = NFramesPerLine;
                DetectorBBCh->initAcquisition();
                DetectorPCh1->initAcquisition();
                DetectorPCh2->initAcquisition();
                Sleep(SDELAY);
                // Acquisition
                addLog("Starting modulation and acquisition...");
                LCVRPolarimeter->startModulation();
                for (int f=0; f<NFramesPerLine; f++) {
                    DetectorBBCh->saveImage();
                    DetectorPCh1->saveImage();
                    DetectorPCh2->saveImage();
                    if (f == 0) {
                        NMissedCAM0 = -DetectorBBCh->Image.nframe;
                        NMissedCAM1 = -DetectorPCh1->Image.nframe;
                        NMissedCAM2 = -DetectorPCh2->Image.nframe;
                    }
                    if (f == NFramesPerLine-1) {
                        NMissedCAM0 += DetectorBBCh->Image.nframe;
                        NMissedCAM1 += DetectorPCh1->Image.nframe;
                        NMissedCAM2 += DetectorPCh2->Image.nframe;
                    }
                    if ((f+1)%NFramesPerWave == 1) {
                        addLog("Tuning etalons...");
                        ET50->scanWavelength();
                        ET70->scanWavelength();
                        emit(updateProgress(100*(1+f)/NFramesPerLine));
                    }
                    TimeStamps << i+1 << "," << c+1 << "," << f+1 << "," <<
                                  DetectorBBCh->Image.nframe << "," << DetectorBBCh->Image.tsSec << "," << DetectorBBCh->Image.tsUSec << "," <<
                                  DetectorPCh1->Image.nframe << "," << DetectorPCh1->Image.tsSec << "," << DetectorPCh1->Image.tsUSec << "," <<
                                  DetectorPCh2->Image.nframe << "," << DetectorPCh2->Image.tsSec << "," << DetectorPCh2->Image.tsUSec << std::endl;
                }
                addLog("Stopping modulation and acquisition...");
                DetectorBBCh->displayImage();
                DetectorPCh1->displayImage();
                DetectorPCh2->displayImage();
                DetectorBBCh->finishAcquisition();
                DetectorPCh1->finishAcquisition();
                DetectorPCh2->finishAcquisition();
                LCVRPolarimeter->stopModulation();
                addLog("Total frames to be recorded: " + std::to_string(NFramesPerLine));
                addLog(DetectorBBCh->Label + " frames missed: " + std::to_string(NMissedCAM0+1 - NFramesPerLine));
                addLog(DetectorPCh1->Label + " frames missed: " + std::to_string(NMissedCAM1+1 - NFramesPerLine));
                addLog(DetectorPCh2->Label + " frames missed: " + std::to_string(NMissedCAM2+1 - NFramesPerLine));
                // Reset etalons if there is an error
                if (!ET50->Operating || !ET70->Operating) {
                    addLog(std::string("Etalon error! resetting both the etalons..."));
                    ET50->resetEtalon();
                    ET70->resetEtalon();
                    addLog("Deleting bad data file : " + DetectorPCh1->DATFileName);
                    std::remove(DetectorPCh1->DATFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorPCh2->DATFileName);
                    std::remove(DetectorPCh2->DATFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorBBCh->DATFileName);
                    std::remove(DetectorBBCh->DATFileName.c_str());
                }
            }
            else {
                finishAcquisition();
                return;
            }
        }
    }
    finishAcquisition();
}

void Acquisition::getCalibrationData()
{
    addLog("Observations mode: Polarimetric Calibration");
    initAcquisition();
    addLog("Inserting the calibration unit (ICU)...");
    VTTControls->insertICU();
    VTTControls->ICUPolarizer->NPositions = NICUPolCalib;
    VTTControls->ICURetarder->NPositions = NICURetCalib;
    for (int i=0; i<NLines; i++) {
        loadLineSettings(QString::fromStdString("Line_"+std::to_string(i+1)));
        if (POLARIMETRY) {
            addLog("Number of accumulations per modulation state: " + std::to_string(NAccumulations));
            addLog("Number of modulations per wave point: " + std::to_string(NModulations));
            addLog("Number of wave points per spectral line: " + std::to_string(NWavePoints));
            int NFramesPerWave = NAccumulations*LCVRPolarimeter->NModulations;
            int NFramesPerLine = NFramesPerWave*ET50->NWavePoints;
            int NMissedCAM0 = 0;
            int NMissedCAM1 = 0;
            int NMissedCAM2 = 0;
            addLog("Total frames to be recorded: " + std::to_string(NFramesPerLine));
            //
            addLog("Moving the pre-filter: " + std::to_string(FilterMatrix->iPreFilter));
            FilterMatrix->selectPreFilter();
            addLog("Adjusting the detector focus...");
            PolarimeterStages->moveStage1();
            addLog("Applying LCVR settings...");
            LCVRPolarimeter->setModulation(POLARIMETRY);
            for (int c=0; c<NCycles; c++) {
                emit(updateOProgress(100*(c+1+i*NCycles)/(NCycles*NLines)));
                if (ACQ_RUN_FLAG) {
                    addLog("Cycle number: " + std::to_string(c+1));
                    addLog("Moving ICU polarizer and retarders..." );
                    VTTControls->gotoICUPosition(c/NICURetCalib, c%NICURetCalib);
                    addLog("Etalons tuning to line start: " + std::to_string(ET50->ZZero) + ", " + std::to_string(ET70->ZZero));
                    ET50->gotoScanStartPosition();
                    ET70->gotoScanStartPosition();
                    addLog("Applying the detector settings...");
                    DetectorBBCh->NFrames = DetectorPCh1->NFrames = DetectorPCh2->NFrames = NFramesPerLine;
                    DetectorBBCh->initAcquisition();
                    DetectorPCh1->initAcquisition();
                    DetectorPCh2->initAcquisition();
                    Sleep(SDELAY);
                    // Setup LCVRs
                    addLog("Starting modulation and acquisition...");
                    LCVRPolarimeter->startModulation();
                    for (int f=0; f<NFramesPerLine; f++) {
                        DetectorBBCh->saveImage();
                        DetectorPCh1->saveImage();
                        DetectorPCh2->saveImage();
                        if (f == 0) {
                            NMissedCAM0 = -DetectorBBCh->Image.nframe;
                            NMissedCAM1 = -DetectorPCh1->Image.nframe;
                            NMissedCAM2 = -DetectorPCh2->Image.nframe;
                        }
                        if (f == NFramesPerLine-1) {
                            NMissedCAM0 += DetectorBBCh->Image.nframe;
                            NMissedCAM1 += DetectorPCh1->Image.nframe;
                            NMissedCAM2 += DetectorPCh2->Image.nframe;
                        }
                        if ((f+1)%NFramesPerWave == 1) {
                            addLog("Tuning etalons...");
                            ET50->scanWavelength();
                            ET70->scanWavelength();
                            emit(updateProgress(100*(1+f)/NFramesPerLine));
                        }
                        TimeStamps << i+1 << "," << c+1 << "," << f+1 << "," <<
                                      DetectorBBCh->Image.nframe << "," << DetectorBBCh->Image.tsSec << "," << DetectorBBCh->Image.tsUSec << "," <<
                                      DetectorPCh1->Image.nframe << "," << DetectorPCh1->Image.tsSec << "," << DetectorPCh1->Image.tsUSec << "," <<
                                      DetectorPCh2->Image.nframe << "," << DetectorPCh2->Image.tsSec << "," << DetectorPCh2->Image.tsUSec << std::endl;
                    }
                    addLog("Stopping modulation and acquisition...");
                    DetectorBBCh->displayImage();
                    DetectorPCh1->displayImage();
                    DetectorPCh2->displayImage();
                    DetectorBBCh->finishAcquisition();
                    DetectorPCh1->finishAcquisition();
                    DetectorPCh2->finishAcquisition();
                    LCVRPolarimeter->stopModulation();
                    addLog("Total frames to be recorded: " + std::to_string(NFramesPerLine));
                    addLog(DetectorBBCh->Label + " frames missed: " + std::to_string(NMissedCAM0+1 - NFramesPerLine));
                    addLog(DetectorPCh1->Label + " frames missed: " + std::to_string(NMissedCAM1+1 - NFramesPerLine));
                    addLog(DetectorPCh2->Label + " frames missed: " + std::to_string(NMissedCAM2+1 - NFramesPerLine));
                    // Reset etalons if there is an error
                    if (!ET50->Operating || !ET70->Operating) {
                        addLog(std::string("Etalon error! resetting both the etalons..."));
                        ET50->resetEtalon();
                        ET70->resetEtalon();
                        addLog("Deleting bad data file : " + DetectorPCh1->DATFileName);
                        std::remove(DetectorPCh1->DATFileName.c_str());
                        addLog("Deleting bad data file : " + DetectorPCh2->DATFileName);
                        std::remove(DetectorPCh2->DATFileName.c_str());
                        addLog("Deleting bad data file : " + DetectorBBCh->DATFileName);
                        std::remove(DetectorBBCh->DATFileName.c_str());
                    }
                }
                else {
                    addLog("removing the calibration unit (ICU)...");
                    VTTControls->removeICU();
                    finishAcquisition();
                    return;
                }
            }
        }
    }
    addLog("removing the calibration unit (ICU)...");
    VTTControls->insertICU();
    finishAcquisition();
}

void Acquisition::getDarksData()
{
    addLog("Observation mode: Darks");
    initAcquisition();
    addLog("Moving stop wheel to dark...");;
    VTTServer->StopWheelPosition = AOSW_DARK;
    VTTServer->positionStopWheel();
    for (int i=0; i<NLines; i++) {
        emit(updateOProgress(100*(i+1)/NLines));
        loadLineSettings(QString::fromStdString("Line_"+std::to_string(i+1)));
        if (ACQ_RUN_FLAG) {
            // Setup components
            addLog("Applying detector settings...");
            DetectorBBCh->NFrames = DetectorPCh1->NFrames = DetectorPCh2->NFrames = NCycles;
            DetectorBBCh->initAcquisition();
            DetectorPCh1->initAcquisition();
            DetectorPCh2->initAcquisition();
            Sleep(SDELAY);
            // Acquisition
            addLog("Starting acquisition...");
            for (int f=0; f<NCycles; f++) {
                DetectorBBCh->recordImage();
                DetectorPCh1->recordImage();
                DetectorPCh2->recordImage();
                emit(updateProgress(100*(f+1)/NCycles));
            }
            addLog("Stopping acquisition...");
            DetectorBBCh->finishAcquisition();
            DetectorPCh1->finishAcquisition();
            DetectorPCh2->finishAcquisition();
        }
        else {
            addLog("Moving stop wheel to default...");
//            VTTServer->StopWheelPosition = AOSW_DEFAULT;
//            VTTServer->positionStopWheel();
            finishAcquisition();
            return;
        }
    }
    addLog("Moving stop wheel to default...");
//    VTTServer->StopWheelPosition = AOSW_DEFAULT;
//    VTTServer->positionStopWheel();
    finishAcquisition();
}

void Acquisition::getPinholeData()
{
    addLog("Observation mode: Pinhole");
    initAcquisition();
    addLog("Moving stop wheel to pinhole...");
    VTTServer->StopWheelPosition = AOSW_PINH;
    VTTServer->positionStopWheel();
    for (int i=0; i<NLines; i++) {
        emit(updateOProgress(100*(i+1)/NLines));
        loadLineSettings(QString::fromStdString("Line_"+std::to_string(i+1)));
        addLog("Filter matrix moving to: " + std::to_string(FilterMatrix->iPreFilter));
        FilterMatrix->selectPreFilter();
        addLog("Focus stage moving to: " + std::to_string(PolarimeterStages->Position1));
        PolarimeterStages->moveStage1();
        addLog("Etalons tuning to line start: " + std::to_string(ET50->ZZero) + ", " + std::to_string(ET70->ZZero));
        ET50->gotoScanStartPosition();
        ET70->gotoScanStartPosition();
        Sleep(XLDELAY);
        if (ACQ_RUN_FLAG) {
            // Setup components
            addLog("Applying detector settings...");
            DetectorBBCh->NFrames = DetectorPCh1->NFrames = DetectorPCh2->NFrames = NCycles;
            DetectorBBCh->initAcquisition();
            DetectorPCh1->initAcquisition();
            DetectorPCh2->initAcquisition();
            Sleep(SDELAY);
            // Acquisition
            addLog("Starting acquisition...");
            for (int f=0; f<NCycles; f++) {
                DetectorBBCh->recordImage();
                DetectorPCh1->recordImage();
                DetectorPCh2->recordImage();
                emit(updateProgress(100*(f+1)/NCycles));
            }
            addLog("Stopping acquisition...");
            DetectorBBCh->finishAcquisition();
            DetectorPCh1->finishAcquisition();
            DetectorPCh2->finishAcquisition();
        }
        else {
            addLog("Moving stop wheel to default...");
//            VTTServer->StopWheelPosition = AOSW_DEFAULT;
//            VTTServer->positionStopWheel();
            finishAcquisition();
            return;
        }
    }
    addLog("Moving stop wheel to default...");
//    VTTServer->StopWheelPosition = AOSW_DEFAULT;
//    VTTServer->positionStopWheel();
    finishAcquisition();
}

void Acquisition::getTargetplateData()
{
    addLog("Observation mode: Targetplate");
    initAcquisition();
    addLog("Moving stop wheel to target plate...");
    VTTServer->StopWheelPosition = AOSW_TARG;
    VTTServer->positionStopWheel();
    for (int i=0; i<NLines; i++) {
        emit(updateOProgress(100*(i+1)/NLines));
        loadLineSettings(QString::fromStdString("Line_"+std::to_string(i+1)));
        addLog("Filter matrix moving to: " + std::to_string(FilterMatrix->iPreFilter));
        FilterMatrix->selectPreFilter();
        addLog("Focus stage moving to: " + std::to_string(PolarimeterStages->Position1));
        PolarimeterStages->moveStage1();
        addLog("Etalons tuning to line start: " + std::to_string(ET50->ZZero) + ", " + std::to_string(ET70->ZZero));
        ET50->gotoScanStartPosition();
        ET70->gotoScanStartPosition();
        Sleep(XLDELAY);
        if (ACQ_RUN_FLAG) {
            // Setup components
            addLog("Applying detector settings...");
            DetectorBBCh->NFrames = DetectorPCh1->NFrames = DetectorPCh2->NFrames = NCycles;
            DetectorBBCh->initAcquisition();
            DetectorPCh1->initAcquisition();
            DetectorPCh2->initAcquisition();
            Sleep(SDELAY);
            // Acquisition
            addLog("Starting acquisition...");
            for (int f=0; f<NCycles; f++) {
                DetectorBBCh->recordImage();
                DetectorPCh1->recordImage();
                DetectorPCh2->recordImage();
                emit(updateProgress(100*(f+1)/NCycles));
            }
            addLog("Stopping acquisition...");
            DetectorBBCh->finishAcquisition();
            DetectorPCh1->finishAcquisition();
            DetectorPCh2->finishAcquisition();
        }
        else {
            addLog("Moving stop wheel to default...");
//            VTTServer->StopWheelPosition = AOSW_DEFAULT;
//            VTTServer->positionStopWheel();
            finishAcquisition();
            return;
        }
    }
    addLog("Moving stop wheel to default...");
//    VTTServer->StopWheelPosition = AOSW_DEFAULT;
//    VTTServer->positionStopWheel();
    finishAcquisition();
}

void Acquisition::loadLineSettings(QString Name)
{
    //
    LineLabel = obsSettings->value(Name + "/Label").toString().toStdString();
    QString FilterName = obsSettings->value(Name + "/Filter").toString();
    QString ModulationName = obsSettings->value(Name + "/Polarimeter/Modulation").toString();
    LCVRPolarimeter->StateTime = obsSettings->value(Name + "/Polarimeter/StateTime").toInt();
    addLog("Observing in line: " + LineLabel);
    // Etalons
    ET50->ZZero = Settings->value(FilterName + "/Etalon_1/ZZero").toInt();
    ET70->ZZero = Settings->value(FilterName + "/Etalon_2/ZZero").toInt();
    ET50->NWavePoints = ET70->NWavePoints = obsSettings->value(Name + "/NWavePoints").toInt();
    ET50->WaveScanRange = ET70->WaveScanRange = obsSettings->value(Name + "/WaveScanRange").toDouble();
    ET50->Wavelength = ET70->Wavelength = obsSettings->value(Name + "/LineWavelength").toDouble();
    // Filter matrix
    FilterMatrix->iPreFilter = Settings->value(FilterName + "/FilterMatrix/iPreFilter").toUInt();
    // Focus stage
    PolarimeterStages->Position1 = Settings->value(FilterName + "/FocusStage/Position").toDouble();
    //
    int TriggerDelay = Settings->value(FilterName + "/Polarimeter/" + ModulationName + "/TriggerDelay").toInt();
    LCVRPolarimeter->NModulations = Settings->value(FilterName + "/Polarimeter/" + ModulationName + "/NModulations").toInt();
    if (LCVRPolarimeter->NModulations > 1) {
        POLARIMETRY = true;
        // LCVR1
        LCVRPolarimeter->LCVR1Voltages.clear();
        QStringList LCVR1mV = Settings->value(FilterName + "/Polarimeter/" + ModulationName + "/Vmod1").toStringList();
        foreach(const QString Voltage, LCVR1mV) {
            LCVRPolarimeter->LCVR1Voltages.push_back(Voltage.toInt());
        }
        // LCVR2
        LCVRPolarimeter->LCVR2Voltages.clear();
        QStringList LCVR2mV = Settings->value(FilterName + "/Polarimeter/" + ModulationName + "/Vmod2").toStringList();
        foreach(const QString Voltage, LCVR2mV) {
            LCVRPolarimeter->LCVR2Voltages.push_back(Voltage.toInt());
        }
    }
    else {
        POLARIMETRY = false;
    }
    LCVRPolarimeter->Vzero1 = Settings->value(FilterName + "/Polarimeter/Vzero1").toInt();
    LCVRPolarimeter->Vzero2 = Settings->value(FilterName + "/Polarimeter/Vzero2").toInt();
    //
    NAccumulations = obsSettings->value(Name + "/Polarimeter/NAccumulations").toInt();
    NModulations = LCVRPolarimeter->NModulations;
    NWavePoints = ET50->NWavePoints;
    // Cameras
    DetectorBBCh->ExposureTime = obsSettings->value(Name + "/Camera_0/ExposureTime").toInt();
    DetectorPCh1->ExposureTime = obsSettings->value(Name + "/Camera_1/ExposureTime").toInt();
    DetectorPCh2->ExposureTime = obsSettings->value(Name + "/Camera_2/ExposureTime").toInt();
    //
    DetectorBBCh->Binning = obsSettings->value(Name + "/Camera_0/Binning").toInt();
    DetectorPCh1->Binning = obsSettings->value(Name + "/Camera_1/Binning").toInt();
    DetectorPCh2->Binning = obsSettings->value(Name + "/Camera_2/Binning").toInt();
    //
    DetectorBBCh->ROI = obsSettings->value(Name + "/Camera_0/ROI").toInt();
    DetectorPCh1->ROI = obsSettings->value(Name + "/Camera_1/ROI").toInt();
    DetectorPCh2->ROI = obsSettings->value(Name + "/Camera_2/ROI").toInt();
    //
    DetectorBBCh->TriggerDelay = TriggerDelay;
    DetectorPCh1->TriggerDelay = TriggerDelay;
    DetectorPCh2->TriggerDelay = TriggerDelay;
    //
    DetectorBBCh->AutoSaveDir = AutoSaveSubDir + "/" + LineLabel;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir + "/" + LineLabel;
    DetectorPCh2->AutoSaveDir = AutoSaveSubDir + "/" + LineLabel;
    //

}

// Characterization subroutines----------------------------------------------------------

void Acquisition::matchET1Passband()
{
    // Mode specific things
    addLog(std::string("Characterization mode: ET50 passband matching with pre-filter"));
    XData.clear();
    YData.clear();
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_ET50pass.csv");
    initAcquisition();
    addLog("FilterMatrix moving to: " + std::to_string(iPreFilter));
    FilterMatrix->iPreFilter = iPreFilter;
    FilterMatrix->selectPreFilter();
    Sleep(XLDELAY);
    addLog("Applying detector settings...");
    DetectorPCh1->Mode = Mode;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->prepareAcquisition();
    DetectorPCh1->NFrames = (ET1Stop-ET1Start+ET1Step)/ET1Step;
    DetectorPCh1->initAcquisition();
    for (int i=ET1Start; i<ET1Stop+ET1Step; i+=ET1Step) {
        if (ACQ_RUN_FLAG) {
            ET50->ZCounts = i;
            ET50->tuneWavelength();
            Sleep(LDELAY);
            DetectorPCh1->recordImage();
            XData.push_back(i);
            YData.push_back(DetectorPCh1->MeanCountValue);
            Numbers << i << "," << DetectorPCh1->MeanCountValue << std::endl;
            emit(updateOProgress(100*(i-ET1Start+ET1Step)/(ET1Stop-ET1Start)));
        }
        else {
            DetectorPCh1->finishAcquisition();
            Numbers.close();
            finishAcquisition();
            return;
        }
    }
    emit(plotData(Mode));
    DetectorPCh1->finishAcquisition();
    Numbers.close();
    finishAcquisition();
}

void Acquisition::matchET2Passband()
{
    // Mode specific things
    addLog(std::string("Characterization mode: ET70 passband matching with ET50 passband"));
    XData.clear();
    YData.clear();
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_ET70pass.csv");
    initAcquisition();
    addLog("FilterMatrix moving to: " + std::to_string(iPreFilter));
    FilterMatrix->iPreFilter = iPreFilter;
    FilterMatrix->selectPreFilter();
    Sleep(XLDELAY);
    addLog("Tuning ET50 to zero position...");
    ET50->ZCounts = ET1Zero;
    ET50->tuneWavelength();
    addLog("Applying detector settings...");
    DetectorPCh1->Mode = Mode;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->prepareAcquisition();
    DetectorPCh1->NFrames = (ET2Stop-ET2Start+ET2Step)/ET2Step;
    DetectorPCh1->initAcquisition();
    for (int i=ET2Start; i<ET2Stop+ET2Step; i+=ET2Step) {
        if (ACQ_RUN_FLAG) {
            ET70->ZCounts = i;
            ET70->tuneWavelength();
            Sleep(LDELAY);
            DetectorPCh1->recordImage();
            XData.push_back(i);
            YData.push_back(DetectorPCh1->MeanCountValue);
            Numbers << i << "," << DetectorPCh1->MeanCountValue << std::endl;
            emit(updateOProgress(100*(i-ET2Start+ET2Step)/(ET2Stop-ET2Start)));
        }
        else {
            DetectorPCh1->finishAcquisition();
            Numbers.close();
            finishAcquisition();
            return;
        }
    }
    emit(plotData(Mode));
    DetectorPCh1->finishAcquisition();
    Numbers.close();
    finishAcquisition();
}

void Acquisition::matchETPassbandsLine()
{
    // Mode specific things
    addLog(std::string("Characterization mode: ET50 and ET70 passband matching with spectral line"));
    XData.clear();
    YData.clear();
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_ETpassLine.csv");
    //
    initAcquisition();
    addLog("FilterMatrix moving to: " + std::to_string(iPreFilter));
    FilterMatrix->iPreFilter = iPreFilter;
    FilterMatrix->selectPreFilter();
    Sleep(XLDELAY);
    addLog("Tuning ET50 and ET70 to zero positions...");
    // ET1 and ET2 starting positions
    ET50->Wavelength = ET70->Wavelength = Wavelength;
    ET50->WaveScan = ET70->WaveScan = -WaveRange/2.0;
    ET50->ZCounts = ET1Zero;
    ET70->ZCounts = ET2Zero;
    ET50->scanWavelength();
    ET70->scanWavelength();
    Sleep(MDELAY);
    ET50->WaveScan = ET70->WaveScan = WaveStep;
    DetectorPCh1->Mode = Mode;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->prepareAcquisition();
    DetectorPCh1->NFrames = (WaveRange+WaveStep)/WaveStep;
    DetectorPCh1->initAcquisition();
    double WaveStart = Wavelength-WaveRange/2.0;
    double WaveStop = Wavelength+WaveRange/2.0;
    for (double i=WaveStart; i<WaveStop+WaveStep; i+=WaveStep) {
        if (ACQ_RUN_FLAG) {
            ET50->scanWavelength();
            ET70->scanWavelength();
            Sleep(LDELAY);
            DetectorPCh1->recordImage();
            XData.push_back(ET50->ZCounts);
            XData2.push_back(ET70->ZCounts);
            YData.push_back(DetectorPCh1->MeanCountValue);
            Numbers << i << "," << ET50->ZCounts << "," << ET70->ZCounts <<
                       "," << DetectorPCh1->MeanCountValue << std::endl;
            emit(updateOProgress(100*(i-WaveStart+WaveStep)/WaveRange));
        }
        else {
            DetectorPCh1->finishAcquisition();
            Numbers.close();
            finishAcquisition();
            return;
        }
    }
    emit(plotData(Mode));
    DetectorPCh1->finishAcquisition();
    Numbers.close();
    finishAcquisition();
}

void Acquisition::examineBestFocus()
{
    // Mode specific things
    addLog(std::string("Characterization mode: ET50 passband matching with pre-filter"));
    QPainter *ImageText;
    QFile *ImageFile;
    initAcquisition();
    addLog("FilterMatrix moving to: " + std::to_string(iPreFilter));
    FilterMatrix->iPreFilter = iPreFilter;
    FilterMatrix->selectPreFilter();
    Sleep(XLDELAY);
    addLog("Tuning ET50 and ET70 to zero positions...");
    // ET1 and ET2 starting positions
    ET50->Wavelength = ET70->Wavelength = Wavelength;
    ET50->WaveScan = ET70->WaveScan = -WaveRange/2.0;
    ET50->ZCounts = ET1Zero;
    ET70->ZCounts = ET2Zero;
    ET50->scanWavelength();
    ET70->scanWavelength();
    Sleep(SDELAY);
    ET50->WaveScan = ET70->WaveScan = WaveStep;
    addLog("Applying detector settings...");
    DetectorBBCh->Mode = Mode;
    DetectorPCh1->Mode = Mode;
    DetectorPCh2->Mode = Mode;
    DetectorBBCh->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh2->AutoSaveDir = AutoSaveSubDir;
    DetectorBBCh->prepareAcquisition();
    DetectorPCh1->prepareAcquisition();
    DetectorPCh2->prepareAcquisition();
    DetectorBBCh->NFrames = DetectorPCh1->NFrames = DetectorPCh2->NFrames = (FocusStop-FocusStart+FocusStep)/FocusStep;
    DetectorBBCh->initAcquisition();
    DetectorPCh1->initAcquisition();
    DetectorPCh2->initAcquisition();
    //
    DetectorBBCh->recordImage();
    for (double i=FocusStart; i<FocusStop+FocusStep; i+=FocusStep) {
        if (ACQ_RUN_FLAG) {
            PolarimeterStages->Position1 = i;
            PolarimeterStages->moveStage1();
            Sleep(LDELAY);
            DetectorPCh1->saveImage();
            DetectorPCh2->saveImage();
            // View and save CAM1 image
            DetectorPCh1->prepareImageDisplay();
            ImageText = new QPainter(&DetectorPCh1->DisplayPixmap);
            ImageText->setFont(QFont("Arial", 24));
            ImageText->setPen(Qt::green);
            ImageText->drawText(QPoint(32, 32), "Focus at: " + QString::number(i));
            DetectorPCh1->displayPixmap();
            ImageFile = new QFile(QString::fromStdString(AutoSaveSubDir + "/HELLRIDE_" + DetectorPCh1->FileNameCameraSuffix +
                                                         "_" + std::to_string(i) + "mm.png"));
            ImageFile->open(QIODevice::WriteOnly);
            DetectorPCh1->DisplayPixmap.save(ImageFile, "PNG");
            ImageFile->close();
            delete ImageText;
            // View and save CAM2 image
            DetectorPCh2->prepareImageDisplay();
            ImageText = new QPainter(&DetectorPCh2->DisplayPixmap);
            ImageText->setFont(QFont("Arial", 24));
            ImageText->setPen(Qt::green);
            ImageText->drawText(QPoint(32, 32), "Focus at: " + QString::number(i));
            DetectorPCh2->displayPixmap();
            ImageFile = new QFile(QString::fromStdString(AutoSaveSubDir + "/HELLRIDE_" + DetectorPCh2->FileNameCameraSuffix +
                                                         "_" + std::to_string(i) + "mm.png"));
            ImageFile->open(QIODevice::WriteOnly);
            DetectorPCh2->DisplayPixmap.save(ImageFile, "PNG");
            ImageFile->close();
            delete ImageText;
            //
            emit(updateOProgress(100*(i-FocusStart+FocusStep)/(FocusStop-FocusStart)));
        }
        else {
            DetectorBBCh->finishAcquisition();
            DetectorPCh1->finishAcquisition();
            DetectorPCh2->finishAcquisition();
            finishAcquisition();
            return;
        }
    }
    DetectorBBCh->finishAcquisition();
    DetectorPCh1->finishAcquisition();
    DetectorPCh2->finishAcquisition();
    finishAcquisition();
}

void Acquisition::doLCVR1Characterization()
{
    // Mode specific things
    addLog(std::string("Characterization mode: LCVR1 Retardance vs. Voltage profiling"));
    XData.clear();
    YData.clear();
    YData2.clear();
    double IRatio, Retard;
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_LCVR1prof.csv");
    //
    initAcquisition();
    addLog("FilterMatrix moving to: " + std::to_string(iPreFilter));
    FilterMatrix->iPreFilter = iPreFilter;
    FilterMatrix->selectPreFilter();
    CWPMount->Position = 0.0;
    CWPMount->movePosition();
    Sleep(XLDELAY);
    addLog("Applying detector settings...");
    DetectorPCh1->Mode = Mode;
    DetectorPCh2->Mode = Mode;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh2->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->prepareAcquisition();
    DetectorPCh2->prepareAcquisition();
    DetectorPCh1->NFrames = DetectorPCh2->NFrames = (LCVR1Stop-LCVR1Start+LCVR1Step)/LCVR1Step;
    DetectorPCh1->initAcquisition();
    DetectorPCh2->initAcquisition();
    //
    for (int v=LCVR1Start; v<LCVR1Stop+LCVR1Step; v+=LCVR1Step) {
        if (ACQ_RUN_FLAG) {
            LCVRPolarimeter->LCVR1Voltage = v;
            LCVRPolarimeter->setLCVR1Voltage();
            Sleep(SDELAY);
            DetectorPCh1->recordImage();
            DetectorPCh2->recordImage();
            IRatio = 1.0*(DetectorPCh2->MeanCountValue-BiasCounts)/(DetectorPCh1->MeanCountValue-BiasCounts);
            Retard = 360*atan(sqrt(IRatio))/PI;
            YData2.push_back(IRatio);
            YData.push_back(Retard);
            XData.push_back(v);
            Numbers << v << "," << DetectorPCh2->MeanCountValue << "," <<
                       DetectorPCh1->MeanCountValue << "," << IRatio << "," << Retard << std::endl;
            emit(updateOProgress(100*(v-LCVR1Start+LCVR1Step)/(LCVR1Stop-LCVR1Start)));
        }
        else {
            DetectorPCh1->finishAcquisition();
            DetectorPCh2->finishAcquisition();
            Numbers.close();
            finishAcquisition();
            return;
        }
    }
    DetectorPCh1->finishAcquisition();
    DetectorPCh2->finishAcquisition();
    //
    emit(plotData(Mode));
    Numbers.close();
    finishAcquisition();
}

void Acquisition::doLCVR2Characterization()
{
    // Mode specific things
    addLog(std::string("Characterization mode: LCVR2 Retardance vs. Voltage profiling"));
    XData.clear();
    YData.clear();
    YData2.clear();
    double IRatio, Retard;
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_LCVR2prof.csv");
    //
    initAcquisition();
    addLog("FilterMatrix moving to: " + std::to_string(iPreFilter));
    FilterMatrix->iPreFilter = iPreFilter;
    FilterMatrix->selectPreFilter();
    CWPMount->Position = 0.0;
    CWPMount->movePosition();
    Sleep(XLDELAY);
    addLog("Applying detector settings...");
    DetectorPCh1->Mode = Mode;
    DetectorPCh2->Mode = Mode;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh2->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->prepareAcquisition();
    DetectorPCh2->prepareAcquisition();
    DetectorPCh1->NFrames = DetectorPCh2->NFrames = (LCVR2Stop-LCVR2Start+LCVR2Step)/LCVR2Step;
    DetectorPCh1->initAcquisition();
    DetectorPCh2->initAcquisition();
    //
    for (int v=LCVR2Start; v<LCVR2Stop+LCVR2Step; v+=LCVR2Step) {
        if (ACQ_RUN_FLAG) {
            LCVRPolarimeter->LCVR2Voltage = v;
            LCVRPolarimeter->setLCVR2Voltage();
            Sleep(SDELAY);
            DetectorPCh1->recordImage();
            DetectorPCh2->recordImage();
            IRatio = 1.0*(DetectorPCh2->MeanCountValue-BiasCounts)/(DetectorPCh1->MeanCountValue-BiasCounts);
            Retard = 360*atan(sqrt(IRatio))/PI;
            YData2.push_back(IRatio);
            YData.push_back(Retard);
            XData.push_back(v);
            Numbers << v << "," << DetectorPCh2->MeanCountValue << "," <<
                       DetectorPCh1->MeanCountValue << "," << IRatio << "," << Retard << std::endl;
            emit(updateOProgress(100*(v-LCVR2Start+LCVR2Step)/(LCVR2Stop-LCVR2Start)));
        }
        else {
            DetectorPCh1->finishAcquisition();
            DetectorPCh2->finishAcquisition();
            Numbers.close();
            finishAcquisition();
            return;
        }
    }
    DetectorPCh1->finishAcquisition();
    DetectorPCh2->finishAcquisition();
    //
    emit(plotData(Mode));
    Numbers.close();
    finishAcquisition();
}

void Acquisition::doET1Profiling()
{
    // Mode specific things
    addLog(std::string("Characterization mode: ET50 transmission profiling"));
    XData.clear();
    YData.clear();
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_ET50trans.csv");
    //
    initAcquisition();
    addLog("Applying detector settings...");
    DetectorPCh1->Mode = Mode;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->prepareAcquisition();
    DetectorPCh1->NFrames = (ET1Stop-ET1Start+ET1Step)/ET1Step;
    DetectorPCh1->initAcquisition();
    for (int i=ET1Start; i<ET1Stop+ET1Step; i+=ET1Step) {
        if (ACQ_RUN_FLAG) {
            ET50->ZCounts = i;
            ET50->tuneWavelength();
            Sleep(MDELAY);
            DetectorPCh1->recordImage();
            XData.push_back(i);
            YData.push_back(DetectorPCh1->MeanCountValue);
            Numbers << i << "," << DetectorPCh1->MeanCountValue << std::endl;
            emit(updateOProgress(100*(i-ET1Start+ET1Step)/(ET1Stop-ET1Start)));
        }
        else {
            DetectorPCh1->finishAcquisition();
            Numbers.close();
            finishAcquisition();
            return;
        }
    }
    emit(plotData(Mode));
    DetectorPCh1->finishAcquisition();
    Numbers.close();
    finishAcquisition();
}

void Acquisition::doET2Profiling()
{
    // Mode specific things
    addLog(std::string("Characterization mode: ET70 transmission profiling"));
    XData.clear();
    YData.clear();
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_ET70trans.csv");
    //
    initAcquisition();
    addLog("Applying detector settings...");
    DetectorPCh1->Mode = Mode;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->prepareAcquisition();
    DetectorPCh1->NFrames = (ET2Stop-ET2Start+ET2Step)/ET2Step;
    DetectorPCh1->initAcquisition();
    for (int i=ET2Start; i<ET2Stop+ET2Step; i+=ET2Step) {
        if (ACQ_RUN_FLAG) {
            ET70->ZCounts = i;
            ET70->tuneWavelength();
            Sleep(MDELAY);
            DetectorPCh1->recordImage();
            XData.push_back(i);
            YData.push_back(DetectorPCh1->MeanCountValue);
            Numbers << i << "," << DetectorPCh1->MeanCountValue << std::endl;
            emit(updateOProgress(100*(i-ET2Start+ET2Step)/(ET2Stop-ET2Start)));
        }
        else {
            DetectorPCh1->finishAcquisition();
            Numbers.close();
            finishAcquisition();
            return;
        }
    }
    emit(plotData(Mode));
    DetectorPCh1->finishAcquisition();
    Numbers.close();
    finishAcquisition();
}

void Acquisition::computeRetardance(int N)
{
    // Function to compute retardance from data assuming NPolarization is even
    // cos(delta) = sum(I'*cos(2*theta))/sum(cos(2*theta)**2) where I' = I/mean(I)-1
    std::vector<double> I, primeI, T1, T2;
    double meanI, sumT1, sumT2, Retard;
    //
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_retard.csv");
    YData.clear();
    for (int i=0; i<N; i++) {
        I.clear();
        for (int j=0; j<NPolarizer; j++) I.push_back(YData2[i*NPolarizer+j]);
        meanI = std::accumulate(I.begin(), I.end(), 0);
        meanI = meanI/NPolarizer;
        for (int j=0; j<NPolarizer; j++) primeI.push_back(meanI/I[j] - 1);
        for (int j=0; j<NPolarizer; j++) {
            T1.push_back(primeI[i]*cos(4*PI*j/NPolarizer));
            T2.push_back(cos(4*PI*j/NPolarizer)*cos(4*PI*j/NPolarizer));
        }
        sumT1 = std::accumulate(T1.begin(), T1.end(), 0);
        sumT2 = std::accumulate(T2.begin(), T2.end(), 0);
        Retard = 180*acos(sumT1/sumT2)/PI;
        YData.push_back(Retard);
        Numbers << XData[i] << "," << Retard << std::endl;
    }
    Numbers.close();
}

void Acquisition::computeRetardance()
{

}


/***
void AcqObservation::addToFITSHeader(fitsfile *FITSFile)
{
    // Acquisition settings
    fits_write_key(FITSFile, TDOUBLE, "ET1STEP", &ET50->ZStep, "Etalon 1 step counts", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ET1ZERO", &ET50->ZZero, "Etalon 1 line center counts", &Error);
    fits_write_key(FITSFile, TUINT, "NWAVES", &ET50->NWavePoints, "Number of wavelength points", &Error);
    fits_write_key(FITSFile, TDOUBLE, "WAVESCAN", &ET50->WaveScanRange, "Wavelength scan range", &Error);
    fits_write_key(FITSFile, TDOUBLE, "AWAVLNTH", &ET50->Wavelength, "Nominal wavelegnth of observation", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ET2STEP", &ET70->ZStep, "Etalon 2 step counts", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ET2ZERO", &ET70->ZZero, "Etalon 2 line center counts", &Error);
    fits_write_key(FITSFile, TUINT, "NACCUM", &LCVRPolarimeter->NAccumulations, "Numbers of frames stacked up", &Error);
    fits_write_key(FITSFile, TSTRING, "FILTER", &LineLabel, "Spectral line ID", &Error);
    fits_write_key(FITSFile, TDOUBLE, "IFWAVE", &FilterCWL, "Interference filter's wavelength", &Error);
    fits_write_key(FITSFile, TDOUBLE, "IFPASS", &FilterFWHM, "Interference filter's passband", &Error);
    fits_write_key(FITSFile, TDOUBLE, "IFTRANS", &FilterTrans, "Interference filter's transmission", &Error);
    fits_write_key(FITSFile, TSTRING, "OBS_MODE", &ModeString, "Mode of data acquisition", &Error);
    // User input data
    fits_write_key(FITSFile, TDOUBLE, "XARCSEC", &DataDetails->XArcsec, "X-coordinate on the disk in arcsec", &Error);
    fits_write_key(FITSFile, TDOUBLE, "YARCSEC", &DataDetails->YArcsec, "Y-coordinate on the disk in arcsec", &Error);
    fits_write_key(FITSFile, TDOUBLE, "PANGLE", &DataDetails->PAngle, "Position angle of the solar equator", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ATMOS_R0", &DataDetails->AtmosR0, "Fried's parameter in cm", &Error);
    fits_write_key(FITSFile, TSTRING, "DATATAGS", &DataDetails->DataTags, "Keywords to describe the data", &Error);
    fits_write_key(FITSFile, TSTRING, "OBSERVER", &DataDetails->Observers, "Names of the observers", &Error);
    fits_write_key(FITSFile, TSTRING, "PLANNER", &DataDetails->Planners, "Names of the planners", &Error);
    // Other settings SOLARNET format
    char* KeysValues;
    char Key[9] = "";
    char Value[33] = "";
    char OtherSettings[2048];
    std::strcpy(OtherSettings, DataDetails->OtherSettings.c_str());
    KeysValues = std::strtok(OtherSettings, " ,=");
    while (KeysValues != NULL) {
        strcpy(Key, KeysValues);
        KeysValues = std::strtok(NULL, " ,=");
        strcpy(Value, KeysValues);
        KeysValues = std::strtok(NULL, " ,=");
        fits_write_key(FITSFile, TSTRING, Key, Value, "Other settings", &Error);
    }
}

void AcqObservation::finishFITS(fitsfile *FITSFile)
{
    // Acquisition settings
    fits_write_key(FITSFile, TDOUBLE, "ET1STEP", &ET50->ZStep, "Etalon 1 step counts", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ET1ZERO", &ET50->ZZero, "Etalon 1 line center counts", &Error);
    fits_write_key(FITSFile, TUINT, "NWAVES", &ET50->NWavePoints, "Number of wavelength points", &Error);
    fits_write_key(FITSFile, TDOUBLE, "WAVESCAN", &ET50->WaveScanRange, "Wavelength scan range", &Error);
    fits_write_key(FITSFile, TDOUBLE, "AWAVLNTH", &ET50->Wavelength, "Nominal wavelegnth of observation", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ET2STEP", &ET70->ZStep, "Etalon 2 step counts", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ET2ZERO", &ET70->ZZero, "Etalon 2 line center counts", &Error);
    fits_write_key(FITSFile, TUINT, "NACCUM", &LCVRPolarimeter->NAccumulations, "Numbers of frames stacked up", &Error);
    fits_write_key(FITSFile, TSTRING, "FILTER", &LineLabel, "Spectral line ID", &Error);
    fits_write_key(FITSFile, TDOUBLE, "IFWAVE", &FilterCWL, "Interference filter's wavelength", &Error);
    fits_write_key(FITSFile, TDOUBLE, "IFPASS", &FilterFWHM, "Interference filter's passband", &Error);
    fits_write_key(FITSFile, TDOUBLE, "IFTRANS", &FilterTrans, "Interference filter's transmission", &Error);
    fits_write_key(FITSFile, TSTRING, "OBS_MODE", &ModeString, "Mode of data acquisition", &Error);
    // User input data
    fits_write_key(FITSFile, TDOUBLE, "XARCSEC", &DataDetails->XArcsec, "X-coordinate on the disk in arcsec", &Error);
    fits_write_key(FITSFile, TDOUBLE, "YARCSEC", &DataDetails->YArcsec, "Y-coordinate on the disk in arcsec", &Error);
    fits_write_key(FITSFile, TDOUBLE, "PANGLE", &DataDetails->PAngle, "Position angle of the solar equator", &Error);
    fits_write_key(FITSFile, TDOUBLE, "ATMOS_R0", &DataDetails->AtmosR0, "Fried's parameter in cm", &Error);
    fits_write_key(FITSFile, TSTRING, "DATATAGS", &DataDetails->DataTags, "Keywords to describe the data", &Error);
    fits_write_key(FITSFile, TSTRING, "OBSERVER", &DataDetails->Observers, "Names of the observers", &Error);
    fits_write_key(FITSFile, TSTRING, "PLANNER", &DataDetails->Planners, "Names of the planners", &Error);
    // Other settings SOLARNET format
    char* KeysValues;
    char Key[9] = "";
    char Value[33] = "";
    char OtherSettings[2048];
    std::strcpy(OtherSettings, DataDetails->OtherSettings.c_str());
    KeysValues = std::strtok(OtherSettings, " ,=");
    while (KeysValues != NULL) {
        strcpy(Key, KeysValues);
        KeysValues = std::strtok(NULL, " ,=");
        strcpy(Value, KeysValues);
        KeysValues = std::strtok(NULL, " ,=");
        fits_write_key(FITSFile, TSTRING, Key, Value, "Other settings", &Error);
    }
    int Timeref;
    char Date;
    fits_get_system_time(&Date, &Timeref, &Error);
    fits_write_key(FITSFile, TSTRING, "DATE-END", &Date, "Date and time of end of observation", &Error);
    fits_close_file(FITSFile, &Error);
}

void AcqObservation::acqScience()
{
    prepareAcquisition();

    ModeString = "Science";
    for (int c=0; c<NScienceCycles; c++) {
        emit(updateCycles(QString::number(c+1) + "/" + QString::number(NScienceCycles)));
        addLog("Starting science observations cycle : " + std::to_string(c+1));
        for (int i=0; i<NLines; i++) {
            // Check if acquisition to be started
            if (ACQ_RUN_FLAG) {
                loadLineSettings(Settings, "Line_"+QString(i+1));
                // Setup pre-filter
                addLog("Moving the pre-filter : " + std::to_string(FilterMatrix->iPreFilter));
                FilterMatrix->selectPreFilter();
                // Setup focus
                addLog(std::string("Adjusting the detector focus..."));
                PolarimeterStages->moveStage1();
                // Setup etalons
                addLog(std::string("Tuning the etalons..."));
                ET50->gotoScanStartPosition();
                ET70->gotoScanStartPosition();
                Sleep(MDELAY);
                // Setup LCVRs
                addLog(std::string("Applying the detector settings and recording frames..."));
                LCVRPolarimeter->setModulation();
                // Setup cameras
                QThread *ThreadCAM1 = new QThread;
                QThread *ThreadCAM2 = new QThread;
                DetectorPCh1->moveToThread(ThreadCAM1);
                DetectorPCh2->moveToThread(ThreadCAM2);
                connect(DetectorBBCh, SIGNAL(scanWavelength()),
                        ET50, SLOT(ScanWavelength()));
                connect(DetectorBBCh, SIGNAL(scanWavelength()),
                        ET70, SLOT(ScanWavelength()));
                connect(ThreadCAM1, SIGNAL(started()),
                        DetectorPCh1, SLOT(acqData()));
                connect(DetectorPCh1, SIGNAL(Finished()),
                        ThreadCAM1, SLOT(deleteLater()));
                connect(ThreadCAM2, SIGNAL(started()),
                        DetectorPCh2, SLOT(acqData()));
                connect(DetectorPCh2, SIGNAL(Finished()),
                        ThreadCAM2, SLOT(deleteLater()));
//                DetectorBBCh->setAcquisition();
//                DetectorPCh1->setAcquisition();
//                DetectorPCh2->setAcquisition();
                //
                ThreadCAM1->start();
                ThreadCAM2->start();
                LCVRPolarimeter->startModulation();
                DetectorBBCh->acqData();
                LCVRPolarimeter->stopModulation();
                // Close data and files
                addToFITSHeader(DetectorBBCh->FITSFile);
                addToFITSHeader(DetectorPCh1->FITSFile);
                addToFITSHeader(DetectorPCh2->FITSFile);
                //
                DetectorBBCh->closeData();
                DetectorPCh1->closeData();
                DetectorPCh2->closeData();
                // Reset etalons if there is an error
                if (!ET50->Operating || !ET70->Operating) {
                    addLog(std::string("Etalon error! resetting both the etalons..."));
                    ET50->resetEtalon();
                    ET70->resetEtalon();
                    addLog("Deleting bad data file : " + DetectorPCh1->FITSFileName);
                    std::remove(DetectorPCh1->FITSFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorPCh2->FITSFileName);
                    std::remove(DetectorPCh2->FITSFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorBBCh->FITSFileName);
                    std::remove(DetectorBBCh->FITSFileName.c_str());
                    i = i-1;
                }
                else {
                    addLog("Frames saved as : " + DetectorPCh1->FITSFileName);
                    addLog("Frames saved as : " + DetectorPCh2->FITSFileName);
                    addLog("Frames saved as : " + DetectorBBCh->FITSFileName);
                    emit(updateProgress(100*(i+1)*(c+1)/NLines/NScienceCycles));
                    emit(updateCycles(QString::number(c+1) + "/" + QString::number(NScienceCycles)));
                }
            }
            // Check if acquisition is to be stopped
            else {
                emit(updateProgress(0));
                emit(updateCycles("0/" + QString::number(NScienceCycles)));
                addLog(std::string("Science observations wrapping up due to interruption."));
                finishAcquisition();
                return;
            }
        }
    }
    emit(updateProgress(0));
    emit(updateCycles("0/" + QString::number(NScienceCycles)));
    addLog(std::string("Science observations completed."));
    finishAcquisition();
}

void AcqObservation::getScienceData()
{
    initAcquisition();
    for (int c=0; c<NCycles; c++) {
        emit(updateOProgress(100*(c+1)/NCycles));
        addLog("Starting science observations cycle : " + std::to_string(c+1));
        for (int i=0; i<NLines; i++) {
            if (ACQ_RUN_FLAG) {
                // Setup components
                loadLineSettings(QString::fromStdString("Line_"+std::to_string(i+1)));
                addLog("Moving the pre-filter: " + std::to_string(FilterMatrix->iPreFilter));
//                FilterMatrix->selectPreFilter();
                addLog("Adjusting the detector focus...");
//                PolarimeterStages->moveStage1();
                addLog("Tuning the etalons...");
//                ET50->gotoScanStartPosition();
//                ET70->gotoScanStartPosition();
                Sleep(LDELAY);
                //
                addLog("Applying the detector settings...");
                int NFramesPerWave = LCVRPolarimeter->NAccumulations*LCVRPolarimeter->NModulations;
                int NFramesPerLine = NFramesPerWave*ET50->NWavePoints;
                int NMissed = 0;
                LCVRPolarimeter->setModulation();
                DetectorBBCh->prepareAcquisition();
                DetectorBBCh->NFrames = NFramesPerLine;
//                CAM1 Threading
                ThreadCAM1 = new QThread();
                DetectorPCh1->NFrames = NFramesPerLine;
                DetectorPCh1->moveToThread(ThreadCAM1);
                connect(ThreadCAM1, SIGNAL(started()),
                        DetectorPCh1, SLOT(saveImages()));
                connect(DetectorPCh1, SIGNAL(Finished()),
                        ThreadCAM1, SLOT(deleteLater()));
                ThreadCAM1->start();
//                CAM2 Threading
                ThreadCAM2 = new QThread();
                DetectorPCh2->NFrames = NFramesPerLine;
                DetectorPCh2->moveToThread(ThreadCAM2);
                connect(ThreadCAM2, SIGNAL(started()),
                        DetectorPCh2, SLOT(saveImages()));
                connect(DetectorPCh2, SIGNAL(Finished()),
                        ThreadCAM2, SLOT(deleteLater()));
                ThreadCAM2->start();
                // This thread
                Sleep(SDELAY);
                addLog("Starting modulation and acquisition...");
                LCVRPolarimeter->startModulation();
                for (int f=0; f<NFramesPerLine; f++) {
                    DetectorBBCh->saveImage();
                    if (f == 0) NMissed = -DetectorBBCh->Image.nframe;
                    if (f == NFramesPerLine-1) NMissed += DetectorBBCh->Image.nframe;
                    if ((f+1)%NFramesPerWave == 1) {
//                        ET50->scanWavelength();
//                        ET70->scanWavelength();
                    }
                    emit(updateProgress(100*(1+f+i*NFramesPerLine)/NFramesPerLine/NLines));
                }
                addLog("Stopping modulation and acquisition...");
                DetectorBBCh->displayImage();
                DetectorBBCh->finishAcquisition();
                LCVRPolarimeter->stopModulation();
                addLog(DetectorBBCh->Label + " frames missed: " + std::to_string(NMissed+1 - NFramesPerLine));
                // Reset etalons if there is an error
                if (!ET50->Operating || !ET70->Operating) {
                    addLog(std::string("Etalon error! resetting both the etalons..."));
//                    ET50->resetEtalon();
//                    ET70->resetEtalon();
                    addLog("Deleting bad data file : " + DetectorPCh1->DATFileName);
                    std::remove(DetectorPCh1->DATFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorPCh2->DATFileName);
                    std::remove(DetectorPCh2->DATFileName.c_str());
                    addLog("Deleting bad data file : " + DetectorBBCh->DATFileName);
                    std::remove(DetectorBBCh->DATFileName.c_str());
                }
            }
            else {
                finishAcquisition();
                return;
            }
        }
    }
    finishAcquisition();
}

void Acquisition::doLCVR1Characterization()
{
    // Mode specific things
    addLog(std::string("Characterization mode: LCVR1 Retardance vs. Voltage profiling"));
    XData.clear();
    YData.clear();
    YData2.clear();
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_LCVR1prof.csv");
    //
    initAcquisition();
    addLog("Applying detector settings...");
    DetectorBBCh->Mode = Mode;
    DetectorPCh1->Mode = Mode;
    DetectorBBCh->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorBBCh->prepareAcquisition();
    DetectorPCh1->prepareAcquisition();
    DetectorBBCh->NFrames = DetectorPCh1->NFrames = NPolarizer*(LCVR1Stop-LCVR1Start+LCVR1Step)/LCVR1Step;
    DetectorBBCh->initAcquisition();
    DetectorPCh1->initAcquisition();
    //
    for (int i=0; i<NPolarizer; i++) {
        CWPMount->Position = 360.0*i/NPolarizer;
        CWPMount->movePosition();
        Sleep(50000.0/NPolarizer);
        emit(updateOProgress(100*(i+1)/NPolarizer));
        for (int v=LCVR1Start; v<LCVR1Stop+LCVR1Step; v+=LCVR1Step) {
            if (ACQ_RUN_FLAG) {
                LCVRPolarimeter->LCVR1Voltage = v;
                LCVRPolarimeter->setLCVR1Voltage();
                Sleep(SDELAY);
                DetectorBBCh->recordImage();
                DetectorPCh1->recordImage();
                YData2.push_back(1.0*DetectorPCh1->MeanCountValue/DetectorBBCh->MeanCountValue);
                Numbers << CWPMount->Position << "," << v << "," << DetectorPCh1->MeanCountValue << "," <<
                           DetectorBBCh->MeanCountValue << std::endl;
                emit(updateProgress(100*(v-LCVR1Start+LCVR1Step)/(LCVR1Stop-LCVR1Start)));
            }
            else {
                DetectorBBCh->finishAcquisition();
                DetectorPCh1->finishAcquisition();
                Numbers.close();
                finishAcquisition();
                return;
            }
        }
    }
    DetectorBBCh->finishAcquisition();
    DetectorPCh1->finishAcquisition();
    //
    for (int v=LCVR1Start; v<LCVR1Stop+LCVR1Step; v+=LCVR1Step) XData.push_back(v);
//    computeRetardance((LCVR1Stop-LCVR1Start+LCVR1Step)/LCVR1Step);
    computeRetardance();
    emit(plotData(Mode));
    Numbers.close();
    finishAcquisition();
}

void Acquisition::doLCVR2Characterization()
{
    // Mode specific things
    addLog(std::string("Characterization mode: LCVR1 Retardance vs. Voltage profiling"));
    XData.clear();
    YData.clear();
    YData2.clear();
    std::ofstream Numbers(AutoSaveSubDir + "/HELLRIDE_" + getDateTimeStringNow() + "_LCVR2prof.csv");
    //
    initAcquisition();
    addLog("Applying detector settings...");
    DetectorBBCh->Mode = Mode;
    DetectorPCh1->Mode = Mode;
    DetectorBBCh->AutoSaveDir = AutoSaveSubDir;
    DetectorPCh1->AutoSaveDir = AutoSaveSubDir;
    DetectorBBCh->prepareAcquisition();
    DetectorPCh1->prepareAcquisition();
    DetectorBBCh->NFrames = DetectorPCh1->NFrames = NPolarizer*(LCVR2Stop-LCVR2Start+LCVR2Step)/LCVR2Step;
    DetectorBBCh->initAcquisition();
    DetectorPCh1->initAcquisition();
    //
    for (int i=0; i<NPolarizer; i++) {
        CWPMount->Position = 360.0*i/NPolarizer;
        CWPMount->movePosition();
        Sleep(50000.0/NPolarizer);
        emit(updateOProgress(100*(i+1)/NPolarizer));
        for (int v=LCVR2Start; v<LCVR2Stop+LCVR2Step; v+=LCVR2Step) {
            if (ACQ_RUN_FLAG) {
                LCVRPolarimeter->LCVR2Voltage = v;
                LCVRPolarimeter->setLCVR2Voltage();
                Sleep(SDELAY);
                DetectorBBCh->recordImage();
                DetectorPCh1->recordImage();
                YData2.push_back(1.0*DetectorPCh1->MeanCountValue/DetectorBBCh->MeanCountValue);
                Numbers << CWPMount->Position << "," << v << "," << DetectorPCh1->MeanCountValue << "," <<
                           DetectorBBCh->MeanCountValue << std::endl;
                emit(updateProgress(100*(v-LCVR2Start+LCVR2Step)/(LCVR2Stop-LCVR2Start)));
            }
            else {
                DetectorBBCh->finishAcquisition();
                DetectorPCh1->finishAcquisition();
                Numbers.close();
                finishAcquisition();
                return;
            }
        }
    }
    DetectorBBCh->finishAcquisition();
    DetectorPCh1->finishAcquisition();
    //
    for (int v=LCVR2Start; v<LCVR2Stop+LCVR2Step; v+=LCVR2Step) XData.push_back(v);
//    computeRetardance((LCVR2Stop-LCVR2Start+LCVR2Step)/LCVR2Step);
    emit(plotData(Mode));
    Numbers.close();
    finishAcquisition();
}
***/
