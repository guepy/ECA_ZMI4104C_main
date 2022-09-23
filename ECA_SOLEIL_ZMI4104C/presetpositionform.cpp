#include "presetpositionform.h"
#include "ui_presetpositionform.h"

presetPositionForm::presetPositionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::presetPositionForm)
{
    ui->setupUi(this);
    currentUnits=0;
    presPosValue=new double[4];
    alreadyApplied = false;
    ui->presPosAxis1->setValidator(new QRegExpValidator(QRegExp(R"re(^(\+?\-?\d*\s?)*$)re"), ui->presPosAxis1));
    ui->presPosAxis2->setValidator(new QRegExpValidator(QRegExp(R"re(^(\+?\-?\d*\s?)*$)re"), ui->presPosAxis2));
    ui->presPosAxis3->setValidator(new QRegExpValidator(QRegExp(R"re(^(\+?\-?\d*\s?)*$)re"), ui->presPosAxis3));
    ui->presPosAxis4->setValidator(new QRegExpValidator(QRegExp(R"re(^(\+?\-?\d*\s?)*$)re"), ui->presPosAxis4));
    ui->presPosAxis1->setText(QString::number(0));
    ui->presPosAxis2->setText(QString::number(0));
    ui->presPosAxis3->setText(QString::number(0));
    ui->presPosAxis4->setText(QString::number(0));
}

presetPositionForm::~presetPositionForm()
{
    delete ui;
}

void presetPositionForm::on_pushButton_5_clicked()
{
    closeForm();
}


void presetPositionForm::on_applyButton_clicked()
{
    getPresPosValues(presPosValue);
    alreadyApplied=true;
}


void presetPositionForm::on_okButton_clicked()
{
    if(!alreadyApplied)
        getPresPosValues(presPosValue);
    closeForm();
}
void presetPositionForm::closeForm(){
    emit closeThis();
    qDebug()<<"Close this emitted";
    this->deleteLater();
}

void presetPositionForm::getPresPosValues(double* valPtr){
    bool ok=false;
    valPtr[0]=(double)((ui->presPosAxis1->text().toDouble(&ok)*unitsCoeffs1[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    valPtr[1]=(double)((ui->presPosAxis2->text().toDouble(&ok)*unitsCoeffs1[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    valPtr[2]=(double)((ui->presPosAxis3->text().toDouble(&ok)*unitsCoeffs1[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    valPtr[3]=(double)((ui->presPosAxis4->text().toDouble(&ok)*unitsCoeffs1[currentUnits]));
    if(!ok)
        qDebug()<<"Conversion failed";
    for(int i=0;i<4;i++){
        qDebug()<<"position preset on axis "<<i+1<<"is"<<valPtr[i];
    }
    emit PresetPosChanged(valPtr);
}

void presetPositionForm::on_leftBlockUnits_currentIndexChanged(int index)
{
    currentUnits = index;
}


void presetPositionForm::on_radioButton_2_clicked(bool checked)
{
    (void)checked;
    // TO DO
}

