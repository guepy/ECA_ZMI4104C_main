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
    QByteArrayData data[83];
    char stringdata0[1353];
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
QT_MOC_LITERAL(21, 270, 1), // "a"
QT_MOC_LITERAL(22, 272, 1), // "b"
QT_MOC_LITERAL(23, 274, 3), // "val"
QT_MOC_LITERAL(24, 278, 16), // "ssiSquelchValues"
QT_MOC_LITERAL(25, 295, 5), // "uint*"
QT_MOC_LITERAL(26, 301, 10), // "KpKvValues"
QT_MOC_LITERAL(27, 312, 4), // "int*"
QT_MOC_LITERAL(28, 317, 5), // "coeff"
QT_MOC_LITERAL(29, 323, 9), // "apdValues"
QT_MOC_LITERAL(30, 333, 18), // "gainControlsValues"
QT_MOC_LITERAL(31, 352, 5), // "bool*"
QT_MOC_LITERAL(32, 358, 25), // "currentIntBoardProperties"
QT_MOC_LITERAL(33, 384, 8), // "sampFreq"
QT_MOC_LITERAL(34, 393, 16), // "cecRatiosUpdated"
QT_MOC_LITERAL(35, 410, 9), // "CEratios*"
QT_MOC_LITERAL(36, 420, 24), // "startSerialOutputRequest"
QT_MOC_LITERAL(37, 445, 23), // "stopSerialOutputRequest"
QT_MOC_LITERAL(38, 469, 24), // "errorSerialOutputRequest"
QT_MOC_LITERAL(39, 494, 8), // "uint32_t"
QT_MOC_LITERAL(40, 503, 4), // "freq"
QT_MOC_LITERAL(41, 508, 27), // "on_sampFreqRequest_received"
QT_MOC_LITERAL(42, 536, 26), // "on_fifoModeSignal_recieved"
QT_MOC_LITERAL(43, 563, 5), // "index"
QT_MOC_LITERAL(44, 569, 36), // "on_stopContinuousScanSignal_r..."
QT_MOC_LITERAL(45, 606, 33), // "on_updateSettingsRequest_rece..."
QT_MOC_LITERAL(46, 640, 21), // "updateSettingsRequest"
QT_MOC_LITERAL(47, 662, 35), // "on_initSettingsFormRequest_re..."
QT_MOC_LITERAL(48, 698, 12), // "getLEDsColor"
QT_MOC_LITERAL(49, 711, 9), // "updatePVT"
QT_MOC_LITERAL(50, 721, 4), // "Temp"
QT_MOC_LITERAL(51, 726, 23), // "initSettingsFormRequest"
QT_MOC_LITERAL(52, 750, 9), // "updateOAS"
QT_MOC_LITERAL(53, 760, 15), // "updateCECRatios"
QT_MOC_LITERAL(54, 776, 5), // "units"
QT_MOC_LITERAL(55, 782, 27), // "on_acquisitionTimer_timeout"
QT_MOC_LITERAL(56, 810, 29), // "on_initBoardsRequest_recieved"
QT_MOC_LITERAL(57, 840, 28), // "on_resetAxisRequest_recieved"
QT_MOC_LITERAL(58, 869, 32), // "on_configureCECHardware_recieved"
QT_MOC_LITERAL(59, 902, 8), // "ceVelMin"
QT_MOC_LITERAL(60, 911, 8), // "ceVelMax"
QT_MOC_LITERAL(61, 920, 27), // "on_stopCECHardware_recieved"
QT_MOC_LITERAL(62, 948, 33), // "on_changeBiasModeRequest_reci..."
QT_MOC_LITERAL(63, 982, 35), // "on_configureFlyscanRequest_re..."
QT_MOC_LITERAL(64, 1018, 39), // "on_configureFifoFlyscanReques..."
QT_MOC_LITERAL(65, 1058, 25), // "on_OffsetPosition_Changed"
QT_MOC_LITERAL(66, 1084, 9), // "offPosPtr"
QT_MOC_LITERAL(67, 1094, 25), // "on_PresetPosition_Changed"
QT_MOC_LITERAL(68, 1120, 10), // "presPosPtr"
QT_MOC_LITERAL(69, 1131, 14), // "vmeSystemReset"
QT_MOC_LITERAL(70, 1146, 36), // "on_modifyBaseAddressRequest_r..."
QT_MOC_LITERAL(71, 1183, 3), // "add"
QT_MOC_LITERAL(72, 1187, 33), // "on_configureSerialOutput_rece..."
QT_MOC_LITERAL(73, 1221, 4), // "SCLK"
QT_MOC_LITERAL(74, 1226, 3), // "clk"
QT_MOC_LITERAL(75, 1230, 18), // "SerialOutputDriver"
QT_MOC_LITERAL(76, 1249, 3), // "sdo"
QT_MOC_LITERAL(77, 1253, 22), // "SerialDataPositionSize"
QT_MOC_LITERAL(78, 1276, 4), // "sdps"
QT_MOC_LITERAL(79, 1281, 9), // "BitWindow"
QT_MOC_LITERAL(80, 1291, 2), // "bw"
QT_MOC_LITERAL(81, 1294, 29), // "on_startSerialOutput_received"
QT_MOC_LITERAL(82, 1324, 28) // "on_stopSerialOutput_received"

    },
    "dataProcessing\0initBoardsDone\0\0"
    "initAxisComplete\0cecConfigComplete\0"
    "flyscanProcTerm\0flyscanErrorCode\0"
    "err_code\0flyscanStatValues\0unsigned char*\0"
    "axisTab\0double*\0mean\0stdDev\0"
    "ssiDataAvailable\0axis\0ssiVals\0optPwrVals\0"
    "readGSEDataComplete\0gseData\0"
    "updateSettingsRequest_completed\0a\0b\0"
    "val\0ssiSquelchValues\0uint*\0KpKvValues\0"
    "int*\0coeff\0apdValues\0gainControlsValues\0"
    "bool*\0currentIntBoardProperties\0"
    "sampFreq\0cecRatiosUpdated\0CEratios*\0"
    "startSerialOutputRequest\0"
    "stopSerialOutputRequest\0"
    "errorSerialOutputRequest\0uint32_t\0"
    "freq\0on_sampFreqRequest_received\0"
    "on_fifoModeSignal_recieved\0index\0"
    "on_stopContinuousScanSignal_received\0"
    "on_updateSettingsRequest_received\0"
    "updateSettingsRequest\0"
    "on_initSettingsFormRequest_received\0"
    "getLEDsColor\0updatePVT\0Temp\0"
    "initSettingsFormRequest\0updateOAS\0"
    "updateCECRatios\0units\0on_acquisitionTimer_timeout\0"
    "on_initBoardsRequest_recieved\0"
    "on_resetAxisRequest_recieved\0"
    "on_configureCECHardware_recieved\0"
    "ceVelMin\0ceVelMax\0on_stopCECHardware_recieved\0"
    "on_changeBiasModeRequest_recieved\0"
    "on_configureFlyscanRequest_recieved\0"
    "on_configureFifoFlyscanRequest_recieved\0"
    "on_OffsetPosition_Changed\0offPosPtr\0"
    "on_PresetPosition_Changed\0presPosPtr\0"
    "vmeSystemReset\0on_modifyBaseAddressRequest_received\0"
    "add\0on_configureSerialOutput_received\0"
    "SCLK\0clk\0SerialOutputDriver\0sdo\0"
    "SerialDataPositionSize\0sdps\0BitWindow\0"
    "bw\0on_startSerialOutput_received\0"
    "on_stopSerialOutput_received"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dataProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      46,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  244,    2, 0x06 /* Public */,
       3,    0,  245,    2, 0x06 /* Public */,
       4,    0,  246,    2, 0x06 /* Public */,
       5,    0,  247,    2, 0x06 /* Public */,
       6,    1,  248,    2, 0x06 /* Public */,
       8,    3,  251,    2, 0x06 /* Public */,
      14,    3,  258,    2, 0x06 /* Public */,
      18,    1,  265,    2, 0x06 /* Public */,
      20,    3,  268,    2, 0x06 /* Public */,
      24,    2,  275,    2, 0x06 /* Public */,
      26,    2,  280,    2, 0x06 /* Public */,
      29,    2,  285,    2, 0x06 /* Public */,
      30,    2,  290,    2, 0x06 /* Public */,
      32,    2,  295,    2, 0x06 /* Public */,
      34,    1,  300,    2, 0x06 /* Public */,
      36,    0,  303,    2, 0x06 /* Public */,
      37,    0,  304,    2, 0x06 /* Public */,
      38,    0,  305,    2, 0x06 /* Public */,
      33,    1,  306,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      41,    0,  309,    2, 0x0a /* Public */,
      42,    1,  310,    2, 0x0a /* Public */,
      44,    0,  313,    2, 0x0a /* Public */,
      45,    3,  314,    2, 0x0a /* Public */,
      46,    3,  321,    2, 0x0a /* Public */,
      47,    0,  328,    2, 0x0a /* Public */,
      48,    1,  329,    2, 0x0a /* Public */,
      49,    3,  332,    2, 0x0a /* Public */,
      49,    3,  339,    2, 0x0a /* Public */,
      51,    0,  346,    2, 0x0a /* Public */,
      52,    2,  347,    2, 0x0a /* Public */,
      53,    2,  352,    2, 0x0a /* Public */,
      55,    0,  357,    2, 0x0a /* Public */,
      56,    0,  358,    2, 0x0a /* Public */,
      57,    1,  359,    2, 0x0a /* Public */,
      58,    3,  362,    2, 0x0a /* Public */,
      61,    1,  369,    2, 0x0a /* Public */,
      62,    0,  372,    2, 0x0a /* Public */,
      63,    0,  373,    2, 0x0a /* Public */,
      64,    0,  374,    2, 0x0a /* Public */,
      65,    1,  375,    2, 0x0a /* Public */,
      67,    1,  378,    2, 0x0a /* Public */,
      69,    0,  381,    2, 0x0a /* Public */,
      70,    1,  382,    2, 0x0a /* Public */,
      72,    5,  385,    2, 0x0a /* Public */,
      81,    0,  396,    2, 0x0a /* Public */,
      82,    0,  397,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11, 0x80000000 | 11,   10,   12,   13,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 11, 0x80000000 | 11,   15,   16,   17,
    QMetaType::Void, 0x80000000 | 11,   19,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 11,   21,   22,   23,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 25,   15,   23,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 27,   15,   28,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 11,   15,   28,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 31,   15,   23,
    QMetaType::Void, 0x80000000 | 31, QMetaType::UInt,   23,   33,
    QMetaType::Void, 0x80000000 | 35,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 39,   40,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   43,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 27,   21,   22,   23,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 27,   21,   22,   23,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 27,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11, 0x80000000 | 11,   43,   23,   50,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11, QMetaType::Int,   43,   23,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,   43,   23,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt,   15,   54,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   15,   59,   60,
    QMetaType::Int, QMetaType::UInt,   15,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 11,   66,
    QMetaType::Void, 0x80000000 | 11,   68,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   71,
    QMetaType::Void, 0x80000000 | 73, 0x80000000 | 75, 0x80000000 | 77, 0x80000000 | 79, 0x80000000 | 39,   74,   76,   78,   80,   33,
    QMetaType::Void,
    QMetaType::Void,

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
        case 8: _t->updateSettingsRequest_completed((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 9: _t->ssiSquelchValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint*(*)>(_a[2]))); break;
        case 10: _t->KpKvValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2]))); break;
        case 11: _t->apdValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 12: _t->gainControlsValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 13: _t->currentIntBoardProperties((*reinterpret_cast< bool*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 14: _t->cecRatiosUpdated((*reinterpret_cast< CEratios*(*)>(_a[1]))); break;
        case 15: _t->startSerialOutputRequest(); break;
        case 16: _t->stopSerialOutputRequest(); break;
        case 17: _t->errorSerialOutputRequest(); break;
        case 18: _t->sampFreq((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        case 19: _t->on_sampFreqRequest_received(); break;
        case 20: _t->on_fifoModeSignal_recieved((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->on_stopContinuousScanSignal_received(); break;
        case 22: _t->on_updateSettingsRequest_received((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3]))); break;
        case 23: _t->updateSettingsRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3]))); break;
        case 24: _t->on_initSettingsFormRequest_received(); break;
        case 25: { int _r = _t->getLEDsColor((*reinterpret_cast< int*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 27: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 28: _t->initSettingsFormRequest(); break;
        case 29: _t->updateOAS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 30: { int _r = _t->updateCECRatios((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 31: { int _r = _t->on_acquisitionTimer_timeout();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 32: _t->on_initBoardsRequest_recieved(); break;
        case 33: _t->on_resetAxisRequest_recieved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: { int _r = _t->on_configureCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 35: { int _r = _t->on_stopCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->on_changeBiasModeRequest_recieved(); break;
        case 37: { int _r = _t->on_configureFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 38: { int _r = _t->on_configureFifoFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->on_OffsetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 40: _t->on_PresetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 41: _t->vmeSystemReset(); break;
        case 42: _t->on_modifyBaseAddressRequest_received((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 43: _t->on_configureSerialOutput_received((*reinterpret_cast< SCLK(*)>(_a[1])),(*reinterpret_cast< SerialOutputDriver(*)>(_a[2])),(*reinterpret_cast< SerialDataPositionSize(*)>(_a[3])),(*reinterpret_cast< BitWindow(*)>(_a[4])),(*reinterpret_cast< uint32_t(*)>(_a[5]))); break;
        case 44: _t->on_startSerialOutput_received(); break;
        case 45: _t->on_stopSerialOutput_received(); break;
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
            using _t = void (dataProcessing::*)(unsigned int , unsigned int , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::updateSettingsRequest_completed)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , unsigned int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::ssiSquelchValues)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::KpKvValues)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::apdValues)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , bool * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::gainControlsValues)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(bool * , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::currentIntBoardProperties)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(CEratios * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::cecRatiosUpdated)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::startSerialOutputRequest)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::stopSerialOutputRequest)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::errorSerialOutputRequest)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::sampFreq)) {
                *result = 18;
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
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 46;
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
void dataProcessing::updateSettingsRequest_completed(unsigned int _t1, unsigned int _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void dataProcessing::ssiSquelchValues(unsigned int _t1, unsigned int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void dataProcessing::KpKvValues(unsigned int _t1, int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void dataProcessing::apdValues(unsigned int _t1, double * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void dataProcessing::gainControlsValues(unsigned int _t1, bool * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void dataProcessing::currentIntBoardProperties(bool * _t1, unsigned int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void dataProcessing::cecRatiosUpdated(CEratios * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void dataProcessing::startSerialOutputRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void dataProcessing::stopSerialOutputRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void dataProcessing::errorSerialOutputRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void dataProcessing::sampFreq(uint32_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
