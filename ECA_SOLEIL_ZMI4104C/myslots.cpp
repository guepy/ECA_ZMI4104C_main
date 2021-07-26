#include "myslots.h"

MySlots::MySlots(QObject *parent) : QObject(parent){
    fs = new FlyscanForm;
    sf=new SettingsForm;
    posOff = new positionOffsetForm;
    posPres= new presetPositionForm;
}

MySlots::~MySlots(){}
;

// --------Bouton continuous acquisition-----------------------
void MySlots::openFsForm(){
    fs->show();
}
void MySlots::closeFsForm(){
    emit closeFlyscan();
    fs->close();
    //delete fs;
    //delete ui;
}
//-------------fin----------------------------------

// --------menu bar settings -----------------------
void MySlots::openSettingsForm(){
    sf->show();
}
void MySlots::closeSettingsForm(){
    emit closeSettings();
    sf->close();
    //delete fs;
    //delete ui;
}
//-------------fin----------------------------------

// --------button set position offesets -----------------------
void MySlots::openPositionOffsetForm(){
    posOff->show();
}
void MySlots::closePositionOffsetForm(){
    emit closePositionOffset();
    posOff->close();
    //delete fs;
    //delete ui;
}
//-------------fin----------------------------------

// --------button set position offesets -----------------------
void MySlots::openPresetPositionForm(){
    posPres->show();
}
void MySlots::closePresetPositionForm(){
    emit closePositionOffset();
    posPres->close();
    //delete fs;
    //delete ui;
}
//-------------fin----------------------------------
