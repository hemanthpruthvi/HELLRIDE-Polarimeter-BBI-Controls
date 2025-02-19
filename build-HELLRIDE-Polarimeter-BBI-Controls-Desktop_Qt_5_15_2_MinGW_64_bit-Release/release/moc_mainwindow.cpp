/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HELLRIDE-Polarimeter-BBI-Controls/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[84];
    char stringdata0[2324];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "stopAcquisition"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "addLog"
QT_MOC_LITERAL(4, 35, 3), // "Log"
QT_MOC_LITERAL(5, 39, 18), // "prepareAcquisition"
QT_MOC_LITERAL(6, 58, 17), // "finishAcquisition"
QT_MOC_LITERAL(7, 76, 21), // "applyDetectorSettings"
QT_MOC_LITERAL(8, 98, 14), // "prepareDisplay"
QT_MOC_LITERAL(9, 113, 4), // "CAM0"
QT_MOC_LITERAL(10, 118, 4), // "CAM1"
QT_MOC_LITERAL(11, 123, 4), // "CAM2"
QT_MOC_LITERAL(12, 128, 8), // "plotData"
QT_MOC_LITERAL(13, 137, 5), // "Index"
QT_MOC_LITERAL(14, 143, 13), // "doObservation"
QT_MOC_LITERAL(15, 157, 18), // "doCharacterization"
QT_MOC_LITERAL(16, 176, 12), // "showSettings"
QT_MOC_LITERAL(17, 189, 12), // "saveSettings"
QT_MOC_LITERAL(18, 202, 14), // "loadFilterList"
QT_MOC_LITERAL(19, 217, 29), // "on_pushButtonSettings_clicked"
QT_MOC_LITERAL(20, 247, 29), // "on_pushButtonAutoSave_clicked"
QT_MOC_LITERAL(21, 277, 32), // "on_pushButtonAcquisition_clicked"
QT_MOC_LITERAL(22, 310, 7), // "checked"
QT_MOC_LITERAL(23, 318, 32), // "on_lineEditComment_returnPressed"
QT_MOC_LITERAL(24, 351, 30), // "on_pushButtonGetValues_clicked"
QT_MOC_LITERAL(25, 382, 29), // "on_pushButtonClearLog_clicked"
QT_MOC_LITERAL(26, 412, 45), // "on_comboBoxStepResolution_cur..."
QT_MOC_LITERAL(27, 458, 5), // "index"
QT_MOC_LITERAL(28, 464, 28), // "on_pushButtonOpenFMS_clicked"
QT_MOC_LITERAL(29, 493, 29), // "on_pushButtonResetFMS_clicked"
QT_MOC_LITERAL(30, 523, 35), // "on_lineEditCommandFMS_returnP..."
QT_MOC_LITERAL(31, 559, 37), // "on_spinBoxFilterPosition_valu..."
QT_MOC_LITERAL(32, 597, 4), // "arg1"
QT_MOC_LITERAL(33, 602, 35), // "on_doubleSpinBoxFMSXmm_valueC..."
QT_MOC_LITERAL(34, 638, 35), // "on_doubleSpinBoxFMSYmm_valueC..."
QT_MOC_LITERAL(35, 674, 38), // "on_comboBoxFilters_currentInd..."
QT_MOC_LITERAL(36, 713, 28), // "on_pushButtonOpenETS_clicked"
QT_MOC_LITERAL(37, 742, 29), // "on_pushButtonResetETS_clicked"
QT_MOC_LITERAL(38, 772, 35), // "on_lineEditCommandETS_returnP..."
QT_MOC_LITERAL(39, 808, 30), // "on_pushButtonRemoveET1_clicked"
QT_MOC_LITERAL(40, 839, 30), // "on_pushButtonRemoveET2_clicked"
QT_MOC_LITERAL(41, 870, 35), // "on_doubleSpinBoxETS1mm_valueC..."
QT_MOC_LITERAL(42, 906, 35), // "on_doubleSpinBoxETS2mm_valueC..."
QT_MOC_LITERAL(43, 942, 27), // "on_pushButtonOpenFS_clicked"
QT_MOC_LITERAL(44, 970, 28), // "on_pushButtonResetFS_clicked"
QT_MOC_LITERAL(45, 999, 34), // "on_lineEditCommandFS_returnPr..."
QT_MOC_LITERAL(46, 1034, 34), // "on_doubleSpinBoxFSPmm_valueCh..."
QT_MOC_LITERAL(47, 1069, 34), // "on_doubleSpinBoxFSBmm_valueCh..."
QT_MOC_LITERAL(48, 1104, 28), // "on_pushButtonOpenET1_clicked"
QT_MOC_LITERAL(49, 1133, 29), // "on_pushButtonResetET1_clicked"
QT_MOC_LITERAL(50, 1163, 35), // "on_lineEditCommandET1_returnP..."
QT_MOC_LITERAL(51, 1199, 32), // "on_spinBoxET1Counts_valueChanged"
QT_MOC_LITERAL(52, 1232, 28), // "on_pushButtonOpenET2_clicked"
QT_MOC_LITERAL(53, 1261, 29), // "on_pushButtonResetET2_clicked"
QT_MOC_LITERAL(54, 1291, 35), // "on_lineEditCommandET2_returnP..."
QT_MOC_LITERAL(55, 1327, 32), // "on_spinBoxET2Counts_valueChanged"
QT_MOC_LITERAL(56, 1360, 29), // "on_pushButtonOpenLCVR_clicked"
QT_MOC_LITERAL(57, 1390, 36), // "on_lineEditCommandLCVR_return..."
QT_MOC_LITERAL(58, 1427, 30), // "on_spinBoxLCVR1mV_valueChanged"
QT_MOC_LITERAL(59, 1458, 30), // "on_spinBoxLCVR2mV_valueChanged"
QT_MOC_LITERAL(60, 1489, 36), // "on_pushButtonStartModulation_..."
QT_MOC_LITERAL(61, 1526, 28), // "on_pushButtonOpenVTT_clicked"
QT_MOC_LITERAL(62, 1555, 35), // "on_lineEditCommandVTT_returnP..."
QT_MOC_LITERAL(63, 1591, 30), // "on_pushButtonInsertICU_clicked"
QT_MOC_LITERAL(64, 1622, 39), // "on_doubleSpinBoxICUPdeg_editi..."
QT_MOC_LITERAL(65, 1662, 39), // "on_doubleSpinBoxICURdeg_editi..."
QT_MOC_LITERAL(66, 1702, 43), // "on_comboBoxVTTStopWheel_curre..."
QT_MOC_LITERAL(67, 1746, 34), // "on_pushButtonOpenVTTServer_cl..."
QT_MOC_LITERAL(68, 1781, 41), // "on_lineEditCommandVTTServer_r..."
QT_MOC_LITERAL(69, 1823, 28), // "on_pushButtonHomeICU_clicked"
QT_MOC_LITERAL(70, 1852, 28), // "on_pushButtonOpenCWP_clicked"
QT_MOC_LITERAL(71, 1881, 28), // "on_pushButtonHomeCWP_clicked"
QT_MOC_LITERAL(72, 1910, 38), // "on_doubleSpinBoxCWPdeg_editin..."
QT_MOC_LITERAL(73, 1949, 38), // "on_comboBoxTrigger_currentInd..."
QT_MOC_LITERAL(74, 1988, 25), // "on_pushButtonLive_clicked"
QT_MOC_LITERAL(75, 2014, 29), // "on_pushButtonOpenCAM0_clicked"
QT_MOC_LITERAL(76, 2044, 29), // "on_pushButtonOpenCAM1_clicked"
QT_MOC_LITERAL(77, 2074, 29), // "on_pushButtonOpenCAM2_clicked"
QT_MOC_LITERAL(78, 2104, 38), // "on_comboBoxBinning_currentInd..."
QT_MOC_LITERAL(79, 2143, 34), // "on_comboBoxROI_currentIndexCh..."
QT_MOC_LITERAL(80, 2178, 36), // "on_toolBoxAcquisition_current..."
QT_MOC_LITERAL(81, 2215, 38), // "on_pushButtonReloadObsSetting..."
QT_MOC_LITERAL(82, 2254, 39), // "on_pushButtonReloadCoreSettin..."
QT_MOC_LITERAL(83, 2294, 29) // "on_pushButtonResetICU_clicked"

    },
    "MainWindow\0stopAcquisition\0\0addLog\0"
    "Log\0prepareAcquisition\0finishAcquisition\0"
    "applyDetectorSettings\0prepareDisplay\0"
    "CAM0\0CAM1\0CAM2\0plotData\0Index\0"
    "doObservation\0doCharacterization\0"
    "showSettings\0saveSettings\0loadFilterList\0"
    "on_pushButtonSettings_clicked\0"
    "on_pushButtonAutoSave_clicked\0"
    "on_pushButtonAcquisition_clicked\0"
    "checked\0on_lineEditComment_returnPressed\0"
    "on_pushButtonGetValues_clicked\0"
    "on_pushButtonClearLog_clicked\0"
    "on_comboBoxStepResolution_currentIndexChanged\0"
    "index\0on_pushButtonOpenFMS_clicked\0"
    "on_pushButtonResetFMS_clicked\0"
    "on_lineEditCommandFMS_returnPressed\0"
    "on_spinBoxFilterPosition_valueChanged\0"
    "arg1\0on_doubleSpinBoxFMSXmm_valueChanged\0"
    "on_doubleSpinBoxFMSYmm_valueChanged\0"
    "on_comboBoxFilters_currentIndexChanged\0"
    "on_pushButtonOpenETS_clicked\0"
    "on_pushButtonResetETS_clicked\0"
    "on_lineEditCommandETS_returnPressed\0"
    "on_pushButtonRemoveET1_clicked\0"
    "on_pushButtonRemoveET2_clicked\0"
    "on_doubleSpinBoxETS1mm_valueChanged\0"
    "on_doubleSpinBoxETS2mm_valueChanged\0"
    "on_pushButtonOpenFS_clicked\0"
    "on_pushButtonResetFS_clicked\0"
    "on_lineEditCommandFS_returnPressed\0"
    "on_doubleSpinBoxFSPmm_valueChanged\0"
    "on_doubleSpinBoxFSBmm_valueChanged\0"
    "on_pushButtonOpenET1_clicked\0"
    "on_pushButtonResetET1_clicked\0"
    "on_lineEditCommandET1_returnPressed\0"
    "on_spinBoxET1Counts_valueChanged\0"
    "on_pushButtonOpenET2_clicked\0"
    "on_pushButtonResetET2_clicked\0"
    "on_lineEditCommandET2_returnPressed\0"
    "on_spinBoxET2Counts_valueChanged\0"
    "on_pushButtonOpenLCVR_clicked\0"
    "on_lineEditCommandLCVR_returnPressed\0"
    "on_spinBoxLCVR1mV_valueChanged\0"
    "on_spinBoxLCVR2mV_valueChanged\0"
    "on_pushButtonStartModulation_clicked\0"
    "on_pushButtonOpenVTT_clicked\0"
    "on_lineEditCommandVTT_returnPressed\0"
    "on_pushButtonInsertICU_clicked\0"
    "on_doubleSpinBoxICUPdeg_editingFinished\0"
    "on_doubleSpinBoxICURdeg_editingFinished\0"
    "on_comboBoxVTTStopWheel_currentIndexChanged\0"
    "on_pushButtonOpenVTTServer_clicked\0"
    "on_lineEditCommandVTTServer_returnPressed\0"
    "on_pushButtonHomeICU_clicked\0"
    "on_pushButtonOpenCWP_clicked\0"
    "on_pushButtonHomeCWP_clicked\0"
    "on_doubleSpinBoxCWPdeg_editingFinished\0"
    "on_comboBoxTrigger_currentIndexChanged\0"
    "on_pushButtonLive_clicked\0"
    "on_pushButtonOpenCAM0_clicked\0"
    "on_pushButtonOpenCAM1_clicked\0"
    "on_pushButtonOpenCAM2_clicked\0"
    "on_comboBoxBinning_currentIndexChanged\0"
    "on_comboBoxROI_currentIndexChanged\0"
    "on_toolBoxAcquisition_currentChanged\0"
    "on_pushButtonReloadObsSettings_clicked\0"
    "on_pushButtonReloadCoreSettings_clicked\0"
    "on_pushButtonResetICU_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      74,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  384,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,  385,    2, 0x08 /* Private */,
       5,    0,  388,    2, 0x08 /* Private */,
       6,    0,  389,    2, 0x08 /* Private */,
       7,    0,  390,    2, 0x08 /* Private */,
       8,    3,  391,    2, 0x08 /* Private */,
      12,    1,  398,    2, 0x08 /* Private */,
      14,    0,  401,    2, 0x08 /* Private */,
      15,    0,  402,    2, 0x08 /* Private */,
      16,    0,  403,    2, 0x08 /* Private */,
      17,    0,  404,    2, 0x08 /* Private */,
      18,    0,  405,    2, 0x08 /* Private */,
      19,    0,  406,    2, 0x08 /* Private */,
      20,    0,  407,    2, 0x08 /* Private */,
      21,    1,  408,    2, 0x08 /* Private */,
      23,    0,  411,    2, 0x08 /* Private */,
      24,    0,  412,    2, 0x08 /* Private */,
      25,    0,  413,    2, 0x08 /* Private */,
      26,    1,  414,    2, 0x08 /* Private */,
      28,    1,  417,    2, 0x08 /* Private */,
      29,    0,  420,    2, 0x08 /* Private */,
      30,    0,  421,    2, 0x08 /* Private */,
      31,    1,  422,    2, 0x08 /* Private */,
      33,    1,  425,    2, 0x08 /* Private */,
      34,    1,  428,    2, 0x08 /* Private */,
      35,    1,  431,    2, 0x08 /* Private */,
      36,    1,  434,    2, 0x08 /* Private */,
      37,    0,  437,    2, 0x08 /* Private */,
      38,    0,  438,    2, 0x08 /* Private */,
      39,    1,  439,    2, 0x08 /* Private */,
      40,    1,  442,    2, 0x08 /* Private */,
      41,    1,  445,    2, 0x08 /* Private */,
      42,    1,  448,    2, 0x08 /* Private */,
      43,    1,  451,    2, 0x08 /* Private */,
      44,    0,  454,    2, 0x08 /* Private */,
      45,    0,  455,    2, 0x08 /* Private */,
      46,    1,  456,    2, 0x08 /* Private */,
      47,    1,  459,    2, 0x08 /* Private */,
      48,    1,  462,    2, 0x08 /* Private */,
      49,    0,  465,    2, 0x08 /* Private */,
      50,    0,  466,    2, 0x08 /* Private */,
      51,    1,  467,    2, 0x08 /* Private */,
      52,    1,  470,    2, 0x08 /* Private */,
      53,    0,  473,    2, 0x08 /* Private */,
      54,    0,  474,    2, 0x08 /* Private */,
      55,    1,  475,    2, 0x08 /* Private */,
      56,    1,  478,    2, 0x08 /* Private */,
      57,    0,  481,    2, 0x08 /* Private */,
      58,    1,  482,    2, 0x08 /* Private */,
      59,    1,  485,    2, 0x08 /* Private */,
      60,    1,  488,    2, 0x08 /* Private */,
      61,    1,  491,    2, 0x08 /* Private */,
      62,    0,  494,    2, 0x08 /* Private */,
      63,    1,  495,    2, 0x08 /* Private */,
      64,    0,  498,    2, 0x08 /* Private */,
      65,    0,  499,    2, 0x08 /* Private */,
      66,    1,  500,    2, 0x08 /* Private */,
      67,    1,  503,    2, 0x08 /* Private */,
      68,    0,  506,    2, 0x08 /* Private */,
      69,    0,  507,    2, 0x08 /* Private */,
      70,    1,  508,    2, 0x08 /* Private */,
      71,    0,  511,    2, 0x08 /* Private */,
      72,    0,  512,    2, 0x08 /* Private */,
      73,    1,  513,    2, 0x08 /* Private */,
      74,    1,  516,    2, 0x08 /* Private */,
      75,    1,  519,    2, 0x08 /* Private */,
      76,    1,  522,    2, 0x08 /* Private */,
      77,    1,  525,    2, 0x08 /* Private */,
      78,    1,  528,    2, 0x08 /* Private */,
      79,    1,  531,    2, 0x08 /* Private */,
      80,    1,  534,    2, 0x08 /* Private */,
      81,    0,  537,    2, 0x08 /* Private */,
      82,    0,  538,    2, 0x08 /* Private */,
      83,    0,  539,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    9,   10,   11,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Double,   32,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::Bool,   22,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::QString,   32,
    QMetaType::Void, QMetaType::Int,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stopAcquisition(); break;
        case 1: _t->addLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->prepareAcquisition(); break;
        case 3: _t->finishAcquisition(); break;
        case 4: _t->applyDetectorSettings(); break;
        case 5: _t->prepareDisplay((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 6: _t->plotData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->doObservation(); break;
        case 8: _t->doCharacterization(); break;
        case 9: _t->showSettings(); break;
        case 10: _t->saveSettings(); break;
        case 11: _t->loadFilterList(); break;
        case 12: _t->on_pushButtonSettings_clicked(); break;
        case 13: _t->on_pushButtonAutoSave_clicked(); break;
        case 14: _t->on_pushButtonAcquisition_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->on_lineEditComment_returnPressed(); break;
        case 16: _t->on_pushButtonGetValues_clicked(); break;
        case 17: _t->on_pushButtonClearLog_clicked(); break;
        case 18: _t->on_comboBoxStepResolution_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_pushButtonOpenFMS_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->on_pushButtonResetFMS_clicked(); break;
        case 21: _t->on_lineEditCommandFMS_returnPressed(); break;
        case 22: _t->on_spinBoxFilterPosition_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_doubleSpinBoxFMSXmm_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: _t->on_doubleSpinBoxFMSYmm_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 25: _t->on_comboBoxFilters_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->on_pushButtonOpenETS_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 27: _t->on_pushButtonResetETS_clicked(); break;
        case 28: _t->on_lineEditCommandETS_returnPressed(); break;
        case 29: _t->on_pushButtonRemoveET1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 30: _t->on_pushButtonRemoveET2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 31: _t->on_doubleSpinBoxETS1mm_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 32: _t->on_doubleSpinBoxETS2mm_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 33: _t->on_pushButtonOpenFS_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 34: _t->on_pushButtonResetFS_clicked(); break;
        case 35: _t->on_lineEditCommandFS_returnPressed(); break;
        case 36: _t->on_doubleSpinBoxFSPmm_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 37: _t->on_doubleSpinBoxFSBmm_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 38: _t->on_pushButtonOpenET1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->on_pushButtonResetET1_clicked(); break;
        case 40: _t->on_lineEditCommandET1_returnPressed(); break;
        case 41: _t->on_spinBoxET1Counts_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->on_pushButtonOpenET2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: _t->on_pushButtonResetET2_clicked(); break;
        case 44: _t->on_lineEditCommandET2_returnPressed(); break;
        case 45: _t->on_spinBoxET2Counts_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 46: _t->on_pushButtonOpenLCVR_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 47: _t->on_lineEditCommandLCVR_returnPressed(); break;
        case 48: _t->on_spinBoxLCVR1mV_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->on_spinBoxLCVR2mV_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->on_pushButtonStartModulation_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 51: _t->on_pushButtonOpenVTT_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 52: _t->on_lineEditCommandVTT_returnPressed(); break;
        case 53: _t->on_pushButtonInsertICU_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->on_doubleSpinBoxICUPdeg_editingFinished(); break;
        case 55: _t->on_doubleSpinBoxICURdeg_editingFinished(); break;
        case 56: _t->on_comboBoxVTTStopWheel_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 57: _t->on_pushButtonOpenVTTServer_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: _t->on_lineEditCommandVTTServer_returnPressed(); break;
        case 59: _t->on_pushButtonHomeICU_clicked(); break;
        case 60: _t->on_pushButtonOpenCWP_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->on_pushButtonHomeCWP_clicked(); break;
        case 62: _t->on_doubleSpinBoxCWPdeg_editingFinished(); break;
        case 63: _t->on_comboBoxTrigger_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 64: _t->on_pushButtonLive_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->on_pushButtonOpenCAM0_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->on_pushButtonOpenCAM1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: _t->on_pushButtonOpenCAM2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 68: _t->on_comboBoxBinning_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 69: _t->on_comboBoxROI_currentIndexChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 70: _t->on_toolBoxAcquisition_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 71: _t->on_pushButtonReloadObsSettings_clicked(); break;
        case 72: _t->on_pushButtonReloadCoreSettings_clicked(); break;
        case 73: _t->on_pushButtonResetICU_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopAcquisition)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 74)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 74;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 74)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 74;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::stopAcquisition()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
