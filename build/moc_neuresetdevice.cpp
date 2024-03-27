/****************************************************************************
** Meta object code from reading C++ file 'neuresetdevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../neuresetdevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'neuresetdevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NeuresetDevice_t {
    QByteArrayData data[13];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NeuresetDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NeuresetDevice_t qt_meta_stringdata_NeuresetDevice = {
    {
QT_MOC_LITERAL(0, 0, 14), // "NeuresetDevice"
QT_MOC_LITERAL(1, 15, 14), // "sessionStarted"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 13), // "sessionPaused"
QT_MOC_LITERAL(4, 45, 14), // "sessionResumed"
QT_MOC_LITERAL(5, 60, 12), // "sessionEnded"
QT_MOC_LITERAL(6, 73, 12), // "pauseSession"
QT_MOC_LITERAL(7, 86, 13), // "resumeSession"
QT_MOC_LITERAL(8, 100, 10), // "endSession"
QT_MOC_LITERAL(9, 111, 13), // "gotNewSession"
QT_MOC_LITERAL(10, 125, 8), // "Session*"
QT_MOC_LITERAL(11, 134, 7), // "session"
QT_MOC_LITERAL(12, 142, 29) // "onBaselineCalculationFinished"

    },
    "NeuresetDevice\0sessionStarted\0\0"
    "sessionPaused\0sessionResumed\0sessionEnded\0"
    "pauseSession\0resumeSession\0endSession\0"
    "gotNewSession\0Session*\0session\0"
    "onBaselineCalculationFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NeuresetDevice[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    0,   61,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    1,   66,    2, 0x0a /* Public */,
      12,    0,   69,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void NeuresetDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NeuresetDevice *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sessionStarted(); break;
        case 1: _t->sessionPaused(); break;
        case 2: _t->sessionResumed(); break;
        case 3: _t->sessionEnded(); break;
        case 4: _t->pauseSession(); break;
        case 5: _t->resumeSession(); break;
        case 6: _t->endSession(); break;
        case 7: _t->gotNewSession((*reinterpret_cast< Session*(*)>(_a[1]))); break;
        case 8: _t->onBaselineCalculationFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Session* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NeuresetDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NeuresetDevice::sessionStarted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NeuresetDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NeuresetDevice::sessionPaused)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NeuresetDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NeuresetDevice::sessionResumed)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NeuresetDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NeuresetDevice::sessionEnded)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NeuresetDevice::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NeuresetDevice.data,
    qt_meta_data_NeuresetDevice,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NeuresetDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NeuresetDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NeuresetDevice.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NeuresetDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void NeuresetDevice::sessionStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NeuresetDevice::sessionPaused()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NeuresetDevice::sessionResumed()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void NeuresetDevice::sessionEnded()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
