#include "settingsform.h"
#include "ui_settingsform.h"
#include <QDebug>
SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    updateTable = (int*)calloc(10, sizeof(int));
    ui->baseAdressInput->setValidator(new QRegExpValidator(QRegExp("^[0-9A-F]{1,7}$", Qt::CaseInsensitive), ui->baseAdressInput));
    ui->baseAdressInput->setText(QString::number(16000));

    ui->apdGainL2SetVal->setMinimum(0);//min freq
    ui->apdGainL2SetVal->setMaximum(5120);//max freq
    ui->apdSigRmsL2Set->setMinimum(0);//min freq
    ui->apdSigRmsL2Set->setMaximum(0xFFFF);//min freq
    ui->apdBiasDac->setMinimum(0);//min freq
    ui->apdBiasDac->setMaximum(0xFFFF);//min freq
    ui->apdOptPwrL2Set->setMinimum(-3920);//min freq
    ui->apdOptPwrL2Set->setMaximum(3402);//max freq

    ui->apdGainL2SetVal_2->setMinimum(0);//min freq
    ui->apdGainL2SetVal_2->setMaximum(5120);//max freq
    ui->apdSigRmsL2Set_2->setMinimum(0);//min freq
    ui->apdSigRmsL2Set_2->setMaximum(0xFFFF);//min freq
    ui->apdBiasDac_2->setMinimum(0);//min freq
    ui->apdBiasDac_2->setMaximum(0xFFFF);//min freq
    ui->apdOptPwrL2Set_2->setMinimum(-3920);//min freq
    ui->apdOptPwrL2Set_2->setMaximum(3402);//max freq

    ui->apdGainL2SetVal_3->setMinimum(0);//min freq
    ui->apdGainL2SetVal_3->setMaximum(5120);//max freq
    ui->apdSigRmsL2Set_3->setMinimum(0);//min freq
    ui->apdSigRmsL2Set_3->setMaximum(0xFFFF);//min freq
    ui->apdBiasDac_3->setMinimum(0);//min freq
    ui->apdBiasDac_3->setMaximum(0xFFFF);//min freq
    ui->apdOptPwrL2Set_3->setMinimum(-3920);//min freq
    ui->apdOptPwrL2Set_3->setMaximum(3402);//max freq

    ui->apdGainL2SetVal_4->setMinimum(0);//min freq
    ui->apdGainL2SetVal_4->setMaximum(5120);//max freq
    ui->apdSigRmsL2Set_4->setMinimum(0);//min freq
    ui->apdSigRmsL2Set_4->setMaximum(0xFFFF);//min freq
    ui->apdBiasDac_4->setMinimum(0);//min freq
    ui->apdBiasDac_4->setMaximum(0xFFFF);//min freq
    ui->apdOptPwrL2Set_4->setMinimum(-3920);//min freq
    ui->apdOptPwrL2Set_4->setMaximum(3402);//max freq

    ui->kpFilterCoeff->setMinimum(-9);
    ui->kpFilterCoeff->setMaximum(-2);
    ui->kvFilterCoeff->setMaximum(-7);
    ui->kvFilterCoeff->setMinimum(-21);

    ui->kpFilterCoeff_2->setMinimum(-9);
    ui->kpFilterCoeff_2->setMaximum(-2);
    ui->kvFilterCoeff_2->setMaximum(-7);
    ui->kvFilterCoeff_2->setMinimum(-21);

    ui->kpFilterCoeff_3->setMinimum(-9);
    ui->kpFilterCoeff_3->setMaximum(-2);
    ui->kvFilterCoeff_3->setMaximum(-7);
    ui->kvFilterCoeff_3->setMinimum(-21);

    ui->kpFilterCoeff_4->setMinimum(-9);
    ui->kpFilterCoeff_4->setMaximum(-2);
    ui->kvFilterCoeff_4->setMaximum(-7);
    ui->kvFilterCoeff_4->setMinimum(-21);

    ui->ssiSquelch_1->setMaximum(0x3FF);
    ui->ssiSquelch_1->setMinimum(0);
    ui->ssiSquelch_2->setMaximum(0x3FF);
    ui->ssiSquelch_2->setMinimum(0);
    ui->ssiSquelch_3->setMaximum(0x3FF);
    ui->ssiSquelch_3->setMinimum(0);
    ui->ssiSquelch_4->setMaximum(0x3FF);
    ui->ssiSquelch_4->setMinimum(0);


    ui->sampFreq->setMaximum(2e7);
    ui->sampFreq->setMinimum(0);
    //*
    //ui->apdBiasDac->setEnabled(false);
    stimer = new QTimer(this);
    connect(stimer, &QTimer::timeout, this, QOverload<>::of(&SettingsForm::refreshSettings));

}

