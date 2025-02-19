/****************************************************************************
** Meta object code from reading C++ file 'acquisition.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HELLRIDE-Polarimeter-BBI-Controls/acquisition.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'acquisition.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Acquisition_t {
    QByteArrayData data[26];
    char stringdata0[351];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Acquisition_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Acquisition_t qt_meta_stringdata_Acquisition = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Acquisition"
QT_MOC_LITERAL(1, 12, 8), // "Finished"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "plotData"
QT_MOC_LITERAL(4, 31, 5), // "Index"
QT_MOC_LITERAL(5, 37, 6), // "addLog"
QT_MOC_LITERAL(6, 44, 3), // "Log"
QT_MOC_LITERAL(7, 48, 14), // "updateProgress"
QT_MOC_LITERAL(8, 63, 7), // "Percent"
QT_MOC_LITERAL(9, 71, 15), // "updateOProgress"
QT_MOC_LITERAL(10, 87, 9), // "Interrupt"
QT_MOC_LITERAL(11, 97, 9), // "startLive"
QT_MOC_LITERAL(12, 107, 12), // "getFlatsData"
QT_MOC_LITERAL(13, 120, 12), // "getDarksData"
QT_MOC_LITERAL(14, 133, 14), // "getPinholeData"
QT_MOC_LITERAL(15, 148, 14), // "getScienceData"
QT_MOC_LITERAL(16, 163, 18), // "getCalibrationData"
QT_MOC_LITERAL(17, 182, 18), // "getTargetplateData"
QT_MOC_LITERAL(18, 201, 14), // "doET1Profiling"
QT_MOC_LITERAL(19, 216, 14), // "doET2Profiling"
QT_MOC_LITERAL(20, 231, 16), // "matchET1Passband"
QT_MOC_LITERAL(21, 248, 16), // "matchET2Passband"
QT_MOC_LITERAL(22, 265, 16), // "examineBestFocus"
QT_MOC_LITERAL(23, 282, 20), // "matchETPassbandsLine"
QT_MOC_LITERAL(24, 303, 23), // "doLCVR1Characterization"
QT_MOC_LITERAL(25, 327, 23) // "doLCVR2Characterization"

    },
    "Acquisition\0Finished\0\0plotData\0Index\0"
    "addLog\0Log\0updateProgress\0Percent\0"
    "updateOProgress\0Interrupt\0startLive\0"
    "getFlatsData\0getDarksData\0getPinholeData\0"
    "getScienceData\0getCalibrationData\0"
    "getTargetplateData\0doET1Profiling\0"
    "doET2Profiling\0matchET1Passband\0"
    "matchET2Passband\0examineBestFocus\0"
    "matchETPassbandsLine\0doLCVR1Characterization\0"
    "doLCVR2Characterization"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Acquisition[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06 /* Public */,
       3,    1,  120,    2, 0x06 /* Public */,
       5,    1,  123,    2, 0x06 /* Public */,
       7,    1,  126,    2, 0x06 /* Public */,
       9,    1,  129,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,  132,    2, 0x0a /* Public */,
      11,    0,  133,    2, 0x0a /* Public */,
      12,    0,  134,    2, 0x0a /* Public */,
      13,    0,  135,    2, 0x0a /* Public */,
      14,    0,  136,    2, 0x0a /* Public */,
      15,    0,  137,    2, 0x0a /* Public */,
      16,    0,  138,    2, 0x0a /* Public */,
      17,    0,  139,    2, 0x0a /* Public */,
      18,    0,  140,    2, 0x0a /* Public */,
      19,    0,  141,    2, 0x0a /* Public */,
      20,    0,  142,    2, 0x0a /* Public */,
      21,    0,  143,    2, 0x0a /* Public */,
      22,    0,  144,    2, 0x0a /* Public */,
      23,    0,  145,    2, 0x0a /* Public */,
      24,    0,  146,    2, 0x0a /* Public */,
      25,    0,  147,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Acquisition::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Acquisition *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Finished(); break;
        case 1: _t->plotData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->addLog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->updateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateOProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->Interrupt(); break;
        case 6: _t->startLive(); break;
        case 7: _t->getFlatsData(); break;
        case 8: _t->getDarksData(); break;
        case 9: _t->getPinholeData(); break;
        case 10: _t->getScienceData(); break;
        case 11: _t->getCalibrationData(); break;
        case 12: _t->getTargetplateData(); break;
        case 13: _t->doET1Profiling(); break;
        case 14: _t->doET2Profiling(); break;
        case 15: _t->matchET1Passband(); break;
        case 16: _t->matchET2Passband(); break;
        case 17: _t->examineBestFocus(); break;
        case 18: _t->matchETPassbandsLine(); break;
        case 19: _t->doLCVR1Characterization(); break;
        case 20: _t->doLCVR2Characterization(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Acquisition::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Acquisition::Finished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Acquisition::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Acquisition::plotData)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Acquisition::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Acquisition::addLog)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Acquisition::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Acquisition::updateProgress)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Acquisition::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Acquisition::updateOProgress)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Acquisition::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Acquisition.data,
    qt_meta_data_Acquisition,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Acquisition::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Acquisition::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Acquisition.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Acquisition::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void Acquisition::Finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Acquisition::plotData(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Acquisition::addLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Acquisition::updateProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Acquisition::updateOProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
