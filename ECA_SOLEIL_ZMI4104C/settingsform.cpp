#include "settingsform.h"
#include "ui_settingsform.h"
#include <QDebug>
SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

//-----Button cancel-------
void SettingsForm::on_pushButton_5_clicked()
{
    closeForm();
}
void SettingsForm::closeForm(){
    emit closeThis();
    qDebug()<<"Close this emitted";
    this->deleteLater();
}
