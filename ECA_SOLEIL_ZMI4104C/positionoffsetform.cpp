#include "positionoffsetform.h"
#include "ui_positionoffsetform.h"

positionOffsetForm::positionOffsetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::positionOffsetForm)
{
    ui->setupUi(this);
    //ui->lineEdit_11->textChanged()
    ui->lineEdit_11->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), ui->lineEdit_11));
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

