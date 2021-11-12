#include "dataprocessing.h"
//bool dataProcessing::accessToken=false;

unsigned int* dataProcessing::base_A24D32_ptr = new unsigned int;
unsigned int* dataProcessing::base_A24D32_FR_ptr = new unsigned int;
bool dataProcessing::precision37 = false;
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
    //qDebug()<<"Freeing buf 0x%p and 0x%p\n", base_A24D32_FR_ptr, base_A24D32_ptr;
    delete (base_A24D32_FR_ptr);
    delete (base_A24D32_ptr);
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

int dataProcessing::on_configureFlyscanRequest_recieved(){
    //*

    qDebug()<<"config ramdata started ";
    QTimer *Ltimer;
    Ltimer = new QTimer(this);
    connect(Ltimer, &QTimer::timeout, this, QOverload<>::of(&dataProcessing::on_acquisitionTimer_timeout));
    Ltimer->setInterval(flyscanTimeValue * 1e3);
    Ltimer->setSingleShot(true);
    qDebug()<<"time is "<<flyscanTimeValue * 1e3;
    dataProcessing::dev_mutex.lock();
    if (configureFlyscan(dev, axisNbr, flyscanFreqValue, 1) != RET_SUCCESS){
        return RET_FAILED;
        emit flyscanErrorCode(RET_FAILED);
        emit flyscanProcTerm();
    }
    dataProcessing::dev_mutex.unlock();
    Ltimer->start();
    return RET_SUCCESS;
}

