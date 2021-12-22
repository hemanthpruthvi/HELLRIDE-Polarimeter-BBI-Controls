#include "twostages.h"

TwoStages::TwoStages(QObject *parent) : QObject(parent)
{
}

TwoStages::~TwoStages()
{
    addLog("closing connection.");
    TCPSocket->close();
}

void TwoStages::initTwoStages(QString Name)
{
    Label = Settings->value(Name + "/Label").toString().toStdString();
    TCPHostName = Settings->value(Name + "/TCPHostName").toString();
    TCPPortNumber = Settings->value(Name + "/TCPPortNumber").toUInt();
    ZeroPosition1 = Settings->value(Name + "/ZeroPosition1").toDouble();
    ZeroPosition2 = Settings->value(Name + "/ZeroPosition2").toDouble();
    DefaultPosition1 = Settings->value(Name + "/DefaultPosition1").toDouble();
    DefaultPosition2 = Settings->value(Name + "/DefaultPosition2").toDouble();
    SingleStep1 = Settings->value(Name + "/SingleStep1").toDouble();
    SingleStep2 = Settings->value(Name + "/SingleStep2").toDouble();
    Speed1 = Settings->value(Name + "/Speed").toDouble();
    Speed2 = Settings->value(Name + "/Speed").toDouble();
    ResetDelay = Settings->value(Name + "/ResetDelay").toInt();
    //
    TCPSocket = new QTcpSocket(this);
    addLog("connecting (" + TCPHostName.toStdString() + ":" + std::to_string(TCPPortNumber) + ")..." );
    TCPSocket->connectToHost(TCPHostName, TCPPortNumber);
    if(!TCPSocket->waitForConnected(5000)) {
        handleError(TCPSocket->error(), "connecting to device");
    }
    else {
        connect(TCPSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        Command = "version";
        sendCommand();
        Sleep(SDELAY);
        setSpeeds();
    }
}

void TwoStages::readyRead()
{
    QByteArray ByteDataReceived = TCPSocket->readAll();
    Response = std::string(ByteDataReceived.data());
    addLog("received controller response: " + std::string(ByteDataReceived.data()));
}

void TwoStages::selectPreFilter()
{
    // Convert filter index to X and Y indices
    int TempX, TempY;
    TempX = iPreFilter%4;
    TempY = iPreFilter/4;
    if (TempY%2==1) TempX = 3-TempX;
    //
    Command = std::to_string(ZeroPosition1 + TempY*SingleStep1) + " 1 nm";
    sendCommand();
    Command = std::to_string(ZeroPosition2 + TempX*SingleStep2) + " 2 nm";
    sendCommand();
}

void TwoStages::moveTwoStages()
{
    Command = std::to_string(ZeroPosition1 + Position1) + " 1 nm";
    sendCommand();
    Command = std::to_string(ZeroPosition2 + Position2) + " 2 nm";
    sendCommand();
}

void TwoStages::moveStage1()
{
    Command = std::to_string(ZeroPosition1 + Position1) + " 1 nm";
    sendCommand();
}

void TwoStages::moveStage2()
{
    Command = std::to_string(ZeroPosition2 + Position2) + " 2 nm";
    sendCommand();
}

void TwoStages::setSpeeds()
{
    Command = std::to_string(Speed1) + " 1 snv";
    sendCommand();
    Sleep(SDELAY);
    Command = std::to_string(Speed2) + " 2 snv";
    sendCommand();
    Sleep(SDELAY);
}

void TwoStages::calibrateTwoStages()
{
    Command = "1 init";
    sendCommand();
    Sleep(SDELAY);
    Command = "2 init";
    sendCommand();
    Sleep(LDELAY);
    // Do a home run
    Command = "1 ncal";
    sendCommand();
    Sleep(SDELAY);
    Command = "2 ncal";
    sendCommand();
    Sleep(ResetDelay*LDELAY);
    // Go to default positions
    Position1 = DefaultPosition1;
    Position2 = DefaultPosition2;
    moveTwoStages();
}

void TwoStages::sendCommand()
{
    addLog("sending controller command: " + Command);
    TCPSocket->write((Command+"\r\n").c_str());
    TCPSocket->waitForBytesWritten();
//    handleError(TCPSocket->write((Command+"\r\n").c_str()), "with TCP socket writing command");
//    handleError(TCPSocket->waitForBytesWritten(), "with TCP socket waiting to write command");
}

void TwoStages::handleError(int Err, std::string Message)
{
    if (Err != 0) {
        Error = Err;
        addLog("error " + Message + " (" + std::to_string(Error) + ").");
    }
}

void TwoStages::addLog(std::string Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void TwoStages::addLog(const char* Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}
