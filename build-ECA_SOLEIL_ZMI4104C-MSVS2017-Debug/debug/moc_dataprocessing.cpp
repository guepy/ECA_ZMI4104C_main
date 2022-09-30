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
    QByteArrayData data[93];
    char stringdata0[1553];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dataProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dataProcessing_t qt_meta_stringdata_dataProcessing = {
    {
QT_MOC_LITERAL(0, 0, 14), // "dataProcessing"
QT_MOC_LITERAL(1, 15, 8), // "ceParams"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 35), // "std::array<std::complex<doubl..."
QT_MOC_LITERAL(4, 61, 6), // "params"
QT_MOC_LITERAL(5, 68, 14), // "initBoardsDone"
QT_MOC_LITERAL(6, 83, 16), // "initAxisComplete"
QT_MOC_LITERAL(7, 100, 17), // "cecConfigComplete"
QT_MOC_LITERAL(8, 118, 15), // "flyscanProcTerm"
QT_MOC_LITERAL(9, 134, 16), // "flyscanErrorCode"
QT_MOC_LITERAL(10, 151, 8), // "err_code"
QT_MOC_LITERAL(11, 160, 17), // "flyscanStatValues"
QT_MOC_LITERAL(12, 178, 14), // "unsigned char*"
QT_MOC_LITERAL(13, 193, 7), // "axisTab"
QT_MOC_LITERAL(14, 201, 7), // "double*"
QT_MOC_LITERAL(15, 209, 4), // "mean"
QT_MOC_LITERAL(16, 214, 6), // "stdDev"
QT_MOC_LITERAL(17, 221, 16), // "ssiDataAvailable"
QT_MOC_LITERAL(18, 238, 4), // "axis"
QT_MOC_LITERAL(19, 243, 7), // "ssiVals"
QT_MOC_LITERAL(20, 251, 10), // "optPwrVals"
QT_MOC_LITERAL(21, 262, 19), // "readGSEDataComplete"
QT_MOC_LITERAL(22, 282, 7), // "gseData"
QT_MOC_LITERAL(23, 290, 31), // "updateSettingsRequest_completed"
QT_MOC_LITERAL(24, 322, 1), // "a"
QT_MOC_LITERAL(25, 324, 1), // "b"
QT_MOC_LITERAL(26, 326, 3), // "val"
QT_MOC_LITERAL(27, 330, 16), // "ssiSquelchValues"
QT_MOC_LITERAL(28, 347, 5), // "uint*"
QT_MOC_LITERAL(29, 353, 10), // "KpKvValues"
QT_MOC_LITERAL(30, 364, 4), // "int*"
QT_MOC_LITERAL(31, 369, 5), // "coeff"
QT_MOC_LITERAL(32, 375, 9), // "apdValues"
QT_MOC_LITERAL(33, 385, 18), // "gainControlsValues"
QT_MOC_LITERAL(34, 404, 5), // "bool*"
QT_MOC_LITERAL(35, 410, 25), // "currentIntBoardProperties"
QT_MOC_LITERAL(36, 436, 8), // "sampFreq"
QT_MOC_LITERAL(37, 445, 16), // "cecRatiosUpdated"
QT_MOC_LITERAL(38, 462, 9), // "CEratios*"
QT_MOC_LITERAL(39, 472, 24), // "startSerialOutputRequest"
QT_MOC_LITERAL(40, 497, 23), // "stopSerialOutputRequest"
QT_MOC_LITERAL(41, 521, 24), // "errorSerialOutputRequest"
QT_MOC_LITERAL(42, 546, 8), // "uint32_t"
QT_MOC_LITERAL(43, 555, 4), // "freq"
QT_MOC_LITERAL(44, 560, 21), // "on_enableUsc_received"
QT_MOC_LITERAL(45, 582, 7), // "uint8_t"
QT_MOC_LITERAL(46, 590, 28), // "on_enableUscStartup_received"
QT_MOC_LITERAL(47, 619, 24), // "on_initCeParams_received"
QT_MOC_LITERAL(48, 644, 26), // "on_updateCeParams_received"
QT_MOC_LITERAL(49, 671, 1), // "i"
QT_MOC_LITERAL(50, 673, 34), // "std::vector<std::complex<doub..."
QT_MOC_LITERAL(51, 708, 27), // "on_sampFreqRequest_received"
QT_MOC_LITERAL(52, 736, 26), // "on_fifoModeSignal_recieved"
QT_MOC_LITERAL(53, 763, 5), // "index"
QT_MOC_LITERAL(54, 769, 36), // "on_stopContinuousScanSignal_r..."
QT_MOC_LITERAL(55, 806, 33), // "on_updateSettingsRequest_rece..."
QT_MOC_LITERAL(56, 840, 21), // "updateSettingsRequest"
QT_MOC_LITERAL(57, 862, 35), // "on_initSettingsFormRequest_re..."
QT_MOC_LITERAL(58, 898, 12), // "getLEDsColor"
QT_MOC_LITERAL(59, 911, 9), // "updatePVT"
QT_MOC_LITERAL(60, 921, 4), // "Temp"
QT_MOC_LITERAL(61, 926, 23), // "initSettingsFormRequest"
QT_MOC_LITERAL(62, 950, 9), // "updateOAS"
QT_MOC_LITERAL(63, 960, 15), // "updateCECRatios"
QT_MOC_LITERAL(64, 976, 5), // "units"
QT_MOC_LITERAL(65, 982, 27), // "on_acquisitionTimer_timeout"
QT_MOC_LITERAL(66, 1010, 29), // "on_initBoardsRequest_recieved"
QT_MOC_LITERAL(67, 1040, 28), // "on_resetAxisRequest_recieved"
QT_MOC_LITERAL(68, 1069, 32), // "on_configureCECHardware_recieved"
QT_MOC_LITERAL(69, 1102, 8), // "ceVelMin"
QT_MOC_LITERAL(70, 1111, 8), // "ceVelMax"
QT_MOC_LITERAL(71, 1120, 27), // "on_stopCECHardware_recieved"
QT_MOC_LITERAL(72, 1148, 33), // "on_changeBiasModeRequest_reci..."
QT_MOC_LITERAL(73, 1182, 35), // "on_configureFlyscanRequest_re..."
QT_MOC_LITERAL(74, 1218, 39), // "on_configureFifoFlyscanReques..."
QT_MOC_LITERAL(75, 1258, 25), // "on_OffsetPosition_Changed"
QT_MOC_LITERAL(76, 1284, 9), // "offPosPtr"
QT_MOC_LITERAL(77, 1294, 25), // "on_PresetPosition_Changed"
QT_MOC_LITERAL(78, 1320, 10), // "presPosPtr"
QT_MOC_LITERAL(79, 1331, 14), // "vmeSystemReset"
QT_MOC_LITERAL(80, 1346, 36), // "on_modifyBaseAddressRequest_r..."
QT_MOC_LITERAL(81, 1383, 3), // "add"
QT_MOC_LITERAL(82, 1387, 33), // "on_configureSerialOutput_rece..."
QT_MOC_LITERAL(83, 1421, 4), // "SCLK"
QT_MOC_LITERAL(84, 1426, 3), // "clk"
QT_MOC_LITERAL(85, 1430, 18), // "SerialOutputDriver"
QT_MOC_LITERAL(86, 1449, 3), // "sdo"
QT_MOC_LITERAL(87, 1453, 22), // "SerialDataPositionSize"
QT_MOC_LITERAL(88, 1476, 4), // "sdps"
QT_MOC_LITERAL(89, 1481, 9), // "BitWindow"
QT_MOC_LITERAL(90, 1491, 2), // "bw"
QT_MOC_LITERAL(91, 1494, 29), // "on_startSerialOutput_received"
QT_MOC_LITERAL(92, 1524, 28) // "on_stopSerialOutput_received"

    },
    "dataProcessing\0ceParams\0\0"
    "std::array<std::complex<double>,14>\0"
    "params\0initBoardsDone\0initAxisComplete\0"
    "cecConfigComplete\0flyscanProcTerm\0"
    "flyscanErrorCode\0err_code\0flyscanStatValues\0"
    "unsigned char*\0axisTab\0double*\0mean\0"
    "stdDev\0ssiDataAvailable\0axis\0ssiVals\0"
    "optPwrVals\0readGSEDataComplete\0gseData\0"
    "updateSettingsRequest_completed\0a\0b\0"
    "val\0ssiSquelchValues\0uint*\0KpKvValues\0"
    "int*\0coeff\0apdValues\0gainControlsValues\0"
    "bool*\0currentIntBoardProperties\0"
    "sampFreq\0cecRatiosUpdated\0CEratios*\0"
    "startSerialOutputRequest\0"
    "stopSerialOutputRequest\0"
    "errorSerialOutputRequest\0uint32_t\0"
    "freq\0on_enableUsc_received\0uint8_t\0"
    "on_enableUscStartup_received\0"
    "on_initCeParams_received\0"
    "on_updateCeParams_received\0i\0"
    "std::vector<std::complex<double> >\0"
    "on_sampFreqRequest_received\0"
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
      51,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      20,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  269,    2, 0x06 /* Public */,
       5,    0,  272,    2, 0x06 /* Public */,
       6,    0,  273,    2, 0x06 /* Public */,
       7,    0,  274,    2, 0x06 /* Public */,
       8,    0,  275,    2, 0x06 /* Public */,
       9,    1,  276,    2, 0x06 /* Public */,
      11,    3,  279,    2, 0x06 /* Public */,
      17,    3,  286,    2, 0x06 /* Public */,
      21,    1,  293,    2, 0x06 /* Public */,
      23,    3,  296,    2, 0x06 /* Public */,
      27,    2,  303,    2, 0x06 /* Public */,
      29,    2,  308,    2, 0x06 /* Public */,
      32,    2,  313,    2, 0x06 /* Public */,
      33,    2,  318,    2, 0x06 /* Public */,
      35,    2,  323,    2, 0x06 /* Public */,
      37,    1,  328,    2, 0x06 /* Public */,
      39,    0,  331,    2, 0x06 /* Public */,
      40,    0,  332,    2, 0x06 /* Public */,
      41,    0,  333,    2, 0x06 /* Public */,
      36,    1,  334,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      44,    2,  337,    2, 0x0a /* Public */,
      46,    2,  342,    2, 0x0a /* Public */,
      47,    1,  347,    2, 0x0a /* Public */,
      48,    3,  350,    2, 0x0a /* Public */,
      51,    0,  357,    2, 0x0a /* Public */,
      52,    1,  358,    2, 0x0a /* Public */,
      54,    0,  361,    2, 0x0a /* Public */,
      55,    3,  362,    2, 0x0a /* Public */,
      56,    3,  369,    2, 0x0a /* Public */,
      57,    0,  376,    2, 0x0a /* Public */,
      58,    1,  377,    2, 0x0a /* Public */,
      59,    3,  380,    2, 0x0a /* Public */,
      59,    3,  387,    2, 0x0a /* Public */,
      61,    0,  394,    2, 0x0a /* Public */,
      62,    2,  395,    2, 0x0a /* Public */,
      63,    2,  400,    2, 0x0a /* Public */,
      65,    0,  405,    2, 0x0a /* Public */,
      66,    0,  406,    2, 0x0a /* Public */,
      67,    1,  407,    2, 0x0a /* Public */,
      68,    3,  410,    2, 0x0a /* Public */,
      71,    1,  417,    2, 0x0a /* Public */,
      72,    0,  420,    2, 0x0a /* Public */,
      73,    0,  421,    2, 0x0a /* Public */,
      74,    0,  422,    2, 0x0a /* Public */,
      75,    1,  423,    2, 0x0a /* Public */,
      77,    1,  426,    2, 0x0a /* Public */,
      79,    0,  429,    2, 0x0a /* Public */,
      80,    1,  430,    2, 0x0a /* Public */,
      82,    5,  433,    2, 0x0a /* Public */,
      91,    0,  444,    2, 0x0a /* Public */,
      92,    0,  445,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14, 0x80000000 | 14,   13,   15,   16,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 14, 0x80000000 | 14,   18,   19,   20,
    QMetaType::Void, 0x80000000 | 14,   22,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 14,   24,   25,   26,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 28,   18,   26,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 30,   18,   31,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 14,   18,   31,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 34,   18,   26,
    QMetaType::Void, 0x80000000 | 34, QMetaType::UInt,   26,   36,
    QMetaType::Void, 0x80000000 | 38,   26,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 42,   43,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 45, QMetaType::Bool,   24,   25,
    QMetaType::Void, 0x80000000 | 45, QMetaType::Bool,   24,   25,
    QMetaType::Void, 0x80000000 | 45,   18,
    QMetaType::Void, 0x80000000 | 45, QMetaType::Int, 0x80000000 | 50,   18,   49,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 30,   24,   25,   26,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, 0x80000000 | 30,   24,   25,   26,
    QMetaType::Void,
    QMetaType::Int, 0x80000000 | 30,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, 0x80000000 | 14,   53,   26,   60,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, QMetaType::Int,   53,   26,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14,   53,   26,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt,   18,   64,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Int, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   18,   69,   70,
    QMetaType::Int, QMetaType::UInt,   18,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, 0x80000000 | 14,   76,
    QMetaType::Void, 0x80000000 | 14,   78,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,   81,
    QMetaType::Void, 0x80000000 | 83, 0x80000000 | 85, 0x80000000 | 87, 0x80000000 | 89, 0x80000000 | 42,   84,   86,   88,   90,   36,
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
        case 0: _t->ceParams((*reinterpret_cast< std::array<std::complex<double>,14>(*)>(_a[1]))); break;
        case 1: _t->initBoardsDone(); break;
        case 2: _t->initAxisComplete(); break;
        case 3: _t->cecConfigComplete(); break;
        case 4: _t->flyscanProcTerm(); break;
        case 5: _t->flyscanErrorCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->flyscanStatValues((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 7: _t->ssiDataAvailable((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 8: _t->readGSEDataComplete((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 9: _t->updateSettingsRequest_completed((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 10: _t->ssiSquelchValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint*(*)>(_a[2]))); break;
        case 11: _t->KpKvValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2]))); break;
        case 12: _t->apdValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 13: _t->gainControlsValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 14: _t->currentIntBoardProperties((*reinterpret_cast< bool*(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 15: _t->cecRatiosUpdated((*reinterpret_cast< CEratios*(*)>(_a[1]))); break;
        case 16: _t->startSerialOutputRequest(); break;
        case 17: _t->stopSerialOutputRequest(); break;
        case 18: _t->errorSerialOutputRequest(); break;
        case 19: _t->sampFreq((*reinterpret_cast< uint32_t(*)>(_a[1]))); break;
        case 20: _t->on_enableUsc_received((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 21: _t->on_enableUscStartup_received((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 22: _t->on_initCeParams_received((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 23: _t->on_updateCeParams_received((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::vector<std::complex<double> >(*)>(_a[3]))); break;
        case 24: _t->on_sampFreqRequest_received(); break;
        case 25: _t->on_fifoModeSignal_recieved((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: _t->on_stopContinuousScanSignal_received(); break;
        case 27: _t->on_updateSettingsRequest_received((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3]))); break;
        case 28: _t->updateSettingsRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3]))); break;
        case 29: _t->on_initSettingsFormRequest_received(); break;
        case 30: { int _r = _t->getLEDsColor((*reinterpret_cast< int*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 31: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 32: _t->updatePVT((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 33: _t->initSettingsFormRequest(); break;
        case 34: _t->updateOAS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 35: { int _r = _t->updateCECRatios((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 36: { int _r = _t->on_acquisitionTimer_timeout();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 37: _t->on_initBoardsRequest_recieved(); break;
        case 38: _t->on_resetAxisRequest_recieved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: { int _r = _t->on_configureCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 40: { int _r = _t->on_stopCECHardware_recieved((*reinterpret_cast< uint(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 41: _t->on_changeBiasModeRequest_recieved(); break;
        case 42: { int _r = _t->on_configureFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 43: { int _r = _t->on_configureFifoFlyscanRequest_recieved();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->on_OffsetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 45: _t->on_PresetPosition_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 46: _t->vmeSystemReset(); break;
        case 47: _t->on_modifyBaseAddressRequest_received((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 48: _t->on_configureSerialOutput_received((*reinterpret_cast< SCLK(*)>(_a[1])),(*reinterpret_cast< SerialOutputDriver(*)>(_a[2])),(*reinterpret_cast< SerialDataPositionSize(*)>(_a[3])),(*reinterpret_cast< BitWindow(*)>(_a[4])),(*reinterpret_cast< uint32_t(*)>(_a[5]))); break;
        case 49: _t->on_startSerialOutput_received(); break;
        case 50: _t->on_stopSerialOutput_received(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (dataProcessing::*)(std::array<std::complex<double>,14> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::ceParams)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::initBoardsDone)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::initAxisComplete)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::cecConfigComplete)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::flyscanProcTerm)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::flyscanErrorCode)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned char * , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::flyscanStatValues)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::ssiDataAvailable)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::readGSEDataComplete)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , unsigned int , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::updateSettingsRequest_completed)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , unsigned int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::ssiSquelchValues)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::KpKvValues)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::apdValues)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(unsigned int , bool * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::gainControlsValues)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(bool * , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::currentIntBoardProperties)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(CEratios * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::cecRatiosUpdated)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::startSerialOutputRequest)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::stopSerialOutputRequest)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::errorSerialOutputRequest)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (dataProcessing::*)(uint32_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&dataProcessing::sampFreq)) {
                *result = 19;
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
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 51)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 51;
    }
    return _id;
}

// SIGNAL 0
void dataProcessing::ceParams(std::array<std::complex<double>,14> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void dataProcessing::initBoardsDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void dataProcessing::initAxisComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void dataProcessing::cecConfigComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void dataProcessing::flyscanProcTerm()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void dataProcessing::flyscanErrorCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void dataProcessing::flyscanStatValues(unsigned char * _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void dataProcessing::ssiDataAvailable(unsigned int _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void dataProcessing::readGSEDataComplete(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void dataProcessing::updateSettingsRequest_completed(unsigned int _t1, unsigned int _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void dataProcessing::ssiSquelchValues(unsigned int _t1, unsigned int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void dataProcessing::KpKvValues(unsigned int _t1, int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void dataProcessing::apdValues(unsigned int _t1, double * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void dataProcessing::gainControlsValues(unsigned int _t1, bool * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void dataProcessing::currentIntBoardProperties(bool * _t1, unsigned int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void dataProcessing::cecRatiosUpdated(CEratios * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void dataProcessing::startSerialOutputRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void dataProcessing::stopSerialOutputRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 17, nullptr);
}

// SIGNAL 18
void dataProcessing::errorSerialOutputRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}

// SIGNAL 19
void dataProcessing::sampFreq(uint32_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
