#include "dataprocessing.h"
//bool dataProcessing::accessToken=false;

unsigned int* dataProcessing::base_A24D32_ptr = new unsigned int;
unsigned int* dataProcessing::base_A24D32_FR_ptr = new unsigned int;
bool dataProcessing::precision37 = false;
bool dataProcessing::fifoMode=false;
bool dataProcessing::currentSerialOutputState = false;
Axes dataProcessing::curSerialBusAxis = Axes::Axis_3;
dataProcessing::dataProcessing(QObject *parent) : QObject(parent)
{
    position=(double*)malloc(5*sizeof (double));
    bias_mode = BIAS_MODE::BIAS_CONSTANT_GAIN_MODE;
    ledsErrorStatus = new bool[5];
    ledsStatus = new bool[5];
    cecRatiosVal = new CEratios;
    //initBoardsThread = new QThread;

}
/*
void dataProcessing::on_initBoardsRequest_recieved(){
    //qDebug()<<"init request recieve";
    initBoards();
}
*/
void dataProcessing::on_initBoardsRequest_recieved(){

    if(initSisBoards(0)!= RET_SUCCESS) {
        fprintf(stderr,"Failed to initialize SIS boards\n");
    }

    emit initAxisComplete();
    //qDebug()<<"initialization complete";
    emit initBoardsDone();
}

