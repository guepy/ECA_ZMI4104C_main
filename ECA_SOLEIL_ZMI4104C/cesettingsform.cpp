#include "cesettingsform.h"
#include "ui_cesettingsform.h"
#define CE_VEL_COEFF    12e-3

CEsettingsForm::CEsettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEsettingsForm)
{

    ui->setupUi(this);
    ui->cecAxis->setCurrentIndex(curCecAxis);
    ui->uscCE0->setMinimum(0);
    ui->uscCE0->setMaximum(5120);
    ui->ce0Lim->setMinimum(0);
    ui->ce0Lim->setMaximum(0xFFFF );
    ui->ceNLim->setMinimum(0);
    ui->ceNLim->setMaximum(0xFFFF);
    ui->ceMaxVel->setMinimum(defCE0Lim * CE_VEL_COEFF);
    ui->ceMaxVel->setMaximum(0xFFFF * CE_VEL_COEFF);
    ui->ceMinVel->setMinimum(defCE0Lim * CE_VEL_COEFF); // 1.2 mm/s
    ui->ceMinVel->setMaximum(0xFFFF * CE_VEL_COEFF);

}

CEsettingsForm::~CEsettingsForm()
{
    delete ui;
}

//-------Button cancel---------------------------
void CEsettingsForm::on_pushButton_5_clicked()
{
    this->destroy(true);
}


void CEsettingsForm::on_StartButton_clicked()
{
    if(curCecAxis != 0){
        std::vector<std::complex<double>> vec{};
        std::for_each(curCecParams.begin(), curCecParams.end(), [&](std::complex<double> d){
            static int i{0};
            if(prevCecParams.at(i) != d){
                if(i < 3)
                    uscChanged = true;
                else{
                    vec.push_back(d);
                    emit updateCeParams(curCecAxis, i,vec);
                    vec.clear();
                }
                prevCecParams.at(i) = d;
            }
            i++;
        });
        if(uscChanged){
            for(int i = 0; i<3; i++)
                vec.push_back(curCecParams.at(i));
            emit updateCeParams(curCecAxis, 0,vec);
            uscChanged = false;
        }

    }
}

void CEsettingsForm::on_uscCE0_valueChanged(double arg1)
{
 curCecParams[0].real(arg1);
}


void CEsettingsForm::on_uscCEN_valueChanged(double arg1)
{
    curCecParams[1].real(arg1);
}


void CEsettingsForm::on_uscCEMeas_valueChanged(double arg1)
{
    curCecParams[2].real(arg1);
}


void CEsettingsForm::on_ceMinVel_valueChanged(double arg1)
{
    curCecParams[3].real(arg1);
}


void CEsettingsForm::on_ceMaxVel_valueChanged(double arg1)
{
    curCecParams[4].real(arg1);
}


void CEsettingsForm::on_ce0Lim_valueChanged(double arg1)
{
    curCecParams[5].real(arg1);
}


void CEsettingsForm::on_ceNLim_valueChanged(double arg1)
{
    curCecParams[6].real(arg1);
}


void CEsettingsForm::on_defCEMinVel_clicked()
{
    curCecParams[3].real(defCEMinVel);
}

void CEsettingsForm::on_defCEMaxVel_clicked()
{
    curCecParams[4].real(defCEMaxVel);
}


void CEsettingsForm::on_defCE0Lim_clicked()
{
    curCecParams[5].real(defCE0Lim);
}


void CEsettingsForm::on_defCENLim_clicked()
{
    curCecParams[6].real(defCENLim);
}


void CEsettingsForm::on_uscCE0_img_valueChanged(double arg1)
{
    curCecParams[0].imag(arg1);

}


void CEsettingsForm::on_uscCEMeas_img_valueChanged(double arg1)
{
    curCecParams[2].imag(arg1);
}


void CEsettingsForm::on_cecAxis_currentIndexChanged(int index)
{
    curCecAxis = index;
    if(index != 0){
        emit initCeParams(curCecAxis);
    }
}

void CEsettingsForm::on_CeParams_received( std::array<std::complex<double>, 14> params){
    double tmp = 0.0;
    int i=0;

    tmp = params.at(i).real();
    ui->uscCE0->setValue(tmp);
    curCecParams[i].real(tmp);
    prevCecParams[i].real(tmp);

    tmp = params.at(i).imag();
    ui->uscCE0_img->setValue(tmp);
    curCecParams[i].imag(tmp);
    prevCecParams[i].imag(tmp);

    i++;

    tmp = params.at(i).real();
    ui->uscCEC1->setValue(tmp);
    curCecParams[i].real(tmp);
    prevCecParams[i].real(tmp);

    i++;

    tmp = params.at(i).real();
    ui->uscCEN->setValue(tmp);
    curCecParams[i].real(tmp);
    prevCecParams[i].real(tmp);

    tmp = params.at(i).imag();
    ui->uscCEN_img->setValue(tmp);
    curCecParams[i].imag(tmp);
    prevCecParams[i].imag(tmp);

    i++;

    tmp = params.at(i).real();
    ui->ceMinVel->setValue(tmp);
    curCecParams[i].real(tmp);
    prevCecParams[i].real(tmp);

    i++;

    tmp = params.at(i).real();
    ui->ceMaxVel->setValue(tmp);
    curCecParams[i].real(tmp);
    prevCecParams[i].real(tmp);

    i++;

    tmp = params.at(i).real();
    ui->ce0Lim->setValue(tmp);
    curCecParams[i].real(tmp);
    prevCecParams[i].real(tmp);

    i++;

    tmp = params.at(i).real();
    ui->ceNLim->setValue(tmp);
    curCecParams[i].real(tmp);
    prevCecParams[i].real(tmp);

    ui->calCE0->setText(QString::number(params.at(7).real()));
    ui->calCE0_img->setText(QString::number(params.at(7).imag()));
    ui->calCEMeas->setText(QString::number(params.at(8).real()));
    ui->calCEN->setText(QString::number(params.at(9).real()));
    ui->calCEN_img->setText(QString::number(params.at(9).imag()));
    ui->ce0Min->setText(QString::number(params.at(10).real()));
    ui->ce0Max->setText(QString::number(params.at(11).real()));
    ui->ceNMin->setText(QString::number(params.at(12).real()));
    ui->ceNMax->setText(QString::number(params.at(13).real()));

}

void CEsettingsForm::on_radioButton_2_clicked(bool checked)
{
    emit enableUsc(curCecAxis,checked);
}


void CEsettingsForm::on_radioButton_clicked(bool checked)
{
    emit enableUscStartup(curCecAxis,checked);
}


void CEsettingsForm::on_pushButton_12_clicked()
{
    emit initCeParams(curCecAxis);
}

