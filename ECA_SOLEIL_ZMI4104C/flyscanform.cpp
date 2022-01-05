#include "flyscanform.h"
#include "ui_flyscanform.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <string.h>
#include <QMessageBox>
FlyscanForm::FlyscanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlyscanForm)
{
    ui->setupUi(this);
    ui->selectAxisWidget->setEnabled(false);
    char txt[1024]="";
    ui->spinBox->setMaximum(30000);//16384 points max
    ui->spinBox->setMinimum(1);//1 point min
    ui->spinBox_3->setMinimum(3e2);//min freq
    ui->spinBox_3->setMaximum(1e6);//max freq
    ui->spinBox_3->setEnabled(false);
    ui->spinBox_2->setEnabled(false);
    ui->spinBox->setEnabled(false);

    ui->spinBox_2->setMaximum(1.44e6);//1.44 sec max
    ui->spinBox_2->setMinimum(3.334e3);//3.33 ms sec min
    strcpy_s(extFolderName,(QDir::currentPath()).toStdString().c_str());
    ui->saveFile->setStyleSheet("font: 75 12pt \"MS Shell Dlg 2\";");
    ui->saveFile->setText(extFolderName);
    ui->saveFile->setDisabled(true);
    ui->display->append("Choose flyscan parameter ");
    sprintf(txt,"default save folder %s ", extFolderName);
    ui->display->append(txt);
    double val[4]={0.0,0.0,0.0,0.0};
    for(int i=0;i<4;i++)
        axisTab[i]=i+1;
    on_flyscanStatValues_received((unsigned char *)axisTab, val,val);
    for(int i=0;i<4;i++)
        axisTab[i]=0;
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
    case 0: //RAM DATA FLYSCAN MODE
        ui->display->append("RAM DATA FLYSCAN MODE activated ");
        ui->selectAxisWidget->setEnabled(false);
        ui->NbrOfAxisWidget->setEnabled(true);
        ui->spinBox->setMaximum(16384);//16384 points max
        ui->spinBox_3->setMinimum(300);//min freq
        ui->spinBox_3->setMaximum(10e6);//max freq
        ui->spinBox_2->setMaximum(1.44e6);//1.44 sec max
        flyscanModeIndex=0;
        break;
    case 1: // FIFO FLYSCAN MODE
        ui->display->append("FIFO FLYSCAN MODE activated ");
        ui->NbrOfAxisWidget->setEnabled(false);
        ui->selectAxisWidget->setEnabled(true);
        ui->spinBox_3->setMinimum(0);//min freq
        ui->spinBox_3->setMaximum(10e6);//max freq
        ui->spinBox->setMaximum(10e6);//1e6 points max
        flyscanModeIndex=1;

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
            ui->display->setTextColor(QColor("dark"));
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
            ui->display->setTextColor("dark");
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
            ui->display->setTextColor("dark");
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
    char txt[1024];
    QString folderName = QFileDialog::getExistingDirectory(0, ("Select Output Folder"), QDir::currentPath());
    if (folderName.isEmpty())
            return;
        else
    {
            ui->saveFile->setStyleSheet("font: 75 12pt \"MS Shell Dlg 2\";");
            ui->saveFile->setText(folderName);
            ui->saveFile->setDisabled(true);
            std::string fname = folderName.toStdString();
            //cstr = new char [fname.size()+1];
            strcpy_s( extFolderName, fname.c_str() );
            sprintf(txt,"save folder changed to %s \n", extFolderName);
            ui->display->append(txt);

    }
}

void FlyscanForm::on_StartButton_clicked()
{

    ui->ButtonForm->setEnabled(false);// don't press start twice in succession
    if(paramNbr<2){
        ui->display->setTextColor("red");
        ui->display->append("You should provide at least 2 scan parameters");
        ui->display->setTextColor("dark");
        ui->ButtonForm->setEnabled(true);
    }
    else{

        bool ok=false;
        switch (scanParam) {
            case 4:
                freqValue=ui->spinBox_3->text().toDouble(&ok);
                timeValue=ui->spinBox_2->text().toDouble(&ok);
                timeValue= timeValue*1e-6; //convert to sec
                sizeValue= (timeValue) * freqValue;
                ui->spinBox->setValue(sizeValue);
                qDebug()<<"param: freq: "<<freqValue<<"Hz, it: "<<timeValue<<"s, size: "<<sizeValue;
            break;
            case 6:
                freqValue=ui->spinBox_3->text().toDouble(&ok);
                sizeValue =ui->spinBox->text().toDouble(&ok);
                timeValue= (sizeValue/ freqValue);
                ui->spinBox_2->setValue(timeValue*1e6);
                qDebug()<<"param: freq: "<<freqValue<<"Hz, it: "<<timeValue<<"s, size: "<<sizeValue;
            break;
            case 8:
                sizeValue =ui->spinBox->text().toDouble(&ok);
                timeValue=ui->spinBox_2->text().toDouble(&ok);
                timeValue= timeValue*1e-6; //convert to sec
                freqValue= sizeValue/(timeValue );
                ui->spinBox_3->setValue(freqValue);
                qDebug()<<"param: freq: "<<freqValue<<"Hz, it: "<<timeValue<<"s, size: "<<sizeValue;
            break;
            default:

            break;
        }
        if(!flyscanModeIndex){
            nbrAxis=ui->NbrOfAxisWidget->currentIndex()+1;
            ui->display->append("Setting up RAMDATA FLYSCAN...");
            emit ramDataFlyscanRequest(freqValue, timeValue, sizeValue, nbrAxis);
        }
        else{
            if(!nbrAxis){
                ui->display->setTextColor(QColor("red"));
                ui->display->append("Select axis on which to perform continuous scan");
                ui->display->setTextColor(QColor("dark"));
            }
            else{
                emit fifoFlyscanRequest(freqValue, timeValue, sizeValue, nbrAxis);
                ui->display->append("Setting up FIFO FLYSCAN...");
                qDebug()<<"emit fifoFlyscanRequest signal";
            }
        }
    }

}


