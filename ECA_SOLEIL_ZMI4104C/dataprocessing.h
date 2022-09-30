#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <QObject>
#include <QPainter>
#include <QDebug>
#include "../eca_soleil_zmi4104_lib/eca_soleil_zmi4104c.h"
#include <QThread>
#include <QTimer>
#include <cmath>
#include <thread>
static bool *ledsErrorStatus,*ledsStatus;

class dataProcessing : public QObject
{
    Q_OBJECT
public:
    explicit dataProcessing(QObject *parent = nullptr);
    ~dataProcessing();
    BIAS_MODE bias_mode;
    double* position;
    //QThread     *initBoardsThread;
    static int currentBiasMode;
    static int currentBiasModeAxis;
    static bool currentSerialOutputState;
    static Axes curSerialBusAxis;
    static std::mutex dev_mutex;
    static std::array<BIAS_MODE,4> biasModeTab;

    double flyscanFreqValue=0.0;
    double  flyscanTimeValue=0.0;
    double flyscanSizeValue=0.0;
    char fifoFlyscanAxisTab[4]={0};
    unsigned int axisNbr=0;
    char flyscanPath[1026];
    static unsigned int * base_A24D32_ptr;
    static unsigned int * base_A24D32_FR_ptr;
    double meanVal[4]={0.0};
    double stdDevVal[4]={0.0};
    static bool precision37;
    double gseData[16]={0.0};
    double ssiVals[3]={0.0},optPwrVals[3]={0.0};
    int kpKvcoeff[2]={0,0};
    unsigned int ssiSq[4]={0};
    double gain[6]={0};
    bool gainControls[3]={0};//Min|Max|AGC
    bool prop[5]={0};
    static bool fifoMode;
    CEratios* cecRatiosVal;
    QTimer *Ltimer;
private:
    static SIS1100_Device_Struct* dev;
    //static bool accessToken;
signals:
    void ceParams(std::array<std::complex<double>, 14> params);
    void initBoardsDone();
    void initAxisComplete();
    void cecConfigComplete();
    void flyscanProcTerm();
    void flyscanErrorCode(int err_code);
    void flyscanStatValues(unsigned char* axisTab, double* mean, double* stdDev);
    void ssiDataAvailable(unsigned int axis,double *ssiVals, double *optPwrVals);
    void readGSEDataComplete(double * gseData);
    void updateSettingsRequest_completed( unsigned int a,  unsigned int b, double* val);
    void ssiSquelchValues( unsigned int axis, unsigned int* val);
    void KpKvValues( unsigned int axis, int* coeff);
    void apdValues( unsigned int axis, double* coeff);
    void gainControlsValues( unsigned int axis, bool* val);
    void currentIntBoardProperties(bool* val, unsigned int sampFreq);// bool*=[intType, sampleSclk, resetSclk]
    void cecRatiosUpdated(CEratios* val);
    void startSerialOutputRequest();
    void stopSerialOutputRequest();
    void errorSerialOutputRequest();
    void sampFreq(uint32_t freq);
public slots:
    void on_enableUsc_received(uint8_t a,bool b);
    void on_enableUscStartup_received(uint8_t a,bool b);
    void on_initCeParams_received(uint8_t axis);
    void on_updateCeParams_received(uint8_t axis, int i,std::vector<std::complex<double>> params);
    void on_sampFreqRequest_received();
    void on_fifoModeSignal_recieved(bool index);
    void on_stopContinuousScanSignal_received();
    void on_updateSettingsRequest_received( unsigned int a,  unsigned int b, int* val);
    void updateSettingsRequest( unsigned int a,  unsigned int b, int* val);
    void on_initSettingsFormRequest_received();
    int  getLEDsColor(int*);
    void updatePVT(int index, double* val, double* Temp);
    void updatePVT(int index, double* val, int axis);
    //void updateMF(std::array<double,4>&);
    void initSettingsFormRequest();
    void updateOAS(int index, double* val);
    int updateCECRatios(unsigned int axis,unsigned int units);
    int on_acquisitionTimer_timeout();
    //void updateTime(double* time);
    void on_initBoardsRequest_recieved();
    void on_resetAxisRequest_recieved(int axis);
    int  on_configureCECHardware_recieved(unsigned int axis, unsigned int ceVelMin, unsigned int ceVelMax);
    int  on_stopCECHardware_recieved(unsigned int axis);
    void on_changeBiasModeRequest_recieved();
    int  on_configureFlyscanRequest_recieved();
    int  on_configureFifoFlyscanRequest_recieved();
    void on_OffsetPosition_Changed(double* offPosPtr);
    void on_PresetPosition_Changed(double* presPosPtr);
    void vmeSystemReset();
    void on_modifyBaseAddressRequest_received(unsigned int add);

    void on_configureSerialOutput_received(SCLK clk, SerialOutputDriver sdo, SerialDataPositionSize sdps, BitWindow bw, uint32_t sampFreq);
    void on_startSerialOutput_received();
    void on_stopSerialOutput_received();


};

#endif // DATAPROCESSING_H
