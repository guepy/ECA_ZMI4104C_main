#include "dataprocessing.h"

dataProcessing::dataProcessing(QObject *parent) : QObject(parent)
{
    position=(double*)malloc(5*sizeof (double));
    bias_mode = BIAS_CONSTANT_VOLT_MODE;
    modifyBaseAddress(0x16000);
    ledsErrorStatus = new bool[5];
    ledsStatus = new bool[5];
    //initBoardsThread = new QThread;
}
/*
void dataProcessing::on_initBoardsRequest_recieved(){
    qDebug()<<"init request recieve";
    initBoards();
}
*/
void dataProcessing::on_initBoardsRequest_recieved(){
    qDebug()<<"initializing boards";
    INFO("Qt app just started!!!\n");
    if(initSISboards(dev)!= RET_SUCCESS) FATAL("Failed to initialize SIS boards\n");
    //Sleep(10);
    if(initZMIboards(dev) != RET_SUCCESS) FATAL("Failed to initialize ZMI board\n");
    //ui->pushButton_11->setEnabled(false);
    if(initAxis(dev, bias_mode) != RET_SUCCESS) FATAL("Failed to initialize axis\n");
    emit initAxisComplete();
    EnableDoublePassInterferometer();
    qDebug()<<"initialization complete";
    emit initBoardsDone();
}

int dataProcessing::getLEDsColor(int* ledsColor){
    qDebug()<<"running refreshLEDsStatus()";
    getLEDsErrorStatus(dev,ledsErrorStatus);
    //qDebug()<<ledsErrorStatus;
    getLEDsStatus(dev,ledsStatus);
    //qDebug()<<*ledsStatus;
    for (int ledi=0;ledi<5 ;ledi++ ) {
       if(ledsStatus[ledi]){
            if(ledsErrorStatus[ledi]){
                ledsColor[ledi] =2;//"yellow";
            }
            else
                ledsColor[ledi] = 1;//"rgb(37, 255, 81)";
       }
            else
                ledsColor[ledi] = 0;//"black";

}
    return 0;
}
void dataProcessing::updatePVT(int index, double* val){
    switch(index){
        case 0:
            ReadSamplePosition32_ForAllAxis(dev,val);
        break;
        case 1:
            ReadVelocity32_ForAllAxis(dev,val);
        break;
        case 2:
            ReadTime32_ForAllAxis(dev,val);
        break;
        default:
        break;
    }

}
void dataProcessing::updateOAS(int index, double* val){
    switch(index){
        case 0:
            ReadOpticalPowerUsingSSIav(dev,val);
            qDebug()<<"Reading Opt Power";
        break;
        case 1:
            ReadAPDGain_ForAllAxis(dev,val);
            qDebug()<<"Reading APD gain";
        break;
        case 2:
            ReadScaledSSIav(dev,val);
            qDebug()<<"Reading SSI values";
        break;
        default:
        break;
    }

}
/*
void dataProcessing::updateTime(double* time){
    ReadTime32_ForAllAxis(dev,time);
}*/
void dataProcessing::on_changeBiasModeRequest_recieved(){
    switch (currentBiasMode) {
        case 0:
        bias_mode = BIAS_CONSTANT_VOLT_MODE;
        break;
        case 1:
        bias_mode = BIAS_CONSTANT_GAIN_MODE;
        break;
        case 2:
        bias_mode = BIAS_CONSTANT_OPT_PWR_MODE;
        break;
        case 3:
        bias_mode = BIAS_SIG_RMS_ADJUST_MODE;
        break;
        case 4:
        bias_mode = BIAS_OFF_MODE;
        break;
        default:
        break;

    }
    initAxis(dev, bias_mode);
    emit initAxisComplete();
}
void dataProcessing::on_resetAxisRequest_recieved(int axis){
    if(axis>4)
        for(int i=1; i<5;i++)
            ResetAxis(dev, i);
    else
        ResetAxis(dev, axis);
}
dataProcessing::~dataProcessing()
{

}
