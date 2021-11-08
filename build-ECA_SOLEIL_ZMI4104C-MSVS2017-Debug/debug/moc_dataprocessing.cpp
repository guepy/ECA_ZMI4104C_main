/****************************************************************************
** Meta object code from reading C++ file 'dataprocessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/dataprocessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dataprocessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dataProcessing_t {
    QByteArrayData data[37];
    char stringdata0[597];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dataProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dataProcessing_t qt_meta_stringdata_dataProcessing = {
    {
QT_MOC_LITERAL(0, 0, 14), // "dataProcessing"
QT_MOC_LITERAL(1, 15, 14), // "initBoardsDone"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "initAxisComplete"
QT_MOC_LITERAL(4, 48, 17), // "cecConfigComplete"
QT_MOC_LITERAL(5, 66, 15), // "flyscanProcTerm"
QT_MOC_LITERAL(6, 82, 16), // "flyscanErrorCode"
QT_MOC_LITERAL(7, 99, 8), // "err_code"
QT_MOC_LITERAL(8, 108, 17), // "flyscanStatValues"
QT_MOC_LITERAL(9, 126, 14), // "unsigned char*"
QT_MOC_LITERAL(10, 141, 7), // "axisTab"
QT_MOC_LITERAL(11, 149, 7), // "double*"
QT_MOC_LITERAL(12, 157, 4), // "mean"
QT_MOC_LITERAL(13, 162, 6), // "stdDev"
QT_MOC_LITERAL(14, 169, 12), // "getLEDsColor"
QT_MOC_LITERAL(15, 182, 4), // "int*"
QT_MOC_LITERAL(16, 187, 9), // "updatePVT"
QT_MOC_LITERAL(17, 197, 5), // "index"
QT_MOC_LITERAL(18, 203, 3), // "val"
QT_MOC_LITERAL(19, 207, 9), // "updateOAS"
QT_MOC_LITERAL(20, 217, 15), // "updateCECRatios"
QT_MOC_LITERAL(21, 233, 4), // "axis"
QT_MOC_LITERAL(22, 238, 9), // "CEratios*"
QT_MOC_LITERAL(23, 248, 27), // "on_acquisitionTimer_timeout"
QT_MOC_LITERAL(24, 276, 29), // "on_initBoardsRequest_recieved"
QT_MOC_LITERAL(25, 306, 28), // "on_resetAxisRequest_recieved"
QT_MOC_LITERAL(26, 335, 32), // "on_configureCECHardware_recieved"
QT_MOC_LITERAL(27, 368, 8), // "ceVelMin"
QT_MOC_LITERAL(28, 377, 8), // "ceVelMax"
QT_MOC_LITERAL(29, 386, 27), // "on_stopCECHardware_recieved"
QT_MOC_LITERAL(30, 414, 33), // "on_changeBiasModeRequest_reci..."
QT_MOC_LITERAL(31, 448, 35), // "on_configureFlyscanRequest_re..."
QT_MOC_LITERAL(32, 484, 39), // "on_configureFifoFlyscanReques..."
QT_MOC_LITERAL(33, 524, 25), // "on_OffsetPosition_Changed"
QT_MOC_LITERAL(34, 550, 9), // "offPosPtr"
QT_MOC_LITERAL(35, 560, 25), // "on_PresetPosition_Changed"
QT_MOC_LITERAL(36, 586, 10) // "presPosPtr"

    },
    "dataProcessing\0initBoardsDone\0\0"
    "initAxisComplete\0cecConfigComplete\0"
    "flyscanProcTerm\0flyscanErrorCode\0"
    "err_code\0flyscanStatValues\0unsigned char*\0"
    "axisTab\0double*\0mean\0stdDev\0getLEDsColor\0"
    "int*\0updatePVT\0index\0val\0updateOAS\0"
    "updateCECRatios\0axis\0CEratios*\0"
    "on_acquisitionTimer_timeout\0"
    "on_initBoardsRequest_recieved\0"
    "on_resetAxisRequest_recieved\0"
    "on_configureCECHardware_recieved\0"
    "ceVelMin\0ceVelMax\0on_stopCECHardware_recieved\0"
    "on_changeBiasModeRequest_recieved\0"
    "on_configureFlyscanRequest_recieved\0"
    "on_configureFifoFlyscanRequest_recieved\0"
    "on_OffsetPosition_Changed\0offPosPtr\0"
    "on_PresetPosition_Changed\0presPosPtr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dataProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,
       3,    0,  115,    2, 0x06 /* Public */,
       4,    0,  116,    2, 0x06 /* Public */,
       5,    0,  117,    2, 0x06 /* Public */,
       6,    1,  118,    2, 0x06 /* Public */,
       8,    3,  121,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,  128,    2, 0x0a /* Public */,
      16,    2,  131,    2, 0x0a /* Public */,
      19,    2,  136,    2, 0x0a /* Public */,
      20,    3,  141,    2, 0x0a /* Public */,
      23,    0,  148,    2, 0x0a /* Public */,
      24,    0,  149,    2, 0x0a /* Public */,
      25,    1,  150,    2, 0x0a /* Public */,
      26,    3,  153,    2, 0x0a /* Public */,
      29,    1,  160,    2, 0x0a /* Public */,
      30,    0,  163,    2, 0x0a /* Public */,
      31,    0,  164,    2, 0x0a /* Public */,
      32,    0,  165,    2, 0x0a /* Public */,
      33,    1,  166,    2, 0x0a /* Public */,
      35,    1,  169,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 11,   10,   12,   13,

 // slots: parameters
    QMetaType::Int, 0x80000000 | 15,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   17,   18,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   17,   18,
    QMetaType::Int, QMetaType::UInt, 0x80000000 | 22, QMetaType::UInt,   21,   18,   17,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   21,   27,   28,
    QMetaType::Int, QMetaType::UInt,   21,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 11,   34,
    QMetaType::Void, 0x80000000 | 11,   36,

       0        // eod
};

void dataProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dataProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initBoardsDone(); break;
        case 1: _t->initAxisComplete(); break;
        case 2: _t->cecConfigComplete(); break;
        case 3: _t->flyscanProcTerm(); break;
        case 4: _t->flyscanErrorCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->flyscanStatValues((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 6: { int _r = _t->getLEDsColor((*reinterpret_cast< int*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 8: _t->updateOAS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 9: { int _r = _t->updateCECRatios((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< CEratios*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->on_acquisitionTimer_timeout();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->on_initBoardsRequest_recieved(); break;
        case 12: _t->on_resetAxisRequest_recieved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: { int _r = _t->on_configureCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: { int _r = _t->on_stopCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->on_changeBiasModeRequest_recieved(); break;
        case 16: { int _r = _t->on_configureFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 17: { int _r = _t->on_configureFifoFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->on_OffsetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 19: _t->on_PresetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::initBoardsDone)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::initAxisComplete)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::cecConfigComplete)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::flyscanProcTerm)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::flyscanErrorCode)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned char * , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::flyscanStatValues)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject dataProcessing::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_dataProcessing.data,
    qt_meta_data_dataProcessing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *dataProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dataProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dataProcessing.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int dataProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void dataProcessing::initBoardsDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void dataProcessing::initAxisComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void dataProcessing::cecConfigComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void dataProcessing::flyscanProcTerm()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void dataProcessing::flyscanErrorCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void dataProcessing::flyscanStatValues(unsigned char * _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
