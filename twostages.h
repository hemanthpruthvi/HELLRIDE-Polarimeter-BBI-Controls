#ifndef TWOSTAGES_H
#define TWOSTAGES_H

#include "common.h"

class TwoStages : public QObject
{ Q_OBJECT

public:
    explicit TwoStages(QObject *parent = nullptr);
    ~TwoStages();
    void initTwoStages(QString Name);               // Initialize pre-filter stage controllers
    void moveTwoStages();                           // Move both stages at a time
    void moveStage1();                              // Move only stage-1 to "Position1"
    void moveStage2();                              // Move only stage-2 to "Position2"
    void getCurrentPositions();                     //
    void setSpeeds();                               // Set moving speeds of two stages to "Speed1" and "Speed2"
    void calibrateTwoStages();                      // Run Home run and zero run
    void sendCommand();                             //
    //
    std::string Label = "";                         // Given name of the object once it's created
    QString TCPHostName = "193.197.56.164";         // IP address of the device
    quint16 TCPPortNumber = 400;                    // Port number of the device
    double ZeroPosition1 = 0.0;                     // Stage-1 position of "Reference" with respect to absolute zero of the stage
    double ZeroPosition2 = 0.0;                     // Stage-2 position of "Reference" with respect to absolute zero of the stage
    double DefaultPosition1 = 0.0;                  // Stage-1 default position w.r.t. ZeroPosition1
    double DefaultPosition2 = 0.0;                  // Stage-2 default position w.r.t. ZeroPosition2
    double Speed1;                                  // Stage-1 moving speed
    double Speed2;                                  // Stage-2 moving speed
    double CurrentPosition1;                        // Stage-1 position read
    double CurrentPosition2;                        // Stage-2 position read
    int ResetDelay;                                 // Wait time in seconds for reset
    //
    int Error = 0;                                  //
    std::string Command = "";                       // ASCII command string to control device
    std::string Response = "";                      // Response received from controller
    double Position1 = 0.0;                         // Stage-1 absolute position
    double Position2 = 0.0;                         // Stage-2 absolute position
    std::vector<double> Positions1;
    std::vector<double> Positions2;
    // Exclusive for filter matrix DO NOT USE WITH OTHER STAGES
    void selectPreFilter();                         // Move selected iPreFilter into the optical path
    unsigned int iPreFilter = 0;                    // Index of pre-filter as per predefined convention
    double SingleStep1 = -62.5;                     // X distance between two successive prefilters
    double SingleStep2 = -62.5;                     // Y distance between two successive prefilters

private:
    QTcpSocket *TCPSocket;                          // TCP-IP socket for conecting to device
    void handleError(int Err,
                     std::string Message);
    void addLog(std::string Log);                   //
    void addLog(const char* Log);
    double Acceleration1;                           // Stage-1 moving acceleration
    double Acceleration2;                           // Stage-2 moving acceleration

public slots:
    void readyRead();                               //

signals:
    void addLog(QString Log);                       //

};

#endif // TWOSTAGES_H
