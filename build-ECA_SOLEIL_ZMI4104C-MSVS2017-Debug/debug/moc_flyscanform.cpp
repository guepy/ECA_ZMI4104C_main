/****************************************************************************
** Meta object code from reading C++ file 'flyscanform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/flyscanform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flyscanform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlyscanForm_t {
    QByteArrayData data[19];
    char stringdata0[278];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlyscanForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlyscanForm_t qt_meta_stringdata_FlyscanForm = {
    {
QT_MOC_LITERAL(0, 0, 11), // "FlyscanForm"
QT_MOC_LITERAL(1, 12, 8), // "openThis"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "closeThis"
QT_MOC_LITERAL(4, 32, 21), // "ramDataFlyscanRequest"
QT_MOC_LITERAL(5, 54, 4), // "freq"
QT_MOC_LITERAL(6, 59, 2), // "it"
QT_MOC_LITERAL(7, 62, 2), // "np"
QT_MOC_LITERAL(8, 65, 2), // "na"
QT_MOC_LITERAL(9, 68, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(10, 92, 10), // "selectFile"
QT_MOC_LITERAL(11, 103, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(12, 135, 5), // "index"
QT_MOC_LITERAL(13, 141, 21), // "on_itCheckBox_clicked"
QT_MOC_LITERAL(14, 163, 23), // "on_freqCheckBox_clicked"
QT_MOC_LITERAL(15, 187, 21), // "on_npCheckBox_clicked"
QT_MOC_LITERAL(16, 209, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(17, 233, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(18, 255, 22) // "on_StartButton_clicked"

    },
    "FlyscanForm\0openThis\0\0closeThis\0"
    "ramDataFlyscanRequest\0freq\0it\0np\0na\0"
    "on_pushButton_5_clicked\0selectFile\0"
    "on_comboBox_currentIndexChanged\0index\0"
    "on_itCheckBox_clicked\0on_freqCheckBox_clicked\0"
    "on_npCheckBox_clicked\0on_pushButton_2_clicked\0"
    "on_pushButton_clicked\0on_StartButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlyscanForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    4,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   85,    2, 0x08 /* Private */,
      10,    0,   86,    2, 0x08 /* Private */,
      11,    1,   87,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,
      17,    0,   94,    2, 0x08 /* Private */,
      18,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FlyscanForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlyscanForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openThis(); break;
        case 1: _t->closeThis(); break;
        case 2: _t->ramDataFlyscanRequest((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 3: _t->on_pushButton_5_clicked(); break;
        case 4: _t->selectFile(); break;
        case 5: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_itCheckBox_clicked(); break;
        case 7: _t->on_freqCheckBox_clicked(); break;
        case 8: _t->on_npCheckBox_clicked(); break;
        case 9: _t->on_pushButton_2_clicked(); break;
        case 10: _t->on_pushButton_clicked(); break;
        case 11: _t->on_StartButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FlyscanForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlyscanForm::openThis)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlyscanForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlyscanForm::closeThis)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FlyscanForm::*)(double , double , double , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlyscanForm::ramDataFlyscanRequest)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FlyscanForm::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_FlyscanForm.data,
    qt_meta_data_FlyscanForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FlyscanForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlyscanForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlyscanForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FlyscanForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void FlyscanForm::openThis()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FlyscanForm::closeThis()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void FlyscanForm::ramDataFlyscanRequest(double _t1, double _t2, double _t3, unsigned int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
