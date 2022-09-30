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
#include "serialoutput.h"
#include "graphsform.h"
#include <string>
#include <memory>
#include <iostream>
#include <thread>
#include <array>
#include <algorithm>
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//using namespace std;
typedef std::unique_ptr<graphsForm> graphsFormPtr;
//QLibrary eca_soleil_zmi4104_lib("eca_soleil_zmi4104_lib");
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //virtual void paintEvent(QPaintEvent *event);
    /*------------Menu Bar settings----------------------------*/
    SettingsForm *settingsForm;
    //-------Bouton continuous acquisition----------------------
    FlyscanForm *flyscanForm;
    // --------Bouton set position offset-----------------------
    positionOffsetForm *posOffsetForm;
    // --------Bouton configure serial output --------------------------
    serialOutput *sdo;
    // --------Bouton configure serial output --------------------------
    CEsettingsForm *ces;
    //-------------plot graphs button --------------------------
    //graphsForm* customplotForm;
    // --------Bouton preset position --------------------------
    presetPositionForm *presPosForm;
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
    unsigned int ceVelMin, ceVelMax;
private:
    constexpr static const int barCoeff = 100;
    constexpr static const int optPwrMax = 20;
    constexpr static const int mixFreqMax = 1;
    constexpr static const int AXES_NBR = 4;
    constexpr static const int BIAS_MODE_CTR_MAX = 5;
    int currentLeftBlockUnits;
    int currentRightBlockUnits;
    unsigned int currentCECUnits;
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
    bool cecHarwareOn;
    unsigned int currentcecAxis;
    unsigned int currentAPDTempAxis;
    bool speedModeOn;
    bool speedAxisSelect[4];
    double* optPwrDC;
    double* scaledOptPwrDC;
    double* mxFreq{};
    double* Temp;
signals:
    void initCeParams(uint8_t axis);
    void sampFreqRequest();
    void fifoModeSignal(bool index);
    void stopContinuousScanSignal();
    void startGraph();
    void updateSettingsRequest(int a, int b, double* val);
    void closeFlyscanFormRequest();
    void closePositionOffsetFormRequest();
    void closePresetPositionFormRequest();
    void closeSettingsFormRequest();
    void closeCustomplotFormRequest();
    void initBoardsRequest();
    void scaleAxisRequest(int units);
    void resetAxisRequest(int axis);
    void changeBiasModeRequest(int index);
    void initAxisRequest();
    void settingsFormRun();
    void OffsetPosChanged(double* posOffPtr);
    void PresetPosChanged(double* PresPosPtr);
    void configureCEChardwareRequest(unsigned int axis, unsigned int ceVelMin, unsigned int ceVelMax);
    void stopCEChardwareRequest(unsigned int axis);
    void updateCECRatiosRequest(unsigned int axis, unsigned int index);
    void flyscanErrorCode(int ret_code);
    void flyscanStatValues(unsigned char* axisTab, double* mean, double* stdDev);
    void flyscanProcTerm();
    void ssiDataAvailable(unsigned int axis,double *ssiVals, double *optPwrVals);
    void ssiSquelchValues(unsigned int axis, unsigned int* val);
    void KpKvValues(unsigned int axis, int* coeff);
    void readGSEDataComplete(double * gseData);
    void initSettingsFormRequest();
    void apdValues(unsigned int axis, uint32_t* coeff);
    void gainControlsValues( unsigned int axis, bool* val);
    void updatePositionOnGraphs(double * position);
    void closeSdoRequest();
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
    // --------------serial output button---------------------------
    void openSdoForm();
    void closeSdoForm();
    void reopenSdoForm();
    // --------------ce settings menu button---------------------------
    void openCesForm();
    void closeCesForm();
    void reopenCesForm();
    //--------------Pot graphs button---------------------------------
    void openCustomplotForm();
    void closeCustomplotForm();
    void reopenCustomplotForm();
    void on_cecRatiosUpdated_recieved( CEratios* val);
    void refresh_screen();
private slots:
    void initBars();
    void setDisplayOutputString(std::string text, std::string col);
    void on_startSerialOutputRequest_recieved();
    void on_stopSerialOutputRequest_recieved();
    void on_errorSerialOutputRequest_recieved();
    void updateBiasMode();
    void updateAPDTemperature();
    void on_OffsetPos_Changed(double* OffPosPtr);
    void on_PresetPos_Changed(double* PresPosPtr);
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
    void initBoards(bool argin);
    void on_leftBlockUnits_currentIndexChanged(int index);
    void on_rightBlockUnits_currentIndexChanged(int index);
    void speedUpdateLeftBlockValue();
    void speedSelectLeftBlockValue(int index);
    void updateLeftBlockValue();
    void selectLeftBlockValue(int index);
    void updateRightBlockValue();
    void selectRightBlockValue(int index);
    void updateCECRatios();
    void on_pushButton_8_clicked();
    void processCecAxisClickedEvent(int axis, int* axisListIndex,QCheckBox* cecAxisCheckBox);
    void cecAxisClickedThreadEvent(int axis, int* axisListIndex, QCheckBox* cecAxisCheckBox);
    void on_resetButtonAllAxis_clicked();
    void on_ramDataFlyscanRequest_recieved(double freq,  double size, double time, unsigned int nbr);
    void on_fifoFlyscanRequest_recieved(double freq,  double size, double time, unsigned int nbr);
    void on_comboBox_3_currentIndexChanged(int index);
    void on_comboBox_4_currentIndexChanged(int index);
    void on_modifyBaseAddressRequest_received(unsigned int add);
    void on_comboBox_currentIndexChanged(int index);
    void on_stopContinuousScanSignal_received();
    void stopContinuousScanThread();
    void on_radioButton_clicked();
    void updateMixingFrequencyBar();
    void on_ceUnits_currentIndexChanged(int index);
    void updateOPtPwrBar();
    void on_radioButton_2_clicked();

    void on_cecAxis1_clicked();

    void on_cecAxis2_clicked();

    void on_cecAxis3_clicked();

    void on_cecAxis4_clicked();

    void on_ceDisplayAxis_currentIndexChanged(int index);

    void on_checkBox_clicked(bool checked);

    void on_enableAxis1_clicked(bool checked);

    void on_enableAxis2_clicked(bool checked);

    void on_enableAxis3_clicked(bool checked);

    void on_enableAxis4_clicked(bool checked);

    void on_biasModeAxis_currentIndexChanged(int index);
    void on_adpTempAxes_currentIndexChanged(int index);

    void on_buttonSerialOutput_clicked();

    void on_cecSettings_clicked();

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
static bool customplotForm_int=0;
// --------------serial output button---------------------------
static bool sdoForm_int=0;
// --------------ce seting menu button---------------------------
static bool cesForm_int=0;
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
    "OFF",//"OFF_MODE",
    "VOLT",//"CONSTANT_VOLTAGE_MODE",
    "GAIN",//"CONSTANT_GAIN_MODE",
    "OPWR",//"CONSTANT_OPT_PWR_MODE",
    "SRMS"//"SIG_RMS_ADJUST_MODE"
};


//static std::string currentColor;
// MAINWINDOW_H

