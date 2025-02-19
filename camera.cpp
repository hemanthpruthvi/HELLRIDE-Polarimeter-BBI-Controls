#include "camera.h"

Camera::Camera(QObject *parent) : QObject(parent)
{
    Error = 0;
    Binning = 2;
    ROIHeight = ROIWidth = 1024;
    ROILeft = ROITop = 0;
    Trigger = XI_TRG_OFF;
    TriggerDelay = 10000;
    BufferSize = 512;
}

Camera::~Camera()
{
    handleError(xiCloseDevice(Detector), "closing detector");
    if (Error == XI_OK) addLog("closed successfully");
}

void Camera::initDetector(QString Name)
{
    Index = Settings->value(Name + "/Index").toInt();
    Label = Settings->value(Name + "/Label").toString().toStdString();
    MakeModel = Settings->value(Name + "/MakeModel").toString().toStdString();
    SerialNumber = Settings->value(Name + "/SerialNumber").toString().toStdString();
    FileNameCameraSuffix = Settings->value(Name + "/FileNameCameraSuffix").toString().toStdString();
    ExposureTime = Settings->value(Name + "/ExposureTime").toInt();
    BufferSize = Settings->value(Name + "/BufferSize").toInt();
    TriggerDelay = Settings->value(Name + "/TriggerDelay").toInt();
    Binning = Settings->value(Name + "/Binning").toInt();
    ROI = Settings->value(Name = "/ROI").toInt();
    // Initialize camera and general settings
    handleError(xiOpenDeviceBy(XI_OPEN_BY_SN, SerialNumber.c_str(), &Detector), "opening camera");
    if (Error) return;
    else addLog("opened successfully");
    handleError(xiSetParamInt(Detector, XI_PRM_DEBUG_LEVEL, XI_DL_FATAL), "setting debug level");
    handleError(xiSetParamInt(Detector, XI_PRM_SHUTTER_TYPE, XI_SHUTTER_GLOBAL), "setting global shutter");
//    handleError(xiSetParamInt(Detector, XI_PRM_OUTPUT_DATA_PACKING, XI_ON), "setting data packing");
    handleError(xiSetParamInt(Detector, XI_PRM_IMAGE_DATA_FORMAT, XI_RAW16), "setting data format");
    // Set exposure time and ROI
    handleError(xiSetParamInt(Detector, XI_PRM_EXPOSURE, ExposureTime), "setting exposure time");
    MainThread = QThread::currentThread();
    //
}

void Camera::prepareLive(bool SAVE_IMAGE_FLAG_)
{
    Mode = LIVE_MODE_CAM;
    prepareAcquisition();
    //
    memset(&Image, 0, sizeof(Image));
    Image.size = sizeof(XI_IMG);
    handleError(xiStartAcquisition(Detector), "starting acquisition");
    if (Error == XI_OK) addLog("started acquisition");
    if (SAVE_IMAGE_FLAG_) initData();
}

