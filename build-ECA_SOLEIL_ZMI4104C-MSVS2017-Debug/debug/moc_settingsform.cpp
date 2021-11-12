/****************************************************************************
** Meta object code from reading C++ file 'settingsform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/settingsform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingsForm_t {
    QByteArrayData data[15];
    char stringdata0[271];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsForm_t qt_meta_stringdata_SettingsForm = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SettingsForm"
QT_MOC_LITERAL(1, 13, 9), // "closeThis"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 24), // "modifyBaseAddressRequest"
QT_MOC_LITERAL(4, 49, 21), // "updateSettingsRequest"
QT_MOC_LITERAL(5, 71, 1), // "a"
QT_MOC_LITERAL(6, 73, 1), // "b"
QT_MOC_LITERAL(7, 75, 3), // "val"
QT_MOC_LITERAL(8, 79, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(9, 103, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(10, 135, 5), // "index"
QT_MOC_LITERAL(11, 141, 32), // "on_interType_currentIndexChanged"
QT_MOC_LITERAL(12, 174, 35), // "on_precisionVal_currentIndexC..."
QT_MOC_LITERAL(13, 210, 35), // "on_resetFindVel_currentIndexC..."
QT_MOC_LITERAL(14, 246, 24) // "on_pushButton_10_clicked"

    },
    "SettingsForm\0closeThis\0\0"
    "modifyBaseAddressRequest\0updateSettingsRequest\0"
    "a\0b\0val\0on_pushButton_5_clicked\0"
    "on_comboBox_currentIndexChanged\0index\0"
    "on_interType_currentIndexChanged\0"
    "on_precisionVal_currentIndexChanged\0"
    "on_resetFindVel_currentIndexChanged\0"
    "on_pushButton_10_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    1,   60,    2, 0x06 /* Public */,
       4,    3,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   70,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,
      11,    1,   74,    2, 0x08 /* Private */,
      12,    1,   77,    2, 0x08 /* Private */,
      13,    1,   80,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void SettingsForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeThis(); break;
        case 1: _t->modifyBaseAddressRequest((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->updateSettingsRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->on_pushButton_5_clicked(); break;
        case 4: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_interType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_precisionVal_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_resetFindVel_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_10_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsForm::closeThis)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsForm::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsForm::modifyBaseAddressRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsForm::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsForm::updateSettingsRequest)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingsForm::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SettingsForm.data,
    qt_meta_data_SettingsForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingsForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void SettingsForm::closeThis()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingsForm::modifyBaseAddressRequest(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingsForm::updateSettingsRequest(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
