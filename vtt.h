#ifndef VTT_H
#define VTT_H

#include "common.h"

class CANDevice : public QObject
{ Q_OBJECT

public:
    CANDevice(QString Name);
    ~CANDevice();
    std::string Label;
    double Start, Stop, Step;
    double Zero, Default, Position, RelPos;
    double InPosition, OutPosition;
    int Factor, Offset;
    int iDevice, NPositions;
    bool RUNNING = false;
    bool ERR = false;
    std::string ErrorResp;
    std::string Acknowledge;
    std::string homeCommand();
    std::string moveCommand();
    std::string onCommand();
    std::string offCommand();
    std::string positionCommand();
    std::string moveRelCommand();
    std::string clearErrorCommand();
};

class VTT : public QObject
{ Q_OBJECT

public:
    explicit VTT(QObject *parent = nullptr);
    ~VTT();
    void initVTT(QString Name);                 //
    void powerICUMotors(bool Power);            //
    void resetICUMotors();                      //
    void homeICU();                             // Go to ICU home positions
    void insertICU();                           // Set LCVR1, LCVR2 modulation
    void removeICU();                           // Setup acquisition with given parameters
    void rotateICU();                           // Rotate polarizer and retarder to certain position
    void rotateICUPolarizer();
    void rotateICURetarder();
    void gotoICUPolarizer(int iPol);
    void gotoICURetarder(int iRet);
    void gotoICUPosition(int iPol, int iRet);   // Go to certain discrete position
    void getICUPolarizerPosition();
    void getICURetarderPosition();
    void sendCommand();                         //
    void rotateRelICURetarder(double aRet);     //
    void rotateRelICUPolarizer(double aPol);    //
    void moveRelICU(double aPol, double aRet);  //
    //
    int Error = 0;
    int NModulations = 4;                       // Number of modulation states
    std::string Response = "";                  // Response from the controller
    std::string Command = "";
    double PolarizerAngle;
    double RetarderAngle;
    //
    std::string Label = "";                     // LCVR controller
    QString TCPHostName;                        // IP address of the VTT
    quint16 TCPPortNumber;                      // Port number of the VTT
    CANDevice *ICUStage;
    CANDevice *ICUPolarizer;
    CANDevice *ICURetarder;

public slots:
    void readyRead();                           // Received response is read

private:
    QTcpSocket *TCPSocket;                      // TCP-IP socket for conecting to device
    void handleError(int Err,
                     std::string Message);      //
    void addLog(std::string Log);               //
    void addLog(const char* Log);
    void waitForIt();

signals:
    void addLog(QString Log);                   //
    void stopWaiting();
};

#endif // VTT_H
