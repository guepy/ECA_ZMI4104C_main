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
    ui->apdGainL2SetVal->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->apdGainL2SetVal));
    ui->apdGainL2SetVal->setText(QString::number(6000));
    ui->apdBiasDac->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->apdBiasDac));
    ui->apdBiasDac->setText(QString::number(6000));
    ui->apdOptPwrL2Set->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->apdOptPwrL2Set));
    ui->apdOptPwrL2Set->setText(QString::number(6000));
    ui->apdSigRmsL2Set->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->apdSigRmsL2Set));
    ui->apdSigRmsL2Set->setText(QString::number(6000));
}

SettingsForm::~SettingsForm()
{
    delete ui;
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


void SettingsForm::on_interType_currentIndexChanged(int index)
{
        emit updateSettingsRequest(1,2,index);
}


void SettingsForm::on_precisionVal_currentIndexChanged(int index)
{
    emit updateSettingsRequest(1,3,index);
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
    emit updateSettingsRequest(1,4,index);
}

