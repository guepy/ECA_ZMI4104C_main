#include "myslots.h"

MySlots::MySlots(QObject *parent) : QObject(parent){
    fs = new FlyscanForm;
    sf=new SettingsForm;
}

MySlots::~MySlots(){}
;
void MySlots::openForm(){
    fs->show();
    sf->show();
}
void MySlots::closeForm(){
    emit closeThis();
    fs->close();
    sf->close();
    //delete fs;
    //delete ui;
}
