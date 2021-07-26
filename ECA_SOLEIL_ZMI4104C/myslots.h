#ifndef MYSLOTS_H
#define MYSLOTS_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include "flyscanform.h"
#include "settingsform.h"
#include "positionoffsetform.h"
#include "presetpositionform.h"

class MySlots : public QObject
{
    Q_OBJECT
    FlyscanForm *fs;
    SettingsForm *sf;
    positionOffsetForm *posOff;
    presetPositionForm *posPres;

public:
    explicit MySlots(QObject *parent = nullptr);
    ~MySlots();
    // --------Bouton continuous acquisition-----------------------
    void openFsForm();
    void closeFsForm();
    // --------menu bar settings-----------------------
    void openSettingsForm();
    void closeSettingsForm();
    // --------button set position offsets-----------------------
    void openPositionOffsetForm();
    void closePositionOffsetForm();
    // --------button preset position -----------------------
    void openPresetPositionForm();
    void closePresetPositionForm();
signals:
    // --------Bouton continuous acquisition-----------------------
    void openFlyscan();
    void closeFlyscan();
    // --------Bouton continuous acquisition-----------------------
    void openSettings();
    void closeSettings();
    // --------button set position offsets-----------------------
    void openPositionOffset();
    void closePositionOffset();
    // --------button preset position ------------------------
    void openPresetPosition();
    void closePresetPosition();

    //--------Connexion myslot <-> settingsForm

};

#endif // MYSLOTS_H
