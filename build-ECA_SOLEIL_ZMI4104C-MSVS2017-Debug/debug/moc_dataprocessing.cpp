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
    QByteArrayData data[40];
    char stringdata0[635];
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
QT_MOC_LITERAL(14, 169, 33), // "on_updateSettingsRequest_reci..."
QT_MOC_LITERAL(15, 203, 1), // "a"
QT_MOC_LITERAL(16, 205, 1), // "b"
QT_MOC_LITERAL(17, 207, 3), // "val"
QT_MOC_LITERAL(18, 211, 12), // "getLEDsColor"
QT_MOC_LITERAL(19, 224, 4), // "int*"
QT_MOC_LITERAL(20, 229, 9), // "updatePVT"
QT_MOC_LITERAL(21, 239, 5), // "index"
QT_MOC_LITERAL(22, 245, 9), // "updateOAS"
QT_MOC_LITERAL(23, 255, 15), // "updateCECRatios"
QT_MOC_LITERAL(24, 271, 4), // "axis"
QT_MOC_LITERAL(25, 276, 9), // "CEratios*"
QT_MOC_LITERAL(26, 286, 27), // "on_acquisitionTimer_timeout"
QT_MOC_LITERAL(27, 314, 29), // "on_initBoardsRequest_recieved"
QT_MOC_LITERAL(28, 344, 28), // "on_resetAxisRequest_recieved"
QT_MOC_LITERAL(29, 373, 32), // "on_configureCECHardware_recieved"
QT_MOC_LITERAL(30, 406, 8), // "ceVelMin"
QT_MOC_LITERAL(31, 415, 8), // "ceVelMax"
QT_MOC_LITERAL(32, 424, 27), // "on_stopCECHardware_recieved"
QT_MOC_LITERAL(33, 452, 33), // "on_changeBiasModeRequest_reci..."
QT_MOC_LITERAL(34, 486, 35), // "on_configureFlyscanRequest_re..."
QT_MOC_LITERAL(35, 522, 39), // "on_configureFifoFlyscanReques..."
QT_MOC_LITERAL(36, 562, 25), // "on_OffsetPosition_Changed"
QT_MOC_LITERAL(37, 588, 9), // "offPosPtr"
QT_MOC_LITERAL(38, 598, 25), // "on_PresetPosition_Changed"
QT_MOC_LITERAL(39, 624, 10) // "presPosPtr"

    },
    "dataProcessing\0initBoardsDone\0\0"
    "initAxisComplete\0cecConfigComplete\0"
    "flyscanProcTerm\0flyscanErrorCode\0"
    "err_code\0flyscanStatValues\0unsigned char*\0"
    "axisTab\0double*\0mean\0stdDev\0"
    "on_updateSettingsRequest_recieved\0a\0"
    "b\0val\0getLEDsColor\0int*\0updatePVT\0"
    "index\0updateOAS\0updateCECRatios\0axis\0"
    "CEratios*\0on_acquisitionTimer_timeout\0"
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
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x06 /* Public */,
       3,    0,  120,    2, 0x06 /* Public */,
       4,    0,  121,    2, 0x06 /* Public */,
       5,    0,  122,    2, 0x06 /* Public */,
       6,    1,  123,    2, 0x06 /* Public */,
       8,    3,  126,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    3,  133,    2, 0x0a /* Public */,
      18,    1,  140,    2, 0x0a /* Public */,
      20,    2,  143,    2, 0x0a /* Public */,
      22,    2,  148,    2, 0x0a /* Public */,
      23,    3,  153,    2, 0x0a /* Public */,
      26,    0,  160,    2, 0x0a /* Public */,
      27,    0,  161,    2, 0x0a /* Public */,
      28,    1,  162,    2, 0x0a /* Public */,
      29,    3,  165,    2, 0x0a /* Public */,
      32,    1,  172,    2, 0x0a /* Public */,
      33,    0,  175,    2, 0x0a /* Public */,
      34,    0,  176,    2, 0x0a /* Public */,
      35,    0,  177,    2, 0x0a /* Public */,
      36,    1,  178,    2, 0x0a /* Public */,
      38,    1,  181,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 11,   10,   12,   13,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   15,   16,   17,
    QMetaType::Int, 0x80000000 | 19,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   21,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   21,   17,
    QMetaType::Int, QMetaType::UInt, 0x80000000 | 25, QMetaType::UInt,   24,   17,   21,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   24,   30,   31,
    QMetaType::Int, QMetaType::UInt,   24,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 11,   37,
    QMetaType::Void, 0x80000000 | 11,   39,

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
        case 6: _t->on_updateSettingsRequest_recieved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: { int _r = _t->getLEDsColor((*reinterpret_cast< int*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 9: _t->updateOAS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 10: { int _r = _t->updateCECRatios((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< CEratios*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 11: { int _r = _t->on_acquisitionTimer_timeout();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->on_initBoardsRequest_recieved(); break;
        case 13: _t->on_resetAxisRequest_recieved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: { int _r = _t->on_configureCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: { int _r = _t->on_stopCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->on_changeBiasModeRequest_recieved(); break;
        case 17: { int _r = _t->on_configureFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 18: { int _r = _t->on_configureFifoFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->on_OffsetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 20: _t->on_PresetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
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
