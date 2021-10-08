#ifndef DATAPROCESSING_H
#define DATAPROCESSING_H

#include <QObject>
#include <QPainter>
#include <QDebug>
#include "../eca_soleil_zmi4104_lib/eca_soleil_zmi4104c.h"
#include <QThread>

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
    static std::mutex dev_mutex;
private:
    static SIS1100_Device_Struct* dev;
    //static bool accessToken;
signals:
    void initBoardsDone();
    void initAxisComplete();
    void cecConfigComplete();
public slots:
    int getLEDsColor(int*);
    void updatePVT(int index, double* val);
    void updateOAS(int index, double* val);
    int updateCECRatios(unsigned int axis,CEratios* val, unsigned int index);
    //void updateTime(double* time);
    void on_initBoardsRequest_recieved();
    void on_resetAxisRequest_recieved(int axis);
    int on_configureCECHardware_recieved(unsigned int axis, unsigned int ceVelMin, unsigned int ceVelMax);
    int on_stopCECHardware_recieved(unsigned int axis);
    void on_changeBiasModeRequest_recieved();
    void on_OffsetPosition_Changed(double* offPosPtr);
    void on_PresetPosition_Changed(double* presPosPtr);
};

#endif // DATAPROCESSING_H
