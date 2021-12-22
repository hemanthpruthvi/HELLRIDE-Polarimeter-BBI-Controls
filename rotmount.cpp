#include "rotmount.h"

RotMount::RotMount(QObject *parent) : QObject(parent)
{
}

RotMount::~RotMount()
{
    Position = 0;
    movePosition();
    addLog("device closed.");
    APTCleanUp();
}

void RotMount::addLog(std::string Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void RotMount::addLog(const char* Log)
{
    emit(addLog(getLogTimeStringNow() + QString::fromStdString(Label + " " + Log)));
}

void RotMount::handleError(int Err, std::string Message)
{
    Error = Err;
    if (Err != XI_OK) addLog("error " + Message + " (" + std::to_string(Error) + ").");
//    else addLog("successfully " + Message + ".");
}

void RotMount::initDevice(QString Name)
{
    Label = Settings->value(Name + "/Label").toString().toStdString();
    SerialNumber = Settings->value(Name + "/SerialNumber").toInt();
    MinVelocity = Settings->value(Name + "/MinVelocity").toFloat();
    MaxVelocity = Settings->value(Name + "/MaxVelocity").toFloat();
    Acceleration = Settings->value(Name + "/Acceleration").toFloat();
    DeviceType = Settings->value(Name + "/DeviceType").toInt();
    Index = Settings->value(Name + "/Index").toInt();
    ZeroPosition = Settings->value(Name + "/ZeroPosition").toFloat();
    //
    APTInit();
    handleError(InitHWDevice(SerialNumber), "initializing device");
    if (!Error) addLog("device initialized.");
    handleError(MOT_SetVelParams(SerialNumber, MinVelocity, Acceleration, MaxVelocity), "setting velocity parameters");
//    MOT_SetJogParams(SerialNumber, 2, 2, SingleStep, MinVelocity, Acceleration, MaxVelocity);
    //
    MOT_GetPosition(SerialNumber, &Position);
}

void RotMount::moveHome()
{
    addLog("moving home...");
    MOT_MoveHome(SerialNumber, BLOCK);
    addLog("home reached.");
}

void RotMount::movePosition()
{
    MOT_MoveAbsoluteEx(SerialNumber, std::fmod(Position+ZeroPosition, 360.0), BLOCK);
    MOT_GetPosition(SerialNumber, &AbsPosition);
    addLog("moved to position: " + std::to_string(Position) +
           " (abspos: " + std::to_string(AbsPosition) + ")");
}

void RotMount::moveNextPosition()
{
    MOT_MoveJog(SerialNumber, SingleStep>0);
}