void Camera::prepareAcquisition() {
    //
    handleError(xiSetParamInt(Detector, XI_PRM_EXPOSURE, ExposureTime), "setting exposure time");
    handleError(xiSetParamInt(Detector, XI_PRM_BINNING_SELECTOR, XI_BIN_SELECT_HOST_CPU), "setting binning selector");
    ROIHeight = ROIWidth = ROI;
    ROILeft = (FULL_WIDTH/Binning - ROIWidth)/2;
    ROITop = (FULL_HEIGHT/Binning - ROIHeight)/2;
    addLog("frame description: " + std::to_string(ROIWidth) + "x" + std::to_string(ROIHeight) +
           " - " + std::to_string(ROILeft) + "||" + std::to_string(ROITop) +
           " (" + std::to_string(Binning) + "x" + std::to_string(Binning) + ")");
    //
    handleError(xiSetParamInt(Detector, XI_PRM_BINNING_HORIZONTAL, Binning), "setting x-binning");
    handleError(xiSetParamInt(Detector, XI_PRM_BINNING_VERTICAL, Binning), "setting y-binning");
    handleError(xiSetParamInt(Detector, XI_PRM_WIDTH, ROIWidth), "setting ROI width");
    handleError(xiSetParamInt(Detector, XI_PRM_HEIGHT, ROIHeight), "setting ROI height");
    handleError(xiSetParamInt(Detector, XI_PRM_OFFSET_X, ROILeft), "setting ROI x-offset");
    handleError(xiSetParamInt(Detector, XI_PRM_OFFSET_Y, ROITop), "setting ROI y-offset");
    //
    handleError(xiSetParamInt(Detector, XI_PRM_BINNING_HORIZONTAL, Binning), "setting x-binning");
    handleError(xiSetParamInt(Detector, XI_PRM_BINNING_VERTICAL, Binning), "setting y-binning");
    handleError(xiSetParamInt(Detector, XI_PRM_WIDTH, ROIWidth), "setting ROI width");
    handleError(xiSetParamInt(Detector, XI_PRM_HEIGHT, ROIHeight), "setting ROI height");
    handleError(xiSetParamInt(Detector, XI_PRM_OFFSET_X, ROILeft), "setting ROI x-offset");
    handleError(xiSetParamInt(Detector, XI_PRM_OFFSET_Y, ROITop), "setting ROI y-offset");
    //
    handleError(xiGetParamInt(Detector, XI_PRM_BINNING_HORIZONTAL, &Binning), "getting x-binning");
    handleError(xiGetParamInt(Detector, XI_PRM_BINNING_VERTICAL, &Binning), "getting y-binning");
    handleError(xiGetParamInt(Detector, XI_PRM_WIDTH, &ROIWidth), "getting ROI width");
    handleError(xiGetParamInt(Detector, XI_PRM_HEIGHT, &ROIHeight), "getting ROI height");
    handleError(xiGetParamInt(Detector, XI_PRM_OFFSET_X, &ROILeft), "getting ROI x-offset");
    handleError(xiGetParamInt(Detector, XI_PRM_OFFSET_Y, &ROITop), "getting ROI y-offset");
    //
    addLog("exposure time is set to " + std::to_string(ExposureTime));
    addLog("frame binning is set to " + std::to_string(Binning));
    addLog("frame width is set to " + std::to_string(ROIWidth));
    addLog("frame height is set to " + std::to_string(ROIHeight));
    addLog("frame x-offset is set to " + std::to_string(ROILeft));
    addLog("frame y-offset is set to " + std::to_string(ROITop));
    NPixel = ROIHeight*ROIWidth;
    // Set aside RAM for circular buffer
    if (Mode==OBS_MODE_SCIE || Mode==OBS_MODE_FLAT || Mode==OBS_MODE_PCAL) {
        handleError(xiSetParamInt(Detector, XI_PRM_BUFFER_POLICY, XI_BP_UNSAFE), "setting buffer policy");
        handleError(xiSetParamInt(Detector, XI_PRM_ACQ_BUFFER_SIZE_UNIT, 1024*1024), "setting acquisition buffer size unit");
        handleError(xiSetParamInt(Detector, XI_PRM_ACQ_BUFFER_SIZE, BufferSize), "setting acquisition buffer size");
        Trigger = XI_TRG_EDGE_RISING;
    }
    else if (Mode==LIVE_MODE_CAM) {
    }
    else {
        handleError(xiSetParamInt(Detector, XI_PRM_BUFFER_POLICY, XI_BP_UNSAFE), "setting buffer policy");
        handleError(xiSetParamInt(Detector, XI_PRM_ACQ_BUFFER_SIZE_UNIT, 1024*1024), "setting acquisition buffer size unit");
        handleError(xiSetParamInt(Detector, XI_PRM_ACQ_BUFFER_SIZE, 256), "setting acquisition buffer size");
        Trigger = XI_TRG_OFF;
    }
    int BufferQueueSize = 0;
    handleError(xiGetParamInt(Detector, XI_PRM_BUFFERS_QUEUE_SIZE XI_PRM_INFO_MAX, &BufferQueueSize), "getting maximum buffer queue size");
    handleError(xiSetParamInt(Detector, XI_PRM_BUFFERS_QUEUE_SIZE, BufferQueueSize), "setting buffer queue size");
    addLog("buffer queue size set to " + std::to_string(BufferQueueSize) + " frames");
    setupTrigger();
}

