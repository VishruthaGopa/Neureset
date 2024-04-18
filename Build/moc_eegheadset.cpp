/****************************************************************************
** Meta object code from reading C++ file 'eegheadset.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Testing2/eegheadset.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eegheadset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EEGHeadset_t {
    QByteArrayData data[11];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EEGHeadset_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EEGHeadset_t qt_meta_stringdata_EEGHeadset = {
    {
QT_MOC_LITERAL(0, 0, 10), // "EEGHeadset"
QT_MOC_LITERAL(1, 11, 10), // "newSession"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 8), // "Session*"
QT_MOC_LITERAL(4, 32, 7), // "session"
QT_MOC_LITERAL(5, 40, 10), // "QDateTime&"
QT_MOC_LITERAL(6, 51, 18), // "mainwindowDateTime"
QT_MOC_LITERAL(7, 70, 18), // "treatmentCompleted"
QT_MOC_LITERAL(8, 89, 3), // "feq"
QT_MOC_LITERAL(9, 93, 20), // "measurementCompleted"
QT_MOC_LITERAL(10, 114, 14) // "updateDateTime"

    },
    "EEGHeadset\0newSession\0\0Session*\0session\0"
    "QDateTime&\0mainwindowDateTime\0"
    "treatmentCompleted\0feq\0measurementCompleted\0"
    "updateDateTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EEGHeadset[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       7,    1,   39,    2, 0x06 /* Public */,
       9,    0,   42,    2, 0x06 /* Public */,
      10,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EEGHeadset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EEGHeadset *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newSession((*reinterpret_cast< Session*(*)>(_a[1])),(*reinterpret_cast< QDateTime(*)>(_a[2]))); break;
        case 1: _t->treatmentCompleted((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->measurementCompleted(); break;
        case 3: _t->updateDateTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            using _t = void (EEGHeadset::*)(Session * , QDateTime & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EEGHeadset::newSession)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EEGHeadset::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EEGHeadset::treatmentCompleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EEGHeadset::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EEGHeadset::measurementCompleted)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EEGHeadset::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EEGHeadset::updateDateTime)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EEGHeadset::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_EEGHeadset.data,
    qt_meta_data_EEGHeadset,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EEGHeadset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EEGHeadset::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EEGHeadset.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EEGHeadset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EEGHeadset::newSession(Session * _t1, QDateTime & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EEGHeadset::treatmentCompleted(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void EEGHeadset::measurementCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void EEGHeadset::updateDateTime()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
