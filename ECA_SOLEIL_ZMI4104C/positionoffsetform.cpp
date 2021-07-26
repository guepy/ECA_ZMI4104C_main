#include "positionoffsetform.h"
#include "ui_positionoffsetform.h"

positionOffsetForm::positionOffsetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::positionOffsetForm)
{
    ui->setupUi(this);
}

positionOffsetForm::~positionOffsetForm()
{
    delete ui;
}

//---Button cancel-----------------
void positionOffsetForm::on_pushButton_5_clicked()
{
    this->destroy(true);
}

