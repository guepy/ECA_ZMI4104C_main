/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[157];
    char stringdata0[2972];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "fifoModeSignal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 24), // "stopContinuousScanSignal"
QT_MOC_LITERAL(5, 58, 10), // "startGraph"
QT_MOC_LITERAL(6, 69, 21), // "updateSettingsRequest"
QT_MOC_LITERAL(7, 91, 1), // "a"
QT_MOC_LITERAL(8, 93, 1), // "b"
QT_MOC_LITERAL(9, 95, 7), // "double*"
QT_MOC_LITERAL(10, 103, 3), // "val"
QT_MOC_LITERAL(11, 107, 23), // "closeFlyscanFormRequest"
QT_MOC_LITERAL(12, 131, 30), // "closePositionOffsetFormRequest"
QT_MOC_LITERAL(13, 162, 30), // "closePresetPositionFormRequest"
QT_MOC_LITERAL(14, 193, 24), // "closeSettingsFormRequest"
QT_MOC_LITERAL(15, 218, 26), // "closeCustomplotFormRequest"
QT_MOC_LITERAL(16, 245, 17), // "initBoardsRequest"
QT_MOC_LITERAL(17, 263, 16), // "scaleAxisRequest"
QT_MOC_LITERAL(18, 280, 5), // "units"
QT_MOC_LITERAL(19, 286, 16), // "resetAxisRequest"
QT_MOC_LITERAL(20, 303, 4), // "axis"
QT_MOC_LITERAL(21, 308, 21), // "changeBiasModeRequest"
QT_MOC_LITERAL(22, 330, 15), // "initAxisRequest"
QT_MOC_LITERAL(23, 346, 15), // "settingsFormRun"
QT_MOC_LITERAL(24, 362, 16), // "OffsetPosChanged"
QT_MOC_LITERAL(25, 379, 9), // "posOffPtr"
QT_MOC_LITERAL(26, 389, 16), // "PresetPosChanged"
QT_MOC_LITERAL(27, 406, 10), // "PresPosPtr"
QT_MOC_LITERAL(28, 417, 27), // "configureCEChardwareRequest"
QT_MOC_LITERAL(29, 445, 8), // "ceVelMin"
QT_MOC_LITERAL(30, 454, 8), // "ceVelMax"
QT_MOC_LITERAL(31, 463, 22), // "stopCEChardwareRequest"
QT_MOC_LITERAL(32, 486, 22), // "updateCECRatiosRequest"
QT_MOC_LITERAL(33, 509, 16), // "flyscanErrorCode"
QT_MOC_LITERAL(34, 526, 8), // "ret_code"
QT_MOC_LITERAL(35, 535, 17), // "flyscanStatValues"
QT_MOC_LITERAL(36, 553, 14), // "unsigned char*"
QT_MOC_LITERAL(37, 568, 7), // "axisTab"
QT_MOC_LITERAL(38, 576, 4), // "mean"
QT_MOC_LITERAL(39, 581, 6), // "stdDev"
QT_MOC_LITERAL(40, 588, 15), // "flyscanProcTerm"
QT_MOC_LITERAL(41, 604, 16), // "ssiDataAvailable"
QT_MOC_LITERAL(42, 621, 7), // "ssiVals"
QT_MOC_LITERAL(43, 629, 10), // "optPwrVals"
QT_MOC_LITERAL(44, 640, 16), // "ssiSquelchValues"
QT_MOC_LITERAL(45, 657, 5), // "uint*"
QT_MOC_LITERAL(46, 663, 10), // "KpKvValues"
QT_MOC_LITERAL(47, 674, 4), // "int*"
QT_MOC_LITERAL(48, 679, 5), // "coeff"
QT_MOC_LITERAL(49, 685, 19), // "readGSEDataComplete"
QT_MOC_LITERAL(50, 705, 7), // "gseData"
QT_MOC_LITERAL(51, 713, 23), // "initSettingsFormRequest"
QT_MOC_LITERAL(52, 737, 9), // "apdValues"
QT_MOC_LITERAL(53, 747, 9), // "uint32_t*"
QT_MOC_LITERAL(54, 757, 18), // "gainControlsValues"
QT_MOC_LITERAL(55, 776, 5), // "bool*"
QT_MOC_LITERAL(56, 782, 22), // "updatePositionOnGraphs"
QT_MOC_LITERAL(57, 805, 8), // "position"
QT_MOC_LITERAL(58, 814, 15), // "closeSdoRequest"
QT_MOC_LITERAL(59, 830, 15), // "openFlyscanForm"
QT_MOC_LITERAL(60, 846, 16), // "closeFlyscanForm"
QT_MOC_LITERAL(61, 863, 17), // "reopenFlyscanForm"
QT_MOC_LITERAL(62, 881, 25), // "on_m_settingsMenu_clicked"
QT_MOC_LITERAL(63, 907, 8), // "QAction*"
QT_MOC_LITERAL(64, 916, 18), // "reopenSettingsForm"
QT_MOC_LITERAL(65, 935, 16), // "openSettingsForm"
QT_MOC_LITERAL(66, 952, 17), // "closeSettingsForm"
QT_MOC_LITERAL(67, 970, 22), // "openPresetPositionForm"
QT_MOC_LITERAL(68, 993, 23), // "closePresetPositionForm"
QT_MOC_LITERAL(69, 1017, 24), // "reopenPresetPositionForm"
QT_MOC_LITERAL(70, 1042, 22), // "openPositionOffsetForm"
QT_MOC_LITERAL(71, 1065, 23), // "closePositionOffsetForm"
QT_MOC_LITERAL(72, 1089, 24), // "reopenPositionOffsetForm"
QT_MOC_LITERAL(73, 1114, 11), // "openSdoForm"
QT_MOC_LITERAL(74, 1126, 12), // "closeSdoForm"
QT_MOC_LITERAL(75, 1139, 13), // "reopenSdoForm"
QT_MOC_LITERAL(76, 1153, 18), // "openCustomplotForm"
QT_MOC_LITERAL(77, 1172, 19), // "closeCustomplotForm"
QT_MOC_LITERAL(78, 1192, 20), // "reopenCustomplotForm"
QT_MOC_LITERAL(79, 1213, 28), // "on_cecRatiosUpdated_recieved"
QT_MOC_LITERAL(80, 1242, 9), // "CEratios*"
QT_MOC_LITERAL(81, 1252, 14), // "refresh_screen"
QT_MOC_LITERAL(82, 1267, 8), // "initBars"
QT_MOC_LITERAL(83, 1276, 22), // "setDisplayOutputString"
QT_MOC_LITERAL(84, 1299, 11), // "std::string"
QT_MOC_LITERAL(85, 1311, 4), // "text"
QT_MOC_LITERAL(86, 1316, 3), // "col"
QT_MOC_LITERAL(87, 1320, 36), // "on_startSerialOutputRequest_r..."
QT_MOC_LITERAL(88, 1357, 35), // "on_stopSerialOutputRequest_re..."
QT_MOC_LITERAL(89, 1393, 36), // "on_errorSerialOutputRequest_r..."
QT_MOC_LITERAL(90, 1430, 14), // "updateBiasMode"
QT_MOC_LITERAL(91, 1445, 20), // "updateAPDTemperature"
QT_MOC_LITERAL(92, 1466, 20), // "on_OffsetPos_Changed"
QT_MOC_LITERAL(93, 1487, 9), // "OffPosPtr"
QT_MOC_LITERAL(94, 1497, 20), // "on_PresetPos_Changed"
QT_MOC_LITERAL(95, 1518, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(96, 1543, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(97, 1568, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(98, 1593, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(99, 1617, 28), // "on_initAxisComplete_recieved"
QT_MOC_LITERAL(100, 1646, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(101, 1670, 27), // "on_resetButtonAxis1_clicked"
QT_MOC_LITERAL(102, 1698, 27), // "on_resetButtonAxis2_clicked"
QT_MOC_LITERAL(103, 1726, 27), // "on_resetButtonAxis3_clicked"
QT_MOC_LITERAL(104, 1754, 27), // "on_resetButtonAxis4_clicked"
QT_MOC_LITERAL(105, 1782, 30), // "onBoardsInitializationComplete"
QT_MOC_LITERAL(106, 1813, 17), // "refreshLEDsStatus"
QT_MOC_LITERAL(107, 1831, 10), // "initBoards"
QT_MOC_LITERAL(108, 1842, 5), // "argin"
QT_MOC_LITERAL(109, 1848, 37), // "on_leftBlockUnits_currentInde..."
QT_MOC_LITERAL(110, 1886, 38), // "on_rightBlockUnits_currentInd..."
QT_MOC_LITERAL(111, 1925, 25), // "speedUpdateLeftBlockValue"
QT_MOC_LITERAL(112, 1951, 25), // "speedSelectLeftBlockValue"
QT_MOC_LITERAL(113, 1977, 20), // "updateLeftBlockValue"
QT_MOC_LITERAL(114, 1998, 20), // "selectLeftBlockValue"
QT_MOC_LITERAL(115, 2019, 21), // "updateRightBlockValue"
QT_MOC_LITERAL(116, 2041, 21), // "selectRightBlockValue"
QT_MOC_LITERAL(117, 2063, 15), // "updateCECRatios"
QT_MOC_LITERAL(118, 2079, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(119, 2103, 26), // "processCecAxisClickedEvent"
QT_MOC_LITERAL(120, 2130, 13), // "axisListIndex"
QT_MOC_LITERAL(121, 2144, 10), // "QCheckBox*"
QT_MOC_LITERAL(122, 2155, 15), // "cecAxisCheckBox"
QT_MOC_LITERAL(123, 2171, 25), // "cecAxisClickedThreadEvent"
QT_MOC_LITERAL(124, 2197, 29), // "on_resetButtonAllAxis_clicked"
QT_MOC_LITERAL(125, 2227, 33), // "on_ramDataFlyscanRequest_reci..."
QT_MOC_LITERAL(126, 2261, 4), // "freq"
QT_MOC_LITERAL(127, 2266, 4), // "size"
QT_MOC_LITERAL(128, 2271, 4), // "time"
QT_MOC_LITERAL(129, 2276, 3), // "nbr"
QT_MOC_LITERAL(130, 2280, 30), // "on_fifoFlyscanRequest_recieved"
QT_MOC_LITERAL(131, 2311, 33), // "on_comboBox_3_currentIndexCha..."
QT_MOC_LITERAL(132, 2345, 33), // "on_comboBox_4_currentIndexCha..."
QT_MOC_LITERAL(133, 2379, 36), // "on_modifyBaseAddressRequest_r..."
QT_MOC_LITERAL(134, 2416, 3), // "add"
QT_MOC_LITERAL(135, 2420, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(136, 2452, 36), // "on_stopContinuousScanSignal_r..."
QT_MOC_LITERAL(137, 2489, 24), // "stopContinuousScanThread"
QT_MOC_LITERAL(138, 2514, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(139, 2537, 24), // "updateMixingFrequencyBar"
QT_MOC_LITERAL(140, 2562, 30), // "on_ceUnits_currentIndexChanged"
QT_MOC_LITERAL(141, 2593, 15), // "updateOPtPwrBar"
QT_MOC_LITERAL(142, 2609, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(143, 2634, 19), // "on_cecAxis1_clicked"
QT_MOC_LITERAL(144, 2654, 19), // "on_cecAxis2_clicked"
QT_MOC_LITERAL(145, 2674, 19), // "on_cecAxis3_clicked"
QT_MOC_LITERAL(146, 2694, 19), // "on_cecAxis4_clicked"
QT_MOC_LITERAL(147, 2714, 36), // "on_ceDisplayAxis_currentIndex..."
QT_MOC_LITERAL(148, 2751, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(149, 2771, 7), // "checked"
QT_MOC_LITERAL(150, 2779, 22), // "on_enableAxis1_clicked"
QT_MOC_LITERAL(151, 2802, 22), // "on_enableAxis2_clicked"
QT_MOC_LITERAL(152, 2825, 22), // "on_enableAxis3_clicked"
QT_MOC_LITERAL(153, 2848, 22), // "on_enableAxis4_clicked"
QT_MOC_LITERAL(154, 2871, 35), // "on_biasModeAxis_currentIndexC..."
QT_MOC_LITERAL(155, 2907, 34), // "on_adpTempAxes_currentIndexCh..."
QT_MOC_LITERAL(156, 2942, 29) // "on_buttonSerialOutput_clicked"

    },
    "MainWindow\0fifoModeSignal\0\0index\0"
    "stopContinuousScanSignal\0startGraph\0"
    "updateSettingsRequest\0a\0b\0double*\0val\0"
    "closeFlyscanFormRequest\0"
    "closePositionOffsetFormRequest\0"
    "closePresetPositionFormRequest\0"
    "closeSettingsFormRequest\0"
    "closeCustomplotFormRequest\0initBoardsRequest\0"
    "scaleAxisRequest\0units\0resetAxisRequest\0"
    "axis\0changeBiasModeRequest\0initAxisRequest\0"
    "settingsFormRun\0OffsetPosChanged\0"
    "posOffPtr\0PresetPosChanged\0PresPosPtr\0"
    "configureCEChardwareRequest\0ceVelMin\0"
    "ceVelMax\0stopCEChardwareRequest\0"
    "updateCECRatiosRequest\0flyscanErrorCode\0"
    "ret_code\0flyscanStatValues\0unsigned char*\0"
    "axisTab\0mean\0stdDev\0flyscanProcTerm\0"
    "ssiDataAvailable\0ssiVals\0optPwrVals\0"
    "ssiSquelchValues\0uint*\0KpKvValues\0"
    "int*\0coeff\0readGSEDataComplete\0gseData\0"
    "initSettingsFormRequest\0apdValues\0"
    "uint32_t*\0gainControlsValues\0bool*\0"
    "updatePositionOnGraphs\0position\0"
    "closeSdoRequest\0openFlyscanForm\0"
    "closeFlyscanForm\0reopenFlyscanForm\0"
    "on_m_settingsMenu_clicked\0QAction*\0"
    "reopenSettingsForm\0openSettingsForm\0"
    "closeSettingsForm\0openPresetPositionForm\0"
    "closePresetPositionForm\0"
    "reopenPresetPositionForm\0"
    "openPositionOffsetForm\0closePositionOffsetForm\0"
    "reopenPositionOffsetForm\0openSdoForm\0"
    "closeSdoForm\0reopenSdoForm\0"
    "openCustomplotForm\0closeCustomplotForm\0"
    "reopenCustomplotForm\0on_cecRatiosUpdated_recieved\0"
    "CEratios*\0refresh_screen\0initBars\0"
    "setDisplayOutputString\0std::string\0"
    "text\0col\0on_startSerialOutputRequest_recieved\0"
    "on_stopSerialOutputRequest_recieved\0"
    "on_errorSerialOutputRequest_recieved\0"
    "updateBiasMode\0updateAPDTemperature\0"
    "on_OffsetPos_Changed\0OffPosPtr\0"
    "on_PresetPos_Changed\0on_pushButton_11_clicked\0"
    "on_pushButton_13_clicked\0"
    "on_pushButton_12_clicked\0"
    "on_toolButton_2_clicked\0"
    "on_initAxisComplete_recieved\0"
    "on_pushButton_7_clicked\0"
    "on_resetButtonAxis1_clicked\0"
    "on_resetButtonAxis2_clicked\0"
    "on_resetButtonAxis3_clicked\0"
    "on_resetButtonAxis4_clicked\0"
    "onBoardsInitializationComplete\0"
    "refreshLEDsStatus\0initBoards\0argin\0"
    "on_leftBlockUnits_currentIndexChanged\0"
    "on_rightBlockUnits_currentIndexChanged\0"
    "speedUpdateLeftBlockValue\0"
    "speedSelectLeftBlockValue\0"
    "updateLeftBlockValue\0selectLeftBlockValue\0"
    "updateRightBlockValue\0selectRightBlockValue\0"
    "updateCECRatios\0on_pushButton_8_clicked\0"
    "processCecAxisClickedEvent\0axisListIndex\0"
    "QCheckBox*\0cecAxisCheckBox\0"
    "cecAxisClickedThreadEvent\0"
    "on_resetButtonAllAxis_clicked\0"
    "on_ramDataFlyscanRequest_recieved\0"
    "freq\0size\0time\0nbr\0on_fifoFlyscanRequest_recieved\0"
    "on_comboBox_3_currentIndexChanged\0"
    "on_comboBox_4_currentIndexChanged\0"
    "on_modifyBaseAddressRequest_received\0"
    "add\0on_comboBox_currentIndexChanged\0"
    "on_stopContinuousScanSignal_received\0"
    "stopContinuousScanThread\0"
    "on_radioButton_clicked\0updateMixingFrequencyBar\0"
    "on_ceUnits_currentIndexChanged\0"
    "updateOPtPwrBar\0on_radioButton_2_clicked\0"
    "on_cecAxis1_clicked\0on_cecAxis2_clicked\0"
    "on_cecAxis3_clicked\0on_cecAxis4_clicked\0"
    "on_ceDisplayAxis_currentIndexChanged\0"
    "on_checkBox_clicked\0checked\0"
    "on_enableAxis1_clicked\0on_enableAxis2_clicked\0"
    "on_enableAxis3_clicked\0on_enableAxis4_clicked\0"
    "on_biasModeAxis_currentIndexChanged\0"
    "on_adpTempAxes_currentIndexChanged\0"
    "on_buttonSerialOutput_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     114,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      32,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  584,    2, 0x06 /* Public */,
       4,    0,  587,    2, 0x06 /* Public */,
       5,    0,  588,    2, 0x06 /* Public */,
       6,    3,  589,    2, 0x06 /* Public */,
      11,    0,  596,    2, 0x06 /* Public */,
      12,    0,  597,    2, 0x06 /* Public */,
      13,    0,  598,    2, 0x06 /* Public */,
      14,    0,  599,    2, 0x06 /* Public */,
      15,    0,  600,    2, 0x06 /* Public */,
      16,    0,  601,    2, 0x06 /* Public */,
      17,    1,  602,    2, 0x06 /* Public */,
      19,    1,  605,    2, 0x06 /* Public */,
      21,    1,  608,    2, 0x06 /* Public */,
      22,    0,  611,    2, 0x06 /* Public */,
      23,    0,  612,    2, 0x06 /* Public */,
      24,    1,  613,    2, 0x06 /* Public */,
      26,    1,  616,    2, 0x06 /* Public */,
      28,    3,  619,    2, 0x06 /* Public */,
      31,    1,  626,    2, 0x06 /* Public */,
      32,    2,  629,    2, 0x06 /* Public */,
      33,    1,  634,    2, 0x06 /* Public */,
      35,    3,  637,    2, 0x06 /* Public */,
      40,    0,  644,    2, 0x06 /* Public */,
      41,    3,  645,    2, 0x06 /* Public */,
      44,    2,  652,    2, 0x06 /* Public */,
      46,    2,  657,    2, 0x06 /* Public */,
      49,    1,  662,    2, 0x06 /* Public */,
      51,    0,  665,    2, 0x06 /* Public */,
      52,    2,  666,    2, 0x06 /* Public */,
      54,    2,  671,    2, 0x06 /* Public */,
      56,    1,  676,    2, 0x06 /* Public */,
      58,    0,  679,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      59,    0,  680,    2, 0x0a /* Public */,
      60,    0,  681,    2, 0x0a /* Public */,
      61,    0,  682,    2, 0x0a /* Public */,
      62,    1,  683,    2, 0x0a /* Public */,
      64,    0,  686,    2, 0x0a /* Public */,
      65,    0,  687,    2, 0x0a /* Public */,
      66,    0,  688,    2, 0x0a /* Public */,
      67,    0,  689,    2, 0x0a /* Public */,
      68,    0,  690,    2, 0x0a /* Public */,
      69,    0,  691,    2, 0x0a /* Public */,
      70,    0,  692,    2, 0x0a /* Public */,
      71,    0,  693,    2, 0x0a /* Public */,
      72,    0,  694,    2, 0x0a /* Public */,
      73,    0,  695,    2, 0x0a /* Public */,
      74,    0,  696,    2, 0x0a /* Public */,
      75,    0,  697,    2, 0x0a /* Public */,
      76,    0,  698,    2, 0x0a /* Public */,
      77,    0,  699,    2, 0x0a /* Public */,
      78,    0,  700,    2, 0x0a /* Public */,
      79,    1,  701,    2, 0x0a /* Public */,
      81,    0,  704,    2, 0x0a /* Public */,
      82,    0,  705,    2, 0x08 /* Private */,
      83,    2,  706,    2, 0x08 /* Private */,
      87,    0,  711,    2, 0x08 /* Private */,
      88,    0,  712,    2, 0x08 /* Private */,
      89,    0,  713,    2, 0x08 /* Private */,
      90,    0,  714,    2, 0x08 /* Private */,
      91,    0,  715,    2, 0x08 /* Private */,
      92,    1,  716,    2, 0x08 /* Private */,
      94,    1,  719,    2, 0x08 /* Private */,
      95,    0,  722,    2, 0x08 /* Private */,
      96,    0,  723,    2, 0x08 /* Private */,
      97,    0,  724,    2, 0x08 /* Private */,
      98,    0,  725,    2, 0x08 /* Private */,
      99,    0,  726,    2, 0x08 /* Private */,
     100,    0,  727,    2, 0x08 /* Private */,
     101,    0,  728,    2, 0x08 /* Private */,
     102,    0,  729,    2, 0x08 /* Private */,
     103,    0,  730,    2, 0x08 /* Private */,
     104,    0,  731,    2, 0x08 /* Private */,
     105,    0,  732,    2, 0x08 /* Private */,
     106,    0,  733,    2, 0x08 /* Private */,
     107,    1,  734,    2, 0x08 /* Private */,
     109,    1,  737,    2, 0x08 /* Private */,
     110,    1,  740,    2, 0x08 /* Private */,
     111,    0,  743,    2, 0x08 /* Private */,
     112,    1,  744,    2, 0x08 /* Private */,
     113,    0,  747,    2, 0x08 /* Private */,
     114,    1,  748,    2, 0x08 /* Private */,
     115,    0,  751,    2, 0x08 /* Private */,
     116,    1,  752,    2, 0x08 /* Private */,
     117,    0,  755,    2, 0x08 /* Private */,
     118,    0,  756,    2, 0x08 /* Private */,
     119,    3,  757,    2, 0x08 /* Private */,
     123,    3,  764,    2, 0x08 /* Private */,
     124,    0,  771,    2, 0x08 /* Private */,
     125,    4,  772,    2, 0x08 /* Private */,
     130,    4,  781,    2, 0x08 /* Private */,
     131,    1,  790,    2, 0x08 /* Private */,
     132,    1,  793,    2, 0x08 /* Private */,
     133,    1,  796,    2, 0x08 /* Private */,
     135,    1,  799,    2, 0x08 /* Private */,
     136,    0,  802,    2, 0x08 /* Private */,
     137,    0,  803,    2, 0x08 /* Private */,
     138,    0,  804,    2, 0x08 /* Private */,
     139,    0,  805,    2, 0x08 /* Private */,
     140,    1,  806,    2, 0x08 /* Private */,
     141,    0,  809,    2, 0x08 /* Private */,
     142,    0,  810,    2, 0x08 /* Private */,
     143,    0,  811,    2, 0x08 /* Private */,
     144,    0,  812,    2, 0x08 /* Private */,
     145,    0,  813,    2, 0x08 /* Private */,
     146,    0,  814,    2, 0x08 /* Private */,
     147,    1,  815,    2, 0x08 /* Private */,
     148,    1,  818,    2, 0x08 /* Private */,
     150,    1,  821,    2, 0x08 /* Private */,
     151,    1,  824,    2, 0x08 /* Private */,
     152,    1,  827,    2, 0x08 /* Private */,
     153,    1,  830,    2, 0x08 /* Private */,
     154,    1,  833,    2, 0x08 /* Private */,
     155,    1,  836,    2, 0x08 /* Private */,
     156,    0,  839,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 9,    7,    8,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   25,
    QMetaType::Void, 0x80000000 | 9,   27,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   20,   29,   30,
    QMetaType::Void, QMetaType::UInt,   20,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,   20,    3,
    QMetaType::Void, QMetaType::Int,   34,
    QMetaType::Void, 0x80000000 | 36, 0x80000000 | 9, 0x80000000 | 9,   37,   38,   39,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 9, 0x80000000 | 9,   20,   42,   43,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 45,   20,   10,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 47,   20,   48,
    QMetaType::Void, 0x80000000 | 9,   50,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 53,   20,   48,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 55,   20,   10,
    QMetaType::Void, 0x80000000 | 9,   57,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 63,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 80,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 84, 0x80000000 | 84,   85,   86,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   93,
    QMetaType::Void, 0x80000000 | 9,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  108,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 47, 0x80000000 | 121,   20,  120,  122,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 47, 0x80000000 | 121,   20,  120,  122,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,  126,  127,  128,  129,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,  126,  127,  128,  129,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::UInt,  134,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,  149,
    QMetaType::Void, QMetaType::Bool,  149,
    QMetaType::Void, QMetaType::Bool,  149,
    QMetaType::Void, QMetaType::Bool,  149,
    QMetaType::Void, QMetaType::Bool,  149,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fifoModeSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->stopContinuousScanSignal(); break;
        case 2: _t->startGraph(); break;
        case 3: _t->updateSettingsRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 4: _t->closeFlyscanFormRequest(); break;
        case 5: _t->closePositionOffsetFormRequest(); break;
        case 6: _t->closePresetPositionFormRequest(); break;
        case 7: _t->closeSettingsFormRequest(); break;
        case 8: _t->closeCustomplotFormRequest(); break;
        case 9: _t->initBoardsRequest(); break;
        case 10: _t->scaleAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->resetAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->changeBiasModeRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->initAxisRequest(); break;
        case 14: _t->settingsFormRun(); break;
        case 15: _t->OffsetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 16: _t->PresetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 17: _t->configureCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 18: _t->stopCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 19: _t->updateCECRatiosRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 20: _t->flyscanErrorCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->flyscanStatValues((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 22: _t->flyscanProcTerm(); break;
        case 23: _t->ssiDataAvailable((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 24: _t->ssiSquelchValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint*(*)>(_a[2]))); break;
        case 25: _t->KpKvValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2]))); break;
        case 26: _t->readGSEDataComplete((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 27: _t->initSettingsFormRequest(); break;
        case 28: _t->apdValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint32_t*(*)>(_a[2]))); break;
        case 29: _t->gainControlsValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 30: _t->updatePositionOnGraphs((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 31: _t->closeSdoRequest(); break;
        case 32: _t->openFlyscanForm(); break;
        case 33: _t->closeFlyscanForm(); break;
        case 34: _t->reopenFlyscanForm(); break;
        case 35: _t->on_m_settingsMenu_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 36: _t->reopenSettingsForm(); break;
        case 37: _t->openSettingsForm(); break;
        case 38: _t->closeSettingsForm(); break;
        case 39: _t->openPresetPositionForm(); break;
        case 40: _t->closePresetPositionForm(); break;
        case 41: _t->reopenPresetPositionForm(); break;
        case 42: _t->openPositionOffsetForm(); break;
        case 43: _t->closePositionOffsetForm(); break;
        case 44: _t->reopenPositionOffsetForm(); break;
        case 45: _t->openSdoForm(); break;
        case 46: _t->closeSdoForm(); break;
        case 47: _t->reopenSdoForm(); break;
        case 48: _t->openCustomplotForm(); break;
        case 49: _t->closeCustomplotForm(); break;
        case 50: _t->reopenCustomplotForm(); break;
        case 51: _t->on_cecRatiosUpdated_recieved((*reinterpret_cast< CEratios*(*)>(_a[1]))); break;
        case 52: _t->refresh_screen(); break;
        case 53: _t->initBars(); break;
        case 54: _t->setDisplayOutputString((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 55: _t->on_startSerialOutputRequest_recieved(); break;
        case 56: _t->on_stopSerialOutputRequest_recieved(); break;
        case 57: _t->on_errorSerialOutputRequest_recieved(); break;
        case 58: _t->updateBiasMode(); break;
        case 59: _t->updateAPDTemperature(); break;
        case 60: _t->on_OffsetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 61: _t->on_PresetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 62: _t->on_pushButton_11_clicked(); break;
        case 63: _t->on_pushButton_13_clicked(); break;
        case 64: _t->on_pushButton_12_clicked(); break;
        case 65: _t->on_toolButton_2_clicked(); break;
        case 66: _t->on_initAxisComplete_recieved(); break;
        case 67: _t->on_pushButton_7_clicked(); break;
        case 68: _t->on_resetButtonAxis1_clicked(); break;
        case 69: _t->on_resetButtonAxis2_clicked(); break;
        case 70: _t->on_resetButtonAxis3_clicked(); break;
        case 71: _t->on_resetButtonAxis4_clicked(); break;
        case 72: _t->onBoardsInitializationComplete(); break;
        case 73: _t->refreshLEDsStatus(); break;
        case 74: _t->initBoards((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 75: _t->on_leftBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->on_rightBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 77: _t->speedUpdateLeftBlockValue(); break;
        case 78: _t->speedSelectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 79: _t->updateLeftBlockValue(); break;
        case 80: _t->selectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 81: _t->updateRightBlockValue(); break;
        case 82: _t->selectRightBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 83: _t->updateCECRatios(); break;
        case 84: _t->on_pushButton_8_clicked(); break;
        case 85: _t->processCecAxisClickedEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 86: _t->cecAxisClickedThreadEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 87: _t->on_resetButtonAllAxis_clicked(); break;
        case 88: _t->on_ramDataFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 89: _t->on_fifoFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 90: _t->on_comboBox_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 91: _t->on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 92: _t->on_modifyBaseAddressRequest_received((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 93: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 94: _t->on_stopContinuousScanSignal_received(); break;
        case 95: _t->stopContinuousScanThread(); break;
        case 96: _t->on_radioButton_clicked(); break;
        case 97: _t->updateMixingFrequencyBar(); break;
        case 98: _t->on_ceUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 99: _t->updateOPtPwrBar(); break;
        case 100: _t->on_radioButton_2_clicked(); break;
        case 101: _t->on_cecAxis1_clicked(); break;
        case 102: _t->on_cecAxis2_clicked(); break;
        case 103: _t->on_cecAxis3_clicked(); break;
        case 104: _t->on_cecAxis4_clicked(); break;
        case 105: _t->on_ceDisplayAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 106: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 107: _t->on_enableAxis1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 108: _t->on_enableAxis2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 109: _t->on_enableAxis3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 110: _t->on_enableAxis4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 111: _t->on_biasModeAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 112: _t->on_adpTempAxes_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 113: _t->on_buttonSerialOutput_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 35:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 85:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        case 86:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::fifoModeSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopContinuousScanSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startGraph)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , int , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateSettingsRequest)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeFlyscanFormRequest)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePositionOffsetFormRequest)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePresetPositionFormRequest)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeSettingsFormRequest)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeCustomplotFormRequest)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initBoardsRequest)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::scaleAxisRequest)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::resetAxisRequest)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::changeBiasModeRequest)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initAxisRequest)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::settingsFormRun)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::OffsetPosChanged)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::PresetPosChanged)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::configureCEChardwareRequest)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopCEChardwareRequest)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateCECRatiosRequest)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanErrorCode)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned char * , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanStatValues)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanProcTerm)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::ssiDataAvailable)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::ssiSquelchValues)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::KpKvValues)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::readGSEDataComplete)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initSettingsFormRequest)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , uint32_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::apdValues)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , bool * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::gainControlsValues)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updatePositionOnGraphs)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeSdoRequest)) {
                *result = 31;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 114)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 114;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 114)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 114;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::fifoModeSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::stopContinuousScanSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::startGraph()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::updateSettingsRequest(int _t1, int _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::closeFlyscanFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::closePositionOffsetFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::closePresetPositionFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::closeSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MainWindow::closeCustomplotFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MainWindow::initBoardsRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MainWindow::scaleAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::resetAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::changeBiasModeRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::initAxisRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void MainWindow::settingsFormRun()
{
    QMetaObject::activate(this, &staticMetaObject, 14, nullptr);
}

// SIGNAL 15
void MainWindow::OffsetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::PresetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::configureCEChardwareRequest(unsigned int _t1, unsigned int _t2, unsigned int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::stopCEChardwareRequest(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void MainWindow::updateCECRatiosRequest(unsigned int _t1, unsigned int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void MainWindow::flyscanErrorCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void MainWindow::flyscanStatValues(unsigned char * _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void MainWindow::flyscanProcTerm()
{
    QMetaObject::activate(this, &staticMetaObject, 22, nullptr);
}

// SIGNAL 23
void MainWindow::ssiDataAvailable(unsigned int _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void MainWindow::ssiSquelchValues(unsigned int _t1, unsigned int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void MainWindow::KpKvValues(unsigned int _t1, int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void MainWindow::readGSEDataComplete(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void MainWindow::initSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 27, nullptr);
}

// SIGNAL 28
void MainWindow::apdValues(unsigned int _t1, uint32_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void MainWindow::gainControlsValues(unsigned int _t1, bool * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 29, _a);
}

// SIGNAL 30
void MainWindow::updatePositionOnGraphs(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void MainWindow::closeSdoRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 31, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