SettingsForm::~SettingsForm()
{
    stimer->stop();
    delete stimer;
    delete ui;
}
void SettingsForm::on_settingsFormRun_received(){

    emit initSettingsFormRequest();
    updateEEPROMData();
    updateDiagnosticsData();
    stimer->start(TIMEOUT_VAL);
}
void SettingsForm::refreshSettings(){

    stimer->stop();
    qDebug()<<"settings timer timeout";
//*/
    updateEEPROMData();
    updateDiagnosticsData();
    stimer->start(TIMEOUT_VAL);
//*/
}
//-----Button cancel-------
void SettingsForm::on_pushButton_5_clicked()
{
    closeForm();
}
void SettingsForm::closeForm(){
    emit closeThis();
    qDebug()<<"Close this emitted";
    this->deleteLater();
}

unsigned int SettingsForm::convertHex2Uint(std::string hex) {
    qDebug()<<"Conversion from Hex to unsigned int...\n";
    unsigned int a=0,s=0;
    int i=0;
    // check if hex < 16
    s=hex.size();
    if(s==0) return 0;
    if(s<2) return ((unsigned int)hex[0] - (int)'0');
    for (i = 1; i < (int)(s); i++) {
        if (hex[i] != '0') break;
    }
    //if (i == s) return (unsigned int)hex[0];
    for (i = s-1; i>=0; i--) {
        if (hex[i] == '0') continue;
        if (hex[i] > '9') {
            a += ((unsigned int)hex[i] - 55) * (unsigned int)pow(16, s-1-i);
        }
        else {
            a += ((unsigned int)hex[i] - (int)'0') * (unsigned int)pow(16, s-1-i);
        }
    }
    return a;
}
void SettingsForm::on_StartButton_clicked()
{
    qDebug()<<"on_StartButton_clicked ";
    //*
    updateGeneralSettings();
    updateApdSettings();
    updateCalibrationData();
    updateBaseAddress();
    //*/
}

void SettingsForm::on_currentIntBoardProperties_received(bool* val, unsigned int sampFreq){// bool*=[intType, sampleSclk, resetSclk]
    curInterferoType = val[0];
    prevInterferoType = val[0];
    qDebug()<<"curInterferoType is "<<curInterferoType;
    ui->interType->setCurrentIndex(curInterferoType);

    curSampleSCLK = val[1];
    prevSampleSCLK = val[1];
    ui->sampleSCLK->setCurrentIndex(val[1]);

    curSampleSCLK = val[1];
    prevSampleSCLK = val[1];
    ui->resetSCLK->setCurrentIndex(val[2]);

    curSampleFreq = val[1];
    prevSampleFreq = val[1];
    ui->sampFreq->setValue(sampFreq);
}
void SettingsForm::updateGeneralSettings(){

    if(curInterferoType != prevInterferoType){
        val[0]=(curInterferoType)?1:0;
        emit updateSettingsRequest(1,2,val);
        prevInterferoType= curInterferoType;
    }
    if(curPrecision != prevPrecision){
        val[0]=(curPrecision)?1:0;
        emit updateSettingsRequest(1,3,val );
        prevPrecision= curPrecision;
    }
    if(curResetFindVelocity != prevResetFindVelocity){
        val[0]=(curResetFindVelocity)?1:0;
        emit updateSettingsRequest(1,4,val );
        prevResetFindVelocity= curResetFindVelocity;
    }
    if(curSampleSCLK != prevSampleSCLK){
        val[0]=(curSampleSCLK)?1:0;
        emit updateSettingsRequest(1,5, val);
        prevSampleSCLK = curSampleSCLK;
    }
    if(curResetSCLK != prevResetSCLK){
        val[0]=(curResetSCLK)?1:0;
        emit updateSettingsRequest(1,1,val);
        prevResetSCLK = curResetSCLK;
    }
    if(curSampleFreq != prevSampleFreq){
        val[0]=curSampleFreq;
        emit updateSettingsRequest(1,6, val);
        prevSampleFreq = curSampleFreq;
    }

    for(int i=0; i<4; i++){
        if(curGainMinControl[i] != prevGainMinControl[i]){
            val[0]=(curGainMinControl[i])?1:0;
            emit updateSettingsRequest(1,7+3*i,val);
            prevGainMinControl[i] = curGainMinControl[i];
        }
        if(curAutoAdjustGainMode[i] != prevAutoAdjustGainMode[i]){
            val[0]=(curAutoAdjustGainMode[i])?1:0;
            emit updateSettingsRequest(1,7+3*i+1,val);
            prevAutoAdjustGainMode[i] = curAutoAdjustGainMode[i];
        }
        if(curGainMaxControl[i] != prevGainMaxControl[i]){
            val[0]=(curGainMaxControl[i])?1:0;
            emit updateSettingsRequest(1,7+3*i+2,val);
            prevGainMaxControl[i] = curGainMaxControl[i];
        }
    }


}
void SettingsForm::on_interType_currentIndexChanged(int index)
{
    curInterferoType=index;
    //emit updateSettingsRequest(1,2,&i);
}


