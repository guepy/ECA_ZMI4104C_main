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
    QByteArrayData data[164];
    char stringdata0[3071];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "initCeParams"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 7), // "uint8_t"
QT_MOC_LITERAL(4, 33, 4), // "axis"
QT_MOC_LITERAL(5, 38, 15), // "sampFreqRequest"
QT_MOC_LITERAL(6, 54, 14), // "fifoModeSignal"
QT_MOC_LITERAL(7, 69, 5), // "index"
QT_MOC_LITERAL(8, 75, 24), // "stopContinuousScanSignal"
QT_MOC_LITERAL(9, 100, 10), // "startGraph"
QT_MOC_LITERAL(10, 111, 21), // "updateSettingsRequest"
QT_MOC_LITERAL(11, 133, 1), // "a"
QT_MOC_LITERAL(12, 135, 1), // "b"
QT_MOC_LITERAL(13, 137, 7), // "double*"
QT_MOC_LITERAL(14, 145, 3), // "val"
QT_MOC_LITERAL(15, 149, 23), // "closeFlyscanFormRequest"
QT_MOC_LITERAL(16, 173, 30), // "closePositionOffsetFormRequest"
QT_MOC_LITERAL(17, 204, 30), // "closePresetPositionFormRequest"
QT_MOC_LITERAL(18, 235, 24), // "closeSettingsFormRequest"
QT_MOC_LITERAL(19, 260, 26), // "closeCustomplotFormRequest"
QT_MOC_LITERAL(20, 287, 17), // "initBoardsRequest"
QT_MOC_LITERAL(21, 305, 16), // "scaleAxisRequest"
QT_MOC_LITERAL(22, 322, 5), // "units"
QT_MOC_LITERAL(23, 328, 16), // "resetAxisRequest"
QT_MOC_LITERAL(24, 345, 21), // "changeBiasModeRequest"
QT_MOC_LITERAL(25, 367, 15), // "initAxisRequest"
QT_MOC_LITERAL(26, 383, 15), // "settingsFormRun"
QT_MOC_LITERAL(27, 399, 16), // "OffsetPosChanged"
QT_MOC_LITERAL(28, 416, 9), // "posOffPtr"
QT_MOC_LITERAL(29, 426, 16), // "PresetPosChanged"
QT_MOC_LITERAL(30, 443, 10), // "PresPosPtr"
QT_MOC_LITERAL(31, 454, 27), // "configureCEChardwareRequest"
QT_MOC_LITERAL(32, 482, 8), // "ceVelMin"
QT_MOC_LITERAL(33, 491, 8), // "ceVelMax"
QT_MOC_LITERAL(34, 500, 22), // "stopCEChardwareRequest"
QT_MOC_LITERAL(35, 523, 22), // "updateCECRatiosRequest"
QT_MOC_LITERAL(36, 546, 16), // "flyscanErrorCode"
QT_MOC_LITERAL(37, 563, 8), // "ret_code"
QT_MOC_LITERAL(38, 572, 17), // "flyscanStatValues"
QT_MOC_LITERAL(39, 590, 14), // "unsigned char*"
QT_MOC_LITERAL(40, 605, 7), // "axisTab"
QT_MOC_LITERAL(41, 613, 4), // "mean"
QT_MOC_LITERAL(42, 618, 6), // "stdDev"
QT_MOC_LITERAL(43, 625, 15), // "flyscanProcTerm"
QT_MOC_LITERAL(44, 641, 16), // "ssiDataAvailable"
QT_MOC_LITERAL(45, 658, 7), // "ssiVals"
QT_MOC_LITERAL(46, 666, 10), // "optPwrVals"
QT_MOC_LITERAL(47, 677, 16), // "ssiSquelchValues"
QT_MOC_LITERAL(48, 694, 5), // "uint*"
QT_MOC_LITERAL(49, 700, 10), // "KpKvValues"
QT_MOC_LITERAL(50, 711, 4), // "int*"
QT_MOC_LITERAL(51, 716, 5), // "coeff"
QT_MOC_LITERAL(52, 722, 19), // "readGSEDataComplete"
QT_MOC_LITERAL(53, 742, 7), // "gseData"
QT_MOC_LITERAL(54, 750, 23), // "initSettingsFormRequest"
QT_MOC_LITERAL(55, 774, 9), // "apdValues"
QT_MOC_LITERAL(56, 784, 9), // "uint32_t*"
QT_MOC_LITERAL(57, 794, 18), // "gainControlsValues"
QT_MOC_LITERAL(58, 813, 5), // "bool*"
QT_MOC_LITERAL(59, 819, 22), // "updatePositionOnGraphs"
QT_MOC_LITERAL(60, 842, 8), // "position"
QT_MOC_LITERAL(61, 851, 15), // "closeSdoRequest"
QT_MOC_LITERAL(62, 867, 15), // "openFlyscanForm"
QT_MOC_LITERAL(63, 883, 16), // "closeFlyscanForm"
QT_MOC_LITERAL(64, 900, 17), // "reopenFlyscanForm"
QT_MOC_LITERAL(65, 918, 25), // "on_m_settingsMenu_clicked"
QT_MOC_LITERAL(66, 944, 8), // "QAction*"
QT_MOC_LITERAL(67, 953, 18), // "reopenSettingsForm"
QT_MOC_LITERAL(68, 972, 16), // "openSettingsForm"
QT_MOC_LITERAL(69, 989, 17), // "closeSettingsForm"
QT_MOC_LITERAL(70, 1007, 22), // "openPresetPositionForm"
QT_MOC_LITERAL(71, 1030, 23), // "closePresetPositionForm"
QT_MOC_LITERAL(72, 1054, 24), // "reopenPresetPositionForm"
QT_MOC_LITERAL(73, 1079, 22), // "openPositionOffsetForm"
QT_MOC_LITERAL(74, 1102, 23), // "closePositionOffsetForm"
QT_MOC_LITERAL(75, 1126, 24), // "reopenPositionOffsetForm"
QT_MOC_LITERAL(76, 1151, 11), // "openSdoForm"
QT_MOC_LITERAL(77, 1163, 12), // "closeSdoForm"
QT_MOC_LITERAL(78, 1176, 13), // "reopenSdoForm"
QT_MOC_LITERAL(79, 1190, 11), // "openCesForm"
QT_MOC_LITERAL(80, 1202, 12), // "closeCesForm"
QT_MOC_LITERAL(81, 1215, 13), // "reopenCesForm"
QT_MOC_LITERAL(82, 1229, 18), // "openCustomplotForm"
QT_MOC_LITERAL(83, 1248, 19), // "closeCustomplotForm"
QT_MOC_LITERAL(84, 1268, 20), // "reopenCustomplotForm"
QT_MOC_LITERAL(85, 1289, 28), // "on_cecRatiosUpdated_recieved"
QT_MOC_LITERAL(86, 1318, 9), // "CEratios*"
QT_MOC_LITERAL(87, 1328, 14), // "refresh_screen"
QT_MOC_LITERAL(88, 1343, 8), // "initBars"
QT_MOC_LITERAL(89, 1352, 22), // "setDisplayOutputString"
QT_MOC_LITERAL(90, 1375, 11), // "std::string"
QT_MOC_LITERAL(91, 1387, 4), // "text"
QT_MOC_LITERAL(92, 1392, 3), // "col"
QT_MOC_LITERAL(93, 1396, 36), // "on_startSerialOutputRequest_r..."
QT_MOC_LITERAL(94, 1433, 35), // "on_stopSerialOutputRequest_re..."
QT_MOC_LITERAL(95, 1469, 36), // "on_errorSerialOutputRequest_r..."
QT_MOC_LITERAL(96, 1506, 14), // "updateBiasMode"
QT_MOC_LITERAL(97, 1521, 20), // "updateAPDTemperature"
QT_MOC_LITERAL(98, 1542, 20), // "on_OffsetPos_Changed"
QT_MOC_LITERAL(99, 1563, 9), // "OffPosPtr"
QT_MOC_LITERAL(100, 1573, 20), // "on_PresetPos_Changed"
QT_MOC_LITERAL(101, 1594, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(102, 1619, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(103, 1644, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(104, 1669, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(105, 1693, 28), // "on_initAxisComplete_recieved"
QT_MOC_LITERAL(106, 1722, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(107, 1746, 27), // "on_resetButtonAxis1_clicked"
QT_MOC_LITERAL(108, 1774, 27), // "on_resetButtonAxis2_clicked"
QT_MOC_LITERAL(109, 1802, 27), // "on_resetButtonAxis3_clicked"
QT_MOC_LITERAL(110, 1830, 27), // "on_resetButtonAxis4_clicked"
QT_MOC_LITERAL(111, 1858, 30), // "onBoardsInitializationComplete"
QT_MOC_LITERAL(112, 1889, 17), // "refreshLEDsStatus"
QT_MOC_LITERAL(113, 1907, 10), // "initBoards"
QT_MOC_LITERAL(114, 1918, 5), // "argin"
QT_MOC_LITERAL(115, 1924, 37), // "on_leftBlockUnits_currentInde..."
QT_MOC_LITERAL(116, 1962, 38), // "on_rightBlockUnits_currentInd..."
QT_MOC_LITERAL(117, 2001, 25), // "speedUpdateLeftBlockValue"
QT_MOC_LITERAL(118, 2027, 25), // "speedSelectLeftBlockValue"
QT_MOC_LITERAL(119, 2053, 20), // "updateLeftBlockValue"
QT_MOC_LITERAL(120, 2074, 20), // "selectLeftBlockValue"
QT_MOC_LITERAL(121, 2095, 21), // "updateRightBlockValue"
QT_MOC_LITERAL(122, 2117, 21), // "selectRightBlockValue"
QT_MOC_LITERAL(123, 2139, 15), // "updateCECRatios"
QT_MOC_LITERAL(124, 2155, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(125, 2179, 26), // "processCecAxisClickedEvent"
QT_MOC_LITERAL(126, 2206, 13), // "axisListIndex"
QT_MOC_LITERAL(127, 2220, 10), // "QCheckBox*"
QT_MOC_LITERAL(128, 2231, 15), // "cecAxisCheckBox"
QT_MOC_LITERAL(129, 2247, 25), // "cecAxisClickedThreadEvent"
QT_MOC_LITERAL(130, 2273, 29), // "on_resetButtonAllAxis_clicked"
QT_MOC_LITERAL(131, 2303, 33), // "on_ramDataFlyscanRequest_reci..."
QT_MOC_LITERAL(132, 2337, 4), // "freq"
QT_MOC_LITERAL(133, 2342, 4), // "size"
QT_MOC_LITERAL(134, 2347, 4), // "time"
QT_MOC_LITERAL(135, 2352, 3), // "nbr"
QT_MOC_LITERAL(136, 2356, 30), // "on_fifoFlyscanRequest_recieved"
QT_MOC_LITERAL(137, 2387, 33), // "on_comboBox_3_currentIndexCha..."
QT_MOC_LITERAL(138, 2421, 33), // "on_comboBox_4_currentIndexCha..."
QT_MOC_LITERAL(139, 2455, 36), // "on_modifyBaseAddressRequest_r..."
QT_MOC_LITERAL(140, 2492, 3), // "add"
QT_MOC_LITERAL(141, 2496, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(142, 2528, 36), // "on_stopContinuousScanSignal_r..."
QT_MOC_LITERAL(143, 2565, 24), // "stopContinuousScanThread"
QT_MOC_LITERAL(144, 2590, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(145, 2613, 24), // "updateMixingFrequencyBar"
QT_MOC_LITERAL(146, 2638, 30), // "on_ceUnits_currentIndexChanged"
QT_MOC_LITERAL(147, 2669, 15), // "updateOPtPwrBar"
QT_MOC_LITERAL(148, 2685, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(149, 2710, 19), // "on_cecAxis1_clicked"
QT_MOC_LITERAL(150, 2730, 19), // "on_cecAxis2_clicked"
QT_MOC_LITERAL(151, 2750, 19), // "on_cecAxis3_clicked"
QT_MOC_LITERAL(152, 2770, 19), // "on_cecAxis4_clicked"
QT_MOC_LITERAL(153, 2790, 36), // "on_ceDisplayAxis_currentIndex..."
QT_MOC_LITERAL(154, 2827, 19), // "on_checkBox_clicked"
QT_MOC_LITERAL(155, 2847, 7), // "checked"
QT_MOC_LITERAL(156, 2855, 22), // "on_enableAxis1_clicked"
QT_MOC_LITERAL(157, 2878, 22), // "on_enableAxis2_clicked"
QT_MOC_LITERAL(158, 2901, 22), // "on_enableAxis3_clicked"
QT_MOC_LITERAL(159, 2924, 22), // "on_enableAxis4_clicked"
QT_MOC_LITERAL(160, 2947, 35), // "on_biasModeAxis_currentIndexC..."
QT_MOC_LITERAL(161, 2983, 34), // "on_adpTempAxes_currentIndexCh..."
QT_MOC_LITERAL(162, 3018, 29), // "on_buttonSerialOutput_clicked"
QT_MOC_LITERAL(163, 3048, 22) // "on_cecSettings_clicked"

    },
    "MainWindow\0initCeParams\0\0uint8_t\0axis\0"
    "sampFreqRequest\0fifoModeSignal\0index\0"
    "stopContinuousScanSignal\0startGraph\0"
    "updateSettingsRequest\0a\0b\0double*\0val\0"
    "closeFlyscanFormRequest\0"
    "closePositionOffsetFormRequest\0"
    "closePresetPositionFormRequest\0"
    "closeSettingsFormRequest\0"
    "closeCustomplotFormRequest\0initBoardsRequest\0"
    "scaleAxisRequest\0units\0resetAxisRequest\0"
    "changeBiasModeRequest\0initAxisRequest\0"
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
    "closeSdoForm\0reopenSdoForm\0openCesForm\0"
    "closeCesForm\0reopenCesForm\0"
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
    "on_buttonSerialOutput_clicked\0"
    "on_cecSettings_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     120,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      34,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  614,    2, 0x06 /* Public */,
       5,    0,  617,    2, 0x06 /* Public */,
       6,    1,  618,    2, 0x06 /* Public */,
       8,    0,  621,    2, 0x06 /* Public */,
       9,    0,  622,    2, 0x06 /* Public */,
      10,    3,  623,    2, 0x06 /* Public */,
      15,    0,  630,    2, 0x06 /* Public */,
      16,    0,  631,    2, 0x06 /* Public */,
      17,    0,  632,    2, 0x06 /* Public */,
      18,    0,  633,    2, 0x06 /* Public */,
      19,    0,  634,    2, 0x06 /* Public */,
      20,    0,  635,    2, 0x06 /* Public */,
      21,    1,  636,    2, 0x06 /* Public */,
      23,    1,  639,    2, 0x06 /* Public */,
      24,    1,  642,    2, 0x06 /* Public */,
      25,    0,  645,    2, 0x06 /* Public */,
      26,    0,  646,    2, 0x06 /* Public */,
      27,    1,  647,    2, 0x06 /* Public */,
      29,    1,  650,    2, 0x06 /* Public */,
      31,    3,  653,    2, 0x06 /* Public */,
      34,    1,  660,    2, 0x06 /* Public */,
      35,    2,  663,    2, 0x06 /* Public */,
      36,    1,  668,    2, 0x06 /* Public */,
      38,    3,  671,    2, 0x06 /* Public */,
      43,    0,  678,    2, 0x06 /* Public */,
      44,    3,  679,    2, 0x06 /* Public */,
      47,    2,  686,    2, 0x06 /* Public */,
      49,    2,  691,    2, 0x06 /* Public */,
      52,    1,  696,    2, 0x06 /* Public */,
      54,    0,  699,    2, 0x06 /* Public */,
      55,    2,  700,    2, 0x06 /* Public */,
      57,    2,  705,    2, 0x06 /* Public */,
      59,    1,  710,    2, 0x06 /* Public */,
      61,    0,  713,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      62,    0,  714,    2, 0x0a /* Public */,
      63,    0,  715,    2, 0x0a /* Public */,
      64,    0,  716,    2, 0x0a /* Public */,
      65,    1,  717,    2, 0x0a /* Public */,
      67,    0,  720,    2, 0x0a /* Public */,
      68,    0,  721,    2, 0x0a /* Public */,
      69,    0,  722,    2, 0x0a /* Public */,
      70,    0,  723,    2, 0x0a /* Public */,
      71,    0,  724,    2, 0x0a /* Public */,
      72,    0,  725,    2, 0x0a /* Public */,
      73,    0,  726,    2, 0x0a /* Public */,
      74,    0,  727,    2, 0x0a /* Public */,
      75,    0,  728,    2, 0x0a /* Public */,
      76,    0,  729,    2, 0x0a /* Public */,
      77,    0,  730,    2, 0x0a /* Public */,
      78,    0,  731,    2, 0x0a /* Public */,
      79,    0,  732,    2, 0x0a /* Public */,
      80,    0,  733,    2, 0x0a /* Public */,
      81,    0,  734,    2, 0x0a /* Public */,
      82,    0,  735,    2, 0x0a /* Public */,
      83,    0,  736,    2, 0x0a /* Public */,
      84,    0,  737,    2, 0x0a /* Public */,
      85,    1,  738,    2, 0x0a /* Public */,
      87,    0,  741,    2, 0x0a /* Public */,
      88,    0,  742,    2, 0x08 /* Private */,
      89,    2,  743,    2, 0x08 /* Private */,
      93,    0,  748,    2, 0x08 /* Private */,
      94,    0,  749,    2, 0x08 /* Private */,
      95,    0,  750,    2, 0x08 /* Private */,
      96,    0,  751,    2, 0x08 /* Private */,
      97,    0,  752,    2, 0x08 /* Private */,
      98,    1,  753,    2, 0x08 /* Private */,
     100,    1,  756,    2, 0x08 /* Private */,
     101,    0,  759,    2, 0x08 /* Private */,
     102,    0,  760,    2, 0x08 /* Private */,
     103,    0,  761,    2, 0x08 /* Private */,
     104,    0,  762,    2, 0x08 /* Private */,
     105,    0,  763,    2, 0x08 /* Private */,
     106,    0,  764,    2, 0x08 /* Private */,
     107,    0,  765,    2, 0x08 /* Private */,
     108,    0,  766,    2, 0x08 /* Private */,
     109,    0,  767,    2, 0x08 /* Private */,
     110,    0,  768,    2, 0x08 /* Private */,
     111,    0,  769,    2, 0x08 /* Private */,
     112,    0,  770,    2, 0x08 /* Private */,
     113,    1,  771,    2, 0x08 /* Private */,
     115,    1,  774,    2, 0x08 /* Private */,
     116,    1,  777,    2, 0x08 /* Private */,
     117,    0,  780,    2, 0x08 /* Private */,
     118,    1,  781,    2, 0x08 /* Private */,
     119,    0,  784,    2, 0x08 /* Private */,
     120,    1,  785,    2, 0x08 /* Private */,
     121,    0,  788,    2, 0x08 /* Private */,
     122,    1,  789,    2, 0x08 /* Private */,
     123,    0,  792,    2, 0x08 /* Private */,
     124,    0,  793,    2, 0x08 /* Private */,
     125,    3,  794,    2, 0x08 /* Private */,
     129,    3,  801,    2, 0x08 /* Private */,
     130,    0,  808,    2, 0x08 /* Private */,
     131,    4,  809,    2, 0x08 /* Private */,
     136,    4,  818,    2, 0x08 /* Private */,
     137,    1,  827,    2, 0x08 /* Private */,
     138,    1,  830,    2, 0x08 /* Private */,
     139,    1,  833,    2, 0x08 /* Private */,
     141,    1,  836,    2, 0x08 /* Private */,
     142,    0,  839,    2, 0x08 /* Private */,
     143,    0,  840,    2, 0x08 /* Private */,
     144,    0,  841,    2, 0x08 /* Private */,
     145,    0,  842,    2, 0x08 /* Private */,
     146,    1,  843,    2, 0x08 /* Private */,
     147,    0,  846,    2, 0x08 /* Private */,
     148,    0,  847,    2, 0x08 /* Private */,
     149,    0,  848,    2, 0x08 /* Private */,
     150,    0,  849,    2, 0x08 /* Private */,
     151,    0,  850,    2, 0x08 /* Private */,
     152,    0,  851,    2, 0x08 /* Private */,
     153,    1,  852,    2, 0x08 /* Private */,
     154,    1,  855,    2, 0x08 /* Private */,
     156,    1,  858,    2, 0x08 /* Private */,
     157,    1,  861,    2, 0x08 /* Private */,
     158,    1,  864,    2, 0x08 /* Private */,
     159,    1,  867,    2, 0x08 /* Private */,
     160,    1,  870,    2, 0x08 /* Private */,
     161,    1,  873,    2, 0x08 /* Private */,
     162,    0,  876,    2, 0x08 /* Private */,
     163,    0,  877,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 13,   11,   12,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   28,
    QMetaType::Void, 0x80000000 | 13,   30,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,    4,   32,   33,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt,    4,    7,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void, 0x80000000 | 39, 0x80000000 | 13, 0x80000000 | 13,   40,   41,   42,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 13, 0x80000000 | 13,    4,   45,   46,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 48,    4,   14,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 50,    4,   51,
    QMetaType::Void, 0x80000000 | 13,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 56,    4,   51,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 58,    4,   14,
    QMetaType::Void, 0x80000000 | 13,   60,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 66,    2,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 86,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 90, 0x80000000 | 90,   91,   92,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   99,
    QMetaType::Void, 0x80000000 | 13,   30,
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
    QMetaType::Void, QMetaType::Bool,  114,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 50, 0x80000000 | 127,    4,  126,  128,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 50, 0x80000000 | 127,    4,  126,  128,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,  132,  133,  134,  135,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,  132,  133,  134,  135,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::UInt,  140,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,  155,
    QMetaType::Void, QMetaType::Bool,  155,
    QMetaType::Void, QMetaType::Bool,  155,
    QMetaType::Void, QMetaType::Bool,  155,
    QMetaType::Void, QMetaType::Bool,  155,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initCeParams((*reinterpret_cast< uint8_t(*)>(_a[1]))); break;
        case 1: _t->sampFreqRequest(); break;
        case 2: _t->fifoModeSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->stopContinuousScanSignal(); break;
        case 4: _t->startGraph(); break;
        case 5: _t->updateSettingsRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 6: _t->closeFlyscanFormRequest(); break;
        case 7: _t->closePositionOffsetFormRequest(); break;
        case 8: _t->closePresetPositionFormRequest(); break;
        case 9: _t->closeSettingsFormRequest(); break;
        case 10: _t->closeCustomplotFormRequest(); break;
        case 11: _t->initBoardsRequest(); break;
        case 12: _t->scaleAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->resetAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->changeBiasModeRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->initAxisRequest(); break;
        case 16: _t->settingsFormRun(); break;
        case 17: _t->OffsetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 18: _t->PresetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 19: _t->configureCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 20: _t->stopCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 21: _t->updateCECRatiosRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 22: _t->flyscanErrorCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->flyscanStatValues((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 24: _t->flyscanProcTerm(); break;
        case 25: _t->ssiDataAvailable((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 26: _t->ssiSquelchValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint*(*)>(_a[2]))); break;
        case 27: _t->KpKvValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2]))); break;
        case 28: _t->readGSEDataComplete((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 29: _t->initSettingsFormRequest(); break;
        case 30: _t->apdValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint32_t*(*)>(_a[2]))); break;
        case 31: _t->gainControlsValues((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 32: _t->updatePositionOnGraphs((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 33: _t->closeSdoRequest(); break;
        case 34: _t->openFlyscanForm(); break;
        case 35: _t->closeFlyscanForm(); break;
        case 36: _t->reopenFlyscanForm(); break;
        case 37: _t->on_m_settingsMenu_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 38: _t->reopenSettingsForm(); break;
        case 39: _t->openSettingsForm(); break;
        case 40: _t->closeSettingsForm(); break;
        case 41: _t->openPresetPositionForm(); break;
        case 42: _t->closePresetPositionForm(); break;
        case 43: _t->reopenPresetPositionForm(); break;
        case 44: _t->openPositionOffsetForm(); break;
        case 45: _t->closePositionOffsetForm(); break;
        case 46: _t->reopenPositionOffsetForm(); break;
        case 47: _t->openSdoForm(); break;
        case 48: _t->closeSdoForm(); break;
        case 49: _t->reopenSdoForm(); break;
        case 50: _t->openCesForm(); break;
        case 51: _t->closeCesForm(); break;
        case 52: _t->reopenCesForm(); break;
        case 53: _t->openCustomplotForm(); break;
        case 54: _t->closeCustomplotForm(); break;
        case 55: _t->reopenCustomplotForm(); break;
        case 56: _t->on_cecRatiosUpdated_recieved((*reinterpret_cast< CEratios*(*)>(_a[1]))); break;
        case 57: _t->refresh_screen(); break;
        case 58: _t->initBars(); break;
        case 59: _t->setDisplayOutputString((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 60: _t->on_startSerialOutputRequest_recieved(); break;
        case 61: _t->on_stopSerialOutputRequest_recieved(); break;
        case 62: _t->on_errorSerialOutputRequest_recieved(); break;
        case 63: _t->updateBiasMode(); break;
        case 64: _t->updateAPDTemperature(); break;
        case 65: _t->on_OffsetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 66: _t->on_PresetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 67: _t->on_pushButton_11_clicked(); break;
        case 68: _t->on_pushButton_13_clicked(); break;
        case 69: _t->on_pushButton_12_clicked(); break;
        case 70: _t->on_toolButton_2_clicked(); break;
        case 71: _t->on_initAxisComplete_recieved(); break;
        case 72: _t->on_pushButton_7_clicked(); break;
        case 73: _t->on_resetButtonAxis1_clicked(); break;
        case 74: _t->on_resetButtonAxis2_clicked(); break;
        case 75: _t->on_resetButtonAxis3_clicked(); break;
        case 76: _t->on_resetButtonAxis4_clicked(); break;
        case 77: _t->onBoardsInitializationComplete(); break;
        case 78: _t->refreshLEDsStatus(); break;
        case 79: _t->initBoards((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 80: _t->on_leftBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 81: _t->on_rightBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 82: _t->speedUpdateLeftBlockValue(); break;
        case 83: _t->speedSelectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 84: _t->updateLeftBlockValue(); break;
        case 85: _t->selectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 86: _t->updateRightBlockValue(); break;
        case 87: _t->selectRightBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 88: _t->updateCECRatios(); break;
        case 89: _t->on_pushButton_8_clicked(); break;
        case 90: _t->processCecAxisClickedEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 91: _t->cecAxisClickedThreadEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 92: _t->on_resetButtonAllAxis_clicked(); break;
        case 93: _t->on_ramDataFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 94: _t->on_fifoFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 95: _t->on_comboBox_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 96: _t->on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 97: _t->on_modifyBaseAddressRequest_received((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 98: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 99: _t->on_stopContinuousScanSignal_received(); break;
        case 100: _t->stopContinuousScanThread(); break;
        case 101: _t->on_radioButton_clicked(); break;
        case 102: _t->updateMixingFrequencyBar(); break;
        case 103: _t->on_ceUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 104: _t->updateOPtPwrBar(); break;
        case 105: _t->on_radioButton_2_clicked(); break;
        case 106: _t->on_cecAxis1_clicked(); break;
        case 107: _t->on_cecAxis2_clicked(); break;
        case 108: _t->on_cecAxis3_clicked(); break;
        case 109: _t->on_cecAxis4_clicked(); break;
        case 110: _t->on_ceDisplayAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 111: _t->on_checkBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 112: _t->on_enableAxis1_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 113: _t->on_enableAxis2_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 114: _t->on_enableAxis3_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 115: _t->on_enableAxis4_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 116: _t->on_biasModeAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 117: _t->on_adpTempAxes_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 118: _t->on_buttonSerialOutput_clicked(); break;
        case 119: _t->on_cecSettings_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 37:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 90:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        case 91:
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
            using _t = void (MainWindow::*)(uint8_t );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initCeParams)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sampFreqRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::fifoModeSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopContinuousScanSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startGraph)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , int , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateSettingsRequest)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeFlyscanFormRequest)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePositionOffsetFormRequest)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePresetPositionFormRequest)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeSettingsFormRequest)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeCustomplotFormRequest)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initBoardsRequest)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::scaleAxisRequest)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::resetAxisRequest)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::changeBiasModeRequest)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initAxisRequest)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::settingsFormRun)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::OffsetPosChanged)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::PresetPosChanged)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::configureCEChardwareRequest)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopCEChardwareRequest)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateCECRatiosRequest)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanErrorCode)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned char * , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanStatValues)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanProcTerm)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::ssiDataAvailable)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::ssiSquelchValues)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::KpKvValues)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::readGSEDataComplete)) {
                *result = 28;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initSettingsFormRequest)) {
                *result = 29;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , uint32_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::apdValues)) {
                *result = 30;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , bool * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::gainControlsValues)) {
                *result = 31;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updatePositionOnGraphs)) {
                *result = 32;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeSdoRequest)) {
                *result = 33;
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
        if (_id < 120)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 120;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 120)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 120;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::initCeParams(uint8_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sampFreqRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::fifoModeSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::stopContinuousScanSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::startGraph()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::updateSettingsRequest(int _t1, int _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::closeFlyscanFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::closePositionOffsetFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MainWindow::closePresetPositionFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MainWindow::closeSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MainWindow::closeCustomplotFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void MainWindow::initBoardsRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void MainWindow::scaleAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::resetAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MainWindow::changeBiasModeRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::initAxisRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 15, nullptr);
}

