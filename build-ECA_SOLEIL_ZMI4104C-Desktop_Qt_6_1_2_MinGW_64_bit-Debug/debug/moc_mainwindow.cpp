/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ECA_SOLEIL_ZMI4104C/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[40];
    char stringdata0[395];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 15), // "openFlyscanForm"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 16), // "closeFlyscanForm"
QT_MOC_LITERAL(45, 17), // "reopenFlyscanForm"
QT_MOC_LITERAL(63, 25), // "on_m_settingsMenu_clicked"
QT_MOC_LITERAL(89, 8), // "QAction*"
QT_MOC_LITERAL(98, 18), // "reopenSettingsForm"
QT_MOC_LITERAL(117, 16), // "openSettingsForm"
QT_MOC_LITERAL(134, 17), // "closeSettingsForm"
QT_MOC_LITERAL(152, 22), // "openPresetPositionForm"
QT_MOC_LITERAL(175, 23), // "closePresetPositionForm"
QT_MOC_LITERAL(199, 24), // "reopenPresetPositionForm"
QT_MOC_LITERAL(224, 22), // "openPositionOffsetForm"
QT_MOC_LITERAL(247, 23), // "closePositionOffsetForm"
QT_MOC_LITERAL(271, 24), // "reopenPositionOffsetForm"
QT_MOC_LITERAL(296, 24), // "on_pushButton_11_clicked"
QT_MOC_LITERAL(321, 24), // "on_pushButton_13_clicked"
QT_MOC_LITERAL(346, 24), // "on_pushButton_12_clicked"
QT_MOC_LITERAL(371, 23) // "on_toolButton_2_clicked"

    },
    "MainWindow\0openFlyscanForm\0\0"
    "closeFlyscanForm\0reopenFlyscanForm\0"
    "on_m_settingsMenu_clicked\0QAction*\0"
    "reopenSettingsForm\0openSettingsForm\0"
    "closeSettingsForm\0openPresetPositionForm\0"
    "closePresetPositionForm\0"
    "reopenPresetPositionForm\0"
    "openPositionOffsetForm\0closePositionOffsetForm\0"
    "reopenPositionOffsetForm\0"
    "on_pushButton_11_clicked\0"
    "on_pushButton_13_clicked\0"
    "on_pushButton_12_clicked\0"
    "on_toolButton_2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  116,    2, 0x0a,    0 /* Public */,
       3,    0,  117,    2, 0x0a,    1 /* Public */,
       4,    0,  118,    2, 0x0a,    2 /* Public */,
       5,    1,  119,    2, 0x0a,    3 /* Public */,
       7,    0,  122,    2, 0x0a,    5 /* Public */,
       8,    0,  123,    2, 0x0a,    6 /* Public */,
       9,    0,  124,    2, 0x0a,    7 /* Public */,
      10,    0,  125,    2, 0x0a,    8 /* Public */,
      11,    0,  126,    2, 0x0a,    9 /* Public */,
      12,    0,  127,    2, 0x0a,   10 /* Public */,
      13,    0,  128,    2, 0x0a,   11 /* Public */,
      14,    0,  129,    2, 0x0a,   12 /* Public */,
      15,    0,  130,    2, 0x0a,   13 /* Public */,
      16,    0,  131,    2, 0x08,   14 /* Private */,
      17,    0,  132,    2, 0x08,   15 /* Private */,
      18,    0,  133,    2, 0x08,   16 /* Private */,
      19,    0,  134,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
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

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->openFlyscanForm(); break;
        case 1: _t->closeFlyscanForm(); break;
        case 2: _t->reopenFlyscanForm(); break;
        case 3: _t->on_m_settingsMenu_clicked((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->reopenSettingsForm(); break;
        case 5: _t->openSettingsForm(); break;
        case 6: _t->closeSettingsForm(); break;
        case 7: _t->openPresetPositionForm(); break;
        case 8: _t->closePresetPositionForm(); break;
        case 9: _t->reopenPresetPositionForm(); break;
        case 10: _t->openPositionOffsetForm(); break;
        case 11: _t->closePositionOffsetForm(); break;
        case 12: _t->reopenPositionOffsetForm(); break;
        case 13: _t->on_pushButton_11_clicked(); break;
        case 14: _t->on_pushButton_13_clicked(); break;
        case 15: _t->on_pushButton_12_clicked(); break;
        case 16: _t->on_toolButton_2_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QAction *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