void SettingsForm::on_precisionVal_currentIndexChanged(int index)
{
    curPrecision = index;
    //emit updateSettingsRequest(1,3,&i);

    /*
    precisionValueIndex_cur=index;
    if(precisionValueIndex_cur != precisionValueIndex_prev){
        updateAv =true;
        updateTable[0]=10*intTypeIndex_cur+2;
        //intTypeIndex_prev = intTypeIndex_cur;
    }
    else{
        updateAv = false;
        updateTable[0]=0;
    }
   */
}


void SettingsForm::on_resetFindVel_currentIndexChanged(int index)
{
    curResetFindVelocity = index;
    //emit updateSettingsRequest(1,4,&i);
}

/*------------------Clock settings-----------------------------*/
void SettingsForm::on_sampleSCLK_currentIndexChanged(int index)
{
    curSampleSCLK=index;
   //emit updateSettingsRequest(1,5, &curClockType);
}

/*------------------digital filter-----------------------------*/

void SettingsForm::on_kpFilterCoeff_valueChanged(int arg1)
{
    curKpFilterCoeff[0] = arg1;
    //emit updateSettingsRequest(1,8, val);
}

void SettingsForm::on_kpFilterCoeff_2_valueChanged(int arg1)
{
    curKpFilterCoeff[1] = arg1;
    //emit updateSettingsRequest(1,8, val);
}


void SettingsForm::on_kpFilterCoeff_3_valueChanged(int arg1)
{
    curKpFilterCoeff[2] = arg1;
    //emit updateSettingsRequest(1,8, val);
}


void SettingsForm::on_kpFilterCoeff_4_valueChanged(int arg1)
{
    curKpFilterCoeff[3] = arg1;
    //emit updateSettingsRequest(1,8, val);
}



void SettingsForm::on_kvFilterCoeff_valueChanged(int arg1)
{
    curKvFilterCoeff[0] = arg1;
    //emit updateSettingsRequest(1,8, val);
}
void SettingsForm::on_kvFilterCoeff_2_valueChanged(int arg1)
{

    curKvFilterCoeff[1] = arg1;
    //emit updateSettingsRequest(1,8, val);
}
void SettingsForm::on_kvFilterCoeff_3_valueChanged(int arg1)
{

    curKvFilterCoeff[2] = arg1;
    //emit updateSettingsRequest(1,8, val);
}
void SettingsForm::on_kvFilterCoeff_4_valueChanged(int arg1)
{

    curKvFilterCoeff[3] = arg1;
    //emit updateSettingsRequest(1,8, val);
}

/*--------------------------------------------------------------*/


