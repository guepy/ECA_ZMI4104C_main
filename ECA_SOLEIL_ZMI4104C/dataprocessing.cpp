#include "dataprocessing.h"

//bool dataProcessing::accessToken=false;

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
    {

    initAxis(dev, bias_mode);
    }

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

void dataProcessing::on_OffsetPosition_Changed(double* offPosPtr){
    for(int i=0;i<4;i++){
        SetPositionOffset32(dev, i+1, (unsigned int)(offPosPtr[i]/positionScale));
    }
}

void dataProcessing::on_PresetPosition_Changed(double* presPosPtr){
    for(int i=0;i<4;i++){
        SetPresetPosition32(dev, i+1, (unsigned int)(presPosPtr[i]/positionScale));
    }
}

int dataProcessing::updateCECRatios(unsigned int axis, CEratios* val, unsigned int index){


    CEratios ceRatios = { 0.0,0.0,0.0 };
    CECoeffs ceCoeffs = { {0,0},0.0,{0,0} };
    CEratioUnits ratioUnits= ratio_in_dB;

    switch (index) {
        case 0:
        ratioUnits = ratio_in_dB;
        break;
        case 1:
        ratioUnits = ratio_in_percent;
        break;
        case 2:
        ratioUnits = ratio_in_nmRMS;
        break;
        default:
        break;
    }
    //int ret = 0;

    if (readCalcCECoeffs(dev, axis, &ceCoeffs) != RET_SUCCESS)
        {
            WARN("Failed to calculate CE ratios \n");
            return RET_FAILED;
        }
    INFO("CEC0coeff %f+i%f, CEC1coeff %f, CECNcoeff  %f+i%f\n", ceCoeffs.CEC0coeff.rpart,
        ceCoeffs.CEC0coeff.ipart, ceCoeffs.CEC1coeff, ceCoeffs.CECNcoeff.rpart, ceCoeffs.CECNcoeff.ipart);
    if (calculateCEratio(dev, axis, &ceRatios, ratioUnits) != RET_SUCCESS)
        {
            WARN("Failed to calculate CE ratios \n");
            return RET_FAILED;
        }
    INFO("Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
    *val = ceRatios;

   /* ceRatios.measSignal = 0;
    ceRatios.CE0ratio = 0;
    ceRatios.CENratio = 0;

    if(getAproximateCEratio(dev, 3, &ceRatios, ratioUnits) != RET_SUCCESS)
        {
            WARN("Failed to calculate CE ratios \n");
            goto exit_flag;
        }
    INFO("Approximate Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
    */
    //*/
    //readCEerrorStatReg(dev, 3, &ret);
    return RET_SUCCESS;
    //*/
}

int dataProcessing::on_configureCECHardware_recieved(unsigned int axis, unsigned int ceVelMin, unsigned int ceVelMax){


    qDebug()<<"config started ";
    if(configureCEChardware(dev, axis, ceVelMin, ceVelMax) != RET_SUCCESS)
        return RET_FAILED;


    qDebug()<<"config terminated ";
    return RET_SUCCESS;
}
int dataProcessing::on_stopCECHardware_recieved(unsigned int axis){

    if (disableCECcompensation(dev, axis) != RET_SUCCESS)
        return RET_FAILED;

    return RET_SUCCESS;
}
