#include "dataprocessing.h"
//bool dataProcessing::accessToken=false;

unsigned int* dataProcessing::base_A24D32_ptr = new unsigned int;
unsigned int* dataProcessing::base_A24D32_FR_ptr = new unsigned int;
bool dataProcessing::precision37 = false;
bool dataProcessing::fifoMode=false;
dataProcessing::dataProcessing(QObject *parent) : QObject(parent)
{
    position=(double*)malloc(5*sizeof (double));
    bias_mode = BIAS_CONSTANT_VOLT_MODE;
    ledsErrorStatus = new bool[5];
    ledsStatus = new bool[5];
    setBaseAddress(0x16000);
    //initBoardsThread = new QThread;

}
/*
void dataProcessing::on_initBoardsRequest_recieved(){
    //qDebug()<<"init request recieve";
    initBoards();
}
*/
void dataProcessing::on_initBoardsRequest_recieved(){

    //qDebug()<<"initializing boards";

    //SIS1100W_STATUS stat = sis1100w_Get_Handle_And_Open(0 , dev); //
    /*/
    if(initSisBoards( )!= RET_SUCCESS) {
        fatal("Failed to initialize SIS boards\n");
    }
    //*/
    vmeSystemReset();
    /*if (stat != Stat1100Success) {
        qDebug()<<"Getting Sis handle failed";
        info("Getting Sis handle failed\n");
        warn("Reinitializing VME System \n");
        vmeSystemReset();
    }*/
    emit initAxisComplete();
    //qDebug()<<"initialization complete";
    emit initBoardsDone();
}
void dataProcessing::vmeSystemReset(){
    info("VME SYSTEM RESET!!!\n");
    if(initSisBoards( )!= RET_SUCCESS) fatal("Failed to initialize SIS boards\n");
    //Sleep(10);
    if(initZmiBoards( ) != RET_SUCCESS) fatal("Failed to initialize ZMI board\n");
    //ui->pushButton_11->setEnabled(false);
    if(initAxis(  bias_mode) != RET_SUCCESS) fatal("Failed to initialize axis\n");
    enableDoublePassInterferometer();

}
int dataProcessing::getLEDsColor(int* ledsColor){
    //qDebug()<<"running refreshLEDsStatus()";

    getLedsErrorStatus( ledsErrorStatus);
    //qDebug()<<ledsErrorStatus;
    getLedsStatus( ledsStatus);

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
                readPositionForAllAxis( val);
        break;
        case 1:
              readVelocityForAllAxis( val);
        break;
        case 2:
            readTimeForAllAxis( val);
        break;
        default:
        break;
    }

}
void dataProcessing::updatePVT(int index, double* val, int axis){


    switch(index){
        case 0:
                readPosition(axis, val);

        break;
        case 1:
              readVelocity(axis, val);
        break;
        case 2:
            readTime(axis, val);
        break;
        default:
        break;
    }

}
void dataProcessing::updateOAS(int index, double* val){


    switch(index){
        case 0:
            readOpticalPowerUsingSsiAv( val);
            //qDebug()<<"Reading Opt Power";
        break;
        case 1:
            readApdGainForAllAxis( val);
            //qDebug()<<"Reading APD gain";
        break;
        case 2:
            readScaledSsiAv( val);
            //qDebug()<<"Reading SSI values";
        break;
        default:
        break;
    }

}
/*
void dataProcessing::updateTime(double* time){
    ReadTime32_ForAllAxis( time);
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

    initAxis(  bias_mode);
    }

    emit initAxisComplete();
}
void dataProcessing::on_resetAxisRequest_recieved(int axis){
    if(axis>4)
        for(int i=1; i<5;i++)
            resetAxis(  i);
    else
        resetAxis(  axis);
}
dataProcessing::~dataProcessing()
{
    //qDebug()<<"Freeing buf 0x%p and 0x%p\n", base_A24D32_FR_ptr, base_A24D32_ptr;
    //delete (base_A24D32_FR_ptr);
    //delete (base_A24D32_ptr);
    dataProcessing::dev_mutex.lock();
    dataProcessing::dev_mutex.unlock();
}

void dataProcessing::on_OffsetPosition_Changed(double* offPosPtr){
    for(int i=0;i<4;i++){
        if(dataProcessing::precision37)
        setPositionOffset32(  i+1, (unsigned int)(offPosPtr[i]/positionScale));
    }
}

void dataProcessing::on_PresetPosition_Changed(double* presPosPtr){
    for(int i=0;i<4;i++){
        if(dataProcessing::precision37)
            setPresetPosition37(  i+1, (presPosPtr[i]/positionScale));
        else
            setPresetPosition32(  i+1,(presPosPtr[i]/positionScale));
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

    if (readCalcCecoeffs(  axis, &ceCoeffs) != RET_SUCCESS)
        {
            warn("Failed to calculate CE ratios \n");
            return RET_FAILED;
        }
    info("CEC0coeff %f+i%f, CEC1coeff %f, CECNcoeff  %f+i%f\n", ceCoeffs.CEC0coeff.rpart,
        ceCoeffs.CEC0coeff.ipart, ceCoeffs.CEC1coeff, ceCoeffs.CECNcoeff.rpart, ceCoeffs.CECNcoeff.ipart);
    if (calculateCeratio(  axis, &ceRatios, ratioUnits) != RET_SUCCESS)
        {
            warn("Failed to calculate CE ratios \n");
            return RET_FAILED;
        }
    info("Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
    *val = ceRatios;

   /* ceRatios.measSignal = 0;
    ceRatios.CE0ratio = 0;
    ceRatios.CENratio = 0;

    if(getAproximateCEratio(  3, &ceRatios, ratioUnits) != RET_SUCCESS)
        {
            warn("Failed to calculate CE ratios \n");
            goto exit_flag;
        }
    info("Approximate Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
    */
    //*/
    //readCEerrorStatReg(  3, &ret);
    return RET_SUCCESS;
    //*/
}

