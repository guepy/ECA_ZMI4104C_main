#include "positionoffsetform.h"
#include "ui_positionoffsetform.h"

positionOffsetForm::positionOffsetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::positionOffsetForm)
{
    ui->setupUi(this);
    currentUnits=0;
    posOffsetValue=new double[4];
    alreadyApplied = false;
    //ui->lineEdit_11->textChanged()
    ui->offPosAxis1->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->offPosAxis1));
    ui->offPosAxis2->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->offPosAxis2));
    ui->offPosAxis3->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->offPosAxis3));
    ui->offPosAxis4->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->offPosAxis4));
    ui->offPosAxis1->setText(QString::number(0));
    ui->offPosAxis2->setText(QString::number(0));
    ui->offPosAxis3->setText(QString::number(0));
    ui->offPosAxis4->setText(QString::number(0));
}

positionOffsetForm::~positionOffsetForm()
{
    delete ui;
}

//---Button cancel-----------------
void positionOffsetForm::on_pushButton_5_clicked()
{
    closeForm();
}
void positionOffsetForm::closeForm(){
    emit closeThis();
    qDebug()<<"Close this emitted";
    this->deleteLater();
}

void positionOffsetForm::on_pushButton_2_clicked()
{
    getPosOffsetValues(posOffsetValue);
    alreadyApplied=true;
}


void positionOffsetForm::on_okButton_clicked()
{
    if(!alreadyApplied)
        getPosOffsetValues(posOffsetValue);
    closeForm();
}

void positionOffsetForm::getPosOffsetValues(double* valPtr){
    bool ok=false;
    valPtr[0]=(double)((ui->offPosAxis1->text().toDouble(&ok)*unitsCoeffs[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    valPtr[1]=(double)((ui->offPosAxis2->text().toDouble(&ok)*unitsCoeffs[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    valPtr[2]=(double)((ui->offPosAxis3->text().toDouble(&ok)*unitsCoeffs[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    valPtr[3]=(double)((ui->offPosAxis4->text().toDouble(&ok)*unitsCoeffs[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    for(int i=0;i<4;i++){
        qDebug()<<"position offset on axis "<<i+1<<"is"<<valPtr[i];
    }
    emit OffsetPosChanged(valPtr);
}

void positionOffsetForm::on_leftBlockUnits_currentIndexChanged(int index)
{
    currentUnits = index;
}

