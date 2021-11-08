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
    QByteArrayData data[102];
    char stringdata0[1986];
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
QT_MOC_LITERAL(3, 25, 23), // "closeFlyscanFormRequest"
QT_MOC_LITERAL(4, 49, 30), // "closePositionOffsetFormRequest"
QT_MOC_LITERAL(5, 80, 30), // "closePresetPositionFormRequest"
QT_MOC_LITERAL(6, 111, 24), // "closeSettingsFormRequest"
QT_MOC_LITERAL(7, 136, 26), // "closeCustomplotFormRequest"
QT_MOC_LITERAL(8, 163, 17), // "initBoardsRequest"
QT_MOC_LITERAL(9, 181, 16), // "scaleAxisRequest"
QT_MOC_LITERAL(10, 198, 5), // "units"
QT_MOC_LITERAL(11, 204, 16), // "resetAxisRequest"
QT_MOC_LITERAL(12, 221, 4), // "axis"
QT_MOC_LITERAL(13, 226, 21), // "changeBiasModeRequest"
QT_MOC_LITERAL(14, 248, 5), // "index"
QT_MOC_LITERAL(15, 254, 15), // "initAxisRequest"
QT_MOC_LITERAL(16, 270, 16), // "OffsetPosChanged"
QT_MOC_LITERAL(17, 287, 7), // "double*"
QT_MOC_LITERAL(18, 295, 9), // "posOffPtr"
QT_MOC_LITERAL(19, 305, 16), // "PresetPosChanged"
QT_MOC_LITERAL(20, 322, 10), // "PresPosPtr"
QT_MOC_LITERAL(21, 333, 27), // "configureCEChardwareRequest"
QT_MOC_LITERAL(22, 361, 8), // "ceVelMin"
QT_MOC_LITERAL(23, 370, 8), // "ceVelMax"
QT_MOC_LITERAL(24, 379, 22), // "stopCEChardwareRequest"
QT_MOC_LITERAL(25, 402, 22), // "updateCECRatiosRequest"
QT_MOC_LITERAL(26, 425, 9), // "CEratios*"
QT_MOC_LITERAL(27, 435, 8), // "ceRatios"
QT_MOC_LITERAL(28, 444, 16), // "flyscanErrorCode"
QT_MOC_LITERAL(29, 461, 8), // "ret_code"
QT_MOC_LITERAL(30, 470, 17), // "flyscanStatValues"
QT_MOC_LITERAL(31, 488, 14), // "unsigned char*"
QT_MOC_LITERAL(32, 503, 7), // "axisTab"
QT_MOC_LITERAL(33, 511, 4), // "mean"
QT_MOC_LITERAL(34, 516, 6), // "stdDev"
QT_MOC_LITERAL(35, 523, 15), // "flyscanProcTerm"
QT_MOC_LITERAL(36, 539, 15), // "openFlyscanForm"
QT_MOC_LITERAL(37, 555, 16), // "closeFlyscanForm"
QT_MOC_LITERAL(38, 572, 17), // "reopenFlyscanForm"
QT_MOC_LITERAL(39, 590, 25), // "on_m_settingsMenu_clicked"
QT_MOC_LITERAL(40, 616, 8), // "QAction*"
QT_MOC_LITERAL(41, 625, 18), // "reopenSettingsForm"
QT_MOC_LITERAL(42, 644, 16), // "openSettingsForm"
QT_MOC_LITERAL(43, 661, 17), // "closeSettingsForm"
QT_MOC_LITERAL(44, 679, 22), // "openPresetPositionForm"
QT_MOC_LITERAL(45, 702, 23), // "closePresetPositionForm"
QT_MOC_LITERAL(46, 726, 24), // "reopenPresetPositionForm"
QT_MOC_LITERAL(47, 751, 22), // "openPositionOffsetForm"
QT_MOC_LITERAL(48, 774, 23), // "closePositionOffsetForm"
QT_MOC_LITERAL(49, 798, 24), // "reopenPositionOffsetForm"
QT_MOC_LITERAL(50, 823, 18), // "openCustomplotForm"
QT_MOC_LITERAL(51, 842, 19), // "closeCustomplotForm"
QT_MOC_LITERAL(52, 862, 20), // "reopenCustomplotForm"
QT_MOC_LITERAL(53, 883, 14), // "refresh_screen"
QT_MOC_LITERAL(54, 898, 20), // "on_OffsetPos_Changed"
QT_MOC_LITERAL(55, 919, 9), // "OffPosPtr"
QT_MOC_LITERAL(56, 929, 20), // "on_PresetPos_Changed"
QT_MOC_LITERAL(57, 950, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(58, 975, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(59, 1000, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(60, 1025, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(61, 1049, 28), // "on_initAxisComplete_recieved"
QT_MOC_LITERAL(62, 1078, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(63, 1102, 27), // "on_resetButtonAxis1_clicked"
QT_MOC_LITERAL(64, 1130, 27), // "on_resetButtonAxis2_clicked"
QT_MOC_LITERAL(65, 1158, 27), // "on_resetButtonAxis3_clicked"
QT_MOC_LITERAL(66, 1186, 27), // "on_resetButtonAxis4_clicked"
QT_MOC_LITERAL(67, 1214, 30), // "onBoardsInitializationComplete"
QT_MOC_LITERAL(68, 1245, 17), // "refreshLEDsStatus"
QT_MOC_LITERAL(69, 1263, 10), // "initBoards"
QT_MOC_LITERAL(70, 1274, 37), // "on_leftBlockUnits_currentInde..."
QT_MOC_LITERAL(71, 1312, 38), // "on_rightBlockUnits_currentInd..."
QT_MOC_LITERAL(72, 1351, 20), // "updateLeftBlockValue"
QT_MOC_LITERAL(73, 1372, 20), // "selectLeftBlockValue"
QT_MOC_LITERAL(74, 1393, 21), // "updateRightBlockValue"
QT_MOC_LITERAL(75, 1415, 21), // "selectRightBlockValue"
QT_MOC_LITERAL(76, 1437, 15), // "updateCECRatios"
QT_MOC_LITERAL(77, 1453, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(78, 1477, 26), // "processCecAxisClickedEvent"
QT_MOC_LITERAL(79, 1504, 4), // "int*"
QT_MOC_LITERAL(80, 1509, 13), // "axisListIndex"
QT_MOC_LITERAL(81, 1523, 10), // "QCheckBox*"
QT_MOC_LITERAL(82, 1534, 15), // "cecAxisCheckBox"
QT_MOC_LITERAL(83, 1550, 25), // "cecAxisClickedThreadEvent"
QT_MOC_LITERAL(84, 1576, 29), // "on_resetButtonAllAxis_clicked"
QT_MOC_LITERAL(85, 1606, 33), // "on_ramDataFlyscanRequest_reci..."
QT_MOC_LITERAL(86, 1640, 4), // "freq"
QT_MOC_LITERAL(87, 1645, 4), // "size"
QT_MOC_LITERAL(88, 1650, 4), // "time"
QT_MOC_LITERAL(89, 1655, 3), // "nbr"
QT_MOC_LITERAL(90, 1659, 30), // "on_fifoFlyscanRequest_recieved"
QT_MOC_LITERAL(91, 1690, 33), // "on_comboBox_3_currentIndexCha..."
QT_MOC_LITERAL(92, 1724, 33), // "on_comboBox_4_currentIndexCha..."
QT_MOC_LITERAL(93, 1758, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(94, 1790, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(95, 1813, 30), // "on_ceUnits_currentIndexChanged"
QT_MOC_LITERAL(96, 1844, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(97, 1869, 19), // "on_cecAxis1_clicked"
QT_MOC_LITERAL(98, 1889, 19), // "on_cecAxis2_clicked"
QT_MOC_LITERAL(99, 1909, 19), // "on_cecAxis3_clicked"
QT_MOC_LITERAL(100, 1929, 19), // "on_cecAxis4_clicked"
QT_MOC_LITERAL(101, 1949, 36) // "on_ceDisplayAxis_currentIndex..."

    },
    "MainWindow\0initComplete\0\0"
    "closeFlyscanFormRequest\0"
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
      75,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      19,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  389,    2, 0x06 /* Public */,
       3,    0,  390,    2, 0x06 /* Public */,
       4,    0,  391,    2, 0x06 /* Public */,
       5,    0,  392,    2, 0x06 /* Public */,
       6,    0,  393,    2, 0x06 /* Public */,
       7,    0,  394,    2, 0x06 /* Public */,
       8,    0,  395,    2, 0x06 /* Public */,
       9,    1,  396,    2, 0x06 /* Public */,
      11,    1,  399,    2, 0x06 /* Public */,
      13,    1,  402,    2, 0x06 /* Public */,
      15,    0,  405,    2, 0x06 /* Public */,
      16,    1,  406,    2, 0x06 /* Public */,
      19,    1,  409,    2, 0x06 /* Public */,
      21,    3,  412,    2, 0x06 /* Public */,
      24,    1,  419,    2, 0x06 /* Public */,
      25,    3,  422,    2, 0x06 /* Public */,
      28,    1,  429,    2, 0x06 /* Public */,
      30,    3,  432,    2, 0x06 /* Public */,
      35,    0,  439,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      36,    0,  440,    2, 0x0a /* Public */,
      37,    0,  441,    2, 0x0a /* Public */,
      38,    0,  442,    2, 0x0a /* Public */,
      39,    1,  443,    2, 0x0a /* Public */,
      41,    0,  446,    2, 0x0a /* Public */,
      42,    0,  447,    2, 0x0a /* Public */,
      43,    0,  448,    2, 0x0a /* Public */,
      44,    0,  449,    2, 0x0a /* Public */,
      45,    0,  450,    2, 0x0a /* Public */,
      46,    0,  451,    2, 0x0a /* Public */,
      47,    0,  452,    2, 0x0a /* Public */,
      48,    0,  453,    2, 0x0a /* Public */,
      49,    0,  454,    2, 0x0a /* Public */,
      50,    0,  455,    2, 0x0a /* Public */,
      51,    0,  456,    2, 0x0a /* Public */,
      52,    0,  457,    2, 0x0a /* Public */,
      53,    0,  458,    2, 0x0a /* Public */,
      54,    1,  459,    2, 0x08 /* Private */,
      56,    1,  462,    2, 0x08 /* Private */,
      57,    0,  465,    2, 0x08 /* Private */,
      58,    0,  466,    2, 0x08 /* Private */,
      59,    0,  467,    2, 0x08 /* Private */,
      60,    0,  468,    2, 0x08 /* Private */,
      61,    0,  469,    2, 0x08 /* Private */,
      62,    0,  470,    2, 0x08 /* Private */,
      63,    0,  471,    2, 0x08 /* Private */,
      64,    0,  472,    2, 0x08 /* Private */,
      65,    0,  473,    2, 0x08 /* Private */,
      66,    0,  474,    2, 0x08 /* Private */,
      67,    0,  475,    2, 0x08 /* Private */,
      68,    0,  476,    2, 0x08 /* Private */,
      69,    0,  477,    2, 0x08 /* Private */,
      70,    1,  478,    2, 0x08 /* Private */,
      71,    1,  481,    2, 0x08 /* Private */,
      72,    0,  484,    2, 0x08 /* Private */,
      73,    1,  485,    2, 0x08 /* Private */,
      74,    0,  488,    2, 0x08 /* Private */,
      75,    1,  489,    2, 0x08 /* Private */,
      76,    0,  492,    2, 0x08 /* Private */,
      77,    0,  493,    2, 0x08 /* Private */,
      78,    3,  494,    2, 0x08 /* Private */,
      83,    3,  501,    2, 0x08 /* Private */,
      84,    0,  508,    2, 0x08 /* Private */,
      85,    4,  509,    2, 0x08 /* Private */,
      90,    4,  518,    2, 0x08 /* Private */,
      91,    1,  527,    2, 0x08 /* Private */,
      92,    1,  530,    2, 0x08 /* Private */,
      93,    1,  533,    2, 0x08 /* Private */,
      94,    0,  536,    2, 0x08 /* Private */,
      95,    1,  537,    2, 0x08 /* Private */,
      96,    0,  540,    2, 0x08 /* Private */,
      97,    0,  541,    2, 0x08 /* Private */,
      98,    0,  542,    2, 0x08 /* Private */,
      99,    0,  543,    2, 0x08 /* Private */,
     100,    0,  544,    2, 0x08 /* Private */,
     101,    1,  545,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 17,   20,
    QMetaType::Void, QMetaType::UInt, QMetaType::UInt, QMetaType::UInt,   12,   22,   23,
    QMetaType::Void, QMetaType::UInt,   12,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 26, QMetaType::UInt,   12,   27,   14,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, 0x80000000 | 31, 0x80000000 | 17, 0x80000000 | 17,   32,   33,   34,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 40,    2,
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
    QMetaType::Void, 0x80000000 | 17,   55,
    QMetaType::Void, 0x80000000 | 17,   20,
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
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 79, 0x80000000 | 81,   12,   80,   82,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 79, 0x80000000 | 81,   12,   80,   82,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,   86,   87,   88,   89,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,   86,   87,   88,   89,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initComplete(); break;
        case 1: _t->closeFlyscanFormRequest(); break;
        case 2: _t->closePositionOffsetFormRequest(); break;
        case 3: _t->closePresetPositionFormRequest(); break;
        case 4: _t->closeSettingsFormRequest(); break;
        case 5: _t->closeCustomplotFormRequest(); break;
        case 6: _t->initBoardsRequest(); break;
        case 7: _t->scaleAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->resetAxisRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->changeBiasModeRequest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->initAxisRequest(); break;
        case 11: _t->OffsetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 12: _t->PresetPosChanged((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 13: _t->configureCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 14: _t->stopCEChardwareRequest((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 15: _t->updateCECRatiosRequest((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< CEratios*(*)>(_a[2])),(*reinterpret_cast< uint(*)>(_a[3]))); break;
        case 16: _t->flyscanErrorCode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->flyscanStatValues((*reinterpret_cast< unsigned char*(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 18: _t->flyscanProcTerm(); break;
        case 19: _t->openFlyscanForm(); break;
        case 20: _t->closeFlyscanForm(); break;
        case 21: _t->reopenFlyscanForm(); break;
        case 22: _t->on_m_settingsMenu_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 23: _t->reopenSettingsForm(); break;
        case 24: _t->openSettingsForm(); break;
        case 25: _t->closeSettingsForm(); break;
        case 26: _t->openPresetPositionForm(); break;
        case 27: _t->closePresetPositionForm(); break;
        case 28: _t->reopenPresetPositionForm(); break;
        case 29: _t->openPositionOffsetForm(); break;
        case 30: _t->closePositionOffsetForm(); break;
        case 31: _t->reopenPositionOffsetForm(); break;
        case 32: _t->openCustomplotForm(); break;
        case 33: _t->closeCustomplotForm(); break;
        case 34: _t->reopenCustomplotForm(); break;
        case 35: _t->refresh_screen(); break;
        case 36: _t->on_OffsetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 37: _t->on_PresetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 38: _t->on_pushButton_11_clicked(); break;
        case 39: _t->on_pushButton_13_clicked(); break;
        case 40: _t->on_pushButton_12_clicked(); break;
        case 41: _t->on_toolButton_2_clicked(); break;
        case 42: _t->on_initAxisComplete_recieved(); break;
        case 43: _t->on_pushButton_7_clicked(); break;
        case 44: _t->on_resetButtonAxis1_clicked(); break;
        case 45: _t->on_resetButtonAxis2_clicked(); break;
        case 46: _t->on_resetButtonAxis3_clicked(); break;
        case 47: _t->on_resetButtonAxis4_clicked(); break;
        case 48: _t->onBoardsInitializationComplete(); break;
        case 49: _t->refreshLEDsStatus(); break;
        case 50: _t->initBoards(); break;
        case 51: _t->on_leftBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->on_rightBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->updateLeftBlockValue(); break;
        case 54: _t->selectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->updateRightBlockValue(); break;
        case 56: _t->selectRightBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 57: _t->updateCECRatios(); break;
        case 58: _t->on_pushButton_8_clicked(); break;
        case 59: _t->processCecAxisClickedEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 60: _t->cecAxisClickedThreadEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 61: _t->on_resetButtonAllAxis_clicked(); break;
        case 62: _t->on_ramDataFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 63: _t->on_fifoFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 64: _t->on_comboBox_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 65: _t->on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 66: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->on_radioButton_clicked(); break;
        case 68: _t->on_ceUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 69: _t->on_radioButton_2_clicked(); break;
        case 70: _t->on_cecAxis1_clicked(); break;
        case 71: _t->on_cecAxis2_clicked(); break;
        case 72: _t->on_cecAxis3_clicked(); break;
        case 73: _t->on_cecAxis4_clicked(); break;
        case 74: _t->on_ceDisplayAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 22:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 59:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        case 60:
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
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeFlyscanFormRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePositionOffsetFormRequest)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closePresetPositionFormRequest)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeSettingsFormRequest)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::closeCustomplotFormRequest)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initBoardsRequest)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::scaleAxisRequest)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::resetAxisRequest)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::changeBiasModeRequest)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::initAxisRequest)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::OffsetPosChanged)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::PresetPosChanged)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , unsigned int , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::configureCEChardwareRequest)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::stopCEChardwareRequest)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned int , CEratios * , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::updateCECRatiosRequest)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanErrorCode)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(unsigned char * , double * , double * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanStatValues)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::flyscanProcTerm)) {
                *result = 18;
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
        if (_id < 75)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 75;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 75)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 75;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::initComplete()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::closeFlyscanFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::closePositionOffsetFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::closePresetPositionFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::closeSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainWindow::closeCustomplotFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainWindow::initBoardsRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::scaleAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void MainWindow::resetAxisRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void MainWindow::changeBiasModeRequest(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void MainWindow::initAxisRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void MainWindow::OffsetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void MainWindow::PresetPosChanged(double * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void MainWindow::configureCEChardwareRequest(unsigned int _t1, unsigned int _t2, unsigned int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void MainWindow::stopCEChardwareRequest(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void MainWindow::updateCECRatiosRequest(unsigned int _t1, CEratios * _t2, unsigned int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void MainWindow::flyscanErrorCode(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void MainWindow::flyscanStatValues(unsigned char * _t1, double * _t2, double * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void MainWindow::flyscanProcTerm()
{
    QMetaObject::activate(this, &staticMetaObject, 18, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
