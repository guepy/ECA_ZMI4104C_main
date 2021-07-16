#ifndef MYSLOTS_H
#define MYSLOTS_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include "flyscanform.h"
#include "settingsform.h"
class MySlots : public QObject
{
    Q_OBJECT
    FlyscanForm *fs;
    SettingsForm *sf;
public:
    explicit MySlots(QObject *parent = nullptr);
    ~MySlots();
    void openForm();
    void closeForm();
signals:
    void openThis();
    void closeThis();
};

#endif // MYSLOTS_H
