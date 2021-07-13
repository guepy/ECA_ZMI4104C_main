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
    delete ui;
}
