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
    QByteArrayData data[95];
    char stringdata0[1908];
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
QT_MOC_LITERAL(28, 444, 15), // "openFlyscanForm"
QT_MOC_LITERAL(29, 460, 16), // "closeFlyscanForm"
QT_MOC_LITERAL(30, 477, 17), // "reopenFlyscanForm"
QT_MOC_LITERAL(31, 495, 25), // "on_m_settingsMenu_clicked"
QT_MOC_LITERAL(32, 521, 8), // "QAction*"
QT_MOC_LITERAL(33, 530, 18), // "reopenSettingsForm"
QT_MOC_LITERAL(34, 549, 16), // "openSettingsForm"
QT_MOC_LITERAL(35, 566, 17), // "closeSettingsForm"
QT_MOC_LITERAL(36, 584, 22), // "openPresetPositionForm"
QT_MOC_LITERAL(37, 607, 23), // "closePresetPositionForm"
QT_MOC_LITERAL(38, 631, 24), // "reopenPresetPositionForm"
QT_MOC_LITERAL(39, 656, 22), // "openPositionOffsetForm"
QT_MOC_LITERAL(40, 679, 23), // "closePositionOffsetForm"
QT_MOC_LITERAL(41, 703, 24), // "reopenPositionOffsetForm"
QT_MOC_LITERAL(42, 728, 18), // "openCustomplotForm"
QT_MOC_LITERAL(43, 747, 19), // "closeCustomplotForm"
QT_MOC_LITERAL(44, 767, 20), // "reopenCustomplotForm"
QT_MOC_LITERAL(45, 788, 14), // "refresh_screen"
QT_MOC_LITERAL(46, 803, 20), // "on_OffsetPos_Changed"
QT_MOC_LITERAL(47, 824, 9), // "OffPosPtr"
QT_MOC_LITERAL(48, 834, 20), // "on_PresetPos_Changed"
QT_MOC_LITERAL(49, 855, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(50, 880, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(51, 905, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(52, 930, 23), // "on_toolButton_2_clicked"
QT_MOC_LITERAL(53, 954, 28), // "on_initAxisComplete_recieved"
QT_MOC_LITERAL(54, 983, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(55, 1007, 27), // "on_resetButtonAxis1_clicked"
QT_MOC_LITERAL(56, 1035, 27), // "on_resetButtonAxis2_clicked"
QT_MOC_LITERAL(57, 1063, 27), // "on_resetButtonAxis3_clicked"
QT_MOC_LITERAL(58, 1091, 27), // "on_resetButtonAxis4_clicked"
QT_MOC_LITERAL(59, 1119, 30), // "onBoardsInitializationComplete"
QT_MOC_LITERAL(60, 1150, 17), // "refreshLEDsStatus"
QT_MOC_LITERAL(61, 1168, 10), // "initBoards"
QT_MOC_LITERAL(62, 1179, 37), // "on_leftBlockUnits_currentInde..."
QT_MOC_LITERAL(63, 1217, 38), // "on_rightBlockUnits_currentInd..."
QT_MOC_LITERAL(64, 1256, 20), // "updateLeftBlockValue"
QT_MOC_LITERAL(65, 1277, 20), // "selectLeftBlockValue"
QT_MOC_LITERAL(66, 1298, 21), // "updateRightBlockValue"
QT_MOC_LITERAL(67, 1320, 21), // "selectRightBlockValue"
QT_MOC_LITERAL(68, 1342, 15), // "updateCECRatios"
QT_MOC_LITERAL(69, 1358, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(70, 1382, 26), // "processCecAxisClickedEvent"
QT_MOC_LITERAL(71, 1409, 4), // "int*"
QT_MOC_LITERAL(72, 1414, 13), // "axisListIndex"
QT_MOC_LITERAL(73, 1428, 10), // "QCheckBox*"
QT_MOC_LITERAL(74, 1439, 15), // "cecAxisCheckBox"
QT_MOC_LITERAL(75, 1455, 25), // "cecAxisClickedThreadEvent"
QT_MOC_LITERAL(76, 1481, 29), // "on_resetButtonAllAxis_clicked"
QT_MOC_LITERAL(77, 1511, 33), // "on_ramDataFlyscanRequest_reci..."
QT_MOC_LITERAL(78, 1545, 4), // "freq"
QT_MOC_LITERAL(79, 1550, 4), // "size"
QT_MOC_LITERAL(80, 1555, 4), // "time"
QT_MOC_LITERAL(81, 1560, 3), // "nbr"
QT_MOC_LITERAL(82, 1564, 27), // "configureFlyscanThreadEvent"
QT_MOC_LITERAL(83, 1592, 19), // "startRamDataFlyscan"
QT_MOC_LITERAL(84, 1612, 33), // "on_comboBox_3_currentIndexCha..."
QT_MOC_LITERAL(85, 1646, 33), // "on_comboBox_4_currentIndexCha..."
QT_MOC_LITERAL(86, 1680, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(87, 1712, 22), // "on_radioButton_clicked"
QT_MOC_LITERAL(88, 1735, 30), // "on_ceUnits_currentIndexChanged"
QT_MOC_LITERAL(89, 1766, 24), // "on_radioButton_2_clicked"
QT_MOC_LITERAL(90, 1791, 19), // "on_cecAxis1_clicked"
QT_MOC_LITERAL(91, 1811, 19), // "on_cecAxis2_clicked"
QT_MOC_LITERAL(92, 1831, 19), // "on_cecAxis3_clicked"
QT_MOC_LITERAL(93, 1851, 19), // "on_cecAxis4_clicked"
QT_MOC_LITERAL(94, 1871, 36) // "on_ceDisplayAxis_currentIndex..."

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
    "ceRatios\0openFlyscanForm\0closeFlyscanForm\0"
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
    "freq\0size\0time\0nbr\0configureFlyscanThreadEvent\0"
    "startRamDataFlyscan\0"
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
      73,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      16,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  379,    2, 0x06 /* Public */,
       3,    0,  380,    2, 0x06 /* Public */,
       4,    0,  381,    2, 0x06 /* Public */,
       5,    0,  382,    2, 0x06 /* Public */,
       6,    0,  383,    2, 0x06 /* Public */,
       7,    0,  384,    2, 0x06 /* Public */,
       8,    0,  385,    2, 0x06 /* Public */,
       9,    1,  386,    2, 0x06 /* Public */,
      11,    1,  389,    2, 0x06 /* Public */,
      13,    1,  392,    2, 0x06 /* Public */,
      15,    0,  395,    2, 0x06 /* Public */,
      16,    1,  396,    2, 0x06 /* Public */,
      19,    1,  399,    2, 0x06 /* Public */,
      21,    3,  402,    2, 0x06 /* Public */,
      24,    1,  409,    2, 0x06 /* Public */,
      25,    3,  412,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      28,    0,  419,    2, 0x0a /* Public */,
      29,    0,  420,    2, 0x0a /* Public */,
      30,    0,  421,    2, 0x0a /* Public */,
      31,    1,  422,    2, 0x0a /* Public */,
      33,    0,  425,    2, 0x0a /* Public */,
      34,    0,  426,    2, 0x0a /* Public */,
      35,    0,  427,    2, 0x0a /* Public */,
      36,    0,  428,    2, 0x0a /* Public */,
      37,    0,  429,    2, 0x0a /* Public */,
      38,    0,  430,    2, 0x0a /* Public */,
      39,    0,  431,    2, 0x0a /* Public */,
      40,    0,  432,    2, 0x0a /* Public */,
      41,    0,  433,    2, 0x0a /* Public */,
      42,    0,  434,    2, 0x0a /* Public */,
      43,    0,  435,    2, 0x0a /* Public */,
      44,    0,  436,    2, 0x0a /* Public */,
      45,    0,  437,    2, 0x0a /* Public */,
      46,    1,  438,    2, 0x08 /* Private */,
      48,    1,  441,    2, 0x08 /* Private */,
      49,    0,  444,    2, 0x08 /* Private */,
      50,    0,  445,    2, 0x08 /* Private */,
      51,    0,  446,    2, 0x08 /* Private */,
      52,    0,  447,    2, 0x08 /* Private */,
      53,    0,  448,    2, 0x08 /* Private */,
      54,    0,  449,    2, 0x08 /* Private */,
      55,    0,  450,    2, 0x08 /* Private */,
      56,    0,  451,    2, 0x08 /* Private */,
      57,    0,  452,    2, 0x08 /* Private */,
      58,    0,  453,    2, 0x08 /* Private */,
      59,    0,  454,    2, 0x08 /* Private */,
      60,    0,  455,    2, 0x08 /* Private */,
      61,    0,  456,    2, 0x08 /* Private */,
      62,    1,  457,    2, 0x08 /* Private */,
      63,    1,  460,    2, 0x08 /* Private */,
      64,    0,  463,    2, 0x08 /* Private */,
      65,    1,  464,    2, 0x08 /* Private */,
      66,    0,  467,    2, 0x08 /* Private */,
      67,    1,  468,    2, 0x08 /* Private */,
      68,    0,  471,    2, 0x08 /* Private */,
      69,    0,  472,    2, 0x08 /* Private */,
      70,    3,  473,    2, 0x08 /* Private */,
      75,    3,  480,    2, 0x08 /* Private */,
      76,    0,  487,    2, 0x08 /* Private */,
      77,    4,  488,    2, 0x08 /* Private */,
      82,    0,  497,    2, 0x08 /* Private */,
      83,    4,  498,    2, 0x08 /* Private */,
      84,    1,  507,    2, 0x08 /* Private */,
      85,    1,  510,    2, 0x08 /* Private */,
      86,    1,  513,    2, 0x08 /* Private */,
      87,    0,  516,    2, 0x08 /* Private */,
      88,    1,  517,    2, 0x08 /* Private */,
      89,    0,  520,    2, 0x08 /* Private */,
      90,    0,  521,    2, 0x08 /* Private */,
      91,    0,  522,    2, 0x08 /* Private */,
      92,    0,  523,    2, 0x08 /* Private */,
      93,    0,  524,    2, 0x08 /* Private */,
      94,    1,  525,    2, 0x08 /* Private */,

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

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32,    2,
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
    QMetaType::Void, 0x80000000 | 17,   47,
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
    QMetaType::Void, QMetaType::Int, 0x80000000 | 71, 0x80000000 | 73,   12,   72,   74,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 71, 0x80000000 | 73,   12,   72,   74,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,   78,   79,   80,   81,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double, QMetaType::UInt,   78,   80,   79,   81,
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
        case 16: _t->openFlyscanForm(); break;
        case 17: _t->closeFlyscanForm(); break;
        case 18: _t->reopenFlyscanForm(); break;
        case 19: _t->on_m_settingsMenu_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 20: _t->reopenSettingsForm(); break;
        case 21: _t->openSettingsForm(); break;
        case 22: _t->closeSettingsForm(); break;
        case 23: _t->openPresetPositionForm(); break;
        case 24: _t->closePresetPositionForm(); break;
        case 25: _t->reopenPresetPositionForm(); break;
        case 26: _t->openPositionOffsetForm(); break;
        case 27: _t->closePositionOffsetForm(); break;
        case 28: _t->reopenPositionOffsetForm(); break;
        case 29: _t->openCustomplotForm(); break;
        case 30: _t->closeCustomplotForm(); break;
        case 31: _t->reopenCustomplotForm(); break;
        case 32: _t->refresh_screen(); break;
        case 33: _t->on_OffsetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 34: _t->on_PresetPos_Changed((*reinterpret_cast< double*(*)>(_a[1]))); break;
        case 35: _t->on_pushButton_11_clicked(); break;
        case 36: _t->on_pushButton_13_clicked(); break;
        case 37: _t->on_pushButton_12_clicked(); break;
        case 38: _t->on_toolButton_2_clicked(); break;
        case 39: _t->on_initAxisComplete_recieved(); break;
        case 40: _t->on_pushButton_7_clicked(); break;
        case 41: _t->on_resetButtonAxis1_clicked(); break;
        case 42: _t->on_resetButtonAxis2_clicked(); break;
        case 43: _t->on_resetButtonAxis3_clicked(); break;
        case 44: _t->on_resetButtonAxis4_clicked(); break;
        case 45: _t->onBoardsInitializationComplete(); break;
        case 46: _t->refreshLEDsStatus(); break;
        case 47: _t->initBoards(); break;
        case 48: _t->on_leftBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->on_rightBlockUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->updateLeftBlockValue(); break;
        case 51: _t->selectLeftBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->updateRightBlockValue(); break;
        case 53: _t->selectRightBlockValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->updateCECRatios(); break;
        case 55: _t->on_pushButton_8_clicked(); break;
        case 56: _t->processCecAxisClickedEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 57: _t->cecAxisClickedThreadEvent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< QCheckBox*(*)>(_a[3]))); break;
        case 58: _t->on_resetButtonAllAxis_clicked(); break;
        case 59: _t->on_ramDataFlyscanRequest_recieved((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 60: _t->configureFlyscanThreadEvent(); break;
        case 61: _t->startRamDataFlyscan((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 62: _t->on_comboBox_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 64: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 65: _t->on_radioButton_clicked(); break;
        case 66: _t->on_ceUnits_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 67: _t->on_radioButton_2_clicked(); break;
        case 68: _t->on_cecAxis1_clicked(); break;
        case 69: _t->on_cecAxis2_clicked(); break;
        case 70: _t->on_cecAxis3_clicked(); break;
        case 71: _t->on_cecAxis4_clicked(); break;
        case 72: _t->on_ceDisplayAxis_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 56:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 2:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCheckBox* >(); break;
            }
            break;
        case 57:
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
        if (_id < 73)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 73;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 73)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 73;
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
