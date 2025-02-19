#include "vtt.h"

VTT::VTT(QObject *parent) : QObject(parent)
{

}

VTT::~VTT()
{
    powerICUMotors(OFF);
    addLog("closing connection.");
    TCPSocket->close();
};

void VTT::initVTT(QString Name)
{
    Label = Settings->value(Name + "/Label").toString().toStdString();
    TCPHostName = Settings->value(Name + "/TCPHostName").toString();
    TCPPortNumber = Settings->value(Name + "/TCPPortNumber").toUInt();
    ICUStage = new CANDevice(Name + "/ICUStage");
    ICUPolarizer = new CANDevice(Name + "/ICUPolarizer");
    ICURetarder = new CANDevice(Name + "/ICURetarder");
    //
    TCPSocket = new QTcpSocket(this);
    addLog("connecting (" + TCPHostName.toStdString() + ":" + std::to_string(TCPPortNumber) + ")." );
    TCPSocket->connectToHost(TCPHostName, TCPPortNumber);
    if(!TCPSocket->waitForConnected(5000)) {
        handleError(TCPSocket->error(), "connecting to device");
    }
    else {
        connect(TCPSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        powerICUMotors(ON);
        Error = SUCCESS;
    }
    return;
}

void VTT::powerICUMotors(bool Power)
{
    if (Power) {
        Command = ICUStage->onCommand();
        sendCommand();
        Command = ICUPolarizer->onCommand();
        sendCommand();
        Command = ICURetarder->onCommand();
        sendCommand();
    }
    else {
        Command = ICUStage->offCommand();
        sendCommand();
        Command = ICUPolarizer->offCommand();
        sendCommand();
        Command = ICURetarder->offCommand();
        sendCommand();
    }
}

void VTT::resetICUMotors()
{
    Command = ICUStage->clearErrorCommand();
    sendCommand();
    Sleep(MDELAY);
    sendCommand();
    Sleep(MDELAY);
    sendCommand();
    Sleep(MDELAY);
    //
    Command = ICUPolarizer->clearErrorCommand();
    sendCommand();
    Sleep(MDELAY);
    sendCommand();
    Sleep(MDELAY);
    sendCommand();
    Sleep(MDELAY);
    //
    Command = ICURetarder->clearErrorCommand();
    sendCommand();
    Sleep(MDELAY);
    sendCommand();
    Sleep(MDELAY);
    sendCommand();
    Sleep(MDELAY);
    //
    powerICUMotors(false);
    Sleep(LDELAY);
    powerICUMotors(true);
    //
    ICUStage->ERR = ICUStage->RUNNING = false;
    ICUPolarizer->ERR = ICUPolarizer->RUNNING = false;
    ICURetarder->ERR = ICURetarder->RUNNING = false;
}

void VTT::homeICU()
{
    Command = ICUStage->homeCommand();
    sendCommand();
    waitForIt();
    Command = ICUPolarizer->homeCommand();
    sendCommand();
    waitForIt();
    Command = ICURetarder->homeCommand();
    sendCommand();
    waitForIt();
}

void VTT::getICUPolarizerPosition()
{
    Command = ICUPolarizer->positionCommand();
    sendCommand();
    waitForIt();
}
void VTT::getICURetarderPosition()
{
    Command = ICURetarder->positionCommand();
    sendCommand();
    waitForIt();
}

void VTT::insertICU()
{
    ICUStage->Position = ICUStage->InPosition;
    Command = ICUStage->moveCommand();
    sendCommand();
    waitForIt();
}

void VTT::removeICU()
{
    ICUStage->Position = ICUStage->OutPosition;
    Command = ICUStage->moveCommand();
    sendCommand();
    waitForIt();
}

void VTT::rotateICU()
{
    rotateICUPolarizer();
    rotateICURetarder();
}

void VTT::rotateICUPolarizer()
{
    ICUPolarizer->Position = PolarizerAngle;
    Command = ICUPolarizer->moveCommand();
    sendCommand();
    waitForIt();
}

void VTT::rotateICURetarder()
{
    ICURetarder->Position = RetarderAngle;
    Command = ICURetarder->moveCommand();
    sendCommand();
    waitForIt();
}

void VTT::rotateRelICUPolarizer(double aPol)
{
    ICUPolarizer->RelPos = aPol;
    Command = ICUPolarizer->moveRelCommand();
    sendCommand();
    waitForIt();
}

void VTT::rotateRelICURetarder(double aRet)
{
    ICURetarder->RelPos = aRet;
    Command = ICURetarder->moveRelCommand();
    sendCommand();
    waitForIt();
}

void VTT::gotoICUPolarizer(int iPol)
{
    if (ICUPolarizer->NPositions == 1) PolarizerAngle = ICUPolarizer->Start;
    else PolarizerAngle = ICUPolarizer->Start + iPol*(ICUPolarizer->Stop-ICUPolarizer->Start)/(ICUPolarizer->NPositions-1);
    PolarizerAngle = std::fmod(PolarizerAngle, 360.0);
    rotateICUPolarizer();
}

void VTT::gotoICURetarder(int iRet)
{
    if (ICURetarder->NPositions == 1) RetarderAngle = ICURetarder->Start;
    else RetarderAngle = ICURetarder->Start + iRet*(ICURetarder->Stop-ICURetarder->Start)/(ICURetarder->NPositions-1);
    RetarderAngle = std::fmod(RetarderAngle, 360.0);
    rotateICURetarder();
}

void VTT::gotoICUPosition(int iPol, int iRet)
{
    gotoICUPolarizer(iPol);
    gotoICURetarder(iRet);
}

void VTT::moveRelICU(double aPol, double aRet)
{
    rotateRelICUPolarizer(aPol);
    rotateRelICURetarder(aRet);
}

void VTT::waitForIt()
{
    QEventLoop WaitLoop;
    connect(this, &VTT::stopWaiting, &WaitLoop, &QEventLoop::quit);
    WaitLoop.exec();
}

void VTT::readyRead()
{
    QByteArray ByteDataReceived = TCPSocket->readAll();
    Response = std::string(ByteDataReceived.data());
    addLog("received controller response: " + std::string(ByteDataReceived.data()));   
    if (Response.find(ICUPolarizer->Acknowledge) != std::string::npos) ICUPolarizer->RUNNING = false;
    if (Response.find(ICURetarder->Acknowledge) != std::string::npos) ICURetarder->RUNNING = false;
    if (Response.find(ICUStage->Acknowledge) != std::string::npos) ICUStage->RUNNING = false;
    if (Response.find(ICUPolarizer->ErrorResp) != std::string::npos) ICUPolarizer->ERR = true;
    if (Response.find(ICURetarder->ErrorResp) != std::string::npos) ICURetarder->ERR = true;
    if (Response.find(ICUStage->ErrorResp) != std::string::npos) ICUStage->ERR = true;
    if (ICUStage->ERR || ICUPolarizer->ERR || ICURetarder->ERR) {
        std::string LastCommand = Command;
        resetICUMotors();
        Command = LastCommand;
        sendCommand();
    }
    if (!ICUPolarizer->RUNNING && !ICURetarder->RUNNING && !ICUStage->RUNNING) emit(stopWaiting());
}

void VTT::sendCommand()
{
    Error = TCPSocket->write((Command+"\n").c_str());
    if (Error == -1) addLog("error writing to TCP socket" + std::to_string(Error));
    Error = TCPSocket->waitForBytesWritten();
    if (!Error) addLog("error waiting for TCP socket: " + std::to_string(TCPSocket->error()));
    Error = TCPSocket->error();
    addLog("controller command sent: " + Command);
    Sleep(SDELAY);
}

void VTT::handleError(int Err, std::string Message)
{
    if (Err != 0) {
        Error = Err;
        addLog("error " + Message + " (" + std::to_string(Error) + ").");
    }
}

void VTT::addLog(std::string Log) {
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void VTT::addLog(const char* Log) {
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}


// CAN devices

CANDevice::CANDevice(QString Name){
    Label = Name.toStdString();
    Start = Settings->value(Name + "/Start").toDouble();
    Stop = Settings->value(Name + "/Stop").toDouble();
    Step = Settings->value(Name + "/Step").toDouble();
    Zero = Settings->value(Name + "/Zero").toDouble();
    Default = Settings->value(Name + "/Default").toDouble();
    InPosition = Settings->value(Name + "/InPosition").toDouble();
    OutPosition = Settings->value(Name + "/OutPosition").toDouble();
    Factor = Settings->value(Name + "/Factor").toDouble();
    Offset = Settings->value(Name + "/Offset").toDouble();
    iDevice = Settings->value(Name + "/iDevice").toInt();
    NPositions = Settings->value(Name + "/NPositions").toInt();
    Step = (Stop-Start)/(NPositions-1);
    Acknowledge = std::to_string(iDevice) + "X";
    ErrorResp = std::to_string(iDevice) + "E";
}

CANDevice::~CANDevice()
{

}

std::string CANDevice::homeCommand() {
    RUNNING = true;
    return "X" + std::to_string(iDevice) + "HG";
}

std::string CANDevice::moveCommand()
{
    int Counts = (Position+Zero)*Factor + Offset;
    RUNNING = true;
    return "X" + std::to_string(iDevice) + "A" + std::to_string(Counts) + "G";
}

std::string CANDevice::moveRelCommand() {
    int Counts = RelPos*Factor;
    RUNNING = true;
    return "X" + std::to_string(iDevice) + "R" + std::to_string(Counts) + "G";
}

std::string CANDevice::onCommand() {
    RUNNING = true;
    return "X" + std::to_string(iDevice) + "nG";
}

std::string CANDevice::offCommand() {
    RUNNING = true;
    return "X" + std::to_string(iDevice) + "fG";
}

std::string CANDevice::positionCommand() {
    RUNNING = true;
    return "X" + std::to_string(iDevice) + "pG";
}

std::string CANDevice::clearErrorCommand() {
    RUNNING = true;
    return "X" + std::to_string(iDevice) + "E";
}