void SettingsForm::updateApdSettings(){
    uint8_t i=0;
    for(i=0;i<4;i++){
        if(curApdGainL2Set[i] != prevApdGainL2Set[i]){
            emit updateSettingsRequest(2,4*i,&curApdGainL2Set[i] );
            prevApdGainL2Set[i]= curApdGainL2Set[i];
        }

        if(curApdBiasDac[i] != prevApdBiasDac[i]){
            emit updateSettingsRequest(2,4*i+1,&curApdBiasDac[i] );
            prevApdBiasDac[i]= curApdBiasDac[i];
        }

        if(curApdSigRmsL2Set[i] != prevApdSigRmsL2Set[i]){
            emit updateSettingsRequest(2,4*i+2,&curApdSigRmsL2Set[i] );
            prevApdSigRmsL2Set[i]= curApdSigRmsL2Set[i];
        }

        if(curApdOptPwrL2Set[i] != prevApdOptPwrL2Set[i]){
            emit updateSettingsRequest(2,4*i+3,&curApdOptPwrL2Set[i] );
            prevApdOptPwrL2Set[i]= curApdOptPwrL2Set[i];
        }
    }

}
void SettingsForm::on_gainControlsValues_received(unsigned int axis,bool* val)
{
    qDebug()<<"on_ssiDataAvailable_received";
    std::thread gainControlsValuesThread(&SettingsForm::gainControlsValuesFunc, this,axis,val);
    gainControlsValuesThread.detach();
}

void SettingsForm::gainControlsValuesFunc(unsigned int axis,bool* val)
{
    switch (axis) {
        case 1:
        curGainMinControl[0]=val[0];
        curGainMaxControl[0]=val[1];
        curAutoAdjustGainMode[0]=val[2];
        prevGainMinControl[0]=val[0];
        prevGainMaxControl[0]=val[1];
        prevAutoAdjustGainMode[0]=val[2];

            ui->gainMinControl->setCurrentIndex(val[0]);
            ui->gainMaxControl->setCurrentIndex(val[1]);
            ui->agcControl->setCurrentIndex(val[2]);

            break;
        case 2:
        curGainMinControl[1]=val[0];
        curGainMaxControl[1]=val[1];
        curAutoAdjustGainMode[1]=val[2];
        prevGainMinControl[1]=val[0];
        prevGainMaxControl[1]=val[1];
        prevAutoAdjustGainMode[1]=val[2];

            ui->gainMinControl_2->setCurrentIndex(val[0]);
            ui->gainMaxControl_2->setCurrentIndex(val[1]);
            ui->agcControl_2->setCurrentIndex(val[2]);
            break;
        case 3:
        curGainMinControl[2]=val[0];
        curGainMaxControl[2]=val[1];
        curAutoAdjustGainMode[2]=val[2];
        prevGainMinControl[2]=val[0];
        prevGainMaxControl[2]=val[1];
        prevAutoAdjustGainMode[2]=val[2];

            ui->gainMinControl_3->setCurrentIndex(val[0]);
            ui->gainMaxControl_3->setCurrentIndex(val[1]);
            ui->agcControl_3->setCurrentIndex(val[2]);
            break;
        case 4:
        curGainMinControl[3]=val[0];
        curGainMaxControl[3]=val[1];
        curAutoAdjustGainMode[3]=val[2];
        prevGainMinControl[3]=val[0];
        prevGainMaxControl[3]=val[1];
        prevAutoAdjustGainMode[3]=val[2];

            ui->gainMinControl_4->setCurrentIndex(val[0]);
            ui->gainMaxControl_4->setCurrentIndex(val[1]);
            ui->agcControl_4->setCurrentIndex(val[2]);
            break;
        default:
            break;
    }

}

void SettingsForm::on_ssiDataAvailable_received(unsigned int axis,double *ssiVals, double *optPwrVals)
{
    qDebug()<<"on_ssiDataAvailable_received";
    std::thread ssiDataAvailableThread(&SettingsForm::ssiDataAvailableFunc, this,axis,ssiVals, optPwrVals);
    ssiDataAvailableThread.detach();
}

