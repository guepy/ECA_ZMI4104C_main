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
    QByteArrayData data[29];
    char stringdata0[478];
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
QT_MOC_LITERAL(6, 82, 12), // "getLEDsColor"
QT_MOC_LITERAL(7, 95, 4), // "int*"
QT_MOC_LITERAL(8, 100, 9), // "updatePVT"
QT_MOC_LITERAL(9, 110, 5), // "index"
QT_MOC_LITERAL(10, 116, 7), // "double*"
QT_MOC_LITERAL(11, 124, 3), // "val"
QT_MOC_LITERAL(12, 128, 9), // "updateOAS"
QT_MOC_LITERAL(13, 138, 15), // "updateCECRatios"
QT_MOC_LITERAL(14, 154, 4), // "axis"
QT_MOC_LITERAL(15, 159, 9), // "CEratios*"
QT_MOC_LITERAL(16, 169, 27), // "on_acquisitionTimer_timeout"
QT_MOC_LITERAL(17, 197, 29), // "on_initBoardsRequest_recieved"
QT_MOC_LITERAL(18, 227, 28), // "on_resetAxisRequest_recieved"
QT_MOC_LITERAL(19, 256, 32), // "on_configureCECHardware_recieved"
QT_MOC_LITERAL(20, 289, 8), // "ceVelMin"
QT_MOC_LITERAL(21, 298, 8), // "ceVelMax"
QT_MOC_LITERAL(22, 307, 27), // "on_stopCECHardware_recieved"
QT_MOC_LITERAL(23, 335, 33), // "on_changeBiasModeRequest_reci..."
QT_MOC_LITERAL(24, 369, 35), // "on_configureFlyscanRequest_re..."
QT_MOC_LITERAL(25, 405, 25), // "on_OffsetPosition_Changed"
QT_MOC_LITERAL(26, 431, 9), // "offPosPtr"
QT_MOC_LITERAL(27, 441, 25), // "on_PresetPosition_Changed"
QT_MOC_LITERAL(28, 467, 10) // "presPosPtr"

    },
    "dataProcessing\0initBoardsDone\0\0"
    "initAxisComplete\0cecConfigComplete\0"
    "flyscanProcTerm\0getLEDsColor\0int*\0"
    "updatePVT\0index\0double*\0val\0updateOAS\0"
    "updateCECRatios\0axis\0CEratios*\0"
    "on_acquisitionTimer_timeout\0"
    "on_initBoardsRequest_recieved\0"
    "on_resetAxisRequest_recieved\0"
    "on_configureCECHardware_recieved\0"
    "ceVelMin\0ceVelMax\0on_stopCECHardware_recieved\0"
    "on_changeBiasModeRequest_recieved\0"
    "on_configureFlyscanRequest_recieved\0"
    "on_OffsetPosition_Changed\0offPosPtr\0"
    "on_PresetPosition_Changed\0presPosPtr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dataProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    0,  101,    2, 0x06 /* Public */,
       5,    0,  102,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,  103,    2, 0x0a /* Public */,
       8,    2,  106,    2, 0x0a /* Public */,
      12,    2,  111,    2, 0x0a /* Public */,
      13,    3,  116,    2, 0x0a /* Public */,
      16,    0,  123,    2, 0x0a /* Public */,
      17,    0,  124,    2, 0x0a /* Public */,
      18,    1,  125,    2, 0x0a /* Public */,
      19,    3,  128,    2, 0x0a /* Public */,
      22,    1,  135,    2, 0x0a /* Public */,
      23,    0,  138,    2, 0x0a /* Public */,
      24,    0,  139,    2, 0x0a /* Public */,
      25,    1,  140,    2, 0x0a /* Public */,
      27,    1,  143,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    9,   11,
    QMetaType::Int, QMetaType::UInt, 0x80000000 | 15, QMetaType::UInt,   14,   11,    9,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   14,   20,   21,
    QMetaType::Int, QMetaType::UInt,   14,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 10,   26,
    QMetaType::Void, 0x80000000 | 10,   28,

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
        case 4: { int _r = _t->getLEDsColor((*reinterpret_cast< int*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 6: _t->updateOAS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 7: { int _r = _t->updateCECRatios((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< CEratios*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->on_acquisitionTimer_timeout();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->on_initBoardsRequest_recieved(); break;
        case 10: _t->on_resetAxisRequest_recieved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: { int _r = _t->on_configureCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: { int _r = _t->on_stopCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->on_changeBiasModeRequest_recieved(); break;
        case 14: { int _r = _t->on_configureFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 15: _t->on_OffsetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 16: _t->on_PresetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
