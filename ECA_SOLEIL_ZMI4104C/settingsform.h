#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

#include <QTimer>
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

    double prevApdBiasDac[4] = {0,0,0,0};
    double curApdBiasDac[4] = {0,0,0,0};
    double curApdGainL2Set[4] = {0,0,0,0};
    double prevApdGainL2Set[4] = {0,0,0,0};
    double curApdOptPwrL2Set[4] = {0,0,0,0};
    double prevApdOptPwrL2Set[4] = {0,0,0,0};
    double prevApdSigRmsL2Set[4] = {0,0,0,0};
    double curApdSigRmsL2Set[4] = {0,0,0,0};

    double curKpFilterCoeff[4] = {0,0,0,0};
    double prevKpFilterCoeff[4] = {0,0,0,0};
    double curKvFilterCoeff[4] = {0,0,0,0};
    double prevKvFilterCoeff[4] = {0,0,0,0};

    double curSSIsquelch[4] = {0,0,0,0};
    double prevSSIsquelch[4] = {0,0,0,0};

    int curGainMinControl[4] = {0,0,0,0};
    int prevGainMinControl [4] = {0,0,0,0};
    int curGainMaxControl [4] = {0,0,0,0};
    int prevGainMaxControl [4] = {0,0,0,0};
    int curAutoAdjustGainMode [4] = {0,0,0,0};
    int prevAutoAdjustGainMode [4] = {0,0,0,0};
    double val[10];

    double prevInterferoType = 0;
    double prevPrecision = 0;
    double prevResetFindVelocity = 0;
    double prevClockType = 0;
    double prevFreq = 0;
    double curInterferoType = 0;
    double curPrecision = 0;
    double curResetFindVelocity = 0;
    double curClockType = 0;
    double curFreq = 0;
public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();
    void closeForm();
    void refreshSettings();
    void on_ssiDataAvailable_received(unsigned int axis,double *ssiVals, double *optPwrVals);
    void on_ssiSquelchValues_received(uint8_t axis, double* val);
    void on_KpKvValues_received(uint8_t axis, uint16_t* val);
    void on_apdValues_received(uint8_t axis, uint32_t* val);
    void on_readGSEDataComplete_received(double* gseData);
signals:
    void closeThis();
    void modifyBaseAddressRequest(unsigned int);
    void updateSettingsRequest(int a, int b, double* val);
    void initSettingsFormRequest();
private slots:
    void on_pushButton_5_clicked();
    void updateApdSettings();
    //void on_comboBox_currentIndexChanged(int index);
    void updateGeneralSettings();
    void on_interType_currentIndexChanged(int index);
    void on_precisionVal_currentIndexChanged(int index);

    void on_resetFindVel_currentIndexChanged(int index);

    //void on_pushButton_10_clicked();

    void on_pushButton_17_clicked();

    void on_comboBox_9_currentIndexChanged(int index);
    void on_comboBox_10_currentIndexChanged(int index);
    void on_comboBox_4_currentIndexChanged(int index);
    void on_comboBox_7_currentIndexChanged(int index);

    void on_comboBox_11_currentIndexChanged(int index);
    void on_comboBox_12_currentIndexChanged(int index);
    void on_comboBox_5_currentIndexChanged(int index);
    void on_comboBox_8_currentIndexChanged(int index);

    void on_comboBox_13_currentIndexChanged(int index);
    void on_comboBox_14_currentIndexChanged(int index);
    void on_comboBox_6_currentIndexChanged(int index);
    void on_comboBox_15_currentIndexChanged(int index);

    void on_StartButton_clicked();
    void on_spinBox_6_valueChanged(int arg1);
    void on_spinBox_5_valueChanged(int arg1);
    void on_spinBox_3_valueChanged(int arg1);
    void on_spinBox_7_valueChanged(int arg1);
    void updateDiagnosticsData();
    void updateEEPROMData();
    void updateCalibrationData();
    void on_comboBox_currentIndexChanged(int index);

    void on_spinBox_4_valueChanged(int arg1);


    //void on_enableGlitchFilterButton_clicked();

    void on_kpFilterCoeff_valueChanged(int arg1);
    void on_kpFilterCoeff_2_valueChanged(int arg1);
    void on_kpFilterCoeff_3_valueChanged(int arg1);
    void on_kpFilterCoeff_4_valueChanged(int arg1);

    void on_kvFilterCoeff_valueChanged(int arg1);
    void on_kvFilterCoeff_2_valueChanged(int arg1);
    void on_kvFilterCoeff_3_valueChanged(int arg1);
    void on_kvFilterCoeff_4_valueChanged(int arg1);

    void on_apdBiasDac_valueChanged(int arg1);
    void on_apdGainL2SetVal_valueChanged(int arg1);
    void on_apdSigRmsL2Set_valueChanged(int arg1);
    void on_apdOptPwrL2Set_valueChanged(int arg1);

    void on_apdBiasDac_2_valueChanged(int arg1);
    void on_apdGainL2SetVal_2_valueChanged(int arg1);
    void on_apdSigRmsL2Set_2_valueChanged(int arg1);
    void on_apdOptPwrL2Set_2_valueChanged(int arg1);

    void on_apdBiasDac_3_valueChanged(int arg1);
    void on_apdGainL2SetVal_3_valueChanged(int arg1);
    void on_apdSigRmsL2Set_3_valueChanged(int arg1);
    void on_apdOptPwrL2Set_3_valueChanged(int arg1);

    void on_apdBiasDac_4_valueChanged(int arg1);
    void on_apdGainL2SetVal_4_valueChanged(int arg1);
    void on_apdSigRmsL2Set_4_valueChanged(int arg1);
    void on_apdOptPwrL2Set_4_valueChanged(int arg1);

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