void dataProcessing::vmeSystemReset(){
    fprintf(stdout, "VME SYSTEM RESET!!!\n");
    if(initSisBoards(0)!= RET_SUCCESS) fprintf(stderr,"Failed to initialize SIS boards\n");
    //Sleep(10);
    if(initZmiBoards() != RET_SUCCESS) fprintf(stderr,"Failed to initialize ZMI board\n");
    //ui->pushButton_11->setEnabled(false);
    if(initAxis(  bias_mode) != RET_SUCCESS) fprintf(stderr,"Failed to initialize axis\n");
    enableDoublePassInterferometer();
    emit initAxisComplete();
    //qDebug()<<"initialization complete";
    emit initBoardsDone();

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
    State s;
    getSerialBusState(curSerialBusAxis, s);
    dataProcessing::currentSerialOutputState = static_cast<bool>(s);
    return 0;
}
void dataProcessing::updatePVT(int index, double* val, double* Temp){

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
    for (const auto& i : AXES){
        readApdTemp(i,Temp+(static_cast<int>(i)-1));
    }

}
void dataProcessing::updatePVT(int index, double* val, int ax){
    if(ax < 5){
        Axes axis = static_cast<Axes>(ax);
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

  else
    qDebug() << "bad axis number" << endl;

}
void dataProcessing::updateOAS(int index, double* val){
    switch(index){
        case 0:
            readOpticalPowerUsingSsiAvForAllAxis( val);
            //qDebug()<<"Reading Opt Power";
        break;
        case 1:
            readApdGainForAllAxis( val);
            //qDebug()<<"Reading APD gain";
        break;
        case 2:
            readScaledSsiAvForAllAxis( val);
            //qDebug()<<"Reading SSI values";
        break;
        case 3:
        {
            std::array<double,4> tmp{0.0};
            readOptPwrDCForAllAxis( tmp);
            for(int i=0; i < 4; i++){
                val[i] = tmp.at(i);
            }
        }
        break;
        default:
        break;
    }
    for (const auto& i : AXES){
        getBiasMode(i, biasModeTab.at(static_cast<int>(i)-1));
    }

}
/*
void dataProcessing::updateTime(double* time){
    ReadTime32_ForAllAxis( time);
}*/
void dataProcessing::on_changeBiasModeRequest_recieved(){
    bias_mode = static_cast<BIAS_MODE>(currentBiasMode);
    setBiasMode( static_cast<Axes>(currentBiasModeAxis+1), bias_mode);

    emit initAxisComplete();
}
void dataProcessing::on_resetAxisRequest_recieved(int axis){
    if(axis>4)
        for (const auto& i : AXES)
            resetAxis(i);
    else
        resetAxis(static_cast<Axes>(axis));
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
    for (const auto& i : AXES){
        setPositionOffset(  i, offPosPtr+static_cast<int>(i)-1);
    }
}

void dataProcessing::on_PresetPosition_Changed(double* presPosPtr){
    for (const auto& i : AXES)
       setPresetPosition(  i, (presPosPtr+static_cast<int>(i)-1));
}

int dataProcessing::updateCECRatios(unsigned int axis, unsigned int units){


    CEratios ceRatios;
    CECoeffs ceCoeffs;
    CEratioUnits ratioUnits= CEratioUnits::ratio_in_dB;

    ceRatios.CE0ratio = 0.0;
    ceRatios.CENratio = 0.0;
    ceRatios.measSignal = 0.0;
    ceCoeffs.CEC0coeff= std::complex<double>(0,0);
    ceCoeffs.CEC1coeff =0;
    ceCoeffs.CECNcoeff= std::complex<double>(0,0);
    switch (units) {
        case 0:
        ratioUnits = CEratioUnits::ratio_in_dB;
        break;
        case 1:
        ratioUnits = CEratioUnits::ratio_in_percent;
        break;
        case 2:
        ratioUnits = CEratioUnits::ratio_in_nmRMS;
        break;
        default:
        break;
    }
    //int ret = 0;

    if (readCalcCecoeffs( static_cast<Axes>(axis) , ceCoeffs) != RET_SUCCESS)
        {
            fprintf(stderr, "[WARNING]Failed to calculate CE ratios \n");
            return RET_FAILED;
        }
    qDebug()<<"CEC0coeff ,"<<ceCoeffs.CEC0coeff.real()<<"+ "<<ceCoeffs.CEC0coeff.imag()<<"i"<<" CEC1coeff "<<ceCoeffs.CEC1coeff<<"CECNcoeff "<<ceCoeffs.CECNcoeff.real()<<" + "<< ceCoeffs.CECNcoeff.imag()<<"i";
    fprintf(stdout, "CEC0coeff %f+i%f, CEC1coeff %f, CECNcoeff  %f+i%f\n", ceCoeffs.CEC0coeff.real(),
        ceCoeffs.CEC0coeff.imag(), ceCoeffs.CEC1coeff, ceCoeffs.CECNcoeff.real(), ceCoeffs.CECNcoeff.imag());
    if (calculateCeratio(   static_cast<Axes>(axis), ceRatios, ratioUnits) != RET_SUCCESS)
        {
            fprintf(stderr, "[WARNING]Failed to calculate CE ratios \n");
            return RET_FAILED;
        }
    fprintf(stdout, "Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
    memcpy(cecRatiosVal, &ceRatios, sizeof (CEratios));

   /* ceRatios.measSignal = 0;
    ceRatios.CE0ratio = 0;
    ceRatios.CENratio = 0;

    if(getAproximateCEratio(  3, &ceRatios, ratioUnits) != RET_SUCCESS)
        {
            fprintf(stderr, "[WARNING]Failed to calculate CE ratios \n");
            goto exit_flag;
        }
    fprintf(stdout, "Approximate Meas signal %f, CE0 Ratio %f, CEN Ratio %f \n", ceRatios.measSignal, ceRatios.CE0ratio, ceRatios.CENratio);
    */
    //*/
    //readCEerrorStatReg(  3, &ret);
    emit cecRatiosUpdated( cecRatiosVal);
    return RET_SUCCESS;
    //*/
}

int dataProcessing::on_configureCECHardware_recieved(unsigned int axis, unsigned int ceVelMin, unsigned int ceVelMax){


    //qDebug()<<"config started ";
    if(configureCecHardware( static_cast<Axes>(axis), ceVelMin, ceVelMax) != RET_SUCCESS)
        return RET_FAILED;

    //qDebug()<<"config terminated ";
    return RET_SUCCESS;
}
int dataProcessing::on_stopCECHardware_recieved(unsigned int axis){

    if (disableCecCompensation( static_cast<Axes>(axis)) != RET_SUCCESS)
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
    switch(axisNbr){
    case 1:
        fifoFlyscanAxisTab[0] = 3;
        fifoFlyscanAxisTab[1] = 0;
        fifoFlyscanAxisTab[2] = 0;
        fifoFlyscanAxisTab[3] = 0;
        break;
    case 2:
        fifoFlyscanAxisTab[0] = 1;
        fifoFlyscanAxisTab[1] = 3;
        fifoFlyscanAxisTab[2] = 0;
        fifoFlyscanAxisTab[3] = 0;
        break;
    default:
        fifoFlyscanAxisTab[0] = 1;
        fifoFlyscanAxisTab[1] = 2;
        fifoFlyscanAxisTab[2] = 3;
        fifoFlyscanAxisTab[3] = 4;
        break;
    }

    Ltimer->start();
    return RET_SUCCESS;
}

int dataProcessing::on_acquisitionTimer_timeout(){

    dataProcessing::dev_mutex.lock();
    static unsigned int ramDataSize;
    if(flyscanSizeValue<NBR_SAMP_PER_PAGE){
        flyscanSizeValue=NBR_SAMP_PER_PAGE;
        //qDebug()<<"setting size to the min: 256";
        emit flyscanErrorCode(-101);
    }
    if(flyscanSizeValue>NBR_RAM_PAGES*NBR_SAMP_PER_PAGE){
        flyscanSizeValue=NBR_RAM_PAGES*NBR_SAMP_PER_PAGE;
        //qDebug()<<"setting size to the max: "<< NBR_RAM_PAGES*256;
        emit flyscanErrorCode(-102);
    }
    if(flyscanSizeValue>(NBR_RAM_PAGES*NBR_SAMP_PER_PAGE/2) && axisNbr>2){
        flyscanSizeValue=(NBR_RAM_PAGES*NBR_SAMP_PER_PAGE)/2;
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

    ramDataSize = ceil(flyscanSizeValue/NBR_SAMP_PER_PAGE);
    if(axisNbr>2){
        //ramDataSize = (flyscanSizeValue*2>16384)?flyscanSizeValue*2:16384;
        ramDataSize = (ramDataSize*4 > NBR_RAM_PAGES)? NBR_RAM_PAGES : ramDataSize*4 ;
    }

    //*/
    if (!(base_A24D32_ptr = (PUINT)calloc(ramDataSize*NBR_SAMP_PER_PAGE, sizeof(unsigned int)))){
        dataProcessing::dev_mutex.unlock();
        Ltimer->stop();
        fprintf(stderr, "[WARNING]can not allocate memory on the host machine");
        emit flyscanErrorCode(-105);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    if (!(base_A24D32_FR_ptr = (PUINT)calloc(ramDataSize*NBR_SAMP_PER_PAGE, sizeof(unsigned int)))){
        dataProcessing::dev_mutex.unlock();
        Ltimer->stop();
        fprintf(stderr, "[WARNING]can not allocate memory on the host machine");
        emit flyscanErrorCode(-105);
        emit flyscanProcTerm();
        return RET_FAILED;
    }
    //*/

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
    qDebug()<<"flysacanaxis tab[0] is "<< (int)(*fifoFlyscanAxisTab)<<"mean val is"<<*meanVal<<" and stdDev val is "<<*stdDevVal;
    emit flyscanErrorCode(RET_SUCCESS);
    delete (base_A24D32_FR_ptr);
    delete (base_A24D32_ptr);

    Ltimer->stop();
    return RET_SUCCESS;
}

void dataProcessing::on_fifoModeSignal_recieved(bool index){
    fifoMode=index;
}
int dataProcessing::on_configureFifoFlyscanRequest_recieved(){
    //*
    int ret_code=1;
    bool ovf =0;
    size_t mysize=0;
    qDebug()<<"config fifo mode is "<<flyscanFreqValue;
    fifoParam flyscanFifoParam{};
    flyscanFifoParam.acqTime=flyscanTimeValue;
    flyscanFifoParam.freq=flyscanFreqValue;
    flyscanFifoParam.nbrPts=flyscanSizeValue;
    //qDebug()<<"flyscansizeValue: "<<flyscanSizeValue;
    //qDebug()<<"axisnbr in dataprocessing: "<<axisNbr;
    if(fifoMode){
        mysize = 0x10000000;//128Mo
}
    else{
        mysize = (UINT)(sizeof(UINT) * (flyscanSizeValue*1.5*axisNbr));
    }

    if (!(base_A24D32_ptr = (PUINT)calloc(mysize, sizeof(unsigned int)))){
        fprintf(stderr, "[WARNING]can not allocate memory on the host machine");
        emit flyscanErrorCode(-105);
        emit flyscanProcTerm();

        return RET_FAILED;
    }
    dataProcessing::dev_mutex.lock();
 ovf_flag:
    if (configureFifoFlyscan(flyscanFifoParam,base_A24D32_ptr,(PUCHAR)fifoFlyscanAxisTab, &axisNbr, &ret_code, fifoMode) != RET_SUCCESS){
        dataProcessing::dev_mutex.unlock();
        //qDebug()<<"fifo config failed";
        emit flyscanErrorCode(-99);
        emit flyscanProcTerm();
        delete (base_A24D32_ptr);

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
        if(ret_code==100){
            //qDebug()<<"overlapping detected";
            emit flyscanErrorCode(ret_code);
            ovf=1;
        }

        dataProcessing::dev_mutex.lock();
        if (processFifoData(axisNbr, (PUCHAR)fifoFlyscanAxisTab, base_A24D32_ptr, flyscanFifoParam.nbrPts, (const char*)flyscanPath,(double*)meanVal, (double*)stdDevVal) != RET_SUCCESS){
            dataProcessing::dev_mutex.unlock();
            emit flyscanErrorCode(-107);
            emit flyscanProcTerm();
            delete (base_A24D32_ptr);

            return RET_FAILED;
        }
        /*
        if(ovf){
            ovf=0;
            memset(base_A24D32_ptr, 0, mysize);
            goto ovf_flag;
        }
*/
        dataProcessing::dev_mutex.unlock();
    }
    emit flyscanStatValues((unsigned char*)fifoFlyscanAxisTab,(double*)meanVal,(double*)stdDevVal);
    //qDebug()<<"Freeing buf \n"<<  base_A24D32_ptr;
    delete (base_A24D32_ptr);

    emit flyscanErrorCode(RET_SUCCESS);
    emit flyscanProcTerm();
    return RET_SUCCESS;
}
void dataProcessing::on_updateSettingsRequest_received( unsigned int a,  unsigned int b, int* val){
    qDebug() << "APD SET CALLED val=" << *val << endl << endl;
    updateSettingsRequest(a,b,val);
   // std::thread updateSettingsRequestThread(&dataProcessing::updateSettingsRequest,this,a,b,val);
   // updateSettingsRequestThread.detach();
}
void dataProcessing::updateSettingsRequest( unsigned int a,  unsigned int b, int* val){
    //qDebug()<<"dataProcessing::updateSettingsRequest";
     unsigned int r=0, q=0;
    dataProcessing::dev_mutex.lock();
    switch ( a) {
    case 1:
        switch ( b) {
        case 1:
            setResetSourceClock(  static_cast<Axes>(3), static_cast<SCLK>(*val));
            break;
        case 2:
            if(*val == 0)
            enableSinglePassInterferometer();
            else if(*val == 1)
                enableDoublePassInterferometer();
            else
                enableQuadPassInterferometer();
            break;
        case 3:

            if(*val < 1){
                dataProcessing::precision37 = false;
            }
            else{
                dataProcessing::precision37 = true;
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
            setVMEBusSampleClk(static_cast<Axes>(3), static_cast<SCLK>(*val));
            break;
        case 6:
            setSamplingFrequency(Axes::Axis_3, (unsigned int)(val[0]), SCLK::SCLK0);
        break;
        default:
            r=( b-7)%3;
            q=( b-7)/3;
            switch (r) {
            case 0:
                if(* val < 1)
                    resetGainMinControl(static_cast<Axes>(q+1));
                else
                    setGainMinControl(static_cast<Axes>(q+1));
                break;
            case 1:
                if(* val < 1)
                    resetGainControlAgc(static_cast<Axes>(q+1));
                else
                    setGainControlAgc(static_cast<Axes>(q+1));
                break;
            case 2:
                if(* val < 1)
                    resetGainMaxControl(static_cast<Axes>(q+1));
                else
                    setGainMaxControl(static_cast<Axes>(q+1));
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
            qDebug() << "APD SET CALLED q=" << q << " , val=" << *val << endl << endl;
            setApdL2GainSet(static_cast<Axes>(q+1), (*val)/1000.0);
        case 1:
            setApdBiasVoltage(static_cast<Axes>(q+1), (*val)/1000.0);
            break;
        case 2:
            setApdL2SigRmsSet(static_cast<Axes>(q+1), (*val)/1000.0);
            break;
        case 3:
            setApdL2OptPwrSet(static_cast<Axes>(q+1), (*val)/1000.0);
            break;
        case 4:
            setApdL2SigRmsMinLim(static_cast<Axes>(q+1), (*val)/1000.0);
            break;
        case 5:
            setApdL2SigRmsMaxLim(static_cast<Axes>(q+1), (*val)/1000.0);
            break;
            break;
        }
    case 3:
        if ( b>=4) {
            setSsiSquelch(static_cast<Axes>(b-3),* val);
        }
        else{
            setKpAndKvCoeff(static_cast<Axes>(b+1), val[0], val[1] );
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
            for(const auto& axis: AXES){
                readSsiCalibrationData(axis, (double*)ssiVals, (double*)optPwrVals);
                emit ssiDataAvailable(static_cast<int>(axis), (double*)ssiVals, (double*)optPwrVals);
            }
            break;
        case 4:
            setSsiSquelch(static_cast<Axes>((int)( val[0])),  val[1]);
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
    initSettingsFormRequest();
    /*
   std::thread initSettingsFormRequestThread(&dataProcessing::initSettingsFormRequest,this);
   initSettingsFormRequestThread.detach();
   */
}

void dataProcessing::initSettingsFormRequest(){
    //qDebug()<<"initSettingsFormRequestThread started";
    dataProcessing::dev_mutex.lock();
    for(const auto& axis: AXES){
        //qDebug()<<"axis "<<axis;
        getSsiSquelch(axis,ssiSq);
        emit ssiSquelchValues(static_cast<int>(axis), ssiSq);
        //qDebug()<<"ssisq= "<<ssiSq[0];
        getKpAndKvCoeff(axis, kpKvcoeff);
        emit KpKvValues(static_cast<int>(axis), kpKvcoeff);
        getApdL2GainSet(axis, gain);
        getApdBiasVoltage(axis, gain+1);
        getApdL2SigRmsSet(axis, gain+2);
        getApdL2OptPwrSet(axis, gain+3);
        getApdL2SigRmsMinLim(axis, gain+4);
        getApdL2SigRmsMaxLim(axis, gain+5);
        emit apdValues(static_cast<int>(axis), gain);
        getGainMinControl(axis,gainControls);
        getGainMaxControl(axis,gainControls+1);
        getGainControlAgc(axis,gainControls+2);
        emit gainControlsValues(static_cast<int>(axis),gainControls);
        getBiasMode(axis, biasModeTab.at(static_cast<int>(axis)-1));
        //qDebug()<<"Gain min state on axis "<<axis<<" is "<<*gainControls;
        //qDebug()<<"Gain max state on axis "<<axis<<" is "<<gainControls[1];
    }
    getSamplingFrequency(Axes::Axis_3, nullptr);
    dataProcessing::dev_mutex.unlock();
    prop[0] = getInterferometerConfiguration()-1;
    prop[1] = static_cast<bool>(getCachedSampleSclk());
    prop[2] = static_cast<bool>(getCachedResetSclk());
    curPrecision = getPrecision();
    prop[3] = curPrecision;
    State s;
    getSerialBusState(curSerialBusAxis, s);
    prop[4] = static_cast<bool>(s);
    emit currentIntBoardProperties(prop, getCachedSamplingFrequency());
}
void dataProcessing::on_modifyBaseAddressRequest_received(unsigned int add){
    //qDebug()<<"on_setBaseAddressRequest_received";
    setBaseAddress(add);
}
void dataProcessing::on_sampFreqRequest_received(){
    emit sampFreq(getCachedSamplingFrequency());
}
void dataProcessing::on_stopContinuousScanSignal_received(){

    stopAquisition(3);
}

void dataProcessing::on_configureSerialOutput_received(SCLK clk, SerialOutputDriver sdo, SerialDataPositionSize sdps, BitWindow bw, uint32_t sampFreq ){

    dataProcessing::dev_mutex.lock();
    if(configureSerialBus(curSerialBusAxis, clk, sdo, sdps, bw, sampFreq))
        emit  errorSerialOutputRequest();
    dataProcessing::dev_mutex.unlock();
}

void dataProcessing::on_startSerialOutput_received(){

    if(startSerialBus(curSerialBusAxis))
        emit  errorSerialOutputRequest();
    else
        emit startSerialOutputRequest();
}

void dataProcessing::on_stopSerialOutput_received(){
    if(stopSerialBus(curSerialBusAxis))
        emit  errorSerialOutputRequest();
    else
        emit stopSerialOutputRequest();
}

void dataProcessing::on_initCeParams_received(uint8_t a){
    CECoeffs coeffs;
    CECoeffBoundaries ce0b{}, cenb{};
    CECLimits lim;
    double tmp;
    Axes axis = static_cast<Axes>(a);
    std::array<std::complex<double>,14> arr{0.0};
    getUserSuppliedCoeffs(axis, coeffs);
    arr.at(0) = coeffs.CEC0coeff;
    arr.at(1).real(coeffs.CEC1coeff);
    arr.at(2) = coeffs.CECNcoeff;
    getCEMinVel(axis, tmp);
    arr.at(3).real(tmp);
    getCEMaxVel(axis, tmp);
    arr.at(4).real(tmp);
    getCELimts(axis, lim);
    arr.at(5).real(lim.CEC0Limit);
    arr.at(6).real(lim.CECNLimit);
    readCalcCecoeffs(axis, coeffs);
    arr.at(7) = coeffs.CEC0coeff;
    arr.at(8).real(coeffs.CEC1coeff);
    arr.at(9) = coeffs.CECNcoeff;
    readCecoefBoundaries(axis, ce0b, cenb);
    arr.at(10) = ce0b.CEMincoeff;
    arr.at(11) = ce0b.CEMaxcoeff;
    arr.at(12) = cenb.CEMincoeff;
    arr.at(13) = cenb.CEMaxcoeff;
    emit ceParams(arr);
}

void dataProcessing::on_updateCeParams_received(uint8_t axis, int i,std::vector<std::complex<double>> params){
    CECoeffs coeffs;
    switch(i){
    case 0:
        coeffs.CEC0coeff = params.at(0);
        coeffs.CEC1coeff = params.at(1).real();
        coeffs.CECNcoeff = params.at(2);
        setUserSuppliedCoeffs(static_cast<Axes>(axis), coeffs);
        break;
    case 3:
        setCEMinVel(static_cast<Axes>(axis),params.at(0).real());
        break;
    case 4:
        setCEMaxVel(static_cast<Axes>(axis),params.at(0).real());
        break;
    case 5:
        setCE0Limit(static_cast<Axes>(axis),params.at(0).real());
        break;
    case 6:
        setCENLimit(static_cast<Axes>(axis),params.at(0).real());
        break;
    default:
        break;
    }
}

void dataProcessing::on_enableUsc_received(uint8_t a,bool b){
    Axes axis = static_cast<Axes>(a);
    if(b){
        enableCeuserSuppliedCoef(axis);
    }
    else{
        disableCeuserSuppliedCoef(axis);
    }
}
void dataProcessing::on_enableUscStartup_received(uint8_t a,bool b){
    Axes axis = static_cast<Axes>(a);
    if(b){
        enableCeuserSuppliedCoefAtStartup(axis);
    }
    else{
        disableCeuserSuppliedCoefAtStartup(axis);
    }
}
