#include "polarimeter.h"

Polarimeter::Polarimeter(QObject *parent) : QObject(parent){
}

Polarimeter::~Polarimeter() {
    USBDRVD_PipeClose(Pipe0);
    USBDRVD_PipeClose(Pipe1);
    USBDRVD_CloseDevice(LCVRController);
    addLog("successfully closed.");
}

void Polarimeter::initPolarimeter(QString Name)
{
    Label = Settings->value(Name + "/Label").toString().toStdString();
    TNEHighVoltage = Settings->value(Name + "/TNEHighVoltage").toInt();
    TNELowVoltage = Settings->value(Name + "/TNELowVoltage").toInt();
    TNETime = Settings->value(Name + "/TNETime").toInt();
    SwitchingTime = Settings->value(Name + "/SwitchingTime").toInt();
    StateTime = Settings->value(Name + "/StateTime").toInt();
    TriggerTime = Settings->value(Name + "/TriggerTime").toInt();
    SyncDuration = Settings->value(Name + "/SyncDuration").toInt();
    Temperature = Settings->value(Name + "/Temperature").toDouble();
    initLCVRController();
    setTemperature();
}

void Polarimeter::initLCVRController()
{
    UINT DeviceCount;
    UINT USB_PID = 0x139C;
    GUID theGUID;
    theGUID.Data1 = 0xa22b5b8b;
    theGUID.Data2 = 0xc670;
    theGUID.Data3 = 0x4198;
    theGUID.Data4 [0] = 0x93;
    theGUID.Data4 [1] = 0x85;
    theGUID.Data4 [2] = 0xaa;
    theGUID.Data4 [3] = 0xba;
    theGUID.Data4 [4] = 0x9d;
    theGUID.Data4 [5] = 0xfc;
    theGUID.Data4 [6] = 0x7d;
    theGUID.Data4 [7] = 0x2b;
    // Get device count
    DeviceCount = USBDRVD_GetDevCount(USB_PID);
    if (DeviceCount == 0) {
        addLog(std::string("controller cannot be found!"));
        Error = -1;
    }
    else {
        LCVRController = USBDRVD_OpenDevice (1, LCVR_FLAGS_ATTRS, USB_PID);
        Pipe0 = USBDRVD_PipeOpen (1, 0, LCVR_FLAGS_ATTRS, &theGUID);
        Pipe1 = USBDRVD_PipeOpen (1, 1, LCVR_FLAGS_ATTRS, &theGUID);
        addLog(std::string("controller successfully opened."));
    }
}

void Polarimeter::setModulation()
{
    std::vector<std::string> V1;
    std::vector<std::string> V2;
    std::vector<std::string> T;

    for (unsigned int i=0; i<NModulations; i++) {
        if (i == 0) {
            if (LCVR1Voltages[i] < LCVR1Voltages[NModulations-1])
                V1.push_back(std::to_string(TNELowVoltage));
            else if (LCVR1Voltages[i] > LCVR1Voltages[NModulations-1])
                V1.push_back(std::to_string(TNEHighVoltage));
            else V1.push_back(std::to_string(LCVR1Voltages[i]));
            //
            if (LCVR2Voltages[i] < LCVR2Voltages[NModulations-1])
                V2.push_back(std::to_string(TNELowVoltage));
            else if (LCVR2Voltages[i] > LCVR2Voltages[NModulations-1])
                V2.push_back(std::to_string(TNEHighVoltage));
            else V2.push_back(std::to_string(LCVR2Voltages[i]));
            //
            T.push_back(std::to_string(TNETime));
        }
        else {
            if (LCVR1Voltages[i] < LCVR1Voltages[i-1])
                V1.push_back(std::to_string(TNELowVoltage));
            else if (LCVR1Voltages[i] > LCVR1Voltages[i-1])
                V1.push_back(std::to_string(TNEHighVoltage));
            else V1.push_back(std::to_string(LCVR1Voltages[i]));
            //
            if (LCVR2Voltages[i] < LCVR2Voltages[i-1])
                V2.push_back(std::to_string(TNELowVoltage));
            else if (LCVR2Voltages[i] > LCVR2Voltages[i-1])
                V2.push_back(std::to_string(TNEHighVoltage));
            else V2.push_back(std::to_string(LCVR2Voltages[i]));
            //
            T.push_back(std::to_string(TNETime));
        }
        V1.push_back(std::to_string(LCVR1Voltages[i]));
        V2.push_back(std::to_string(LCVR2Voltages[i]));
        T.push_back(std::to_string(StateTime - TNETime));
    }
    for (int i=0; i<(2*NModulations); i++) {
        addLog("State " + std::to_string(i+1) + " : " +
               V1[i] + " V, " + V2[i] + " mV, " + T[i] + " ms.");
        Command = "stv:" + std::to_string(i+1) + "," + V1[i] + "," + V2[i];
        sendCommand();
        Command = "stt:" + std::to_string(i+1) + "," + T[i];
        sendCommand();
    }
    Command = "syncd:" + std::to_string(SyncDuration);
    sendCommand();
}

