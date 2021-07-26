QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cesettingsform.cpp \
    flyscanform.cpp \
    main.cpp \
    mainwindow.cpp \
    myslots.cpp \
    positionoffsetform.cpp \
    presetpositionform.cpp \
    settingsform.cpp

HEADERS += \
    cesettingsform.h \
    flyscanform.h \
    mainwindow.h \
    myslots.h \
    positionoffsetform.h \
    presetpositionform.h \
    settingsform.h

FORMS += \
    cesettingsform.ui \
    flyscanform.ui \
    mainwindow.ui \
    positionoffsetform.ui \
    presetpositionform.ui \
    settingsform.ui

TRANSLATIONS += \
    ECA_SOLEIL_ZMI4104C_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc
