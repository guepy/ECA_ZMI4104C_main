#include "cesettingsform.h"
#include "ui_cesettingsform.h"

CEsettingsForm::CEsettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEsettingsForm)
{
    ui->setupUi(this);
    ui->uscCE0->setMinimum(0);
    ui->uscCE0->setMaximum(5120);
    ui->ce0Lim->setMinimum(0);
    ui->ce0Lim->setMaximum(0xFFFF * 0.0763);
    ui->ceNLim->setMinimum(0);
    ui->ceNLim->setMaximum(0xFFFF * 0.0763);
    ui->ceMaxVel->setMinimum(96 * 0.0763);
    ui->ceMaxVel->setMaximum(0xFFFF * 0.0763);
    ui->ceMinVel->setMinimum(96 * 0.0763); // 1.2 mm/s
    ui->ceMinVel->setMaximum(0xFFFF * 0.0763);
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


void CEsettingsForm::on_uscCE0_valueChanged(double arg1)
{

}