void SettingsForm::ssiDataAvailableFunc(unsigned int axis,double *ssiVals, double *optPwrVals)
{
switch (axis) {
    case 1:
        ui->ssiMinVal_1->setText(QString::number(ssiVals[0]));
        ui->ssiNomVal_1->setText(QString::number(ssiVals[1]));
        ui->ssiMaxVal_1->setText(QString::number(ssiVals[2]));

        ui->optPwrMin_1->setText(QString::number(optPwrVals[0]));
        ui->optPwrNom_1->setText(QString::number(optPwrVals[1]));
        ui->optPwrMax_1->setText(QString::number(optPwrVals[2]));
        break;
    case 2:
        ui->ssiMinVal_2->setText(QString::number(ssiVals[0]));
        ui->ssiNomVal_2->setText(QString::number(ssiVals[1]));
        ui->ssiMaxVal_2->setText(QString::number(ssiVals[2]));

        ui->optPwrMin_2->setText(QString::number(optPwrVals[0]));
        ui->optPwrNom_2->setText(QString::number(optPwrVals[1]));
        ui->optPwrMax_2->setText(QString::number(optPwrVals[2]));
        break;
    case 3:
        ui->ssiMinVal_3->setText(QString::number(ssiVals[0]));
        ui->ssiNomVal_3->setText(QString::number(ssiVals[1]));
        ui->ssiMaxVal_3->setText(QString::number(ssiVals[2]));

        ui->optPwrMin_3->setText(QString::number(optPwrVals[0]));
        ui->optPwrNom_3->setText(QString::number(optPwrVals[1]));
        ui->optPwrMax_3->setText(QString::number(optPwrVals[2]));
        break;
    case 4:
        ui->ssiMinVal_4->setText(QString::number(ssiVals[0]));
        ui->ssiNomVal_4->setText(QString::number(ssiVals[1]));
        ui->ssiMaxVal_4->setText(QString::number(ssiVals[2]));

        ui->optPwrMin_4->setText(QString::number(optPwrVals[0]));
        ui->optPwrNom_4->setText(QString::number(optPwrVals[1]));
        ui->optPwrMax_4->setText(QString::number(optPwrVals[2]));
        break;
    default:
        break;
}
}

