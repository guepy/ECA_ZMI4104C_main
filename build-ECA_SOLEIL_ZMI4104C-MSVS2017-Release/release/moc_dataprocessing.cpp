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
    QByteArrayData data[54];
    char stringdata0[839];
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
QT_MOC_LITERAL(14, 169, 16), // "ssiDataAvailable"
QT_MOC_LITERAL(15, 186, 4), // "axis"
QT_MOC_LITERAL(16, 191, 7), // "ssiVals"
QT_MOC_LITERAL(17, 199, 10), // "optPwrVals"
QT_MOC_LITERAL(18, 210, 19), // "readGSEDataComplete"
QT_MOC_LITERAL(19, 230, 7), // "gseData"
QT_MOC_LITERAL(20, 238, 31), // "updateSettingsRequest_completed"
QT_MOC_LITERAL(21, 270, 7), // "uint8_t"
QT_MOC_LITERAL(22, 278, 1), // "a"
QT_MOC_LITERAL(23, 280, 1), // "b"
QT_MOC_LITERAL(24, 282, 3), // "val"
QT_MOC_LITERAL(25, 286, 16), // "ssiSquelchValues"
QT_MOC_LITERAL(26, 303, 10), // "KpKvValues"
QT_MOC_LITERAL(27, 314, 9), // "uint16_t*"
QT_MOC_LITERAL(28, 324, 5), // "coeff"
QT_MOC_LITERAL(29, 330, 9), // "apdValues"
QT_MOC_LITERAL(30, 340, 9), // "uint32_t*"
QT_MOC_LITERAL(31, 350, 33), // "on_updateSettingsRequest_reci..."
QT_MOC_LITERAL(32, 384, 35), // "on_initSettingsFormRequest_re..."
QT_MOC_LITERAL(33, 420, 12), // "getLEDsColor"
QT_MOC_LITERAL(34, 433, 4), // "int*"
QT_MOC_LITERAL(35, 438, 9), // "updatePVT"
QT_MOC_LITERAL(36, 448, 5), // "index"
QT_MOC_LITERAL(37, 454, 9), // "updateOAS"
QT_MOC_LITERAL(38, 464, 15), // "updateCECRatios"
QT_MOC_LITERAL(39, 480, 9), // "CEratios*"
QT_MOC_LITERAL(40, 490, 27), // "on_acquisitionTimer_timeout"
QT_MOC_LITERAL(41, 518, 29), // "on_initBoardsRequest_recieved"
QT_MOC_LITERAL(42, 548, 28), // "on_resetAxisRequest_recieved"
QT_MOC_LITERAL(43, 577, 32), // "on_configureCECHardware_recieved"
QT_MOC_LITERAL(44, 610, 8), // "ceVelMin"
QT_MOC_LITERAL(45, 619, 8), // "ceVelMax"
QT_MOC_LITERAL(46, 628, 27), // "on_stopCECHardware_recieved"
QT_MOC_LITERAL(47, 656, 33), // "on_changeBiasModeRequest_reci..."
QT_MOC_LITERAL(48, 690, 35), // "on_configureFlyscanRequest_re..."
QT_MOC_LITERAL(49, 726, 39), // "on_configureFifoFlyscanReques..."
QT_MOC_LITERAL(50, 766, 25), // "on_OffsetPosition_Changed"
QT_MOC_LITERAL(51, 792, 9), // "offPosPtr"
QT_MOC_LITERAL(52, 802, 25), // "on_PresetPosition_Changed"
QT_MOC_LITERAL(53, 828, 10) // "presPosPtr"

    },
    "dataProcessing\0initBoardsDone\0\0"
    "initAxisComplete\0cecConfigComplete\0"
    "flyscanProcTerm\0flyscanErrorCode\0"
    "err_code\0flyscanStatValues\0unsigned char*\0"
    "axisTab\0double*\0mean\0stdDev\0"
    "ssiDataAvailable\0axis\0ssiVals\0optPwrVals\0"
    "readGSEDataComplete\0gseData\0"
    "updateSettingsRequest_completed\0uint8_t\0"
    "a\0b\0val\0ssiSquelchValues\0KpKvValues\0"
    "uint16_t*\0coeff\0apdValues\0uint32_t*\0"
    "on_updateSettingsRequest_recieved\0"
    "on_initSettingsFormRequest_received\0"
    "getLEDsColor\0int*\0updatePVT\0index\0"
    "updateOAS\0updateCECRatios\0CEratios*\0"
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
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      12,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  154,    2, 0x06 /* Public */,
       3,    0,  155,    2, 0x06 /* Public */,
       4,    0,  156,    2, 0x06 /* Public */,
       5,    0,  157,    2, 0x06 /* Public */,
       6,    1,  158,    2, 0x06 /* Public */,
       8,    3,  161,    2, 0x06 /* Public */,
      14,    3,  168,    2, 0x06 /* Public */,
      18,    1,  175,    2, 0x06 /* Public */,
      20,    3,  178,    2, 0x06 /* Public */,
      25,    2,  185,    2, 0x06 /* Public */,
      26,    2,  190,    2, 0x06 /* Public */,
      29,    2,  195,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      31,    3,  200,    2, 0x0a /* Public */,
      32,    0,  207,    2, 0x0a /* Public */,
      33,    1,  208,    2, 0x0a /* Public */,
      35,    2,  211,    2, 0x0a /* Public */,
      37,    2,  216,    2, 0x0a /* Public */,
      38,    3,  221,    2, 0x0a /* Public */,
      40,    0,  228,    2, 0x0a /* Public */,
      41,    0,  229,    2, 0x0a /* Public */,
      42,    1,  230,    2, 0x0a /* Public */,
      43,    3,  233,    2, 0x0a /* Public */,
      46,    1,  240,    2, 0x0a /* Public */,
      47,    0,  243,    2, 0x0a /* Public */,
      48,    0,  244,    2, 0x0a /* Public */,
      49,    0,  245,    2, 0x0a /* Public */,
      50,    1,  246,    2, 0x0a /* Public */,
      52,    1,  249,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 11,   10,   12,   13,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 11, 0x80000000 | 11,   15,   16,   17,
    QMetaType::Void, 0x80000000 | 11,   19,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 21, 0x80000000 | 11,   22,   23,   24,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 11,   15,   24,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 27,   15,   28,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 30,   15,   28,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 21, 0x80000000 | 11,   22,   23,   24,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 34,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   36,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   36,   24,
    QMetaType::Int, QMetaType::UInt, 0x80000000 | 39, QMetaType::UInt,   15,   24,   36,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   15,   44,   45,
    QMetaType::Int, QMetaType::UInt,   15,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 11,   51,
    QMetaType::Void, 0x80000000 | 11,   53,

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
        case 6: _t->ssiDataAvailable((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 7: _t->readGSEDataComplete((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 8: _t->updateSettingsRequest_completed((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 9: _t->ssiSquelchValues((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 10: _t->KpKvValues((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint16_t*(*)>(_a[2]))); break;
        case 11: _t->apdValues((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint32_t*(*)>(_a[2]))); break;
        case 12: _t->on_updateSettingsRequest_recieved((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 13: _t->on_initSettingsFormRequest_received(); break;
        case 14: { int _r = _t->getLEDsColor((*reinterpret_cast< int*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 16: _t->updateOAS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 17: { int _r = _t->updateCECRatios((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< CEratios*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 18: { int _r = _t->on_acquisitionTimer_timeout();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 19: _t->on_initBoardsRequest_recieved(); break;
        case 20: _t->on_resetAxisRequest_recieved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: { int _r = _t->on_configureCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: { int _r = _t->on_stopCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->on_changeBiasModeRequest_recieved(); break;
        case 24: { int _r = _t->on_configureFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: { int _r = _t->on_configureFifoFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->on_OffsetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 27: _t->on_PresetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
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
        {
            using _t = void (dataProcessing::*)(unsigned int , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::ssiDataAvailable)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::readGSEDataComplete)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(uint8_t , uint8_t , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::updateSettingsRequest_completed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(uint8_t , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::ssiSquelchValues)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(uint8_t , uint16_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::KpKvValues)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(uint8_t , uint32_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::apdValues)) {
                *result = 11;
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
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
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

// SIGNAL 6
void dataProcessing::ssiDataAvailable(unsigned int _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void dataProcessing::readGSEDataComplete(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void dataProcessing::updateSettingsRequest_completed(uint8_t _t1, uint8_t _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void dataProcessing::ssiSquelchValues(uint8_t _t1, double * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void dataProcessing::KpKvValues(uint8_t _t1, uint16_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void dataProcessing::apdValues(uint8_t _t1, uint32_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
