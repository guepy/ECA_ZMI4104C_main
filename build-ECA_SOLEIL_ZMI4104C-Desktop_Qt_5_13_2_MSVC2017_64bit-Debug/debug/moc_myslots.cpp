/****************************************************************************
** Meta object code from reading C++ file 'myslots.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/myslots.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myslots.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MySlots_t {
    QByteArrayData data[10];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MySlots_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MySlots_t qt_meta_stringdata_MySlots = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MySlots"
QT_MOC_LITERAL(1, 8, 11), // "openFlyscan"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "closeFlyscan"
QT_MOC_LITERAL(4, 34, 12), // "openSettings"
QT_MOC_LITERAL(5, 47, 13), // "closeSettings"
QT_MOC_LITERAL(6, 61, 18), // "openPositionOffset"
QT_MOC_LITERAL(7, 80, 19), // "closePositionOffset"
QT_MOC_LITERAL(8, 100, 18), // "openPresetPosition"
QT_MOC_LITERAL(9, 119, 19) // "closePresetPosition"

    },
    "MySlots\0openFlyscan\0\0closeFlyscan\0"
    "openSettings\0closeSettings\0"
    "openPositionOffset\0closePositionOffset\0"
    "openPresetPosition\0closePresetPosition"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MySlots[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,
       4,    0,   56,    2, 0x06 /* Public */,
       5,    0,   57,    2, 0x06 /* Public */,
       6,    0,   58,    2, 0x06 /* Public */,
       7,    0,   59,    2, 0x06 /* Public */,
       8,    0,   60,    2, 0x06 /* Public */,
       9,    0,   61,    2, 0x06 /* Public */,

 // signals: parameters
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

void MySlots::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MySlots *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFlyscan(); break;
        case 1: _t->closeFlyscan(); break;
        case 2: _t->openSettings(); break;
        case 3: _t->closeSettings(); break;
        case 4: _t->openPositionOffset(); break;
        case 5: _t->closePositionOffset(); break;
        case 6: _t->openPresetPosition(); break;
        case 7: _t->closePresetPosition(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::openFlyscan)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::closeFlyscan)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::openSettings)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::closeSettings)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::openPositionOffset)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::closePositionOffset)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::openPresetPosition)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MySlots::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MySlots::closePresetPosition)) {
                *result = 7;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MySlots::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_MySlots.data,
    qt_meta_data_MySlots,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MySlots::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MySlots::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MySlots.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MySlots::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MySlots::openFlyscan()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MySlots::closeFlyscan()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MySlots::openSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MySlots::closeSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MySlots::openPositionOffset()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MySlots::closePositionOffset()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MySlots::openPresetPosition()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MySlots::closePresetPosition()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
