/****************************************************************************
** Meta object code from reading C++ file 'plotview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../HELLRIDE-Polarimeter-BBI-Controls/plotview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plotview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_plotview_t {
    QByteArrayData data[13];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_plotview_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_plotview_t qt_meta_stringdata_plotview = {
    {
QT_MOC_LITERAL(0, 0, 8), // "plotview"
QT_MOC_LITERAL(1, 9, 10), // "plotDataXY"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 19), // "std::vector<double>"
QT_MOC_LITERAL(4, 41, 1), // "X"
QT_MOC_LITERAL(5, 43, 1), // "Y"
QT_MOC_LITERAL(6, 45, 11), // "plotDataXXY"
QT_MOC_LITERAL(7, 57, 2), // "X1"
QT_MOC_LITERAL(8, 60, 2), // "X2"
QT_MOC_LITERAL(9, 63, 11), // "plotDataXYY"
QT_MOC_LITERAL(10, 75, 2), // "Y1"
QT_MOC_LITERAL(11, 78, 2), // "Y2"
QT_MOC_LITERAL(12, 81, 12) // "plotDataXXYY"

    },
    "plotview\0plotDataXY\0\0std::vector<double>\0"
    "X\0Y\0plotDataXXY\0X1\0X2\0plotDataXYY\0Y1\0"
    "Y2\0plotDataXXYY"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_plotview[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x0a /* Public */,
       6,    3,   39,    2, 0x0a /* Public */,
       9,    3,   46,    2, 0x0a /* Public */,
      12,    4,   53,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    7,    8,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    4,   10,   11,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3, 0x80000000 | 3,    7,    8,   10,   11,

       0        // eod
};

void plotview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<plotview *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->plotDataXY((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< std::vector<double>(*)>(_a[2]))); break;
        case 1: _t->plotDataXXY((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< std::vector<double>(*)>(_a[2])),(*reinterpret_cast< std::vector<double>(*)>(_a[3]))); break;
        case 2: _t->plotDataXYY((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< std::vector<double>(*)>(_a[2])),(*reinterpret_cast< std::vector<double>(*)>(_a[3]))); break;
        case 3: _t->plotDataXXYY((*reinterpret_cast< std::vector<double>(*)>(_a[1])),(*reinterpret_cast< std::vector<double>(*)>(_a[2])),(*reinterpret_cast< std::vector<double>(*)>(_a[3])),(*reinterpret_cast< std::vector<double>(*)>(_a[4]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject plotview::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_plotview.data,
    qt_meta_data_plotview,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *plotview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *plotview::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_plotview.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int plotview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