void Camera::initAcquisition() {
    if (!QDir(QString::fromStdString(AutoSaveDir)).exists()) {
        QDir().mkdir(QString::fromStdString(AutoSaveDir));
        addLog("creating directory: " + AutoSaveDir);
    }
    switch(Mode) {
    case OBS_MODE_SCIE:
        FileNameModeSuffix = OBS_MODE_SCIE_SUFF;
        break;
    case OBS_MODE_FLAT:
        FileNameModeSuffix = OBS_MODE_FLAT_SUFF;
        break;
    case OBS_MODE_PCAL:
        FileNameModeSuffix = OBS_MODE_PCAL_SUFF;
        break;
    case OBS_MODE_DARK:
        FileNameModeSuffix = OBS_MODE_DARK_SUFF;
        break;
    case OBS_MODE_TARG:
        FileNameModeSuffix = OBS_MODE_TARG_SUFF;
        break;
    case OBS_MODE_PINH:
        FileNameModeSuffix = OBS_MODE_PINH_SUFF;
        break;
    case CHR_MODE_ET1_MATCH:
        FileNameModeSuffix = CHR_MODE_ET1_MATCH_SUFF;
        break;
    case CHR_MODE_ET2_MATCH:
        FileNameModeSuffix = CHR_MODE_ET2_MATCH_SUFF;
        break;
    case CHR_MODE_LINE_PROF:
        FileNameModeSuffix = CHR_MODE_LINE_PROF_SUFF;
        break;
    case CHR_MODE_CAM_FOCUS:
        FileNameModeSuffix = CHR_MODE_CAM_FOCUS_SUFF;
        break;
    case CHR_MODE_LCVR1_PROF:
        FileNameModeSuffix = CHR_MODE_LCVR1_PROF_SUFF;
        break;
    case CHR_MODE_LCVR2_PROF:
        FileNameModeSuffix = CHR_MODE_LCVR2_PROF_SUFF;
        break;
    case CHR_MODE_ET1_PROF:
        FileNameModeSuffix = CHR_MODE_ET1_PROF_SUFF;
        break;
    case CHR_MODE_ET2_PROF:
        FileNameModeSuffix = CHR_MODE_ET2_PROF_SUFF;
        break;
    default:
        FileNameModeSuffix = "";
        break;
    }
    //
    memset(&Image, 0, sizeof(Image));
    Image.size = sizeof(XI_IMG);
    handleError(xiStartAcquisition(Detector), "starting acquisition");
    if (Error == XI_OK) addLog("started acquisition");
    else return;
    //
    std::string DateTimeString = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmsszzz").toStdString();
    initData();
}

void Camera::viewImage() {
    handleError(xiGetImage(Detector, CAMERA_TIMEOUT, &Image), "getting image");
    if (Error != XI_OK) return;
    displayImage();
}

void Camera::saveImage() {
    handleError(xiGetImage(Detector, CAMERA_TIMEOUT, &Image), "getting image");
    if (Error != XI_OK) return;
    DATFile.write(static_cast<char*>(Image.bp), Image.bp_size);
//    fits_write_img(FITSFile, TUSHORT, 1+iFrames*NPixel, static_cast<long>(NPixel), Image.bp, &Error);
    iFrames++;
}

void Camera::recordImage() {
    handleError(xiGetImage(Detector, CAMERA_TIMEOUT, &Image), "getting image");
    if (Error != XI_OK) return;
    addLog("acquired image(#" + std::to_string(Image.nframe) + "): " + std::to_string(iFrames));
    DATFile.write(static_cast<char*>(Image.bp), Image.bp_size);
//    fits_write_img(FITSFile, TUSHORT, 1+iFrames*NPixel, static_cast<long>(NPixel), Image.bp, &Error);
    iFrames++;
    displayImage();
}

