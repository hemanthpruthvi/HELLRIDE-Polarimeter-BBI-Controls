#ifndef VTTNET_H
#define VTTNET_H

#include "common.h"

class VTTNet : public QObject
{ Q_OBJECT

public:
    explicit VTTNet(QObject *parent = nullptr);
    ~VTTNet();
    void initVTTNet(QString Name);              //
    void positionStopWheel();
    void sendCommand();                         //
    void waitForIt();
    //
    int Error = 0;
    std::string Response = "";                  // Response from the controller
    std::string Command = "";
    //
    std::string Label = "";                     // LCVR controller
    QString TCPHostName;                        // IP address of the VTT
    quint16 TCPPortNumber;                      // Port number of the VTT
    std::string DeviceName;                     // This PC name on the network
    int StopWheelPosition;

public slots:
    void readyRead();                           // Received response is read

private:
    QTcpSocket *TCPSocket;                      // TCP-IP socket for conecting to device
    void shakeHand();
    void handleError(int Err,
                     std::string Message);      //
    void addLog(std::string Log);               //
    void addLog(const char* Log);

signals:
    void addLog(QString Log);                   //
    void stopWaiting();
};

#endif // VTTNET_H
