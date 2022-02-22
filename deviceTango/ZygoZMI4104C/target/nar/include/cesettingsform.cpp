#include "cesettingsform.h"
#include "ui_cesettingsform.h"

CEsettingsForm::CEsettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEsettingsForm)
{
    ui->setupUi(this);
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

