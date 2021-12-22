#ifndef ROTMOUNT_H
#define ROTMOUNT_H


#include "common.h"

class RotMount : public QObject
{ Q_OBJECT

public:
    explicit RotMount(QObject *parent = nullptr);
    ~RotMount();
    void initDevice(QString Name);                  // Initialize pre-filter stage controllers
    void moveHome();
    void movePosition();
    void moveNextPosition();
    //
    int Error = 0;
    std::string Label;
    long SerialNumber;
    float Position;
    float AbsPosition;
    float ZeroPosition;
    float SingleStep;

private:
    void addLog(std::string Log);                   //
    void addLog(const char* Log);                   //
    void handleError(int Err, std::string Message); //
    float MinVelocity;
    float MaxVelocity;
    float Acceleration;
    long DeviceType;
    long Index;

public slots:

signals:
    void addLog(QString Log);                       //
};


#endif // ROTMOUNT_H
