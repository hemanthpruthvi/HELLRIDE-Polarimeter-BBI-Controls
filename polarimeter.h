#ifndef POLARIMETER_H
#define POLARIMETER_H

#include "common.h"
#define  LCVR_FLAGS_ATTRS  0x40000000

class Polarimeter : public QObject
{ Q_OBJECT

public:
    explicit Polarimeter(QObject *parent = nullptr);
    ~Polarimeter();
    void initPolarimeter(QString Name);             //
    void setVoltages();                             // Set LCVR1, LCVR2 voltages
    void setTemperature();
    void setLCVR1Voltage();
    void setLCVR2Voltage();
    void setModulation();                           // Set LCVR1, LCVR2 modulation
    void setDummyModulation();                      // Set LCVR1, LCVR2 modulation voltages which cause the same retardance (e.g., 0, 0.1 V)
    void setModulation(bool POLARIMETRY_DISABLE);   //
    void startModulation();                         // Start LCVR modulation
    void stopModulation();                          // Stop LCVR modulation
    void sendCommand();                             //
    //
    int Error = 0;                                  //
    int NModulations = 4;                           // Number of modulation states
    int TNEHighVoltage;                             // TNE high voltage
    int TNELowVoltage;                              // TNE low voltage
    int TNETime;                                    // Time for TNE voltage duration
    int SwitchingTime;                              // Time taken for switching state
    int TriggerTime;                                // Time duration for trigger pulse
    int StateTime;                                  // Time for each state
    int SyncDuration;                               //
    int LCVR1Voltage;                               //
    int LCVR2Voltage;                               //
    int Vzero1;
    int Vzero2;
    double Temperature;                                //
    HANDLE LCVRController;                          // LCVR controller handle
    HANDLE Pipe0, Pipe1;                            // LCVR controller pipes
    std::string Label = "";                         // LCVR controller
    std::string Command = "";                       // ASCII command string to control device
    std::string Response = "";                      // Response from the controller
    std::vector<int> LCVR1Voltages;                 // LCVR1 modulation voltages
    std::vector<int> LCVR2Voltages;                 // LCVR2 modulation voltages

public slots:

private:
    void addLog(std::string Log);                   //
    void addLog(const char* Log);
    void initLCVRController();                      // Initialize D5020 controller

signals:
    void addLog(QString Log);                       //
};

#endif // POLARIMETER_H