// SIGNAL 16
void MainWindow::settingsFormRun()
{
    QMetaObject::activate(this, &staticMetaObject, 16, nullptr);
}

// SIGNAL 17
void MainWindow::OffsetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::PresetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void MainWindow::configureCEChardwareRequest(unsigned int _t1, unsigned int _t2, unsigned int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void MainWindow::stopCEChardwareRequest(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void MainWindow::updateCECRatiosRequest(unsigned int _t1, unsigned int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void MainWindow::flyscanErrorCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void MainWindow::flyscanStatValues(unsigned char * _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void MainWindow::flyscanProcTerm()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void MainWindow::ssiDataAvailable(unsigned int _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void MainWindow::ssiSquelchValues(unsigned int _t1, unsigned int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 26, _a);
}

// SIGNAL 27
void MainWindow::KpKvValues(unsigned int _t1, int * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void MainWindow::readGSEDataComplete(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}

// SIGNAL 29
void MainWindow::initSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 29, nullptr);
}

// SIGNAL 30
void MainWindow::apdValues(unsigned int _t1, uint32_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 30, _a);
}

// SIGNAL 31
void MainWindow::gainControlsValues(unsigned int _t1, bool * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 31, _a);
}

// SIGNAL 32
void MainWindow::updatePositionOnGraphs(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 32, _a);
}

// SIGNAL 33
void MainWindow::closeSdoRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 33, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
