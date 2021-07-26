#include "presetpositionform.h"
#include "ui_presetpositionform.h"

presetPositionForm::presetPositionForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::presetPositionForm)
{
    ui->setupUi(this);
}

presetPositionForm::~presetPositionForm()
{
    delete ui;
}

void presetPositionForm::on_pushButton_5_clicked()
{
    this->destroy(true);
}

