#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QLibrary>
#include <QTimer>
#include <QDebug>
#include "flyscanform.h"
#include "settingsform.h"
#include "positionoffsetform.h"
#include "presetpositionform.h"
#include "cesettingsform.h"
#include "dataprocessing.h"
#include "graphsform.h"
#include "../eca_soleil_zmi4104_lib/eca_soleil_zmi4104c.h"
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


//QLibrary eca_soleil_zmi4104_lib("eca_soleil_zmi4104_lib");
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //virtual void paintEvent(QPaintEvent *event);
    /*------------Menu Bar settings----------------------------*/
    SettingsForm *setForm;
    //-------Bouton continuous acquisition----------------------
    FlyscanForm *flyscanForm;
    // --------Bouton set position offset-----------------------
    positionOffsetForm *posOffsetForm;
    //-------------plot graphs button --------------------------
    graphsForm* graphsform;
    // --------Bouton preset position --------------------------
    presetPositionForm *presPositionForm;
    QAction     *a_openMenu;
    QMenu       *m_settingsMenu;
    QTimer      *gtimer;
    unsigned int startApp;
    double *position;
    double *velocity;
    double *mTime;
    double *APDGain;
    double *OptPwr;
    double *SSIav;
private:
    int currentLeftBlockUnits;
    int currentRightBlockUnits;
    int *ledsColor, *ledsColorPrev;
    double* scaledPosition;
    double* scaledValueLeftBlock;
    double* scaledValueRightBlock;
    double *scaledAPDGain;
    double *scaledOptPwr;
    double *scaledSSIav;
    dataProcessing *dataProc;
    int leftBlockIndex;
    int rightBlockIndex;
signals:
    void initComplete();
    void initBoardsRequest();
    void scaleAxisRequest(int units);
    void resetAxisRequest(int axis);
    void changeBiasModeRequest(int index);
    void initAxisRequest();
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
    //--------------Pot graphs button---------------------------------
    void openGraphsForm();
    void closeGraphsForm();
    void reopenGraphsForm();

    void refresh_screen();
private slots:

    void on_pushButton_11_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_12_clicked();
    void on_toolButton_2_clicked();
    void on_initAxisComplete_recieved();
    void on_pushButton_7_clicked();
    void on_resetButtonAxis1_clicked();
    void on_resetButtonAxis2_clicked();
    void on_resetButtonAxis3_clicked();
    void on_resetButtonAxis4_clicked();
    void onBoardsInitializationComplete();
    void refreshLEDsStatus();
    void initBoards();
    void on_leftBlockUnits_currentIndexChanged(int index);
    void on_rightBlockUnits_currentIndexChanged(int index);
    void updateLeftBlockValue();
    void selectLeftBlockValue(int index);
    void updateRightBlockValue();
    void selectRightBlockValue(int index);

    void on_pushButton_8_clicked();

    void on_resetButtonAllAxis_clicked();

    void on_comboBox_3_currentIndexChanged(int index);

    void on_comboBox_4_currentIndexChanged(int index);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
// --------------button continuous acquisition---------------------------
static bool fsForm_int=0;
// --------------menu bar setings--------------------------------
static bool sfForm_int=0;
// --------------button preset position---------------------------
static bool presPosForm_int=0;
// --------------button preset position---------------------------
static bool posOffForm_int=0;
// --------------plot graphs button---------------------------
static bool graphsForm_int=0;
//---------------LEDs-----------------
//static QPainter* circlePainter;
static const char* ledsColorString[3] = {
    "background-color: black;",
    "background-color: rgb(37, 255, 81);",
    "background-color: rgb(255, 221, 26);"
};

static const double displayUnitsCoeffs[5]{
    1,
    1000,
    1000000,
    0.1,
    0.001
};

static const char* biasMode[5] = {
    "CONSTANT_VOLTAGE_MODE",
    "CONSTANT_GAIN_MODE",
    "CONSTANT_OPT_PWR_MODE",
    "SIG_RMS_ADJUST_MODE",
    "OFF_MODE"
};


//static std::string currentColor;
// MAINWINDOW_H