void Camera::saveImages() {
    prepareAcquisition();
    int NMissed = 0;
    for (int i=0; i<NFrames; i++) {
        saveImage();
        if (i == 0) NMissed = -Image.nframe;
        if (i == NFrames-1) NMissed += Image.nframe;
    }
    displayImage();
    finishAcquisition();
    addLog(Label + " frames missed: " + std::to_string(NMissed+1 - NFrames));
//    moveToThread(ThreadAcquisition);
    emit(Finished());
}

void Camera::startLive()
{
    ACQ_RUN_FLAG = true;
    prepareLive(SAVE_IMAGE_FLAG);
    while (ACQ_RUN_FLAG) {
        if (Trigger == XI_TRG_SOFTWARE) handleError(xiSetParamInt(Detector, XI_PRM_TRG_SOFTWARE, 1), "sending software trigger");
        handleError(xiGetImage(Detector, CAMERA_TIMEOUT, &Image), "getting image");
        addLog("acquired image #" + std::to_string(Image.nframe));
        if (SAVE_IMAGE_FLAG) {
            DATFile.write((char*)Image.bp, Image.bp_size);
//            fits_write_img(FITSFile, TUSHORT, 1+iFrames*NPixel, static_cast<long>(NPixel), Image.bp, &Error);
            iFrames++;
        }
        displayImage();
        emit(displayImage(DisplayPixmap, MaxCountValue, MeanCountValue, MinCountValue));
    }
    if (SAVE_IMAGE_FLAG) closeData();
    finishAcquisition();
    moveToThread(MainThread);
    emit(Finished());
}

void Camera::stopAcquisition()
{
    ACQ_RUN_FLAG = false;
}

void Camera::finishAcquisition()
{
    handleError(xiStopAcquisition(Detector), "stopping acquisition");
    if (Error == XI_OK) addLog("stopped acquisition");
    closeData();
}

void Camera::setupTrigger()
{
    if (Trigger == XI_TRG_EDGE_RISING || Trigger == XI_TRG_EDGE_FALLING) {
        handleError(xiSetParamInt(Detector, XI_PRM_GPI_SELECTOR,  XI_GPI_PORT1), "selecting GP input");
        handleError(xiSetParamInt(Detector, XI_PRM_GPI_MODE, XI_GPI_TRIGGER), "setting GPI mode to trigger");
        handleError(xiSetParamInt(Detector, XI_PRM_TRG_SOURCE, Trigger), "setting trigger source");
        handleError(xiSetParamInt(Detector, XI_PRM_TRG_SELECTOR, XI_TRG_SEL_FRAME_START), "setting trigger function");
        handleError(xiSetParamInt(Detector, XI_PRM_TRG_DELAY, TriggerDelay), "setting trigger delay");
        handleError(xiSetParamInt(Detector, XI_PRM_RECENT_FRAME, XI_ON), "setting recent frame");
        int TriggerDelayTemp;
        handleError(xiGetParamInt(Detector, XI_PRM_TRG_DELAY, &TriggerDelayTemp), "getting trigger delay");
        addLog("trigger delay set to: " + std::to_string(TriggerDelayTemp));
    }
    else {
        handleError(xiSetParamInt(Detector, XI_PRM_TRG_SOURCE, Trigger), "setting trigger source");
        handleError(xiSetParamInt(Detector, XI_PRM_RECENT_FRAME, XI_ON), "setting recent frame");

    }
    addLog("setting up trigger: " + std::to_string(Trigger));
}

void Camera::prepareImageDisplay()
{
    //
    uint8_t *Image8 = new uint8_t[2*NPixel];
    uint16_t *Image16 = new uint16_t[NPixel];
    QImage DisplayImage;
    //
    std::memcpy(Image16, Image.bp, NPixel*sizeof(uint16_t));
    MinCountValue = *std::min_element(Image16, Image16+NPixel);
    MaxCountValue = *std::max_element(Image16, Image16+NPixel);
    MeanCountValue = std::accumulate(Image16, Image16+NPixel, 0)/NPixel;
    //
    double Norm = 65535.0/MaxCountValue;
    for (int i=0; i<NPixel; i++) Image16[i] = (uint16_t)(Norm*Image16[i]);
    std::memcpy(Image8, Image16, NPixel*sizeof(uint16_t));
    //
    DisplayImage =  QImage(Image8, ROIWidth, ROIHeight, QImage::Format_Grayscale16);
    DisplayPixmap = QPixmap::fromImage(DisplayImage).scaledToWidth(800);
    //
    delete [] Image8;
    delete [] Image16;
}