void Polarimeter::setDummyModulation()
{
    std::vector<std::string> V1;
    std::vector<std::string> V2;
    std::vector<std::string> T;
    Command = "stv:1," + std::to_string(Vzero1+10) + "," + std::to_string(Vzero2+10);
    sendCommand();
    Command = "stv:2," + std::to_string(Vzero1) + "," + std::to_string(Vzero2);
    sendCommand();
    Command = "stt:1," + std::to_string(TNETime);
    sendCommand();
    Command = "stt:2," + std::to_string(StateTime-TNETime);
    sendCommand();
    for (int i=3; i<17; i++) {
        Command = "stt:" + std::to_string(i) + ",0";
        sendCommand();
    }

//    for (unsigned int i=0; i<NModulations; i++) {
//        V1.push_back(std::to_string(Vzero1+10));
//        V2.push_back(std::to_string(Vzero2+10));
//        T.push_back(std::to_string(TNETime));
//        V1.push_back(std::to_string(Vzero1));
//        V2.push_back(std::to_string(Vzero2));
//        T.push_back(std::to_string(StateTime - TNETime));
//    }
//    for (int i=0; i<(2*NModulations); i++) {
//        addLog("State " + std::to_string(i+1) + " : " +
//               V1[i] + " V, " + V2[i] + " mV, " + T[i] + " ms.");
//        Command = "stv:" + std::to_string(i+1) + "," + V1[i] + "," + V2[i];
//        sendCommand();
//        Command = "stt:" + std::to_string(i+1) + "," + T[i];
//        sendCommand();
//    }
    Command = "syncd:" + std::to_string(SyncDuration);
    sendCommand();
}

void Polarimeter::setModulation(bool POLARIMETRY)
{
    if (POLARIMETRY) setModulation();
    else setDummyModulation();
}


void Polarimeter::startModulation()
{
    Command = "cycl:1";
    sendCommand();
}

void Polarimeter::stopModulation()
{
    Command = "cycl:0";
    sendCommand();
}

void Polarimeter::setTemperature()
{
    int Count;
    double Temp, Temper;
    Count = int(65535*(Temperature+273.15)/500);
    //
    Command = "tmp:1," + std::to_string(Count);
    sendCommand();
    if (Response.find("tmp") != std::string::npos) {
        Temp = std::stoi(Response.substr(6,5));
        Temper = 500.0*Temp/65535 - 273.15;
        addLog("current temperature-1: " + std::to_string(Temper));
    }
    //
    Command = "tmp:2," + std::to_string(Count);
    sendCommand();
    if (Response.find("tmp") != std::string::npos) {
        Temp = std::stoi(Response.substr(6,5));
        Temper = 500.0*Temp/65535 - 273.15;
        addLog("current temperature-2: " + std::to_string(Temper));
    }
    //
    addLog("temperature setpoint: " + std::to_string(Temperature));
}

void Polarimeter::setVoltages()
{
    setLCVR1Voltage();
    setLCVR2Voltage();
}

void Polarimeter::setLCVR1Voltage()
{
    Command = "inv:1," + std::to_string(LCVR1Voltage);
    sendCommand();
}

void Polarimeter::setLCVR2Voltage()
{
    Command = "inv:2," + std::to_string(LCVR2Voltage);
    sendCommand();
}

void Polarimeter::sendCommand()
{
    addLog("controller command sent: " + Command);
    Command = Command + "\r";
    unsigned char chrCommand[64];
    unsigned char chrResponse[64];
    std::stringstream ssResponse;
    strcpy(reinterpret_cast<char*>(chrCommand), Command.c_str());
    USBDRVD_BulkWrite(LCVRController, 1, chrCommand, sizeof (chrCommand));
    USBDRVD_BulkRead(LCVRController, 0, chrResponse, sizeof (chrResponse));
    for (int i = 0; chrResponse[i] != '\r'; i++) ssResponse << chrResponse[i];
    ssResponse >> Response ;
    addLog("controller response received: " + Response);
    Sleep(XSDELAY);
}

void Polarimeter::addLog(std::string Log) {
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void Polarimeter::addLog(const char* Log)
{
//    std::cout << Log << std::endl;
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}
