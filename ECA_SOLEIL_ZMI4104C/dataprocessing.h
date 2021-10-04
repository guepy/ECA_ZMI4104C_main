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
private:
    static SIS1100_Device_Struct* dev;
signals:
    void initBoardsDone();
    void initAxisComplete();
public slots:
    int getLEDsColor(int*);
    void updatePVT(int index, double* val);
    void updateOAS(int index, double* val);
    //void updateTime(double* time);
    void on_initBoardsRequest_recieved();
    void on_resetAxisRequest_recieved(int axis);
    void on_changeBiasModeRequest_recieved();
};

#endif // DATAPROCESSING_H
