#-------------------------------------------------
#
# Project created by QtCreator 2019-08-21T14:57:08
#
#-------------------------------------------------

QT += core gui
QT += network
QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HELLRIDE-PolarimeterControls
TEMPLATE = app
RC_ICONS = vtt.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QCUSTOMPLOT_COMPILE_LIBRARY

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += console

SOURCES += \
        acquisition.cpp \
        camera.cpp \
        common.cpp \
        etalon.cpp \
        imageview.cpp \
        main.cpp \
        mainwindow.cpp \
        plotview.cpp \
        polarimeter.cpp \
        qcustomplot.cpp \
        rotmount.cpp \
        twostages.cpp \
        vtt.cpp \
        vttnet.cpp

HEADERS += \
        acquisition.h \
        camera.h \
        common.h \
        etalon.h \
        imageview.h \
        mainwindow.h \
        plotview.h \
        polarimeter.h \
        qcustomplot.h \
        rotmount.h \
        twostages.h \
        vtt.h \
        vttnet.h

FORMS += \
        imageview.ui \
        mainwindow.ui \
        plotview.ui

# FITS C-library; not used for polarimeter software anymore due to write performance issues
INCLUDEPATH += "C:\cfitsio"
LIBS += -L"C:\cfitsio" -lcfitsio
# xiAPI Camera libraries
INCLUDEPATH += "C:\XIMEA\API\xiAPI"
LIBS += -L"C:\XIMEA\API\xiAPI" -lxiapi64
# LCVR controller USB divers
INCLUDEPATH += "C:\Meadowlark"
LIBS += -L"C:\Meadowlark" -lusbdrvd
# Thorlabs rotation mount APT drivers
INCLUDEPATH += "C:\Program Files\Thorlabs\APT\APT Server"
LIBS += -L"C:\Program Files\Thorlabs\APT\APT Server" -lAPT

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3

QMAKE_LFLAGS_RELEASE -= -O
QMAKE_LFLAGS_RELEASE -= -O1
QMAKE_LFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE += -O3

DISTFILES += \
    coreSettings.ini
