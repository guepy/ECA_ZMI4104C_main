/****************************************************************************
** Meta object code from reading C++ file 'serialoutput.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/serialoutput.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialoutput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_serialOutput_t {
    QByteArrayData data[30];
    char stringdata0[499];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serialOutput_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serialOutput_t qt_meta_stringdata_serialOutput = {
    {
QT_MOC_LITERAL(0, 0, 12), // "serialOutput"
QT_MOC_LITERAL(1, 13, 12), // "updateParams"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 1), // "i"
QT_MOC_LITERAL(4, 29, 20), // "std::complex<double>"
QT_MOC_LITERAL(5, 50, 6), // "params"
QT_MOC_LITERAL(6, 57, 21), // "configureSerialOutput"
QT_MOC_LITERAL(7, 79, 4), // "SCLK"
QT_MOC_LITERAL(8, 84, 3), // "clk"
QT_MOC_LITERAL(9, 88, 18), // "SerialOutputDriver"
QT_MOC_LITERAL(10, 107, 3), // "sdo"
QT_MOC_LITERAL(11, 111, 22), // "SerialDataPositionSize"
QT_MOC_LITERAL(12, 134, 4), // "sdps"
QT_MOC_LITERAL(13, 139, 9), // "BitWindow"
QT_MOC_LITERAL(14, 149, 2), // "bw"
QT_MOC_LITERAL(15, 152, 8), // "uint32_t"
QT_MOC_LITERAL(16, 161, 8), // "sampFreq"
QT_MOC_LITERAL(17, 170, 17), // "startSerialOutput"
QT_MOC_LITERAL(18, 188, 16), // "stopSerialOutput"
QT_MOC_LITERAL(19, 205, 9), // "closeThis"
QT_MOC_LITERAL(20, 215, 36), // "on_serialClockIn_currentIndex..."
QT_MOC_LITERAL(21, 252, 5), // "index"
QT_MOC_LITERAL(22, 258, 41), // "on_serialDriverOutput_current..."
QT_MOC_LITERAL(23, 300, 32), // "on_bitWindow_currentIndexChanged"
QT_MOC_LITERAL(24, 333, 32), // "on_precision_currentIndexChanged"
QT_MOC_LITERAL(25, 366, 32), // "on_configureSerialOutput_clicked"
QT_MOC_LITERAL(26, 399, 27), // "on_stopSerialOutput_clicked"
QT_MOC_LITERAL(27, 427, 28), // "on_startSerialOutput_clicked"
QT_MOC_LITERAL(28, 456, 37), // "on_serialBusSamplingFreq_valu..."
QT_MOC_LITERAL(29, 494, 4) // "arg1"

    },
    "serialOutput\0updateParams\0\0i\0"
    "std::complex<double>\0params\0"
    "configureSerialOutput\0SCLK\0clk\0"
    "SerialOutputDriver\0sdo\0SerialDataPositionSize\0"
    "sdps\0BitWindow\0bw\0uint32_t\0sampFreq\0"
    "startSerialOutput\0stopSerialOutput\0"
    "closeThis\0on_serialClockIn_currentIndexChanged\0"
    "index\0on_serialDriverOutput_currentIndexChanged\0"
    "on_bitWindow_currentIndexChanged\0"
    "on_precision_currentIndexChanged\0"
    "on_configureSerialOutput_clicked\0"
    "on_stopSerialOutput_clicked\0"
    "on_startSerialOutput_clicked\0"
    "on_serialBusSamplingFreq_valueChanged\0"
    "arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serialOutput[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   79,    2, 0x06 /* Public */,
       6,    5,   84,    2, 0x06 /* Public */,
      17,    0,   95,    2, 0x06 /* Public */,
      18,    0,   96,    2, 0x06 /* Public */,
      19,    0,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,   98,    2, 0x08 /* Private */,
      22,    1,  101,    2, 0x08 /* Private */,
      23,    1,  104,    2, 0x08 /* Private */,
      24,    1,  107,    2, 0x08 /* Private */,
      25,    0,  110,    2, 0x08 /* Private */,
      26,    0,  111,    2, 0x08 /* Private */,
      27,    0,  112,    2, 0x08 /* Private */,
      28,    1,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 13, 0x80000000 | 15,    8,   10,   12,   14,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   29,

       0        // eod
};

void serialOutput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<serialOutput *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateParams((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::complex<double>(*)>(_a[2]))); break;
        case 1: _t->configureSerialOutput((*reinterpret_cast< SCLK(*)>(_a[1])),(*reinterpret_cast< SerialOutputDriver(*)>(_a[2])),(*reinterpret_cast< SerialDataPositionSize(*)>(_a[3])),(*reinterpret_cast< BitWindow(*)>(_a[4])),(*reinterpret_cast< uint32_t(*)>(_a[5]))); break;
        case 2: _t->startSerialOutput(); break;
        case 3: _t->stopSerialOutput(); break;
        case 4: _t->closeThis(); break;
        case 5: _t->on_serialClockIn_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_serialDriverOutput_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_bitWindow_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_precision_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_configureSerialOutput_clicked(); break;
        case 10: _t->on_stopSerialOutput_clicked(); break;
        case 11: _t->on_startSerialOutput_clicked(); break;
        case 12: _t->on_serialBusSamplingFreq_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (serialOutput::*)(int , std::complex<double> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialOutput::updateParams)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (serialOutput::*)(SCLK , SerialOutputDriver , SerialDataPositionSize , BitWindow , uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialOutput::configureSerialOutput)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (serialOutput::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialOutput::startSerialOutput)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (serialOutput::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialOutput::stopSerialOutput)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (serialOutput::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&serialOutput::closeThis)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject serialOutput::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_serialOutput.data,
    qt_meta_data_serialOutput,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *serialOutput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serialOutput::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_serialOutput.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int serialOutput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void serialOutput::updateParams(int _t1, std::complex<double> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void serialOutput::configureSerialOutput(SCLK _t1, SerialOutputDriver _t2, SerialDataPositionSize _t3, BitWindow _t4, uint32_t _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void serialOutput::startSerialOutput()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void serialOutput::stopSerialOutput()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void serialOutput::closeThis()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE