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
    QByteArrayData data[106];
    char stringdata0[2016];
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
QT_MOC_LITERAL(6, 51, 3), // "val"
QT_MOC_LITERAL(7, 55, 23), // "closeFlyscanFormRequest"
QT_MOC_LITERAL(8, 79, 30), // "closePositionOffsetFormRequest"
QT_MOC_LITERAL(9, 110, 30), // "closePresetPositionFormRequest"
QT_MOC_LITERAL(10, 141, 24), // "closeSettingsFormRequest"
QT_MOC_LITERAL(11, 166, 26), // "closeCustomplotFormRequest"
QT_MOC_LITERAL(12, 193, 17), // "initBoardsRequest"
QT_MOC_LITERAL(13, 211, 16), // "scaleAxisRequest"
QT_MOC_LITERAL(14, 228, 5), // "units"
QT_MOC_LITERAL(15, 234, 16), // "resetAxisRequest"
QT_MOC_LITERAL(16, 251, 4), // "axis"
QT_MOC_LITERAL(17, 256, 21), // "changeBiasModeRequest"
QT_MOC_LITERAL(18, 278, 5), // "index"
QT_MOC_LITERAL(19, 284, 15), // "initAxisRequest"
QT_MOC_LITERAL(20, 300, 16), // "OffsetPosChanged"
QT_MOC_LITERAL(21, 317, 7), // "double*"
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
QT_MOC_LITERAL(40, 569, 15), // "openFlyscanForm"
QT_MOC_LITERAL(41, 585, 16), // "closeFlyscanForm"
QT_MOC_LITERAL(42, 602, 17), // "reopenFlyscanForm"
QT_MOC_LITERAL(43, 620, 25), // "on_m_settingsMenu_clicked"
QT_MOC_LITERAL(44, 646, 8), // "QAction*"
QT_MOC_LITERAL(45, 655, 18), // "reopenSettingsForm"
QT_MOC_LITERAL(46, 674, 16), // "openSettingsForm"
QT_MOC_LITERAL(47, 691, 17), // "closeSettingsForm"
QT_MOC_LITERAL(48, 709, 22), // "openPresetPositionForm"
QT_MOC_LITERAL(49, 732, 23), // "closePresetPositionForm"
QT_MOC_LITERAL(50, 756, 24), // "reopenPresetPositionForm"
QT_MOC_LITERAL(51, 781, 22), // "openPositionOffsetForm"
QT_MOC_LITERAL(52, 804, 23), // "closePositionOffsetForm"
QT_MOC_LITERAL(53, 828, 24), // "reopenPositionOffsetForm"
QT_MOC_LITERAL(54, 853, 18), // "openCustomplotForm"
QT_MOC_LITERAL(55, 872, 19), // "closeCustomplotForm"
QT_MOC_LITERAL(56, 892, 20), // "reopenCustomplotForm"
QT_MOC_LITERAL(57, 913, 14), // "refresh_screen"
QT_MOC_LITERAL(58, 928, 20), // "on_OffsetPos_Changed"
QT_MOC_LITERAL(59, 949, 9), // "OffPosPtr"
QT_MOC_LITERAL(60, 959, 20), // "on_PresetPos_Changed"
QT_MOC_LITERAL(61, 980, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(62, 1005, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(63, 1030, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(64, 1055, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(65, 1079, 28), // "on_initAxisComplete_recieved"
QT_MOC_LITERAL(66, 1108, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(67, 1132, 27), // "on_resetButtonAxis1_clicked"
QT_MOC_LITERAL(68, 1160, 27), // "on_resetButtonAxis2_clicked"
QT_MOC_LITERAL(69, 1188, 27), // "on_resetButtonAxis3_clicked"
QT_MOC_LITERAL(70, 1216, 27), // "on_resetButtonAxis4_clicked"
QT_MOC_LITERAL(71, 1244, 30), // "onBoardsInitializationComplete"
QT_MOC_LITERAL(72, 1275, 17), // "refreshLEDsStatus"
QT_MOC_LITERAL(73, 1293, 10), // "initBoards"
QT_MOC_LITERAL(74, 1304, 37), // "on_leftBlockUnits_currentInde..."
QT_MOC_LITERAL(75, 1342, 38), // "on_rightBlockUnits_currentInd..."
QT_MOC_LITERAL(76, 1381, 20), // "updateLeftBlockValue"
QT_MOC_LITERAL(77, 1402, 20), // "selectLeftBlockValue"
QT_MOC_LITERAL(78, 1423, 21), // "updateRightBlockValue"
QT_MOC_LITERAL(79, 1445, 21), // "selectRightBlockValue"
QT_MOC_LITERAL(80, 1467, 15), // "updateCECRatios"
QT_MOC_LITERAL(81, 1483, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(82, 1507, 26), // "processCecAxisClickedEvent"
QT_MOC_LITERAL(83, 1534, 4), // "int*"
QT_MOC_LITERAL(84, 1539, 13), // "axisListIndex"
QT_MOC_LITERAL(85, 1553, 10), // "QCheckBox*"
QT_MOC_LITERAL(86, 1564, 15), // "cecAxisCheckBox"
QT_MOC_LITERAL(87, 1580, 25), // "cecAxisClickedThreadEvent"
QT_MOC_LITERAL(88, 1606, 29), // "on_resetButtonAllAxis_clicked"
QT_MOC_LITERAL(89, 1636, 33), // "on_ramDataFlyscanRequest_reci..."
QT_MOC_LITERAL(90, 1670, 4), // "freq"
QT_MOC_LITERAL(91, 1675, 4), // "size"
QT_MOC_LITERAL(92, 1680, 4), // "time"
QT_MOC_LITERAL(93, 1685, 3), // "nbr"
QT_MOC_LITERAL(94, 1689, 30), // "on_fifoFlyscanRequest_recieved"
QT_MOC_LITERAL(95, 1720, 33), // "on_comboBox_3_currentIndexCha..."
QT_MOC_LITERAL(96, 1754, 33), // "on_comboBox_4_currentIndexCha..."
QT_MOC_LITERAL(97, 1788, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(98, 1820, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(99, 1843, 30), // "on_ceUnits_currentIndexChanged"
QT_MOC_LITERAL(100, 1874, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(101, 1899, 19), // "on_cecAxis1_clicked"
QT_MOC_LITERAL(102, 1919, 19), // "on_cecAxis2_clicked"
QT_MOC_LITERAL(103, 1939, 19), // "on_cecAxis3_clicked"
QT_MOC_LITERAL(104, 1959, 19), // "on_cecAxis4_clicked"
QT_MOC_LITERAL(105, 1979, 36) // "on_ceDisplayAxis_currentIndex..."

    },
    "MainWindow\0initComplete\0\0updateSettingsRequest\0"
    "a\0b\0val\0closeFlyscanFormRequest\0"
    "closePositionOffsetFormRequest\0"
    "closePresetPositionFormRequest\0"
    "closeSettingsFormRequest\0"
    "closeCustomplotFormRequest\0initBoardsRequest\0"
    "scaleAxisRequest\0units\0resetAxisRequest\0"
    "axis\0changeBiasModeRequest\0index\0"
    "initAxisRequest\0OffsetPosChanged\0"
    "double*\0posOffPtr\0PresetPosChanged\0"
    "PresPosPtr\0configureCEChardwareRequest\0"
    "ceVelMin\0ceVelMax\0stopCEChardwareRequest\0"
    "updateCECRatiosRequest\0CEratios*\0"
    "ceRatios\0flyscanErrorCode\0ret_code\0"
    "flyscanStatValues\0unsigned char*\0"
    "axisTab\0mean\0stdDev\0flyscanProcTerm\0"
    "openFlyscanForm\0closeFlyscanForm\0"
    "reopenFlyscanForm\0on_m_settingsMenu_clicked\0"
    "QAction*\0reopenSettingsForm\0"
    "openSettingsForm\0closeSettingsForm\0"
    "openPresetPositionForm\0closePresetPositionForm\0"
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
      76,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      20,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  394,    2, 0x06 /* Public */,
       3,    3,  395,    2, 0x06 /* Public */,
       7,    0,  402,    2, 0x06 /* Public */,
       8,    0,  403,    2, 0x06 /* Public */,
       9,    0,  404,    2, 0x06 /* Public */,
      10,    0,  405,    2, 0x06 /* Public */,
      11,    0,  406,    2, 0x06 /* Public */,
      12,    0,  407,    2, 0x06 /* Public */,
      13,    1,  408,    2, 0x06 /* Public */,
      15,    1,  411,    2, 0x06 /* Public */,
      17,    1,  414,    2, 0x06 /* Public */,
      19,    0,  417,    2, 0x06 /* Public */,
      20,    1,  418,    2, 0x06 /* Public */,
      23,    1,  421,    2, 0x06 /* Public */,
      25,    3,  424,    2, 0x06 /* Public */,
      28,    1,  431,    2, 0x06 /* Public */,
      29,    3,  434,    2, 0x06 /* Public */,
      32,    1,  441,    2, 0x06 /* Public */,
      34,    3,  444,    2, 0x06 /* Public */,
      39,    0,  451,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      40,    0,  452,    2, 0x0a /* Public */,
      41,    0,  453,    2, 0x0a /* Public */,
      42,    0,  454,    2, 0x0a /* Public */,
      43,    1,  455,    2, 0x0a /* Public */,
      45,    0,  458,    2, 0x0a /* Public */,
      46,    0,  459,    2, 0x0a /* Public */,
      47,    0,  460,    2, 0x0a /* Public */,
      48,    0,  461,    2, 0x0a /* Public */,
      49,    0,  462,    2, 0x0a /* Public */,
      50,    0,  463,    2, 0x0a /* Public */,
      51,    0,  464,    2, 0x0a /* Public */,
      52,    0,  465,    2, 0x0a /* Public */,
      53,    0,  466,    2, 0x0a /* Public */,
      54,    0,  467,    2, 0x0a /* Public */,
      55,    0,  468,    2, 0x0a /* Public */,
      56,    0,  469,    2, 0x0a /* Public */,
      57,    0,  470,    2, 0x0a /* Public */,
      58,    1,  471,    2, 0x08 /* Private */,
      60,    1,  474,    2, 0x08 /* Private */,
      61,    0,  477,    2, 0x08 /* Private */,
      62,    0,  478,    2, 0x08 /* Private */,
      63,    0,  479,    2, 0x08 /* Private */,
      64,    0,  480,    2, 0x08 /* Private */,
      65,    0,  481,    2, 0x08 /* Private */,
      66,    0,  482,    2, 0x08 /* Private */,
      67,    0,  483,    2, 0x08 /* Private */,
      68,    0,  484,    2, 0x08 /* Private */,
      69,    0,  485,    2, 0x08 /* Private */,
      70,    0,  486,    2, 0x08 /* Private */,
      71,    0,  487,    2, 0x08 /* Private */,
      72,    0,  488,    2, 0x08 /* Private */,
      73,    0,  489,    2, 0x08 /* Private */,
      74,    1,  490,    2, 0x08 /* Private */,
      75,    1,  493,    2, 0x08 /* Private */,
      76,    0,  496,    2, 0x08 /* Private */,
      77,    1,  497,    2, 0x08 /* Private */,
      78,    0,  500,    2, 0x08 /* Private */,
      79,    1,  501,    2, 0x08 /* Private */,
      80,    0,  504,    2, 0x08 /* Private */,
      81,    0,  505,    2, 0x08 /* Private */,
      82,    3,  506,    2, 0x08 /* Private */,
      87,    3,  513,    2, 0x08 /* Private */,
      88,    0,  520,    2, 0x08 /* Private */,
      89,    4,  521,    2, 0x08 /* Private */,
      94,    4,  530,    2, 0x08 /* Private */,
      95,    1,  539,    2, 0x08 /* Private */,
      96,    1,  542,    2, 0x08 /* Private */,
      97,    1,  545,    2, 0x08 /* Private */,
      98,    0,  548,    2, 0x08 /* Private */,
      99,    1,  549,    2, 0x08 /* Private */,
     100,    0,  552,    2, 0x08 /* Private */,
     101,    0,  553,    2, 0x08 /* Private */,
     102,    0,  554,    2, 0x08 /* Private */,
     103,    0,  555,    2, 0x08 /* Private */,
     104,    0,  556,    2, 0x08 /* Private */,
     105,    1,  557,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    4,    5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 21,   24,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   16,   26,   27,
    QMetaType::Void, QMetaType::UInt,   16,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 30, QMetaType::UInt,   16,   31,   18,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, 0x80000000 | 35, 0x80000000 | 21, 0x80000000 | 21,   36,   37,   38,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 44,    2,
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
    QMetaType::Void, 0x80000000 | 21,   59,
    QMetaType::Void, 0x80000000 | 21,   24,
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
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 83, 0x80000000 | 85,   16,   84,   86,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 83, 0x80000000 | 85,   16,   84,   86,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,   90,   91,   92,   93,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,   90,   91,   92,   93,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initComplete(); break;
        case 1: _t->updateSettingsRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
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
        case 20: _t->openFlyscanForm(); break;
        case 21: _t->closeFlyscanForm(); break;
        case 22: _t->reopenFlyscanForm(); break;
        case 23: _t->on_m_settingsMenu_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 24: _t->reopenSettingsForm(); break;
        case 25: _t->openSettingsForm(); break;
        case 26: _t->closeSettingsForm(); break;
        case 27: _t->openPresetPositionForm(); break;
        case 28: _t->closePresetPositionForm(); break;
        case 29: _t->reopenPresetPositionForm(); break;
        case 30: _t->openPositionOffsetForm(); break;
        case 31: _t->closePositionOffsetForm(); break;
        case 32: _t->reopenPositionOffsetForm(); break;
        case 33: _t->openCustomplotForm(); break;
        case 34: _t->closeCustomplotForm(); break;
        case 35: _t->reopenCustomplotForm(); break;
        case 36: _t->refresh_screen(); break;
        case 37: _t->on_OffsetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 38: _t->on_PresetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 39: _t->on_pushButton_11_clicked(); break;
        case 40: _t->on_pushButton_13_clicked(); break;
        case 41: _t->on_pushButton_12_clicked(); break;
        case 42: _t->on_toolButton_2_clicked(); break;
        case 43: _t->on_initAxisComplete_recieved(); break;
        case 44: _t->on_pushButton_7_clicked(); break;
        case 45: _t->on_resetButtonAxis1_clicked(); break;
        case 46: _t->on_resetButtonAxis2_clicked(); break;
        case 47: _t->on_resetButtonAxis3_clicked(); break;
        case 48: _t->on_resetButtonAxis4_clicked(); break;
        case 49: _t->onBoardsInitializationComplete(); break;
        case 50: _t->refreshLEDsStatus(); break;
        case 51: _t->initBoards(); break;
        case 52: _t->on_leftBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->on_rightBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->updateLeftBlockValue(); break;
        case 55: _t->selectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->updateRightBlockValue(); break;
        case 57: _t->selectRightBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 58: _t->updateCECRatios(); break;
        case 59: _t->on_pushButton_8_clicked(); break;
        case 60: _t->processCecAxisClickedEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 61: _t->cecAxisClickedThreadEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 62: _t->on_resetButtonAllAxis_clicked(); break;
        case 63: _t->on_ramDataFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 64: _t->on_fifoFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 65: _t->on_comboBox_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 66: _t->on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 68: _t->on_radioButton_clicked(); break;
        case 69: _t->on_ceUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 70: _t->on_radioButton_2_clicked(); break;
        case 71: _t->on_cecAxis1_clicked(); break;
        case 72: _t->on_cecAxis2_clicked(); break;
        case 73: _t->on_cecAxis3_clicked(); break;
        case 74: _t->on_cecAxis4_clicked(); break;
        case 75: _t->on_ceDisplayAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 60:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        case 61:
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
            using _t = void (MainWindow::*)(int , int , int );
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
        if (_id < 76)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 76;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 76)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 76;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::initComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::updateSettingsRequest(int _t1, int _t2, int _t3)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
