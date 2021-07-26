#include "flyscanform.h"
#include "ui_flyscanform.h"

FlyscanForm::FlyscanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlyscanForm)
{
    ui->setupUi(this);
}

FlyscanForm::~FlyscanForm()
{
    //emit closeThis();
    delete ui;
}

//-----Button cancel--------------------
void FlyscanForm::on_pushButton_5_clicked()
{
    this->destroy(true);
}