void SettingsForm::on_ssiSquelchValues_received(unsigned int axis, unsigned int* ssiSq){
    qDebug()<<"on_ssiSquelchValues_received";
    qDebug()<<"ssisq1= "<<ssiSq[0];
    switch (axis) {
        case 1:
        curSSIsquelch[0]=*ssiSq;
        prevSSIsquelch[0]=*ssiSq;
        ui->ssiSquelch_1->setValue(*ssiSq);
            break;
        case 2:
        curSSIsquelch[1]=*ssiSq;
        prevSSIsquelch[1]=*ssiSq;
        ui->ssiSquelch_2->setValue(*ssiSq);
            break;
        case 3:
        curSSIsquelch[2]=*ssiSq;
        prevSSIsquelch[2]=*ssiSq;
        ui->ssiSquelch_3->setValue(*ssiSq);
            break;
        case 4:
        curSSIsquelch[3]=*ssiSq;
        prevSSIsquelch[3]=*ssiSq;
        ui->ssiSquelch_4->setValue(*ssiSq);
            break;
        default:
            break;
    }
}
void SettingsForm::on_KpKvValues_received(unsigned int axis, int* coeff){
    qDebug()<<"on_KpKvValues_received";
    switch (axis) {
        case 1:
        curKpFilterCoeff[0] = coeff[0];
        curKvFilterCoeff[0] = coeff[1];
        prevKpFilterCoeff[0] = coeff[0];
        prevKvFilterCoeff[0] = coeff[1];
        ui->kpFilterCoeff->setValue(coeff[0]);
        ui->kvFilterCoeff->setValue(coeff[1]);
            break;
        case 2:
        curKpFilterCoeff[1] = coeff[0];
        curKvFilterCoeff[1] = coeff[1];
        prevKpFilterCoeff[1] = coeff[0];
        prevKvFilterCoeff[1] = coeff[1];
        ui->kpFilterCoeff_2->setValue(coeff[0]);
        ui->kvFilterCoeff_2->setValue(coeff[1]);
            break;
        case 3:
        curKpFilterCoeff[2] = coeff[0];
        curKvFilterCoeff[2] = coeff[1];
        prevKpFilterCoeff[2] = coeff[0];
        prevKvFilterCoeff[2] = coeff[1];
        ui->kpFilterCoeff_3->setValue(coeff[0]);
        ui->kvFilterCoeff_3->setValue(coeff[1]);
            break;
        case 4:
        curKpFilterCoeff[3] = coeff[0];
        curKvFilterCoeff[3] = coeff[1];
        prevKpFilterCoeff[3] = coeff[0];
        prevKvFilterCoeff[3] = coeff[1];
        ui->kpFilterCoeff_4->setValue(coeff[0]);
        ui->kvFilterCoeff_4->setValue(coeff[1]);
            break;
        default:
            break;
    }
}
void SettingsForm::on_readGSEDataComplete_received(double* gseData){
    qDebug()<<"on_readGSEDataComplete_received";
    ui->gseTarGain_1->setText(QString::number(gseData[0]));
    ui->gseTarGain_2->setText(QString::number(gseData[1]));
    ui->gseTarGain_3->setText(QString::number(gseData[2]));
    ui->gseTarGain_4->setText(QString::number(gseData[3]));

    ui->gseActGain_1->setText(QString::number(gseData[4]));
    ui->gseActGain_2->setText(QString::number(gseData[5]));
    ui->gseActGain_3->setText(QString::number(gseData[6]));
    ui->gseActGain_4->setText(QString::number(gseData[7]));

    ui->gseSigRMSGain_1->setText(QString::number(gseData[8]));
    ui->gseSigRMSGain_2->setText(QString::number(gseData[9]));
    ui->gseSigRMSGain_3->setText(QString::number(gseData[10]));
    ui->gseSigRMSGain_4->setText(QString::number(gseData[11]));

    ui->gseOptPwrGain_1->setText(QString::number(gseData[12]));
    ui->gseOptPwrGain_2->setText(QString::number(gseData[13]));
    ui->gseOptPwrGain_3->setText(QString::number(gseData[14]));
    ui->gseOptPwrGain_4->setText(QString::number(gseData[15]));

}