int dataProcessing::on_configureCECHardware_recieved(unsigned int axis, unsigned int ceVelMin, unsigned int ceVelMax){


    //qDebug()<<"config started ";
    if(configureCecHardware(  axis, ceVelMin, ceVelMax) != RET_SUCCESS)
        return RET_FAILED;

    //qDebug()<<"config terminated ";
    return RET_SUCCESS;
}
int dataProcessing::on_stopCECHardware_recieved(unsigned int axis){

    if (disableCecCompensation(  axis) != RET_SUCCESS)
        return RET_FAILED;

    return RET_SUCCESS;
}

int dataProcessing::on_configureFlyscanRequest_recieved(){
    //*

    //qDebug()<<"config ramdata started ";
    Ltimer = new QTimer(this);
    connect(Ltimer, &QTimer::timeout, this, QOverload<>::of(&dataProcessing::on_acquisitionTimer_timeout));
    Ltimer->setInterval(flyscanTimeValue * 1e3);
    Ltimer->setSingleShot(true);
    //qDebug()<<"time is "<<flyscanTimeValue * 1e3;
    dataProcessing::dev_mutex.lock();
    if (configureFlyscan(  axisNbr, flyscanFreqValue, 1) != RET_SUCCESS){
        dataProcessing::dev_mutex.unlock();
        emit flyscanErrorCode(-99);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    dataProcessing::dev_mutex.unlock();
    Ltimer->start();
    return RET_SUCCESS;
}

int dataProcessing::on_acquisitionTimer_timeout(){

    dataProcessing::dev_mutex.lock();
    if(flyscanSizeValue<256){
        flyscanSizeValue=256;
        //qDebug()<<"setting size to the min: 256";
        emit flyscanErrorCode(-101);
    }
    if(flyscanSizeValue>NBR_RAM_PAGES*256){
        flyscanSizeValue=NBR_RAM_PAGES*256;
        //qDebug()<<"setting size to the max: "<< NBR_RAM_PAGES*256;
        emit flyscanErrorCode(-102);
    }
    if(flyscanSizeValue>NBR_RAM_PAGES*128 && axisNbr>2){
        flyscanSizeValue=NBR_RAM_PAGES*256;
        //qDebug()<<"setting size to the max: "<< NBR_RAM_PAGES*128;
        emit flyscanErrorCode(-103);
    }
    if (stopAquisition( axisNbr) != RET_SUCCESS){
        dataProcessing::dev_mutex.unlock();
        Ltimer->stop();
        emit flyscanProcTerm();
        emit flyscanErrorCode(-104);
        return RET_FAILED;
    }
    //*/
    if (!(dataProcessing::base_A24D32_ptr = (PUINT)calloc((UINT)( sizeof (UINT)*(flyscanSizeValue*1.5*axisNbr)), sizeof(unsigned int)))){
        dataProcessing::dev_mutex.unlock();
        Ltimer->stop();
        warn("can not allocate memory on the host machine");
        emit flyscanErrorCode(-105);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    if (!(dataProcessing::base_A24D32_FR_ptr = (PUINT)calloc((UINT)( sizeof (UINT)*flyscanSizeValue*1.5*axisNbr), sizeof(unsigned int)))){
        dataProcessing::dev_mutex.unlock();
        Ltimer->stop();
        warn("can not allocate memory on the host machine");
        emit flyscanErrorCode(-105);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    //*/
    unsigned int ramDataSize = flyscanSizeValue/256;
    if(axisNbr>2){
        ramDataSize = (flyscanSizeValue*2>16384)?flyscanSizeValue*2:16384;
    }

    info("Sampling data... \n");
    if (getFlyscanData(  base_A24D32_FR_ptr, base_A24D32_ptr, &axisNbr, ramDataSize) != RET_SUCCESS)
    {
        dataProcessing::dev_mutex.unlock();
        Ltimer->stop();
        emit flyscanErrorCode(-106);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    dataProcessing::dev_mutex.unlock();
    if (processRamData(axisNbr, base_A24D32_FR_ptr, base_A24D32_ptr, ramDataSize, flyscanPath,(double*)meanVal, (double*)stdDevVal) != RET_SUCCESS)
    {
        Ltimer->stop();
        emit flyscanErrorCode(-107);
        emit flyscanProcTerm();
        return RET_FAILED;
    }

    //qDebug()<<"flyscan data processing terminated";
    emit flyscanProcTerm();
    emit flyscanStatValues((unsigned char*)fifoFlyscanAxisTab,(double*)meanVal,(double*)stdDevVal);
    //qDebug()<<"Freeing buf "<<base_A24D32_FR_ptr<<" and "<<base_A24D32_ptr;
    delete (base_A24D32_FR_ptr);
    delete (base_A24D32_ptr);
    emit flyscanErrorCode(RET_SUCCESS);
    Ltimer->stop();
    return RET_SUCCESS;
}

void dataProcessing::on_fifoModeSignal_recieved(bool index){
    fifoMode=index;
}
int dataProcessing::on_configureFifoFlyscanRequest_recieved(){
    //*
    int ret_code=0;
    unsigned int mysize=0;
    qDebug()<<"config fifo mode is "<<flyscanFreqValue;
    fifoParam* flyscanFifoParam = new fifoParam;
    flyscanFifoParam->acqTime=flyscanTimeValue;
    flyscanFifoParam->freq=flyscanFreqValue;
    flyscanFifoParam->nbrPts=flyscanSizeValue;
    //qDebug()<<"flyscansizeValue: "<<flyscanSizeValue;
    //qDebug()<<"axisnbr in dataprocessing: "<<axisNbr;
    if(fifoMode){
        mysize = 1300000;
}
    else{
        mysize = (UINT)(sizeof(UINT) * (flyscanSizeValue*1.5*axisNbr));
    }

    if (!(base_A24D32_ptr = (PUINT)calloc(mysize, sizeof(unsigned int)))){
        warn("can not allocate memory on the host machine");
        emit flyscanErrorCode(-105);
        emit flyscanProcTerm();
        delete flyscanFifoParam;
        return RET_FAILED;
    }
    dataProcessing::dev_mutex.lock();
    if (configureFifoFlyscan(  flyscanFifoParam,base_A24D32_ptr,(PUCHAR)fifoFlyscanAxisTab, &axisNbr, &ret_code, fifoMode) != RET_SUCCESS){
        dataProcessing::dev_mutex.unlock();
        //qDebug()<<"fifo config failed";
        emit flyscanErrorCode(-99);
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
            //qDebug()<<"overlapping detected";
            emit flyscanErrorCode(ret_code);
        }
        //qDebug()<<"fifo config success";
        //qDebug()<<"processing fifo data, axis number: "<<axisNbr;

        dataProcessing::dev_mutex.lock();
        if (processFifoData(axisNbr, (PUCHAR)fifoFlyscanAxisTab, base_A24D32_ptr, flyscanFifoParam->nbrPts, (PUCHAR)flyscanPath,(double*)meanVal, (double*)stdDevVal) != RET_SUCCESS){
            dataProcessing::dev_mutex.unlock();
            emit flyscanErrorCode(-107);
            emit flyscanProcTerm();
            delete (base_A24D32_ptr);
            delete flyscanFifoParam;
            return RET_FAILED;
        }

        dataProcessing::dev_mutex.unlock();
    }
    emit flyscanStatValues((unsigned char*)fifoFlyscanAxisTab,(double*)meanVal,(double*)stdDevVal);
    //qDebug()<<"Freeing buf \n"<<  base_A24D32_ptr;
    delete (base_A24D32_ptr);
    delete flyscanFifoParam;
    emit flyscanErrorCode(RET_SUCCESS);
    emit flyscanProcTerm();
    return RET_SUCCESS;
}
void dataProcessing::on_updateSettingsRequest_received( unsigned int a,  unsigned int b, int* val){
    std::thread updateSettingsRequestThread(&dataProcessing::updateSettingsRequest,this,a,b,val);
    updateSettingsRequestThread.detach();
}
void dataProcessing::updateSettingsRequest( unsigned int a,  unsigned int b, int* val){
    //qDebug()<<"dataProcessing::updateSettingsRequest";
     unsigned int r=0, q=0;
    dataProcessing::dev_mutex.lock();
    switch ( a) {
    case 1:
        switch ( b) {
        case 1:
            setResetSourceClock(  3, (unsigned int*) val);
            break;
        case 2:
            if(* val)
                enableDoublePassInterferometer();
            else
                enableSinglePassInterferometer();
            break;
        case 3:

            if(* val < 1){
                dataProcessing::precision37 = true;
            }
            else{
                dataProcessing::precision37 = false;
            }
            setPrecision(dataProcessing::precision37);
            break;
        case 4:

            if(* val > 0)
                enableResetFindsVelocityForAllAxis( );
            else
                disableResetFindsVelocityForAllAxis( );
            break;
        case 5:
            setSampleSourceClock(  3, (unsigned int*) val);
            break;
        case 6:
            setSamplingFrequency((unsigned int)(val[0]));
        break;
        default:
            r=( b-7)%3;
            q=( b-7)/3;
            switch (r) {
            case 0:
                if(* val < 1)
                    resetGainMinControl(q+1);
                else
                    setGainMinControl(q+1);
                break;
            case 1:
                if(* val < 1)
                    resetGainControlAgc(q+1);
                else
                    setGainControlAgc(q+1);
                break;
            case 2:
                if(* val < 1)
                    resetGainMaxControl(q+1);
                else
                    setGainMaxControl(q+1);
                break;
            }
        break;
        }
    break;
    case 2:
        r= b%4;
        q= b/4;
        switch (r) {
        case 0:
            setApdL2Gain(q+1, * val);
        case 1:
            setApdBiasDac(q+1, * val);
            break;
        case 2:
            setApdL2SigRms(q+1, * val);
            break;
        case 3:
            setApdL2OptPwr(q+1, * val);
            break;
        }
        break;
    case 3:
        if ( b>=4) {
            setSsiSquelch( b-3,* val);
        }
        else{
            setKpAndKvCoeff(   b+1, val[0], val[1] );
        }
        break;
    case 4:
        switch ( b) {
        case 1:
            /*for(int axis=1;axis<5;axis++)
                EnableGlitchFilter(  axis, *val);
                */
            break;
        case 5:
            //qDebug()<<"updateSettingsRequest(4,5) received";
            for(int axis=1;axis<5;axis++){
                readSsiCalibrationData(  axis, (double*)ssiVals, (double*)optPwrVals);
                emit ssiDataAvailable(axis, (double*)ssiVals, (double*)optPwrVals);
            }
            break;
        case 4:
            setSsiSquelch((int)( val[0]),  val[1]);
            break;
        default:
            //qDebug()<<"Unknow value of b: "<< b;
            break;
        }
        break;
    case 5:
        readGseDataForAllAxis(gseData, gseData+4, gseData+8,gseData+12);
        emit readGSEDataComplete(gseData);
    break;
}
    dataProcessing::dev_mutex.unlock();
}
void dataProcessing::on_initSettingsFormRequest_received(){
   std::thread initSettingsFormRequestThread(&dataProcessing::initSettingsFormRequest,this);
   initSettingsFormRequestThread.detach();
}

void dataProcessing::initSettingsFormRequest(){
    //qDebug()<<"initSettingsFormRequestThread started";
    dataProcessing::dev_mutex.lock();
    for(int axis=1; axis<5; axis++){
        //qDebug()<<"axis "<<axis;
        getSsiSquelch(axis,ssiSq);
        emit ssiSquelchValues(axis, ssiSq);
        //qDebug()<<"ssisq= "<<ssiSq[0];
        getKpAndKvCoeff(axis, kpKvcoeff);
        emit KpKvValues(axis, kpKvcoeff);
        getApdL2Gain(axis, gain);
        getApdBiasDac(axis, gain+1);
        getApdL2SigRms(axis, gain+2);
        getApdL2OptPwr(axis, gain+3);
        emit apdValues(axis, gain);
        getGainMinControl(axis,gainControls);
        getGainMaxControl(axis,gainControls+1);
        getGainControlAgc(axis,gainControls+2);
        emit gainControlsValues(axis,gainControls);
        //qDebug()<<"Gain min state on axis "<<axis<<" is "<<*gainControls;
        //qDebug()<<"Gain max state on axis "<<axis<<" is "<<gainControls[1];
    }
    getSamplingFrequency(nullptr);
    dataProcessing::dev_mutex.unlock();
    prop[0] = getCurrentInterType()-1;
    prop[1] = getSampleSclk();
    prop[2] = getResetSclk();
    emit currentIntBoardProperties(prop, getSampFreq());
    //qDebug()<<"dataProcessing::apdval0"<<getCurrentInterType()<<"apdval1"<<prop[0]<<"apdval2"<<prop[2]<<"apdval3"<<getSampFreq();
    //qDebug()<<"initSettingsFormRequestThread done";
}
void dataProcessing::on_modifyBaseAddressRequest_received(unsigned int add){
    //qDebug()<<"on_setBaseAddressRequest_received";
    setBaseAddress(add);
}

void dataProcessing::on_stopContinuousScanSignal_received(){

    qDebug()<<"OK 3";
    stopAquisition(3);
    qDebug()<<"OK 4";
}
