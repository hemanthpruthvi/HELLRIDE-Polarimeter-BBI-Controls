#include "vttnet.h"

VTTNet::VTTNet(QObject *parent) : QObject(parent)
{

}

VTTNet::~VTTNet()
{
    addLog("closing connection.");
    TCPSocket->close();
};


void VTTNet::initVTTNet(QString Name)
{
    Label = Settings->value(Name + "/Label").toString().toStdString();
    TCPHostName = Settings->value(Name + "/TCPHostName").toString();
    TCPPortNumber = Settings->value(Name + "/TCPPortNumber").toUInt();
    DeviceName = Settings->value(Name + "/DeviceName").toString().toStdString();
    //
    TCPSocket = new QTcpSocket(this);
    addLog("connecting (" + TCPHostName.toStdString() + ":" + std::to_string(TCPPortNumber) + ")." );
    TCPSocket->connectToHost(TCPHostName, TCPPortNumber);
    if(!TCPSocket->waitForConnected(5000)) {
        handleError(TCPSocket->error(), "connecting to device");
    }
    else {
        connect(TCPSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
        shakeHand();
        Error = SUCCESS;
    }
    return;
}

void VTTNet::positionStopWheel()
{
    Command = "hobbit: " + DeviceName + " ct opt sw" + std::to_string(StopWheelPosition);
    sendCommand();
    waitForIt();
}

void VTTNet::waitForIt()
{
    QEventLoop WaitLoop;
    connect(this, &VTTNet::stopWaiting, &WaitLoop, &QEventLoop::quit);
    WaitLoop.exec();
}

void VTTNet::readyRead()
{
    QByteArray ByteDataReceived = TCPSocket->readAll();
    Response = std::string(ByteDataReceived.data());
    addLog("received controller response: " + std::string(ByteDataReceived.data()));
    emit(stopWaiting());
}

void VTTNet::shakeHand()
{
    Command = DeviceName + "\4";
    Error = TCPSocket->write(Command.c_str());
    if (Error == -1) addLog("error writing to TCP socket" + std::to_string(Error));
    Error = TCPSocket->waitForBytesWritten();
    if (!Error) addLog("error waiting for TCP socket: " + std::to_string(TCPSocket->error()));
    else Error = SUCCESS;
    addLog("controller command sent: " + Command);
}

void VTTNet::sendCommand()
{
    Command = Command + "\4";
    Error = TCPSocket->write(Command.c_str());
    if (Error == -1) addLog("error writing to TCP socket" + std::to_string(Error));
    Error = TCPSocket->waitForBytesWritten();
    if (!Error) addLog("error waiting for TCP socket: " + std::to_string(TCPSocket->error()));
    Error = TCPSocket->error();
    addLog("controller command sent: " + Command);
    Sleep(SDELAY);
}

void VTTNet::handleError(int Err, std::string Message)
{
    if (Err != 0) {
        Error = Err;
        addLog("error " + Message + " (" + std::to_string(Error) + ").");
    }
}

void VTTNet::addLog(std::string Log) {
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void VTTNet::addLog(const char* Log) {
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}
