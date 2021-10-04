#ifndef MYSLOTS_H
#define MYSLOTS_H

#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include "flyscanform.h"
#include "settingsform.h"
#include "positionoffsetform.h"
#include "presetpositionform.h"
#include "../eca_soleil_zmi4104_lib/eca_soleil_zmi4104c.h"
#include <QThread>
#include<QObject>


class MySlots : public QObject
{
    Q_OBJECT
public:
    explicit MySlots(QObject *parent = nullptr);
    ~MySlots();
signals:

};

#endif // MYSLOTS_H
