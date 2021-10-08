#include "flyscanform.h"
#include "ui_flyscanform.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
FlyscanForm::FlyscanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlyscanForm)
{
    ui->setupUi(this);
    ui->freqLineEdit->setEnabled(false);
    ui->itLineEdit->setEnabled(false);
    ui->spinBox->setEnabled(false);
    ui->selectAxisWidget->setEnabled(false);
    ui->spinBox->setMaximum(1e6);


    ui->freqLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->freqLineEdit));
    ui->itLineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*[.][0-9]*"), ui->itLineEdit));
    ui->freqLineEdit->setText(QString::number(0));
    ui->itLineEdit->setText(QString::number(0));
}

FlyscanForm::~FlyscanForm()
{

    delete ui;
}

//-----Button cancel--------------------
void FlyscanForm::on_pushButton_5_clicked()
{
    closeForm();
}
void FlyscanForm::closeForm(){
    emit closeThis();
    qDebug()<<"Close this emitted";
    this->deleteLater();
}

void FlyscanForm::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        ui->selectAxisWidget->setEnabled(false);
        ui->NbrOfAxisWidget->setEnabled(true);
        break;
    case 1:
        ui->NbrOfAxisWidget->setEnabled(false);
        ui->selectAxisWidget->setEnabled(true);

        break;
    default:
        break;
    }
}


void FlyscanForm::on_itCheckBox_clicked()
{
    if(ui->itCheckBox->isChecked()){
        if(paramNbr>1){
            ui->display->setTextColor(QColor("red"));
            ui->display->append("Can not choose more than 2 scan parameters");
            ui->itCheckBox->setCheckState(Qt::Unchecked);
            ui->itLineEdit->setEnabled(false);
        }
        else{
            ui->itLineEdit->setEnabled(true);
            paramNbr++;
            //scanParam+=3;

        }
    }
    else{
        paramNbr=0?0:(paramNbr-1);
    }
}



void FlyscanForm::on_freqCheckBox_clicked()
{
    if(ui->freqCheckBox->isChecked()){
        if(paramNbr>1){
            ui->display->setTextColor(QColor("red"));
            ui->display->append("Can not choose more than 2 scan parameters");
            ui->freqCheckBox->setCheckState(Qt::Unchecked);
            ui->freqLineEdit->setEnabled(false);
        }
        else{
            ui->freqLineEdit->setEnabled(true);
            paramNbr++;
            //scanParam+=1;


        }
    }
    else{
        paramNbr=0?0:(paramNbr-1);
    }
}


void FlyscanForm::on_npCheckBox_clicked()
{
    if(ui->npCheckBox->isChecked()){
        if(paramNbr>1){
            ui->display->setTextColor(QColor("red"));
            ui->display->append("Can not choose more than 2 scan parameters");
            ui->npCheckBox->setCheckState(Qt::Unchecked);
            ui->spinBox->setEnabled(false);
        }
        else{
            ui->spinBox->setEnabled(true);
            paramNbr++;
            scanParam+=5;

        }
    }
    else{
        paramNbr=(paramNbr-1<0)?0:(paramNbr-1);
        //scanParam-=5;
    }
}


void FlyscanForm::on_pushButton_2_clicked()
{
    paramNbr=0;
}


void FlyscanForm::on_pushButton_clicked()
{
    selectFile();
}

void FlyscanForm::selectFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Select File"), "",
        tr("Excel book (*.csv);;All Files (*)"));
    if (fileName.isEmpty())
            return;
        else {
            ui->saveFile->setStyleSheet("font: 75 12pt \"MS Shell Dlg 2\";");
            ui->saveFile->setText(fileName);
            ui->saveFile->setDisabled(true);
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
            QDataStream out(&file);
            out.setVersion(QDataStream::Qt_4_5);
            //out << contacts;
        }
}

void FlyscanForm::on_StartButton_clicked()
{
    if(paramNbr<2){
        ui->display->setTextColor("red");
        ui->display->append("You should provide at least 2 scan parameters");
    }
    else{

    }
}

