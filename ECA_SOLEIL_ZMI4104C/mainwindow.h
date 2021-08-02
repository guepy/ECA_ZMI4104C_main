#pragma once
#include <QMainWindow>
#include <QPainter>
#include "flyscanform.h"
#include "settingsform.h"
#include "positionoffsetform.h"
#include "presetpositionform.h"
#include "cesettingsform.h"
#include "eca_soleil_zmi4104c.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
    void initialize_FsForm_Ptr();
    /*------------Menu Bar settings----------------------------*/
    SettingsForm *setForm;
    //-------Bouton continuous acquisition----------------------
    FlyscanForm *flyscanForm;
    // --------Bouton set position offset-----------------------
    positionOffsetForm *posOffsetForm;

    // --------Bouton preset position --------------------------
    presetPositionForm *presPositionForm;
    QAction     *a_openMenu;
    QMenu       *m_settingsMenu;
    BIAS_MODE bias_mode;
    SIS1100_Device_Struct* dev;
signals:
public slots:
    // --------------button continuous acquisition---------------------------
    void openFlyscanForm();
    void closeFlyscanForm();
    void reopenFlyscanForm();
    // --------------menu bar setings--------------------------------
    void on_m_settingsMenu_clicked(QAction*);
    void reopenSettingsForm();
    void openSettingsForm();
    void closeSettingsForm();
    // --------------button preset position---------------------------
    void openPresetPositionForm();
    void closePresetPositionForm();
    void reopenPresetPositionForm();
    // --------------button position offset---------------------------
    void openPositionOffsetForm();
    void closePositionOffsetForm();
    void reopenPositionOffsetForm();
private slots:

    void on_pushButton_11_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_12_clicked();
    void on_toolButton_2_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
};
// --------------button continuous acquisition---------------------------
static int fsForm_int=0;
// --------------menu bar setings--------------------------------
static int sfForm_int=0;
// --------------button preset position---------------------------
static int presPosForm_int=0;
// --------------button preset position---------------------------
static int posOffForm_int=0;


// MAINWINDOW_H

