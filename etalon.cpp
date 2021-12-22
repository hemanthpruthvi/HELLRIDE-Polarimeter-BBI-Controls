#include "etalon.h"

Etalon::Etalon(QObject *parent) : QObject(parent)
{

}

Etalon::~Etalon()
{
    Command = "I0";
    sendCommand();
    Sleep(SDELAY);
    Command = "O/2";
    sendCommand();
    Sleep(SDELAY);
    TCPSocket->close();
    addLog("closing connection.");
    delete TCPSocket;
}

void Etalon::initEtalon(QString Name)
{
    Label = Settings->value(Name + "/Label").toString().toStdString();
    TCPHostName = Settings->value(Name + "/TCPHostName").toString();
    TCPPortNumber = Settings->value(Name + "/TCPPortNumber").toUInt();
    ZSpacing = Settings->value(Name + "/ZSpacing").toDouble();
    ZScanRange = Settings->value(Name + "/ZScanRange").toDouble();
    Wavelength = Settings->value(Name + "/Wavelength").toDouble();
    //
    TCPSocket = new QTcpSocket(this);
    addLog("connecting (" + TCPHostName.toStdString() + ":" + std::to_string(TCPPortNumber) + ")." );
    TCPSocket->connectToHost(TCPHostName, TCPPortNumber);
    if(!TCPSocket->waitForConnected(5000)) {
        handleError(TCPSocket->error(), "connecting to device");
    }
    else {
        connect(TCPSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        Command = "!QT";        // Define read-only ports
        sendCommand();
        Sleep(SDELAY);
        Error = SUCCESS;
    }
    return;
}

void Etalon::readyRead()
{
    QByteArray ByteDataReceived = TCPSocket->readAll();
    Response = std::string(ByteDataReceived.data());
//    addLog("received controller response: " + Response);
    if (Response.length() < 3) {
        if (Response == "0") {
            handleError(-1, "BALANCE MODE and OUT OF RANGE");
            Operating = false;
        }
        else if (Response == "1") {
            handleError(-2, "OUT OF RANGE");
            Operating = false;
        }
        else if (Response == "2") {
            handleError(-3, "BALANCE MODE");
            Operating = false;
        }
        else if (Response == "3") {
//            addLog(Label + " is in order.");
            Operating = true;
        }
        else{};
    }
    else if (Response.length() == 5) {
        int Count;
        std::stringstream Temp;
        Temp << std::hex << Response;
        Temp >> Count;
        Response = std::to_string(Count-2048);
        addLog("Z-spacing counts read: " + Response);
    }
    else if (Response.length() == 6) {
        std::string Temp1;
        Temp1 = Response.at(0);
        if (Temp1 == "0") {
            handleError(-1, "BALANCE MODE and OUT OF RANGE");
            Operating = false;
        }
        else if (Temp1 == "1") {
            handleError(-2, "OUT OF RANGE");
            Operating = false;
        }
        else if (Temp1 == "2") {
            handleError(-3, "BALANCE MODE");
            Operating = false;
        }
        else if (Temp1 == "3") {
//            addLog("is in order");
            Operating = true;
        }
        else;
        //
        Temp1 = Response.substr(1,3);
        int Count;
        std::stringstream Temp2;
        Temp2 << std::hex << Temp1;
        Temp2 >> Count;
        Response = std::to_string(Count-2048);
        addLog("Z-spacing counts read: " + Response);
    }
    return;
}

void Etalon::scanWavelength()
{
//    SingleStepinAngstrom = Wavelength*ZScanRange/ZSpacing/4096.0
    WaveScan = WaveScanRange/(NWavePoints-1);
    ZStep = 4096.0*(ZSpacing/ZScanRange)*(WaveScan/Wavelength);
    ZCounts += ZStep;
    generateCommandFromCounts();
    sendCommand();
    return;
}

void Etalon::gotoScanStartPosition()
{
    ZCounts = ZZero;
    // SingleStepinAngstrom = Wavelength*ZScanRange/ZSpacing/4096.0
    double TempWaveScan = -WaveScanRange/2.0;
    ZStep = 4096.0*(ZSpacing/ZScanRange)*(TempWaveScan/Wavelength);
    ZCounts += ZStep;
    generateCommandFromCounts();
    sendCommand();
    return;
}

void Etalon::tuneWavelength()
{
    generateCommandFromCounts();
    sendCommand();
    return;
}

void Etalon::generateCommandFromCounts()  // See etalon command sytax
{
    int Counts = static_cast<int>(std::round(ZCounts));
    if (Counts < 0) Counts += 4096;
    if (Counts < 0 || Counts > 4095) {
        addLog("invalid number of steps: " + std::to_string(ZCounts));
        return;
    }
    else {
        std::stringstream HexStream;
        HexStream << std::uppercase << std::setfill ('0') << std::setw(3) << std::hex << Counts;
//        Command = PreFix + "I4" + HexStream.str() + "P1P0I0";
        Command = "I4" + HexStream.str() + "P1P0?";
//        Command = "J" + HexStream.str() + "P1P0?";
        return;
    }
}

void Etalon::resetEtalon()
{
    Command = "O+D";            // Disable controller board switches
    sendCommand();
    Sleep(SDELAY);
    Command = "N8";             // Set response time to 2ms
    sendCommand();
    Sleep(SDELAY);
    Command = "O1";             // Set to balance mode
    sendCommand();
    Sleep(LDELAY);
    Command = "O0";             // Set to operate mode
    sendCommand();
    Sleep(2*LDELAY);
    Operating = true;
    //
    resetXYParallelism();
    return;
}

void Etalon::resetXYParallelism()
{
    Command = "I0";             // Close XYZ ports for writing
    sendCommand();
    Sleep(SDELAY);
    Command = "I1000P1P0I0";   // Apply X-parallelsim = 0
    sendCommand();
    Sleep(SDELAY);
    Command = "I2000P1P0I0";   // Apply Y-parallelsim = 0
    sendCommand();
    Sleep(SDELAY);
    Command = "I4";             // Open Z-spacing for writing
    sendCommand();
    Sleep(SDELAY);
}

void Etalon::getCurrentStatus()
{
    Command = "?";
    sendCommand();
    return;
}

void Etalon::sendCommand()
{
    Error = TCPSocket->write((Command+"\r").c_str());
    if (Error == -1) addLog("error writing to TCP socket" + std::to_string(Error));
    Error = TCPSocket->waitForBytesWritten();
    if (!Error) addLog("error waiting for TCP socket: " + std::to_string(TCPSocket->error()));
    addLog("controller command sent: " + Command);
    return;
}

void Etalon::handleError(int Err, std::string Message)
{
    if (Err != 0) {
        Error = Err;
        addLog("error " + Message + " (" + std::to_string(Error) + ").");
    }
}

void Etalon::addLog(std::string Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void Etalon::addLog(const char* Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}