void Camera::displayPixmap()
{
    emit(displayImage(DisplayPixmap, MinCountValue, MeanCountValue, MaxCountValue));
}

void Camera::displayImage()
{
    prepareImageDisplay();
    displayPixmap();
}


void Camera::handleError(int Err, std::string Message)
{
    Error = Err;
    if (Err != XI_OK) addLog("error " + Message + " (" + std::to_string(Error) + ")");
//    else addLog("successfully " + Message + " (" + std::to_string(Error) + ")");
}

void Camera::addLog(std::string Log)
{
//    std::cout << Log << std::endl;
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void Camera::addLog(const char* Log)
{
//    std::cout << Log << std::endl;
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void Camera::initData()
{
    ImageShape[0] = ROIWidth;
    ImageShape[1] = ROIHeight;
    ImageShape[2] = NFrames;
    iFrames = 0;
//    FITSFileName =  AutoSaveDir + "/HELLRIDE_" +
//                    FileNameCameraSuffix + "_" +
//                    getDateTimeStringNow() + "_" +
//                    FileNameModeSuffix + ".FITS";
//    char FileName[1024];
//    strcpy(FileName, FITSFileName.c_str());
//    addLog("creating file : " + FITSFileName);
//    FITSFile = new fitsfile();
//    fits_create_file(&FITSFile, FileName, &Error);
//    handleError(Error, "creating " + Label + " camera FITS file");
//    fits_create_img(FITSFile,  TUSHORT, 3, ImageShape, &Error);
//    handleError(Error, "creating " + Label + " camera FITS image");
//    //
//    int Timeref;
//    char Date;
//    double WaveUnit = 10;
//    fits_get_system_time(&Date, &Timeref, &Error);
//    fits_write_key(FITSFile, TSTRING, "DATE-BEG", &Date, "Date and time of beginning of observation", &Error);
//    fits_write_key(FITSFile, TSTRING, "DATE-OBS", &Date, "Same as DATE_BEG, for other compliances", &Error);
//    fits_write_key(FITSFile, TSTRING, "OBSRVTRY", &Observatory, "Observatory name ", &Error);
//    fits_write_key(FITSFile, TSTRING, "TELESCOP", &Telescope, "Telescope name", &Error);
//    fits_write_key(FITSFile, TSTRING, "INSTRUME", &Instrument, "Instrument name", &Error);
//    fits_write_key(FITSFile, TSTRING, "DETECTOR", &MakeModel, "Detector make and model", &Error);
//    fits_write_key(FITSFile, TINT, "TEXPOSUR", &ExposureTime, "Exposure time in micro-seconds", &Error);
//    fits_write_key(FITSFile, TDOUBLE, "WAVEUNIT", &WaveUnit, "Wavelength uint (Angstrom)", &Error);
    //
    DATFileName = AutoSaveDir + "/HELLRIDE_" +
                    FileNameCameraSuffix + "_" +
                    getDateTimeStringNow() + "_" +
                    FileNameModeSuffix + ".DAT";
    DATFile.open(DATFileName, std::ios::out | std::ios::binary);
    addLog("creating file : " + DATFileName);
}

void Camera::closeData()
{
//    int Timeref;
//    char Date;
//    fits_get_system_time(&Date, &Timeref, &Error);
//    fits_write_key(FITSFile, TSTRING, "DATE-END", &Date, "Date and time of end of observation", &Error);
//    fits_close_file(FITSFile, &Error);
//    handleError(Error, "closing FITS file");
//    addLog("Frames saved as: " + FITSFileName);
    if (DATFile.is_open()) {
        DATFile.close();
        addLog("Frames saved as: " + DATFileName);
    }
}