void FlyscanForm::on_flyscanProcTerm_received(){
    ui->ButtonForm->setEnabled(true);
}
void FlyscanForm::on_fifoAxis1_clicked()
{
    if(ui->fifoAxis1->isChecked()){
        axisTab[0]=1;
        nbrAxis++;
    }
    else{
        axisTab[0]=0;
        nbrAxis--;
    }
}
void FlyscanForm::on_fifoAxis2_clicked()
{
    if(ui->fifoAxis2->isChecked()){
        axisTab[1]=2;
        nbrAxis++;
    }
    else{
        axisTab[1]=0;
        nbrAxis--;
    }
}

void FlyscanForm::on_fifoAxis3_clicked()
{
    if(ui->fifoAxis3->isChecked()){
        axisTab[2]=3;
        nbrAxis++;
    }
    else{
        axisTab[2]=0;
        nbrAxis--;
    }
}
void FlyscanForm::on_fifoAxis4_clicked()
{
    if(ui->fifoAxis4->isChecked()){
        axisTab[3]=4;
        nbrAxis++;
    }
    else{
        axisTab[3]=0;
        nbrAxis--;
    }
}

void FlyscanForm::on_flyscanErrorCode_recieved(int err_code){
    switch (err_code) {
    case 0:
        ui->display->setTextColor(QColor("green"));
        ui->display->append("flyscan operation successful");
        ui->display->setTextColor(QColor("dark"));
        break;
    case 1:
        ui->display->setTextColor(QColor("green"));
        ui->display->append("flyscan configuration successful");
        ui->display->setTextColor(QColor("dark"));
        break;
    case 2:
        ui->display->setTextColor(QColor("green"));
        ui->display->append("data have been successfully saved to the save folder");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -1:
        ui->display->setTextColor(QColor("red"));
        ui->display->append("Flyscan operation failed");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -99:
        ui->display->setTextColor(QColor("red"));
        ui->display->append("Flyscan configuration failed ");
        ui->display->append("Try to reset the system ");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -100:
        ui->display->setTextColor(QColor("red"));
        ui->display->append("Overlapping detected, somme data may have been corrupted ");
        ui->display->append("Try to adjust scan parameter ");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -101:
        ui->display->setTextColor(QColor(QColor::fromRgb(255, 170, 0)));
        ui->display->append("In the current method, min size is 256 ");
        ui->spinBox->setValue(256);
        ui->display->append("size has been set to 256 ");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -102:
        ui->display->setTextColor(QColor(QColor::fromRgb(255, 170, 0)));
        ui->display->append("With the current parameters, max size is 16384");
        ui->spinBox->setValue(16384);
        ui->display->append("size has been set to 16384");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -103:
        ui->display->setTextColor(QColor(QColor::fromRgb(255, 170, 0)));
        ui->display->append("With the current parameters, only 8192 per axis has been saved");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -104:
        ui->display->setTextColor(QColor("red"));
        ui->display->append("failed to stop continuous acquisition");
        ui->display->append("Try to adjust scan parameter ");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -105:
        ui->display->setTextColor(QColor("red"));
        ui->display->append("null pointer has been passed to store data in");
        ui->display->append("Try to restart the application ");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -106:
        ui->display->setTextColor(QColor("red"));
        ui->display->append("error while retreiving flyscan data");
        ui->display->append("Try to reset the system");
        ui->display->setTextColor(QColor("dark"));
        break;
    case -107:
        ui->display->setTextColor(QColor("red"));
        ui->display->append("Faillure while processing flyscan data");
        ui->display->append("Try to reset the system ");
        ui->display->setTextColor(QColor("dark"));
        break;
    default:
        break;
    }
}


void FlyscanForm::on_flyscanStatValues_received(unsigned char* axisTab, double* mean, double* stdDev){
    qDebug()<<"flyscan stat val";

    for(int i=0; i<4;i++){
        switch ((unsigned int)axisTab[i]) {
        case 1:
            ui->meanAxis1->setText(QString::number(mean[0]));
            ui->meanAxis1->setAlignment(Qt::AlignCenter);
            ui->stdDevAxis1->setText(QString::number(stdDev[0]));
            ui->stdDevAxis1->setAlignment(Qt::AlignCenter);
        break;
        case 2:
            ui->meanAxis2->setText(QString::number(mean[1]));
            ui->meanAxis2->setAlignment(Qt::AlignCenter);
            ui->stdDevAxis2->setText(QString::number(stdDev[1]));
            ui->stdDevAxis2->setAlignment(Qt::AlignCenter);
        break;
        case 3:
            ui->meanAxis3->setText(QString::number(mean[2]));
            ui->meanAxis3->setAlignment(Qt::AlignCenter);
            ui->stdDevAxis3->setText(QString::number(stdDev[2]));
            ui->stdDevAxis3->setAlignment(Qt::AlignCenter);
        break;
        case 4:
            ui->meanAxis4->setText(QString::number(mean[3]));
            ui->meanAxis4->setAlignment(Qt::AlignCenter);
            ui->stdDevAxis4->setText(QString::number(stdDev[3]));
            ui->stdDevAxis4->setAlignment(Qt::AlignCenter);
        break;
        default:
        break;
        }
    }

}
