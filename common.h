#ifndef COMMON_H
#define COMMON_H

#include <QDir>
#include <QTime>
#include <QIcon>
#include <QDebug>
#include <QImage>
#include <QThread>
#include <QPixmap>
#include <QObject>
#include <QString>
#include <QVector>
#include <QPainter>
#include <QSettings>
#include <QDateTime>
#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
//
#include <map>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <numeric>
#include <cstdint>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
//
#include "xiApi.h"
#include "fitsio.h"
#include "longnam.h"
#include "windows.h"
#include "usbdrvd.h"
#include "APTAPI.h"
//
#define PI 3.14159265
#define BLOCK 1
#define NO_BLOCK 0
#define ON 1
#define OFF 0
#define FULL_HEIGHT 2048
#define FULL_WIDTH 2048
#define COUNT_LIMIT 4096
#define CAMERA_TIMEOUT 10000
#define ICU_TIMEOUT 120000
#define AOSW_TARG 1
#define AOSW_DARK 2
#define AOSW_AP34 3
#define AOSW_AP40 4
#define AOSW_AP60 5
#define AOSW_PINH 6
#define AOSW_DEFAULT 3
#define FILTER_BLIND 0
#define XSDELAY 20
#define SDELAY 50
#define MDELAY 200
#define LDELAY 1000
#define XLDELAY 2000
#define SUCCESS 0
#define BOT_LEF 0
#define TOP_LEF 1
#define BOT_RIG 2
#define TOP_RIG 3
#define LIVE_MODE_VIEW_ONLY 0
#define LIVE_MODE_SAVE_ONLY 1
#define LIVE_MODE_VIEW_SAVE 2
#define LIVE_MODE_CAM 20
#define OBS_MODE_SCIE 13
#define OBS_MODE_PCAL 12
#define OBS_MODE_FLAT 11
#define OBS_MODE_DARK 10
#define OBS_MODE_PINH 9
#define OBS_MODE_TARG 8
#define CHR_MODE_ET1_MATCH 7
#define CHR_MODE_ET2_MATCH 6
#define CHR_MODE_LINE_PROF 5
#define CHR_MODE_CAM_FOCUS 4
#define CHR_MODE_LCVR1_PROF 3
#define CHR_MODE_LCVR2_PROF 2
#define CHR_MODE_ET1_PROF 1
#define CHR_MODE_ET2_PROF 0
#define OBS_MODE_SCIE_SUFF "sc"
#define OBS_MODE_FLAT_SUFF "ff"
#define OBS_MODE_PCAL_SUFF "pc"
#define OBS_MODE_DARK_SUFF "dk"
#define OBS_MODE_TARG_SUFF "tf"
#define OBS_MODE_PINH_SUFF "ph"
#define CHR_MODE_ET1_MATCH_SUFF "et1match"
#define CHR_MODE_ET2_MATCH_SUFF "et2match"
#define CHR_MODE_LINE_PROF_SUFF "lineprof"
#define CHR_MODE_CAM_FOCUS_SUFF "camfocus"
#define CHR_MODE_LCVR1_PROF_SUFF "lcvr1pro"
#define CHR_MODE_LCVR2_PROF_SUFF "lcvr2pro"
#define CHR_MODE_ET1_PROF_SUFF "et1profl"
#define CHR_MODE_ET2_PROF_SUFF "et2profl"

extern QSettings *Settings;
extern QSettings *obsSettings;
extern QSettings *chrSettings;
extern std::vector<double> XData, YData;
extern std::vector<double> XData2, YData2;
//extern QThread *ThreadAcquisition;
//extern QThread *ThreadCAM1;
//extern QThread *ThreadCAM2;

std::string getDateTimeStringNow();
QString getLogTimeStringNow();

class Details : public QObject
{ Q_OBJECT
public:
    explicit Details(QObject *parent = nullptr);
    ~Details();
    double XArcsec;
    double YArcsec;
    double PAngle;
    double AtmosR0;
    std::string DataTags;
    std::string Observers;
    std::string Planners;
    std::string OtherSettings;
};
#endif // COMMON_H
