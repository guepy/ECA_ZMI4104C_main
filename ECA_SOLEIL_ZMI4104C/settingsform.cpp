#include "settingsform.h"
#include "ui_settingsform.h"
#include <QDebug>
SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    updateTable = (int*)calloc(10, sizeof(int));
    ui->baseAdressInput->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->baseAdressInput));
    ui->baseAdressInput->setText(QString::number(6000));

    ui->apdGainL2SetVal->setMinimum(0);//min freq
    ui->apdGainL2SetVal->setMaximum(5120);//max freq
    ui->apdSigRmsL2Set->setMinimum(0);//min freq
    ui->apdOptPwrL2Set->setMinimum(-3920);//min freq
    ui->apdOptPwrL2Set->setMaximum(3402);//max freq
    ui->kpFilterCoeff->setMaximum(7);
    ui->kvFilterCoeff->setMaximum(7);
    //*
    ui->apdBiasDac->setEnabled(false);
    stimer = new QTimer(this);
    connect(stimer, &QTimer::timeout, this, QOverload<>::of(&SettingsForm::refreshSettings));
    //timer->setSingleShot(true);
    emit initSettingsFormRequest();
    stimer->start(1000);
}

SettingsForm::~SettingsForm()
{
    stimer->stop();
    delete stimer;
    delete ui;
}
void SettingsForm::refreshSettings(){

    stimer->stop();
//*/
    qDebug()<<"settings timer timeout";
    updateEEPROMData();
    updateDiagnosticsData();

    stimer->start(1000);
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

void SettingsForm::on_StartButton_clicked()
{
    updateGeneralSettings();
    updateApdSettings();
    updateCalibrationData();
}

void SettingsForm::updateGeneralSettings(){
    if(curInterferoType != prevInterferoType){
        emit updateSettingsRequest(1,2,&curInterferoType );
        prevInterferoType= curInterferoType;
    }
    if(curPrecision != prevPrecision){
        emit updateSettingsRequest(1,3,&curPrecision );
        prevPrecision= curPrecision;
    }
    if(curResetFindVelocity != prevResetFindVelocity){
        emit updateSettingsRequest(1,4,&curResetFindVelocity );
        prevResetFindVelocity= curResetFindVelocity;
    }
    if(curClockType != prevClockType){
        emit updateSettingsRequest(1,5, &curClockType);
        prevClockType = curClockType;
    }
    if(curFreq != prevFreq){
        emit updateSettingsRequest(1,6, &curFreq);
        prevFreq = curFreq;
    }

    for(int i=0; i<4; i++){
        if(curGainMinControl[i] != prevGainMinControl[i]){
            emit updateSettingsRequest(1,7+3*i,(double*)&curGainMinControl[i]);
            prevGainMinControl[i] = curGainMinControl[i];
        }
        if(curAutoAdjustGainMode[i] != prevAutoAdjustGainMode[i]){
            emit updateSettingsRequest(1,7+3*i+1,(double*)&curAutoAdjustGainMode[i]);
            prevAutoAdjustGainMode[i] = curAutoAdjustGainMode[i];
        }
        if(curGainMaxControl[i] != prevGainMaxControl[i]){
            emit updateSettingsRequest(1,7+3*i+2,(double*)&curGainMaxControl[i]);
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
void SettingsForm::on_comboBox_currentIndexChanged(int index)
{
    curClockType=(double)index;
   //emit updateSettingsRequest(1,5, &curClockType);
}


void SettingsForm::on_spinBox_4_valueChanged(int arg1)
{

    curFreq=(double)arg1;
    //emit updateSettingsRequest(1,6, &curFreq);
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
void SettingsForm::on_ssiDataAvailable_received(unsigned int axis,double *ssiVals, double *optPwrVals)
{
switch (axis) {
    case 1:
        ui->ssiMinVal_1->setText(QString::number(ssiVals[0]));
        ui->ssiNomVal_1->setText(QString::number(ssiVals[1]));
        ui->ssiMaxVal_1->setText(QString::number(ssiVals[2]));
        break;
    case 2:
    ui->ssiMinVal_2->setText(QString::number(ssiVals[0]));
    ui->ssiNomVal_2->setText(QString::number(ssiVals[1]));
    ui->ssiMaxVal_2->setText(QString::number(ssiVals[2]));
        break;
    case 3:
    ui->ssiMinVal_3->setText(QString::number(ssiVals[0]));
    ui->ssiNomVal_3->setText(QString::number(ssiVals[1]));
    ui->ssiMaxVal_3->setText(QString::number(ssiVals[2]));
        break;
    case 4:
    ui->ssiMinVal_4->setText(QString::number(ssiVals[0]));
    ui->ssiNomVal_4->setText(QString::number(ssiVals[1]));
    ui->ssiMaxVal_4->setText(QString::number(ssiVals[2]));
        break;
    default:
        break;
}
}

void SettingsForm::on_ssiSquelchValues_received(uint8_t axis, double* ssiSq){
    switch (axis) {
        case 1:
        ui->ssiSquelch_1->setValue(ssiSq[0]);
            break;
        case 2:
        ui->ssiSquelch_2->setValue(ssiSq[1]);
            break;
        case 3:
        ui->ssiSquelch_3->setValue(ssiSq[2]);
            break;
        case 4:
        ui->ssiSquelch_4->setValue(ssiSq[3]);
            break;
        default:
            break;
    }
}
void SettingsForm::on_KpKvValues_received(uint8_t axis, uint16_t* coeff){
    switch (axis) {
        case 1:
        ui->kpFilterCoeff->setValue(coeff[0]);
        ui->kvFilterCoeff->setValue(coeff[1]);
            break;
        case 2:
        ui->kpFilterCoeff_2->setValue(coeff[0]);
        ui->kvFilterCoeff_2->setValue(coeff[1]);
            break;
        case 3:
        ui->kpFilterCoeff_3->setValue(coeff[0]);
        ui->kvFilterCoeff_3->setValue(coeff[1]);
            break;
        case 4:
        ui->kpFilterCoeff_4->setValue(coeff[0]);
        ui->kvFilterCoeff_4->setValue(coeff[1]);
            break;
        default:
            break;
    }
}
void SettingsForm::on_readGSEDataComplete_received(double* gseData){
    ui->gseTarGain_1->setText(QString::number(gseData[0]));
    ui->gseTarGain_2->setText(QString::number(gseData[1]));
    ui->gseTarGain_3->setText(QString::number(gseData[2]));
    ui->gseTarGain_4->setText(QString::number(gseData[3]));

    ui->gseActGain_1->setText(QString::number(gseData[4]));
    ui->gseActGain_2->setText(QString::number(gseData[5]));
    ui->gseActGain_3->setText(QString::number(gseData[6]));
    ui->gseActGain_4->setText(QString::number(gseData[7]));

    ui->gseSigRMSGain_1->setText(QString::number(gseData[8]));
    ui->gseSigRMSGain_1->setText(QString::number(gseData[9]));
    ui->gseSigRMSGain_1->setText(QString::number(gseData[10]));
    ui->gseSigRMSGain_1->setText(QString::number(gseData[11]));

    ui->gseOptPwrGain_1->setText(QString::number(gseData[12]));
    ui->gseOptPwrGain_2->setText(QString::number(gseData[13]));
    ui->gseOptPwrGain_3->setText(QString::number(gseData[14]));
    ui->gseOptPwrGain_4->setText(QString::number(gseData[15]));

}


void SettingsForm::on_apdValues_received(uint8_t axis, uint32_t* val){

    switch (axis) {
        case 1:
        ui->apdGainL2SetVal->setValue(val[0]);
        ui->apdBiasDac->setValue(val[1]);
        ui->apdSigRmsL2Set->setValue(val[2]);
        ui->apdOptPwrL2Set->setValue(val[2]);
            break;
        case 2:
        ui->apdGainL2SetVal_2->setValue(val[0]);
        ui->apdBiasDac_2->setValue(val[1]);
        ui->apdSigRmsL2Set_2->setValue(val[2]);
        ui->apdOptPwrL2Set_2->setValue(val[2]);
            break;
        case 3:
        ui->apdGainL2SetVal_3->setValue(val[0]);
        ui->apdBiasDac_3->setValue(val[1]);
        ui->apdSigRmsL2Set_3->setValue(val[2]);
        ui->apdOptPwrL2Set_3->setValue(val[2]);
            break;
        case 4:
        ui->apdGainL2SetVal_4->setValue(val[0]);
        ui->apdBiasDac_4->setValue(val[1]);
        ui->apdSigRmsL2Set_4->setValue(val[2]);
        ui->apdOptPwrL2Set_4->setValue(val[2]);
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
void SettingsForm::on_comboBox_9_currentIndexChanged(int index)
{
    curGainMinControl[0] = index;

}
void SettingsForm::on_comboBox_10_currentIndexChanged(int index)
{
    curGainMinControl[1] = index;

}
void SettingsForm::on_comboBox_4_currentIndexChanged(int index)
{
    curGainMinControl[2] = index;

}
void SettingsForm::on_comboBox_7_currentIndexChanged(int index)
{
    curGainMinControl[3] = index;

}

//-------------------Gain max control---------------------------------
void SettingsForm::on_comboBox_11_currentIndexChanged(int index)
{
    curGainMaxControl[0] = index;

}
void SettingsForm::on_comboBox_12_currentIndexChanged(int index)
{
    curGainMaxControl[1] = index;

}
void SettingsForm::on_comboBox_5_currentIndexChanged(int index)
{
    curGainMaxControl[2] = index;

}
void SettingsForm::on_comboBox_8_currentIndexChanged(int index)
{
    curGainMaxControl[3] = index;

}


//-------------------AGA control---------------------------------
void SettingsForm::on_comboBox_13_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[0] = index;

}
void SettingsForm::on_comboBox_14_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[1] = index;

}
void SettingsForm::on_comboBox_6_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[2] = index;

}
void SettingsForm::on_comboBox_15_currentIndexChanged(int index)
{
    curAutoAdjustGainMode[3] = index;

}

void SettingsForm::updateCalibrationData()
{
    int i=0;

    for(i=0;i<4;i++){
        if((curKpFilterCoeff[i] != prevKpFilterCoeff[i]) || (curKvFilterCoeff[i] != prevKvFilterCoeff[i])){
            double coeff[2];
            coeff[0]=curKpFilterCoeff[i];
            coeff[1]=curKvFilterCoeff[i];
            emit updateSettingsRequest(3,i, coeff);
            prevKpFilterCoeff[i] = curKpFilterCoeff[i];
            prevKvFilterCoeff[i] = curKvFilterCoeff[i];
        }
    }
    for(i=0;i<4;i++){
        if(prevSSIsquelch[i] != curSSIsquelch[i]){
            emit updateSettingsRequest(3,4+i,(double*)&curSSIsquelch[i]);
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


void SettingsForm::on_spinBox_7_valueChanged(int arg1)
{
    curSSIsquelch[0] = arg1;
    //emit updateSettingsRequest(4,4, val);
}

void SettingsForm::on_spinBox_3_valueChanged(int arg1)
{
    curSSIsquelch[3] = arg1;
}
void SettingsForm::on_spinBox_5_valueChanged(int arg1)
{
    curSSIsquelch[2] = arg1;
}
void SettingsForm::on_spinBox_6_valueChanged(int arg1)
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