void SettingsForm::on_apdValues_received(unsigned int axis, uint32_t* val){
qDebug()<<"on_apdValues_received here";

qDebug()<<"settingForm::apdval0"<<val[0]<<"apdval1"<<val[1]<<"apdval2"<<val[2]<<"apdval3"<<val[3];
    switch (axis) {
        case 1:
        curApdGainL2Set[0] = val[0];
        prevApdGainL2Set[0] = val[0];
        prevApdBiasDac[0] = val[1];
        curApdBiasDac[0] = val[1];
        prevApdSigRmsL2Set[0] = val[2];
        curApdSigRmsL2Set[0] = val[2];
        curApdOptPwrL2Set[0] = val[3];
        prevApdOptPwrL2Set[0] = val[3];
        ui->apdGainL2SetVal->setValue(val[0]);
        ui->apdBiasDac->setValue(val[1]);
        ui->apdSigRmsL2Set->setValue(val[2]);
        ui->apdOptPwrL2Set->setValue(val[3]);
            break;
        case 2:
        curApdGainL2Set[1] = val[0];
        prevApdGainL2Set[1] = val[0];
        prevApdBiasDac[1] = val[1];
        curApdBiasDac[1] = val[1];
        prevApdSigRmsL2Set[1] = val[2];
        curApdSigRmsL2Set[1] = val[2];
        curApdOptPwrL2Set[1] = val[3];
        prevApdOptPwrL2Set[1] = val[3];
        ui->apdGainL2SetVal_2->setValue(val[0]);
        ui->apdBiasDac_2->setValue(val[1]);
        ui->apdSigRmsL2Set_2->setValue(val[2]);
        ui->apdOptPwrL2Set_2->setValue(val[3]);
            break;
        case 3:
        curApdGainL2Set[2] = val[0];
        prevApdGainL2Set[2] = val[0];
        prevApdBiasDac[2] = val[1];
        curApdBiasDac[2] = val[1];
        prevApdSigRmsL2Set[2] = val[2];
        curApdSigRmsL2Set[2] = val[2];
        curApdOptPwrL2Set[2] = val[3];
        prevApdOptPwrL2Set[2] = val[3];

        ui->apdGainL2SetVal_3->setValue(val[0]);
        ui->apdBiasDac_3->setValue(val[1]);
        ui->apdSigRmsL2Set_3->setValue(val[2]);
        ui->apdOptPwrL2Set_3->setValue(val[3]);
            break;
        case 4:
        curApdGainL2Set[3] = val[0];
        prevApdGainL2Set[3] = val[0];
        prevApdBiasDac[3] = val[1];
        curApdBiasDac[3] = val[1];
        prevApdSigRmsL2Set[3] = val[2];
        curApdSigRmsL2Set[3] = val[2];
        curApdOptPwrL2Set[3] = val[3];
        prevApdOptPwrL2Set[3] = val[3];

        ui->apdGainL2SetVal_4->setValue(val[0]);
        ui->apdBiasDac_4->setValue(val[1]);
        ui->apdSigRmsL2Set_4->setValue(val[2]);
        ui->apdOptPwrL2Set_4->setValue(val[3]);
            break;
        default:
            break;
    }
}
void SettingsForm::on_pushButton_17_clicked()
{
/*
    bool ok=false;
    double coeff[2];
    kpFilterCoeff_cur =  ui->kpFilterCoeff->text().toDouble((&ok));
    kvFilterCoeff_cur = ui->kvFilterCoeff->text().toDouble((&ok));
    coeff[0]=kpFilterCoeff_cur;
    coeff[1]=kvFilterCoeff_cur;
    if((kpFilterCoeff_cur != kpFilterCoeff_prev) || (kpFilterCoeff_cur != kpFilterCoeff_prev)){
        emit updateSettingsRequest(3,1,coeff );
        kpFilterCoeff_prev = kpFilterCoeff_cur;
        kvFilterCoeff_prev = kvFilterCoeff_cur;
    }
    */
}

//-------------------Gain min control---------------------------------
void SettingsForm::on_gainMinControl_currentIndexChanged(int index)
{
    curGainMinControl[0] = index;

}
void SettingsForm::on_gainMinControl_2_currentIndexChanged(int index)
{
    curGainMinControl[1] = index;

}
void SettingsForm::on_gainMinControl_3_currentIndexChanged(int index)
{
    curGainMinControl[2] = index;

}
void SettingsForm::on_gainMinControl_4_currentIndexChanged(int index)
{
    curGainMinControl[3] = index;

}

//-------------------Gain max control---------------------------------
void SettingsForm::on_gainMaxControl_currentIndexChanged(int index)
{
    curGainMaxControl[0] = index;

}
void SettingsForm::on_gainMaxControl_2_currentIndexChanged(int index)
{
    curGainMaxControl[1] = index;

}
void SettingsForm::on_gainMaxControl_3_currentIndexChanged(int index)
{
    curGainMaxControl[2] = index;

}
void SettingsForm::on_gainMaxControl_4_currentIndexChanged(int index)
{
    curGainMaxControl[3] = index;

}


//-------------------AGA control---------------------------------
void SettingsForm::on_agcControl_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[0] = index;

}
void SettingsForm::on_agcControl_2_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[1] = index;

}
void SettingsForm::on_agcControl_3_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[2] = index;

}
void SettingsForm::on_agcControl_4_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[3] = index;

}

void SettingsForm::updateCalibrationData()
{
    int i=0;

    for(i=0;i<4;i++){
        if((curKpFilterCoeff[i] != prevKpFilterCoeff[i]) || (curKvFilterCoeff[i] != prevKvFilterCoeff[i])){
            val[0]=curKpFilterCoeff[i];
            val[1]=curKvFilterCoeff[i];
            emit updateSettingsRequest(3,i, val);
            prevKpFilterCoeff[i] = curKpFilterCoeff[i];
            prevKvFilterCoeff[i] = curKvFilterCoeff[i];
        }
        if(prevSSIsquelch[i] != curSSIsquelch[i]){
            emit updateSettingsRequest(3,4+i,&curSSIsquelch[i]);
            prevSSIsquelch[i] = curSSIsquelch[i];
        }
    }

}

