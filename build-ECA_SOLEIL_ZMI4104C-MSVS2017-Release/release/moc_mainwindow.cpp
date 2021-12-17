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
    QByteArrayData data[119];
    char stringdata0[2176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "initComplete"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 21), // "updateSettingsRequest"
QT_MOC_LITERAL(4, 47, 1), // "a"
QT_MOC_LITERAL(5, 49, 1), // "b"
QT_MOC_LITERAL(6, 51, 7), // "double*"
QT_MOC_LITERAL(7, 59, 3), // "val"
QT_MOC_LITERAL(8, 63, 23), // "closeFlyscanFormRequest"
QT_MOC_LITERAL(9, 87, 30), // "closePositionOffsetFormRequest"
QT_MOC_LITERAL(10, 118, 30), // "closePresetPositionFormRequest"
QT_MOC_LITERAL(11, 149, 24), // "closeSettingsFormRequest"
QT_MOC_LITERAL(12, 174, 26), // "closeCustomplotFormRequest"
QT_MOC_LITERAL(13, 201, 17), // "initBoardsRequest"
QT_MOC_LITERAL(14, 219, 16), // "scaleAxisRequest"
QT_MOC_LITERAL(15, 236, 5), // "units"
QT_MOC_LITERAL(16, 242, 16), // "resetAxisRequest"
QT_MOC_LITERAL(17, 259, 4), // "axis"
QT_MOC_LITERAL(18, 264, 21), // "changeBiasModeRequest"
QT_MOC_LITERAL(19, 286, 5), // "index"
QT_MOC_LITERAL(20, 292, 15), // "initAxisRequest"
QT_MOC_LITERAL(21, 308, 16), // "OffsetPosChanged"
QT_MOC_LITERAL(22, 325, 9), // "posOffPtr"
QT_MOC_LITERAL(23, 335, 16), // "PresetPosChanged"
QT_MOC_LITERAL(24, 352, 10), // "PresPosPtr"
QT_MOC_LITERAL(25, 363, 27), // "configureCEChardwareRequest"
QT_MOC_LITERAL(26, 391, 8), // "ceVelMin"
QT_MOC_LITERAL(27, 400, 8), // "ceVelMax"
QT_MOC_LITERAL(28, 409, 22), // "stopCEChardwareRequest"
QT_MOC_LITERAL(29, 432, 22), // "updateCECRatiosRequest"
QT_MOC_LITERAL(30, 455, 9), // "CEratios*"
QT_MOC_LITERAL(31, 465, 8), // "ceRatios"
QT_MOC_LITERAL(32, 474, 16), // "flyscanErrorCode"
QT_MOC_LITERAL(33, 491, 8), // "ret_code"
QT_MOC_LITERAL(34, 500, 17), // "flyscanStatValues"
QT_MOC_LITERAL(35, 518, 14), // "unsigned char*"
QT_MOC_LITERAL(36, 533, 7), // "axisTab"
QT_MOC_LITERAL(37, 541, 4), // "mean"
QT_MOC_LITERAL(38, 546, 6), // "stdDev"
QT_MOC_LITERAL(39, 553, 15), // "flyscanProcTerm"
QT_MOC_LITERAL(40, 569, 16), // "ssiDataAvailable"
QT_MOC_LITERAL(41, 586, 7), // "ssiVals"
QT_MOC_LITERAL(42, 594, 10), // "optPwrVals"
QT_MOC_LITERAL(43, 605, 16), // "ssiSquelchValues"
QT_MOC_LITERAL(44, 622, 7), // "uint8_t"
QT_MOC_LITERAL(45, 630, 10), // "KpKvValues"
QT_MOC_LITERAL(46, 641, 9), // "uint16_t*"
QT_MOC_LITERAL(47, 651, 5), // "coeff"
QT_MOC_LITERAL(48, 657, 19), // "readGSEDataComplete"
QT_MOC_LITERAL(49, 677, 7), // "gseData"
QT_MOC_LITERAL(50, 685, 23), // "initSettingsFormRequest"
QT_MOC_LITERAL(51, 709, 9), // "apdValues"
QT_MOC_LITERAL(52, 719, 9), // "uint32_t*"
QT_MOC_LITERAL(53, 729, 15), // "openFlyscanForm"
QT_MOC_LITERAL(54, 745, 16), // "closeFlyscanForm"
QT_MOC_LITERAL(55, 762, 17), // "reopenFlyscanForm"
QT_MOC_LITERAL(56, 780, 25), // "on_m_settingsMenu_clicked"
QT_MOC_LITERAL(57, 806, 8), // "QAction*"
QT_MOC_LITERAL(58, 815, 18), // "reopenSettingsForm"
QT_MOC_LITERAL(59, 834, 16), // "openSettingsForm"
QT_MOC_LITERAL(60, 851, 17), // "closeSettingsForm"
QT_MOC_LITERAL(61, 869, 22), // "openPresetPositionForm"
QT_MOC_LITERAL(62, 892, 23), // "closePresetPositionForm"
QT_MOC_LITERAL(63, 916, 24), // "reopenPresetPositionForm"
QT_MOC_LITERAL(64, 941, 22), // "openPositionOffsetForm"
QT_MOC_LITERAL(65, 964, 23), // "closePositionOffsetForm"
QT_MOC_LITERAL(66, 988, 24), // "reopenPositionOffsetForm"
QT_MOC_LITERAL(67, 1013, 18), // "openCustomplotForm"
QT_MOC_LITERAL(68, 1032, 19), // "closeCustomplotForm"
QT_MOC_LITERAL(69, 1052, 20), // "reopenCustomplotForm"
QT_MOC_LITERAL(70, 1073, 14), // "refresh_screen"
QT_MOC_LITERAL(71, 1088, 20), // "on_OffsetPos_Changed"
QT_MOC_LITERAL(72, 1109, 9), // "OffPosPtr"
QT_MOC_LITERAL(73, 1119, 20), // "on_PresetPos_Changed"
QT_MOC_LITERAL(74, 1140, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(75, 1165, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(76, 1190, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(77, 1215, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(78, 1239, 28), // "on_initAxisComplete_recieved"
QT_MOC_LITERAL(79, 1268, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(80, 1292, 27), // "on_resetButtonAxis1_clicked"
QT_MOC_LITERAL(81, 1320, 27), // "on_resetButtonAxis2_clicked"
QT_MOC_LITERAL(82, 1348, 27), // "on_resetButtonAxis3_clicked"
QT_MOC_LITERAL(83, 1376, 27), // "on_resetButtonAxis4_clicked"
QT_MOC_LITERAL(84, 1404, 30), // "onBoardsInitializationComplete"
QT_MOC_LITERAL(85, 1435, 17), // "refreshLEDsStatus"
QT_MOC_LITERAL(86, 1453, 10), // "initBoards"
QT_MOC_LITERAL(87, 1464, 37), // "on_leftBlockUnits_currentInde..."
QT_MOC_LITERAL(88, 1502, 38), // "on_rightBlockUnits_currentInd..."
QT_MOC_LITERAL(89, 1541, 20), // "updateLeftBlockValue"
QT_MOC_LITERAL(90, 1562, 20), // "selectLeftBlockValue"
QT_MOC_LITERAL(91, 1583, 21), // "updateRightBlockValue"
QT_MOC_LITERAL(92, 1605, 21), // "selectRightBlockValue"
QT_MOC_LITERAL(93, 1627, 15), // "updateCECRatios"
QT_MOC_LITERAL(94, 1643, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(95, 1667, 26), // "processCecAxisClickedEvent"
QT_MOC_LITERAL(96, 1694, 4), // "int*"
QT_MOC_LITERAL(97, 1699, 13), // "axisListIndex"
QT_MOC_LITERAL(98, 1713, 10), // "QCheckBox*"
QT_MOC_LITERAL(99, 1724, 15), // "cecAxisCheckBox"
QT_MOC_LITERAL(100, 1740, 25), // "cecAxisClickedThreadEvent"
QT_MOC_LITERAL(101, 1766, 29), // "on_resetButtonAllAxis_clicked"
QT_MOC_LITERAL(102, 1796, 33), // "on_ramDataFlyscanRequest_reci..."
QT_MOC_LITERAL(103, 1830, 4), // "freq"
QT_MOC_LITERAL(104, 1835, 4), // "size"
QT_MOC_LITERAL(105, 1840, 4), // "time"
QT_MOC_LITERAL(106, 1845, 3), // "nbr"
QT_MOC_LITERAL(107, 1849, 30), // "on_fifoFlyscanRequest_recieved"
QT_MOC_LITERAL(108, 1880, 33), // "on_comboBox_3_currentIndexCha..."
QT_MOC_LITERAL(109, 1914, 33), // "on_comboBox_4_currentIndexCha..."
QT_MOC_LITERAL(110, 1948, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(111, 1980, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(112, 2003, 30), // "on_ceUnits_currentIndexChanged"
QT_MOC_LITERAL(113, 2034, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(114, 2059, 19), // "on_cecAxis1_clicked"
QT_MOC_LITERAL(115, 2079, 19), // "on_cecAxis2_clicked"
QT_MOC_LITERAL(116, 2099, 19), // "on_cecAxis3_clicked"
QT_MOC_LITERAL(117, 2119, 19), // "on_cecAxis4_clicked"
QT_MOC_LITERAL(118, 2139, 36) // "on_ceDisplayAxis_currentIndex..."

    },
    "MainWindow\0initComplete\0\0updateSettingsRequest\0"
    "a\0b\0double*\0val\0closeFlyscanFormRequest\0"
    "closePositionOffsetFormRequest\0"
    "closePresetPositionFormRequest\0"
    "closeSettingsFormRequest\0"
    "closeCustomplotFormRequest\0initBoardsRequest\0"
    "scaleAxisRequest\0units\0resetAxisRequest\0"
    "axis\0changeBiasModeRequest\0index\0"
    "initAxisRequest\0OffsetPosChanged\0"
    "posOffPtr\0PresetPosChanged\0PresPosPtr\0"
    "configureCEChardwareRequest\0ceVelMin\0"
    "ceVelMax\0stopCEChardwareRequest\0"
    "updateCECRatiosRequest\0CEratios*\0"
    "ceRatios\0flyscanErrorCode\0ret_code\0"
    "flyscanStatValues\0unsigned char*\0"
    "axisTab\0mean\0stdDev\0flyscanProcTerm\0"
    "ssiDataAvailable\0ssiVals\0optPwrVals\0"
    "ssiSquelchValues\0uint8_t\0KpKvValues\0"
    "uint16_t*\0coeff\0readGSEDataComplete\0"
    "gseData\0initSettingsFormRequest\0"
    "apdValues\0uint32_t*\0openFlyscanForm\0"
    "closeFlyscanForm\0reopenFlyscanForm\0"
    "on_m_settingsMenu_clicked\0QAction*\0"
    "reopenSettingsForm\0openSettingsForm\0"
    "closeSettingsForm\0openPresetPositionForm\0"
    "closePresetPositionForm\0"
    "reopenPresetPositionForm\0"
    "openPositionOffsetForm\0closePositionOffsetForm\0"
    "reopenPositionOffsetForm\0openCustomplotForm\0"
    "closeCustomplotForm\0reopenCustomplotForm\0"
    "refresh_screen\0on_OffsetPos_Changed\0"
    "OffPosPtr\0on_PresetPos_Changed\0"
    "on_pushButton_11_clicked\0"
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
    "refreshLEDsStatus\0initBoards\0"
    "on_leftBlockUnits_currentIndexChanged\0"
    "on_rightBlockUnits_currentIndexChanged\0"
    "updateLeftBlockValue\0selectLeftBlockValue\0"
    "updateRightBlockValue\0selectRightBlockValue\0"
    "updateCECRatios\0on_pushButton_8_clicked\0"
    "processCecAxisClickedEvent\0int*\0"
    "axisListIndex\0QCheckBox*\0cecAxisCheckBox\0"
    "cecAxisClickedThreadEvent\0"
    "on_resetButtonAllAxis_clicked\0"
    "on_ramDataFlyscanRequest_recieved\0"
    "freq\0size\0time\0nbr\0on_fifoFlyscanRequest_recieved\0"
    "on_comboBox_3_currentIndexChanged\0"
    "on_comboBox_4_currentIndexChanged\0"
    "on_comboBox_currentIndexChanged\0"
    "on_radioButton_clicked\0"
    "on_ceUnits_currentIndexChanged\0"
    "on_radioButton_2_clicked\0on_cecAxis1_clicked\0"
    "on_cecAxis2_clicked\0on_cecAxis3_clicked\0"
    "on_cecAxis4_clicked\0"
    "on_ceDisplayAxis_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      82,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      26,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  424,    2, 0x06 /* Public */,
       3,    3,  425,    2, 0x06 /* Public */,
       8,    0,  432,    2, 0x06 /* Public */,
       9,    0,  433,    2, 0x06 /* Public */,
      10,    0,  434,    2, 0x06 /* Public */,
      11,    0,  435,    2, 0x06 /* Public */,
      12,    0,  436,    2, 0x06 /* Public */,
      13,    0,  437,    2, 0x06 /* Public */,
      14,    1,  438,    2, 0x06 /* Public */,
      16,    1,  441,    2, 0x06 /* Public */,
      18,    1,  444,    2, 0x06 /* Public */,
      20,    0,  447,    2, 0x06 /* Public */,
      21,    1,  448,    2, 0x06 /* Public */,
      23,    1,  451,    2, 0x06 /* Public */,
      25,    3,  454,    2, 0x06 /* Public */,
      28,    1,  461,    2, 0x06 /* Public */,
      29,    3,  464,    2, 0x06 /* Public */,
      32,    1,  471,    2, 0x06 /* Public */,
      34,    3,  474,    2, 0x06 /* Public */,
      39,    0,  481,    2, 0x06 /* Public */,
      40,    3,  482,    2, 0x06 /* Public */,
      43,    2,  489,    2, 0x06 /* Public */,
      45,    2,  494,    2, 0x06 /* Public */,
      48,    1,  499,    2, 0x06 /* Public */,
      50,    0,  502,    2, 0x06 /* Public */,
      51,    2,  503,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      53,    0,  508,    2, 0x0a /* Public */,
      54,    0,  509,    2, 0x0a /* Public */,
      55,    0,  510,    2, 0x0a /* Public */,
      56,    1,  511,    2, 0x0a /* Public */,
      58,    0,  514,    2, 0x0a /* Public */,
      59,    0,  515,    2, 0x0a /* Public */,
      60,    0,  516,    2, 0x0a /* Public */,
      61,    0,  517,    2, 0x0a /* Public */,
      62,    0,  518,    2, 0x0a /* Public */,
      63,    0,  519,    2, 0x0a /* Public */,
      64,    0,  520,    2, 0x0a /* Public */,
      65,    0,  521,    2, 0x0a /* Public */,
      66,    0,  522,    2, 0x0a /* Public */,
      67,    0,  523,    2, 0x0a /* Public */,
      68,    0,  524,    2, 0x0a /* Public */,
      69,    0,  525,    2, 0x0a /* Public */,
      70,    0,  526,    2, 0x0a /* Public */,
      71,    1,  527,    2, 0x08 /* Private */,
      73,    1,  530,    2, 0x08 /* Private */,
      74,    0,  533,    2, 0x08 /* Private */,
      75,    0,  534,    2, 0x08 /* Private */,
      76,    0,  535,    2, 0x08 /* Private */,
      77,    0,  536,    2, 0x08 /* Private */,
      78,    0,  537,    2, 0x08 /* Private */,
      79,    0,  538,    2, 0x08 /* Private */,
      80,    0,  539,    2, 0x08 /* Private */,
      81,    0,  540,    2, 0x08 /* Private */,
      82,    0,  541,    2, 0x08 /* Private */,
      83,    0,  542,    2, 0x08 /* Private */,
      84,    0,  543,    2, 0x08 /* Private */,
      85,    0,  544,    2, 0x08 /* Private */,
      86,    0,  545,    2, 0x08 /* Private */,
      87,    1,  546,    2, 0x08 /* Private */,
      88,    1,  549,    2, 0x08 /* Private */,
      89,    0,  552,    2, 0x08 /* Private */,
      90,    1,  553,    2, 0x08 /* Private */,
      91,    0,  556,    2, 0x08 /* Private */,
      92,    1,  557,    2, 0x08 /* Private */,
      93,    0,  560,    2, 0x08 /* Private */,
      94,    0,  561,    2, 0x08 /* Private */,
      95,    3,  562,    2, 0x08 /* Private */,
     100,    3,  569,    2, 0x08 /* Private */,
     101,    0,  576,    2, 0x08 /* Private */,
     102,    4,  577,    2, 0x08 /* Private */,
     107,    4,  586,    2, 0x08 /* Private */,
     108,    1,  595,    2, 0x08 /* Private */,
     109,    1,  598,    2, 0x08 /* Private */,
     110,    1,  601,    2, 0x08 /* Private */,
     111,    0,  604,    2, 0x08 /* Private */,
     112,    1,  605,    2, 0x08 /* Private */,
     113,    0,  608,    2, 0x08 /* Private */,
     114,    0,  609,    2, 0x08 /* Private */,
     115,    0,  610,    2, 0x08 /* Private */,
     116,    0,  611,    2, 0x08 /* Private */,
     117,    0,  612,    2, 0x08 /* Private */,
     118,    1,  613,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,   22,
    QMetaType::Void, 0x80000000 | 6,   24,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   17,   26,   27,
    QMetaType::Void, QMetaType::UInt,   17,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 30, QMetaType::UInt,   17,   31,   19,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, 0x80000000 | 35, 0x80000000 | 6, 0x80000000 | 6,   36,   37,   38,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 6, 0x80000000 | 6,   17,   41,   42,
    QMetaType::Void, 0x80000000 | 44, 0x80000000 | 6,   17,    7,
    QMetaType::Void, 0x80000000 | 44, 0x80000000 | 46,   17,   47,
    QMetaType::Void, 0x80000000 | 6,   49,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 44, 0x80000000 | 52,   17,   47,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 57,    2,
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
    QMetaType::Void, 0x80000000 | 6,   72,
    QMetaType::Void, 0x80000000 | 6,   24,
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
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 96, 0x80000000 | 98,   17,   97,   99,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 96, 0x80000000 | 98,   17,   97,   99,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,  103,  104,  105,  106,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,  103,  104,  105,  106,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initComplete(); break;
        case 1: _t->updateSettingsRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 2: _t->closeFlyscanFormRequest(); break;
        case 3: _t->closePositionOffsetFormRequest(); break;
        case 4: _t->closePresetPositionFormRequest(); break;
        case 5: _t->closeSettingsFormRequest(); break;
        case 6: _t->closeCustomplotFormRequest(); break;
        case 7: _t->initBoardsRequest(); break;
        case 8: _t->scaleAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->resetAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->changeBiasModeRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->initAxisRequest(); break;
        case 12: _t->OffsetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 13: _t->PresetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 14: _t->configureCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 15: _t->stopCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 16: _t->updateCECRatiosRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< CEratios*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 17: _t->flyscanErrorCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->flyscanStatValues((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 19: _t->flyscanProcTerm(); break;
        case 20: _t->ssiDataAvailable((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 21: _t->ssiSquelchValues((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2]))); break;
        case 22: _t->KpKvValues((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint16_t*(*)>(_a[2]))); break;
        case 23: _t->readGSEDataComplete((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 24: _t->initSettingsFormRequest(); break;
        case 25: _t->apdValues((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint32_t*(*)>(_a[2]))); break;
        case 26: _t->openFlyscanForm(); break;
        case 27: _t->closeFlyscanForm(); break;
        case 28: _t->reopenFlyscanForm(); break;
        case 29: _t->on_m_settingsMenu_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 30: _t->reopenSettingsForm(); break;
        case 31: _t->openSettingsForm(); break;
        case 32: _t->closeSettingsForm(); break;
        case 33: _t->openPresetPositionForm(); break;
        case 34: _t->closePresetPositionForm(); break;
        case 35: _t->reopenPresetPositionForm(); break;
        case 36: _t->openPositionOffsetForm(); break;
        case 37: _t->closePositionOffsetForm(); break;
        case 38: _t->reopenPositionOffsetForm(); break;
        case 39: _t->openCustomplotForm(); break;
        case 40: _t->closeCustomplotForm(); break;
        case 41: _t->reopenCustomplotForm(); break;
        case 42: _t->refresh_screen(); break;
        case 43: _t->on_OffsetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 44: _t->on_PresetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 45: _t->on_pushButton_11_clicked(); break;
        case 46: _t->on_pushButton_13_clicked(); break;
        case 47: _t->on_pushButton_12_clicked(); break;
        case 48: _t->on_toolButton_2_clicked(); break;
        case 49: _t->on_initAxisComplete_recieved(); break;
        case 50: _t->on_pushButton_7_clicked(); break;
        case 51: _t->on_resetButtonAxis1_clicked(); break;
        case 52: _t->on_resetButtonAxis2_clicked(); break;
        case 53: _t->on_resetButtonAxis3_clicked(); break;
        case 54: _t->on_resetButtonAxis4_clicked(); break;
        case 55: _t->onBoardsInitializationComplete(); break;
        case 56: _t->refreshLEDsStatus(); break;
        case 57: _t->initBoards(); break;
        case 58: _t->on_leftBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 59: _t->on_rightBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 60: _t->updateLeftBlockValue(); break;
        case 61: _t->selectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 62: _t->updateRightBlockValue(); break;
        case 63: _t->selectRightBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 64: _t->updateCECRatios(); break;
        case 65: _t->on_pushButton_8_clicked(); break;
        case 66: _t->processCecAxisClickedEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 67: _t->cecAxisClickedThreadEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 68: _t->on_resetButtonAllAxis_clicked(); break;
        case 69: _t->on_ramDataFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 70: _t->on_fifoFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 71: _t->on_comboBox_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 72: _t->on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 73: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 74: _t->on_radioButton_clicked(); break;
        case 75: _t->on_ceUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->on_radioButton_2_clicked(); break;
        case 77: _t->on_cecAxis1_clicked(); break;
        case 78: _t->on_cecAxis2_clicked(); break;
        case 79: _t->on_cecAxis3_clicked(); break;
        case 80: _t->on_cecAxis4_clicked(); break;
        case 81: _t->on_ceDisplayAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 29:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 66:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        case 67:
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
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initComplete)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , int , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateSettingsRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeFlyscanFormRequest)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePositionOffsetFormRequest)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePresetPositionFormRequest)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeSettingsFormRequest)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeCustomplotFormRequest)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initBoardsRequest)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::scaleAxisRequest)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::resetAxisRequest)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::changeBiasModeRequest)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initAxisRequest)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::OffsetPosChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::PresetPosChanged)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::configureCEChardwareRequest)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopCEChardwareRequest)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , CEratios * , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateCECRatiosRequest)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanErrorCode)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned char * , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanStatValues)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanProcTerm)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::ssiDataAvailable)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(uint8_t , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::ssiSquelchValues)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(uint8_t , uint16_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::KpKvValues)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::readGSEDataComplete)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initSettingsFormRequest)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(uint8_t , uint32_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::apdValues)) {
                *result = 25;
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
        if (_id < 82)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 82;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 82)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 82;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::initComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::updateSettingsRequest(int _t1, int _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::closeFlyscanFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::closePositionOffsetFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::closePresetPositionFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::closeSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::closeCustomplotFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::initBoardsRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MainWindow::scaleAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::resetAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::changeBiasModeRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void MainWindow::initAxisRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void MainWindow::OffsetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::PresetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MainWindow::configureCEChardwareRequest(unsigned int _t1, unsigned int _t2, unsigned int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::stopCEChardwareRequest(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::updateCECRatiosRequest(unsigned int _t1, CEratios * _t2, unsigned int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::flyscanErrorCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::flyscanStatValues(unsigned char * _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void MainWindow::flyscanProcTerm()
{
    QMetaObject::activate(this, &staticMetaObject, 19, nullptr);
}

// SIGNAL 20
void MainWindow::ssiDataAvailable(unsigned int _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void MainWindow::ssiSquelchValues(uint8_t _t1, double * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void MainWindow::KpKvValues(uint8_t _t1, uint16_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void MainWindow::readGSEDataComplete(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 23, _a);
}

// SIGNAL 24
void MainWindow::initSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 24, nullptr);
}

// SIGNAL 25
void MainWindow::apdValues(uint8_t _t1, uint32_t * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
