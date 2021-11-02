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
    ui->selectAxisWidget->setEnabled(false);

    ui->spinBox->setMaximum(16384);//16384 points max
    ui->spinBox->setMinimum(1);//1 point min
    ui->spinBox_3->setMinimum(300);//min freq
    ui->spinBox_3->setMaximum(10e6);//max freq
    ui->spinBox_3->setEnabled(false);
    ui->spinBox_2->setEnabled(false);
    ui->spinBox->setEnabled(false);

    ui->spinBox_2->setMaximum(1.44e6);//1.44 sec max
    ui->spinBox_2->setMinimum(3.334e3);//3.33 ms sec min
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
        ui->spinBox->setMaximum(16384);//16384 points max
        ui->spinBox_3->setMinimum(300);//min freq
        ui->spinBox_3->setMaximum(10e6);//max freq
        ui->spinBox_2->setMaximum(1.44e6);//1.44 sec max
        break;
    case 1:
        ui->NbrOfAxisWidget->setEnabled(false);
        ui->selectAxisWidget->setEnabled(true);
        ui->spinBox_3->setMinimum(0);//min freq
        ui->spinBox_3->setMaximum(10e6);//max freq
        ui->spinBox->setMaximum(10e6);//1e6 points max

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
            ui->spinBox_2->setEnabled(false);
        }
        else{
            ui->spinBox_2->setEnabled(true);
            paramNbr++;
            scanParam+=3;

        }
    }
    else{
        paramNbr=(paramNbr-1<0)?0:(paramNbr-1);
        ui->spinBox_2->setEnabled(false);
        scanParam-=3;
    }
}


void FlyscanForm::on_freqCheckBox_clicked()
{
    if(ui->freqCheckBox->isChecked()){
        if(paramNbr>1){
            ui->display->setTextColor(QColor("red"));
            ui->display->append("Can not choose more than 2 scan parameters");
            ui->freqCheckBox->setCheckState(Qt::Unchecked);
            ui->spinBox_3->setEnabled(false);
        }
        else{
            ui->spinBox_3->setEnabled(true);
            paramNbr++;
            scanParam+=1;


        }
    }
    else{
        paramNbr=(paramNbr-1<0)?0:(paramNbr-1);
        ui->spinBox_3->setEnabled(false);
        scanParam-=1;
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
        ui->spinBox->setEnabled(false);
        scanParam-=5;
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
    QString folderName = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
    if (folderName.isEmpty())
            return;
        else {
            ui->saveFile->setStyleSheet("font: 75 12pt \"MS Shell Dlg 2\";");
            ui->saveFile->setText(folderName);
            ui->saveFile->setDisabled(true);
            std::string fname = folderName.toStdString();
            //cstr = new char [fname.size()+1];
            strcpy_s( extFolderName, fname.c_str() );

            //extFolderName = folderName.toStdString().C_str();
        }
}

void FlyscanForm::on_StartButton_clicked()
{
    if(paramNbr<2){
        ui->display->setTextColor("red");
        ui->display->append("You should provide at least 2 scan parameters");
    }
    else{
        bool ok=false;
        switch (scanParam) {
            case 4:
                freqValue=ui->spinBox_3->text().toDouble(&ok);
                timeValue=ui->spinBox_2->text().toDouble(&ok);
                timeValue= timeValue*1e-6; //convert to sec
                sizeValue= (timeValue) * freqValue;
                qDebug()<<"param: freq: "<<freqValue<<"Hz, it: "<<timeValue<<"s, size: "<<sizeValue;
            break;
            case 6:
                freqValue=ui->spinBox_3->text().toDouble(&ok);
                sizeValue =ui->spinBox->text().toDouble(&ok);
                timeValue= (sizeValue/ freqValue);
                qDebug()<<"param: freq: "<<freqValue<<"Hz, it: "<<timeValue<<"s, size: "<<sizeValue;
            break;
            case 8:
                sizeValue =ui->spinBox->text().toDouble(&ok);
                timeValue=ui->spinBox_2->text().toDouble(&ok);
                timeValue= timeValue*1e-6; //convert to sec
                freqValue= sizeValue/(timeValue );
                qDebug()<<"param: freq: "<<freqValue<<"Hz, it: "<<timeValue<<"s, size: "<<sizeValue;
            break;
            default:

            break;
        }
        nbrAxis=ui->NbrOfAxisWidget->currentIndex()+1;
        emit ramDataFlyscanRequest(freqValue, timeValue, sizeValue, nbrAxis);
        qDebug()<<"Nbr of axis: "<<nbrAxis;
    }
}