int dataProcessing::on_acquisitionTimer_timeout(){

    dataProcessing::dev_mutex.lock();
    if(flyscanSizeValue<256){
        flyscanSizeValue=256;
        qDebug()<<"setting size to the min: 256";
        emit flyscanErrorCode(-101);
    }
    if(flyscanSizeValue>NBR_RAM_PAGES*256){
        flyscanSizeValue=NBR_RAM_PAGES*256;
        qDebug()<<"setting size to the max: "<< NBR_RAM_PAGES*256;
        emit flyscanErrorCode(-102);
    }
    if(flyscanSizeValue>NBR_RAM_PAGES*128 && axisNbr>2){
        flyscanSizeValue=NBR_RAM_PAGES*256;
        qDebug()<<"setting size to the max: "<< NBR_RAM_PAGES*128;
        emit flyscanErrorCode(-103);
    }
    if (stopAquisition(dev, axisNbr) != RET_SUCCESS){
        dataProcessing::dev_mutex.unlock();
        emit flyscanProcTerm();
        emit flyscanErrorCode(RET_FAILED);
        return RET_FAILED;
    }
    if (!(dataProcessing::base_A24D32_ptr = (PUINT)calloc((UINT)( sizeof (UINT)*(flyscanSizeValue*1.5*axisNbr)), sizeof(unsigned int)))){
        dataProcessing::dev_mutex.unlock();
        WARN("can not allocate memory on the host machine");
        emit flyscanErrorCode(RET_FAILED);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    if (!(dataProcessing::base_A24D32_FR_ptr = (PUINT)calloc((UINT)( sizeof (UINT)*flyscanSizeValue*1.5*axisNbr), sizeof(unsigned int)))){
        dataProcessing::dev_mutex.unlock();
        WARN("can not allocate memory on the host machine");
        emit flyscanErrorCode(RET_FAILED);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    unsigned int ramDataSize = flyscanSizeValue/256;
    if(axisNbr>2){
        ramDataSize = (flyscanSizeValue*2>16384)?flyscanSizeValue*2:16384;
    }

    INFO("Sampling data... \n");
    if (getFlyscanData(dev, base_A24D32_FR_ptr, base_A24D32_ptr, &axisNbr, ramDataSize) != RET_SUCCESS)
    {
        dataProcessing::dev_mutex.unlock();
        emit flyscanErrorCode(RET_FAILED);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    dataProcessing::dev_mutex.unlock();
    if (processRAMData(axisNbr, base_A24D32_FR_ptr, base_A24D32_ptr, ramDataSize, flyscanPath,(double*)meanVal, (double*)stdDevVal) != RET_SUCCESS)
    {
        emit flyscanErrorCode(RET_FAILED);
        emit flyscanProcTerm();
        return RET_FAILED;
    }

    qDebug()<<"flyscan data processing terminated";
    emit flyscanProcTerm();
    emit flyscanStatValues((unsigned char*)fifoFlyscanAxisTab,(double*)meanVal,(double*)stdDevVal);
    qDebug()<<"Freeing buf "<<base_A24D32_FR_ptr<<" and "<<base_A24D32_ptr;
    delete (base_A24D32_FR_ptr);
    delete (base_A24D32_ptr);
    emit flyscanErrorCode(RET_SUCCESS);
    return RET_SUCCESS;
}

int dataProcessing::on_configureFifoFlyscanRequest_recieved(){
    //*
    int ret_code=0;
    qDebug()<<"config fifo flyscan started ";
    fifoParam* flyscanFifoParam = new fifoParam;
    flyscanFifoParam->acqTime=flyscanTimeValue;
    flyscanFifoParam->freq=flyscanFreqValue;
    flyscanFifoParam->nbrPts=flyscanSizeValue;
    qDebug()<<"flyscansizeValue: "<<flyscanSizeValue;
    qDebug()<<"axisnbr in dataprocessing: "<<axisNbr;
    if (!(base_A24D32_ptr = (PUINT)calloc((UINT)(sizeof(UINT) * (flyscanSizeValue*1.5*axisNbr)), sizeof(unsigned int)))){
        WARN("can not allocate memory on the host machine");
        emit flyscanErrorCode(RET_FAILED);
        emit flyscanProcTerm();
        delete flyscanFifoParam;
        return RET_FAILED;
    }

    for(int h=0;h<4;h++){
        qDebug()<<"axistab "<<h<<" in dataprocessing: "<<(int)fifoFlyscanAxisTab[h];
    }
    dataProcessing::dev_mutex.lock();
    if (configureFifoFlyscan(dev, flyscanFifoParam,base_A24D32_ptr,(PUCHAR)fifoFlyscanAxisTab, &axisNbr, &ret_code) != RET_SUCCESS){
        dataProcessing::dev_mutex.unlock();
        qDebug()<<"fifo config failed";
        emit flyscanErrorCode(RET_FAILED);
        emit flyscanProcTerm();
        delete (base_A24D32_ptr);
        delete flyscanFifoParam;
        return RET_FAILED;
    }
    else
    {
        emit flyscanErrorCode(1); // currently processing
        dataProcessing::dev_mutex.unlock();
        if(ret_code==-100){
            qDebug()<<"overlapping detected";
            emit flyscanErrorCode(ret_code);
        }
        qDebug()<<"fifo config success";
        qDebug()<<"processing fifo data, axis number: "<<axisNbr;
        if (processFifoData(axisNbr, (PUCHAR)fifoFlyscanAxisTab, base_A24D32_ptr, flyscanFifoParam->nbrPts, (PUCHAR)flyscanPath,(double*)meanVal, (double*)stdDevVal) != RET_SUCCESS){
            dataProcessing::dev_mutex.unlock();
            emit flyscanErrorCode(RET_FAILED);
            emit flyscanProcTerm();
            delete (base_A24D32_ptr);
            delete flyscanFifoParam;
            return RET_FAILED;
        }
    }
    emit flyscanStatValues((unsigned char*)fifoFlyscanAxisTab,(double*)meanVal,(double*)stdDevVal);
    qDebug()<<"Freeing buf \n"<<  base_A24D32_ptr;
    delete (base_A24D32_ptr);
    delete flyscanFifoParam;
    emit flyscanErrorCode(RET_SUCCESS);
    emit flyscanProcTerm();
    return RET_SUCCESS;
}

void dataProcessing::on_updateSettingsRequest_recieved(int a, int b, int val){
    dataProcessing::dev_mutex.lock();
    switch (a) {
        case 1:
        switch (b) {
        case 2:
            if(val)
                EnableDoublePassInterferometer();
            else
                EnableSinglePassInterferometer();
            break;
        case 3:

            if(val)
                dataProcessing::precision37 = true;
            else
                dataProcessing::precision37 = false;
            break;
        case 4:

            if(val)
                EnableResetFindsVelocity_ForAllAxis(dev);
            else
                DisableResetFindsVelocity_ForAllAxis(dev);
            break;
        }
        break;
    }
    dataProcessing::dev_mutex.unlock();
}
