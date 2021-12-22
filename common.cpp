#include "common.h"

Details::Details(QObject *parent) : QObject(parent)
{
}

Details::~Details()
{
}

std::string getDateTimeStringNow()
{
   return QDateTime::currentDateTime().toString("yyyyMMdd_hhmmsszzz").toStdString();
}

QString getLogTimeStringNow()
{
    return QDateTime::currentDateTime().toString("hh:mm:ss.zzz   ");

}
