void SettingsForm::updateEEPROMData()
{
    emit updateSettingsRequest(4,5, nullptr);
}

void SettingsForm::updateDiagnosticsData()
{
    emit updateSettingsRequest(5,0, nullptr);
}


void SettingsForm::on_ssiSquelch_1_valueChanged(int arg1)
{
    curSSIsquelch[0] = arg1;
    //emit updateSettingsRequest(4,4, val);
}

void SettingsForm::on_ssiSquelch_2_valueChanged(int arg1)
{
    curSSIsquelch[3] = arg1;
}
void SettingsForm::on_ssiSquelch_3_valueChanged(int arg1)
{
    curSSIsquelch[2] = arg1;
}
void SettingsForm::on_ssiSquelch_4_valueChanged(int arg1)
{
    curSSIsquelch[1] = arg1;
}


void SettingsForm::on_apdBiasDac_valueChanged(int arg1)
{
    curApdBiasDac[0] = (double) arg1;
}

void SettingsForm::on_apdGainL2SetVal_valueChanged(int arg1)
{
    curApdGainL2Set[0] = (double) arg1;
}

void SettingsForm::on_apdSigRmsL2Set_valueChanged(int arg1)
{
    curApdSigRmsL2Set[0] = (double) arg1;
}

void SettingsForm::on_apdOptPwrL2Set_valueChanged(int arg1)
{
    curApdOptPwrL2Set[0] = (double) arg1;
}


void SettingsForm::on_apdBiasDac_2_valueChanged(int arg1)
{
    curApdBiasDac[1] = (double) arg1;
}

void SettingsForm::on_apdGainL2SetVal_2_valueChanged(int arg1)
{
    curApdGainL2Set[1] = (double) arg1;
}

void SettingsForm::on_apdSigRmsL2Set_2_valueChanged(int arg1)
{
    curApdSigRmsL2Set[1] = (double) arg1;
}

void SettingsForm::on_apdOptPwrL2Set_2_valueChanged(int arg1)
{
    curApdOptPwrL2Set[1] = (double) arg1;
}

void SettingsForm::on_apdBiasDac_3_valueChanged(int arg1)
{
    curApdBiasDac[2] = (double) arg1;
}

void SettingsForm::on_apdGainL2SetVal_3_valueChanged(int arg1)
{
    curApdGainL2Set[2] = (double) arg1;
}

void SettingsForm::on_apdSigRmsL2Set_3_valueChanged(int arg1)
{
    curApdSigRmsL2Set[2] = (double) arg1;
}

void SettingsForm::on_apdOptPwrL2Set_3_valueChanged(int arg1)
{
    curApdOptPwrL2Set[2] = (double) arg1;
}

void SettingsForm::on_apdBiasDac_4_valueChanged(int arg1)
{
    curApdBiasDac[3] = (double) arg1;
}

void SettingsForm::on_apdGainL2SetVal_4_valueChanged(int arg1)
{
    curApdGainL2Set[3] = (double) arg1;
}

void SettingsForm::on_apdSigRmsL2Set_4_valueChanged(int arg1)
{
    curApdSigRmsL2Set[3] = (double) arg1;
}

void SettingsForm::on_apdOptPwrL2Set_4_valueChanged(int arg1)
{
    curApdOptPwrL2Set[3] = (double) arg1;
}

void SettingsForm::on_baseAdressInput_textChanged(const QString &arg1)
{
    basAd=ui->baseAdressInput->text().toStdString();
    baseAdChange =true;
}

void SettingsForm::updateBaseAddress(){
    unsigned int add=0;
    if(baseAdChange){
    add=convertHex2Uint(basAd);
    baseAdChange = false;
    emit modifyBaseAddressRequest(add);
    }
}

void SettingsForm::on_resetSCLK_currentIndexChanged(int index)
{
    curResetSCLK = index;
}


void SettingsForm::on_sampFreq_valueChanged(int arg1)
{
    curSampleFreq=(unsigned int)arg1;
}

