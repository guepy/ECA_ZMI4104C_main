#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

#include <QTimer>
#include <thread>

#define TIMEOUT_VAL 100//100ms
namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT
    QTimer *stimer;
    int precisionValueIndex_cur=0;
    int intTypeIndex_cur=0;
    int precisionValueIndex_prev=0;
    int intTypeIndex_prev=0;
    int resetFindVelocityIndex_cur=0;
    int resetFindVelocityIndex_prev=5;
    bool updateAv=false;
    int* updateTable;

    double prevApdBiasDac[4] = {0};
    double curApdBiasDac[4] = {0};
    double curApdGainL2Set[4] = {0};
    double prevApdGainL2Set[4] = {0};
    double curApdOptPwrL2Set[4] = {0};
    double prevApdOptPwrL2Set[4] = {0};
    double prevApdSigRmsL2Set[4] = {0};
    double curApdSigRmsL2Set[4] = {0};
    double curApdSigRmsL2MaxLim[4] = {0};
    double prevApdSigRmsL2MaxLim[4] = {0};
    double curApdSigRmsL2MinLim[4] = {0};
    double prevApdSigRmsL2MinLim[4] = {0};

    int curKpFilterCoeff[4] = {0};
    int prevKpFilterCoeff[4] = {0};
    int curKvFilterCoeff[4] = {0};
    int prevKvFilterCoeff[4] = {0};

    int curSSIsquelch[4] = {0};
    int prevSSIsquelch[4] = {0};

    int curGainMinControl[4] = {0};
    int prevGainMinControl [4] = {0};
    int curGainMaxControl [4] = {0};
    int prevGainMaxControl [4] = {0};
    int curAutoAdjustGainMode [4] = {0};
    int prevAutoAdjustGainMode [4] = {0};
    int val[10];

    bool prevInterferoType = 0;
    bool prevPrecision = 0;
    bool prevResetFindVelocity = 0;
    char curInterferoType = 0;
    std::string basAd;
    bool curPrecision = 0;
    bool curResetFindVelocity = 0;
    bool curSampleSCLK = 0;
    bool prevSampleSCLK = 0;
    bool curResetSCLK = 0;
    bool prevResetSCLK = 0;
    unsigned int curSampleFreq = 0;
    unsigned int prevSampleFreq = 0;
    bool baseAdChange=true;
public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();
    void closeForm();
    void refreshSettings();
    void on_ssiDataAvailable_received(unsigned int axis,double *ssiVals, double *optPwrVals);
    void on_ssiSquelchValues_received(unsigned int axis, unsigned int* val);
    void on_KpKvValues_received(unsigned int axis, int* val);
    void on_apdValues_received(unsigned int axis, double* val);
    void on_readGSEDataComplete_received(double* gseData);
    void on_gainControlsValues_received( unsigned int axis, bool* val);
    void on_currentIntBoardProperties_received(bool* val,unsigned int sampFreq);// bool*=[intType, sampleSclk, resetSclk]
    void on_settingsFormRun_received();
signals:
    void closeThis();
    void modifyBaseAddressRequest(unsigned int add);
    void updateSettingsRequest(int a, int b, int* val);
    void initSettingsFormRequest();
private slots:
    void on_pushButton_5_clicked();
    void updateBaseAddress();
    void updateApdSettings();
    unsigned int convertHex2Uint(std::string hex);
    //void on_comboBox_currentIndexChanged(int index);
    void updateGeneralSettings();
    void on_interType_currentIndexChanged(int index);
    void on_precisionVal_currentIndexChanged(int index);
    void gainControlsValuesFunc( unsigned int axis, bool* val);

    void on_resetFindVel_currentIndexChanged(int index);

    //void on_pushButton_10_clicked();

    void on_pushButton_17_clicked();

    void on_agcControl_currentIndexChanged(int index);
    void on_agcControl_2_currentIndexChanged(int index);
    void on_agcControl_4_currentIndexChanged(int index);
    void on_agcControl_3_currentIndexChanged(int index);

    void on_gainMinControl_currentIndexChanged(int index);
    void on_gainMinControl_2_currentIndexChanged(int index);
    void on_gainMinControl_3_currentIndexChanged(int index);
    void on_gainMinControl_4_currentIndexChanged(int index);

    void on_gainMaxControl_currentIndexChanged(int index);
    void on_gainMaxControl_2_currentIndexChanged(int index);
    void on_gainMaxControl_3_currentIndexChanged(int index);
    void on_gainMaxControl_4_currentIndexChanged(int index);

    void ssiDataAvailableFunc(unsigned int axis,double *ssiVals, double *optPwrVals);
    void on_StartButton_clicked();
    void on_ssiSquelch_1_valueChanged(int arg1);
    void on_ssiSquelch_2_valueChanged(int arg1);
    void on_ssiSquelch_3_valueChanged(int arg1);
    void on_ssiSquelch_4_valueChanged(int arg1);
    void updateDiagnosticsData();
    void updateEEPROMData();
    void updateCalibrationData();
    void on_sampleSCLK_currentIndexChanged(int index);


    //void on_enableGlitchFilterButton_clicked();

    void on_kpFilterCoeff_valueChanged(int arg1);
    void on_kpFilterCoeff_2_valueChanged(int arg1);
    void on_kpFilterCoeff_3_valueChanged(int arg1);
    void on_kpFilterCoeff_4_valueChanged(int arg1);

    void on_kvFilterCoeff_valueChanged(int arg1);
    void on_kvFilterCoeff_2_valueChanged(int arg1);
    void on_kvFilterCoeff_3_valueChanged(int arg1);
    void on_kvFilterCoeff_4_valueChanged(int arg1);

    void on_apdBiasDac_valueChanged(double arg1);
    void on_apdGainL2SetVal_valueChanged(double arg1);
    void on_apdSigRmsL2Set_valueChanged(double arg1);
    void on_apdOptPwrL2Set_valueChanged(double arg1);

    void on_apdBiasDac_2_valueChanged(double arg1);
    void on_apdGainL2SetVal_2_valueChanged(double arg1);
    void on_apdSigRmsL2Set_2_valueChanged(double arg1);
    void on_apdOptPwrL2Set_2_valueChanged(double arg1);

    void on_apdBiasDac_3_valueChanged(double arg1);
    void on_apdGainL2SetVal_3_valueChanged(double arg1);
    void on_apdSigRmsL2Set_3_valueChanged(double arg1);
    void on_apdOptPwrL2Set_3_valueChanged(double arg1);

    void on_apdBiasDac_4_valueChanged(double arg1);
    void on_apdGainL2SetVal_4_valueChanged(double arg1);
    void on_apdSigRmsL2Set_4_valueChanged(double arg1);
    void on_apdOptPwrL2Set_4_valueChanged(double arg1);

    void on_baseAdressInput_textChanged(const QString &arg1);

    void on_resetSCLK_currentIndexChanged(int index);

    void on_sampFreq_valueChanged(int arg1);

    void on_sigRmsL2MaxLim_1_valueChanged(double arg1);

    void on_sigRmsL2MaxLim_2_valueChanged(double arg1);

    void on_sigRmsL2MaxLim_4_valueChanged(double arg1);

    void on_sigRmsL2MaxLim_3_valueChanged(double arg1);

    void on_sigRmsL2MinLim_1_valueChanged(double arg1);

    void on_sigRmsL2MinLim_2_valueChanged(double arg1);

    void on_sigRmsL2MinLim_3_valueChanged(double arg1);

    void on_sigRmsL2MinLim_4_valueChanged(double arg1);

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
