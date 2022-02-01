/****************************************************************************
** Meta object code from reading C++ file 'settingsform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/settingsform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingsForm_t {
    QByteArrayData data[79];
    char stringdata0[1990];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingsForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingsForm_t qt_meta_stringdata_SettingsForm = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SettingsForm"
QT_MOC_LITERAL(1, 13, 9), // "closeThis"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 24), // "modifyBaseAddressRequest"
QT_MOC_LITERAL(4, 49, 3), // "add"
QT_MOC_LITERAL(5, 53, 21), // "updateSettingsRequest"
QT_MOC_LITERAL(6, 75, 1), // "a"
QT_MOC_LITERAL(7, 77, 1), // "b"
QT_MOC_LITERAL(8, 79, 4), // "int*"
QT_MOC_LITERAL(9, 84, 3), // "val"
QT_MOC_LITERAL(10, 88, 23), // "initSettingsFormRequest"
QT_MOC_LITERAL(11, 112, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(12, 136, 17), // "updateBaseAddress"
QT_MOC_LITERAL(13, 154, 17), // "updateApdSettings"
QT_MOC_LITERAL(14, 172, 15), // "convertHex2Uint"
QT_MOC_LITERAL(15, 188, 11), // "std::string"
QT_MOC_LITERAL(16, 200, 3), // "hex"
QT_MOC_LITERAL(17, 204, 21), // "updateGeneralSettings"
QT_MOC_LITERAL(18, 226, 32), // "on_interType_currentIndexChanged"
QT_MOC_LITERAL(19, 259, 5), // "index"
QT_MOC_LITERAL(20, 265, 35), // "on_precisionVal_currentIndexC..."
QT_MOC_LITERAL(21, 301, 22), // "gainControlsValuesFunc"
QT_MOC_LITERAL(22, 324, 4), // "axis"
QT_MOC_LITERAL(23, 329, 5), // "bool*"
QT_MOC_LITERAL(24, 335, 35), // "on_resetFindVel_currentIndexC..."
QT_MOC_LITERAL(25, 371, 24), // "on_pushButton_17_clicked"
QT_MOC_LITERAL(26, 396, 33), // "on_agcControl_currentIndexCha..."
QT_MOC_LITERAL(27, 430, 35), // "on_agcControl_2_currentIndexC..."
QT_MOC_LITERAL(28, 466, 35), // "on_agcControl_4_currentIndexC..."
QT_MOC_LITERAL(29, 502, 35), // "on_agcControl_3_currentIndexC..."
QT_MOC_LITERAL(30, 538, 37), // "on_gainMinControl_currentInde..."
QT_MOC_LITERAL(31, 576, 39), // "on_gainMinControl_2_currentIn..."
QT_MOC_LITERAL(32, 616, 39), // "on_gainMinControl_3_currentIn..."
QT_MOC_LITERAL(33, 656, 39), // "on_gainMinControl_4_currentIn..."
QT_MOC_LITERAL(34, 696, 37), // "on_gainMaxControl_currentInde..."
QT_MOC_LITERAL(35, 734, 39), // "on_gainMaxControl_2_currentIn..."
QT_MOC_LITERAL(36, 774, 39), // "on_gainMaxControl_3_currentIn..."
QT_MOC_LITERAL(37, 814, 39), // "on_gainMaxControl_4_currentIn..."
QT_MOC_LITERAL(38, 854, 20), // "ssiDataAvailableFunc"
QT_MOC_LITERAL(39, 875, 7), // "double*"
QT_MOC_LITERAL(40, 883, 7), // "ssiVals"
QT_MOC_LITERAL(41, 891, 10), // "optPwrVals"
QT_MOC_LITERAL(42, 902, 22), // "on_StartButton_clicked"
QT_MOC_LITERAL(43, 925, 28), // "on_ssiSquelch_1_valueChanged"
QT_MOC_LITERAL(44, 954, 4), // "arg1"
QT_MOC_LITERAL(45, 959, 28), // "on_ssiSquelch_2_valueChanged"
QT_MOC_LITERAL(46, 988, 28), // "on_ssiSquelch_3_valueChanged"
QT_MOC_LITERAL(47, 1017, 28), // "on_ssiSquelch_4_valueChanged"
QT_MOC_LITERAL(48, 1046, 21), // "updateDiagnosticsData"
QT_MOC_LITERAL(49, 1068, 16), // "updateEEPROMData"
QT_MOC_LITERAL(50, 1085, 21), // "updateCalibrationData"
QT_MOC_LITERAL(51, 1107, 33), // "on_sampleSCLK_currentIndexCha..."
QT_MOC_LITERAL(52, 1141, 29), // "on_kpFilterCoeff_valueChanged"
QT_MOC_LITERAL(53, 1171, 31), // "on_kpFilterCoeff_2_valueChanged"
QT_MOC_LITERAL(54, 1203, 31), // "on_kpFilterCoeff_3_valueChanged"
QT_MOC_LITERAL(55, 1235, 31), // "on_kpFilterCoeff_4_valueChanged"
QT_MOC_LITERAL(56, 1267, 29), // "on_kvFilterCoeff_valueChanged"
QT_MOC_LITERAL(57, 1297, 31), // "on_kvFilterCoeff_2_valueChanged"
QT_MOC_LITERAL(58, 1329, 31), // "on_kvFilterCoeff_3_valueChanged"
QT_MOC_LITERAL(59, 1361, 31), // "on_kvFilterCoeff_4_valueChanged"
QT_MOC_LITERAL(60, 1393, 26), // "on_apdBiasDac_valueChanged"
QT_MOC_LITERAL(61, 1420, 31), // "on_apdGainL2SetVal_valueChanged"
QT_MOC_LITERAL(62, 1452, 30), // "on_apdSigRmsL2Set_valueChanged"
QT_MOC_LITERAL(63, 1483, 30), // "on_apdOptPwrL2Set_valueChanged"
QT_MOC_LITERAL(64, 1514, 28), // "on_apdBiasDac_2_valueChanged"
QT_MOC_LITERAL(65, 1543, 33), // "on_apdGainL2SetVal_2_valueCha..."
QT_MOC_LITERAL(66, 1577, 32), // "on_apdSigRmsL2Set_2_valueChanged"
QT_MOC_LITERAL(67, 1610, 32), // "on_apdOptPwrL2Set_2_valueChanged"
QT_MOC_LITERAL(68, 1643, 28), // "on_apdBiasDac_3_valueChanged"
QT_MOC_LITERAL(69, 1672, 33), // "on_apdGainL2SetVal_3_valueCha..."
QT_MOC_LITERAL(70, 1706, 32), // "on_apdSigRmsL2Set_3_valueChanged"
QT_MOC_LITERAL(71, 1739, 32), // "on_apdOptPwrL2Set_3_valueChanged"
QT_MOC_LITERAL(72, 1772, 28), // "on_apdBiasDac_4_valueChanged"
QT_MOC_LITERAL(73, 1801, 33), // "on_apdGainL2SetVal_4_valueCha..."
QT_MOC_LITERAL(74, 1835, 32), // "on_apdSigRmsL2Set_4_valueChanged"
QT_MOC_LITERAL(75, 1868, 32), // "on_apdOptPwrL2Set_4_valueChanged"
QT_MOC_LITERAL(76, 1901, 30), // "on_baseAdressInput_textChanged"
QT_MOC_LITERAL(77, 1932, 32), // "on_resetSCLK_currentIndexChanged"
QT_MOC_LITERAL(78, 1965, 24) // "on_sampFreq_valueChanged"

    },
    "SettingsForm\0closeThis\0\0"
    "modifyBaseAddressRequest\0add\0"
    "updateSettingsRequest\0a\0b\0int*\0val\0"
    "initSettingsFormRequest\0on_pushButton_5_clicked\0"
    "updateBaseAddress\0updateApdSettings\0"
    "convertHex2Uint\0std::string\0hex\0"
    "updateGeneralSettings\0"
    "on_interType_currentIndexChanged\0index\0"
    "on_precisionVal_currentIndexChanged\0"
    "gainControlsValuesFunc\0axis\0bool*\0"
    "on_resetFindVel_currentIndexChanged\0"
    "on_pushButton_17_clicked\0"
    "on_agcControl_currentIndexChanged\0"
    "on_agcControl_2_currentIndexChanged\0"
    "on_agcControl_4_currentIndexChanged\0"
    "on_agcControl_3_currentIndexChanged\0"
    "on_gainMinControl_currentIndexChanged\0"
    "on_gainMinControl_2_currentIndexChanged\0"
    "on_gainMinControl_3_currentIndexChanged\0"
    "on_gainMinControl_4_currentIndexChanged\0"
    "on_gainMaxControl_currentIndexChanged\0"
    "on_gainMaxControl_2_currentIndexChanged\0"
    "on_gainMaxControl_3_currentIndexChanged\0"
    "on_gainMaxControl_4_currentIndexChanged\0"
    "ssiDataAvailableFunc\0double*\0ssiVals\0"
    "optPwrVals\0on_StartButton_clicked\0"
    "on_ssiSquelch_1_valueChanged\0arg1\0"
    "on_ssiSquelch_2_valueChanged\0"
    "on_ssiSquelch_3_valueChanged\0"
    "on_ssiSquelch_4_valueChanged\0"
    "updateDiagnosticsData\0updateEEPROMData\0"
    "updateCalibrationData\0"
    "on_sampleSCLK_currentIndexChanged\0"
    "on_kpFilterCoeff_valueChanged\0"
    "on_kpFilterCoeff_2_valueChanged\0"
    "on_kpFilterCoeff_3_valueChanged\0"
    "on_kpFilterCoeff_4_valueChanged\0"
    "on_kvFilterCoeff_valueChanged\0"
    "on_kvFilterCoeff_2_valueChanged\0"
    "on_kvFilterCoeff_3_valueChanged\0"
    "on_kvFilterCoeff_4_valueChanged\0"
    "on_apdBiasDac_valueChanged\0"
    "on_apdGainL2SetVal_valueChanged\0"
    "on_apdSigRmsL2Set_valueChanged\0"
    "on_apdOptPwrL2Set_valueChanged\0"
    "on_apdBiasDac_2_valueChanged\0"
    "on_apdGainL2SetVal_2_valueChanged\0"
    "on_apdSigRmsL2Set_2_valueChanged\0"
    "on_apdOptPwrL2Set_2_valueChanged\0"
    "on_apdBiasDac_3_valueChanged\0"
    "on_apdGainL2SetVal_3_valueChanged\0"
    "on_apdSigRmsL2Set_3_valueChanged\0"
    "on_apdOptPwrL2Set_3_valueChanged\0"
    "on_apdBiasDac_4_valueChanged\0"
    "on_apdGainL2SetVal_4_valueChanged\0"
    "on_apdSigRmsL2Set_4_valueChanged\0"
    "on_apdOptPwrL2Set_4_valueChanged\0"
    "on_baseAdressInput_textChanged\0"
    "on_resetSCLK_currentIndexChanged\0"
    "on_sampFreq_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingsForm[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      63,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  329,    2, 0x06 /* Public */,
       3,    1,  330,    2, 0x06 /* Public */,
       5,    3,  333,    2, 0x06 /* Public */,
      10,    0,  340,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,  341,    2, 0x08 /* Private */,
      12,    0,  342,    2, 0x08 /* Private */,
      13,    0,  343,    2, 0x08 /* Private */,
      14,    1,  344,    2, 0x08 /* Private */,
      17,    0,  347,    2, 0x08 /* Private */,
      18,    1,  348,    2, 0x08 /* Private */,
      20,    1,  351,    2, 0x08 /* Private */,
      21,    2,  354,    2, 0x08 /* Private */,
      24,    1,  359,    2, 0x08 /* Private */,
      25,    0,  362,    2, 0x08 /* Private */,
      26,    1,  363,    2, 0x08 /* Private */,
      27,    1,  366,    2, 0x08 /* Private */,
      28,    1,  369,    2, 0x08 /* Private */,
      29,    1,  372,    2, 0x08 /* Private */,
      30,    1,  375,    2, 0x08 /* Private */,
      31,    1,  378,    2, 0x08 /* Private */,
      32,    1,  381,    2, 0x08 /* Private */,
      33,    1,  384,    2, 0x08 /* Private */,
      34,    1,  387,    2, 0x08 /* Private */,
      35,    1,  390,    2, 0x08 /* Private */,
      36,    1,  393,    2, 0x08 /* Private */,
      37,    1,  396,    2, 0x08 /* Private */,
      38,    3,  399,    2, 0x08 /* Private */,
      42,    0,  406,    2, 0x08 /* Private */,
      43,    1,  407,    2, 0x08 /* Private */,
      45,    1,  410,    2, 0x08 /* Private */,
      46,    1,  413,    2, 0x08 /* Private */,
      47,    1,  416,    2, 0x08 /* Private */,
      48,    0,  419,    2, 0x08 /* Private */,
      49,    0,  420,    2, 0x08 /* Private */,
      50,    0,  421,    2, 0x08 /* Private */,
      51,    1,  422,    2, 0x08 /* Private */,
      52,    1,  425,    2, 0x08 /* Private */,
      53,    1,  428,    2, 0x08 /* Private */,
      54,    1,  431,    2, 0x08 /* Private */,
      55,    1,  434,    2, 0x08 /* Private */,
      56,    1,  437,    2, 0x08 /* Private */,
      57,    1,  440,    2, 0x08 /* Private */,
      58,    1,  443,    2, 0x08 /* Private */,
      59,    1,  446,    2, 0x08 /* Private */,
      60,    1,  449,    2, 0x08 /* Private */,
      61,    1,  452,    2, 0x08 /* Private */,
      62,    1,  455,    2, 0x08 /* Private */,
      63,    1,  458,    2, 0x08 /* Private */,
      64,    1,  461,    2, 0x08 /* Private */,
      65,    1,  464,    2, 0x08 /* Private */,
      66,    1,  467,    2, 0x08 /* Private */,
      67,    1,  470,    2, 0x08 /* Private */,
      68,    1,  473,    2, 0x08 /* Private */,
      69,    1,  476,    2, 0x08 /* Private */,
      70,    1,  479,    2, 0x08 /* Private */,
      71,    1,  482,    2, 0x08 /* Private */,
      72,    1,  485,    2, 0x08 /* Private */,
      73,    1,  488,    2, 0x08 /* Private */,
      74,    1,  491,    2, 0x08 /* Private */,
      75,    1,  494,    2, 0x08 /* Private */,
      76,    1,  497,    2, 0x08 /* Private */,
      77,    1,  500,    2, 0x08 /* Private */,
      78,    1,  503,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 8,    6,    7,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::UInt, 0x80000000 | 15,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 23,   22,    9,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::UInt, 0x80000000 | 39, 0x80000000 | 39,   22,   40,   41,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   44,

       0        // eod
};

void SettingsForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SettingsForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->closeThis(); break;
        case 1: _t->modifyBaseAddressRequest((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->updateSettingsRequest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int*(*)>(_a[3]))); break;
        case 3: _t->initSettingsFormRequest(); break;
        case 4: _t->on_pushButton_5_clicked(); break;
        case 5: _t->updateBaseAddress(); break;
        case 6: _t->updateApdSettings(); break;
        case 7: { uint _r = _t->convertHex2Uint((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< uint*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->updateGeneralSettings(); break;
        case 9: _t->on_interType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_precisionVal_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->gainControlsValuesFunc((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool*(*)>(_a[2]))); break;
        case 12: _t->on_resetFindVel_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->on_pushButton_17_clicked(); break;
        case 14: _t->on_agcControl_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_agcControl_2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_agcControl_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_agcControl_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_gainMinControl_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_gainMinControl_2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_gainMinControl_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->on_gainMinControl_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->on_gainMaxControl_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_gainMaxControl_2_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->on_gainMaxControl_3_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->on_gainMaxControl_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->ssiDataAvailableFunc((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< double*(*)>(_a[2])),(*reinterpret_cast< double*(*)>(_a[3]))); break;
        case 27: _t->on_StartButton_clicked(); break;
        case 28: _t->on_ssiSquelch_1_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->on_ssiSquelch_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->on_ssiSquelch_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->on_ssiSquelch_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->updateDiagnosticsData(); break;
        case 33: _t->updateEEPROMData(); break;
        case 34: _t->updateCalibrationData(); break;
        case 35: _t->on_sampleSCLK_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->on_kpFilterCoeff_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->on_kpFilterCoeff_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->on_kpFilterCoeff_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->on_kpFilterCoeff_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->on_kvFilterCoeff_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->on_kvFilterCoeff_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 42: _t->on_kvFilterCoeff_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 43: _t->on_kvFilterCoeff_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->on_apdBiasDac_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 45: _t->on_apdGainL2SetVal_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 46: _t->on_apdSigRmsL2Set_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 47: _t->on_apdOptPwrL2Set_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->on_apdBiasDac_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->on_apdGainL2SetVal_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->on_apdSigRmsL2Set_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 51: _t->on_apdOptPwrL2Set_2_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->on_apdBiasDac_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 53: _t->on_apdGainL2SetVal_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->on_apdSigRmsL2Set_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->on_apdOptPwrL2Set_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->on_apdBiasDac_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 57: _t->on_apdGainL2SetVal_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 58: _t->on_apdSigRmsL2Set_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 59: _t->on_apdOptPwrL2Set_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 60: _t->on_baseAdressInput_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 61: _t->on_resetSCLK_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 62: _t->on_sampFreq_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingsForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsForm::closeThis)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingsForm::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsForm::modifyBaseAddressRequest)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SettingsForm::*)(int , int , int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsForm::updateSettingsRequest)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SettingsForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingsForm::initSettingsFormRequest)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingsForm::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SettingsForm.data,
    qt_meta_data_SettingsForm,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SettingsForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingsForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingsForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SettingsForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 63)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 63;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 63)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 63;
    }
    return _id;
}

// SIGNAL 0
void SettingsForm::closeThis()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SettingsForm::modifyBaseAddressRequest(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SettingsForm::updateSettingsRequest(int _t1, int _t2, int * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SettingsForm::initSettingsFormRequest()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
