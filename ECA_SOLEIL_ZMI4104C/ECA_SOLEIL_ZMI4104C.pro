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
    eca_soleil_zmi4104c.h \
    flyscanform.h \
    mainwindow.h \
    myslots.h \
    positionoffsetform.h \
    presetpositionform.h \
    settingsform.h \
    sis1100w.h \
    sis1100wStat.h \
    sis1100wType.h \
    sis3100.h \
    sis3100_vme_calls.h \
    wingetopt.h \
    zVME_const.h

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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../eca_soleil_zmi4104_lib/x64/Release/ -leca_soleil_zmi4104_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../eca_soleil_zmi4104_lib/x64/Debug/ -leca_soleil_zmi4104_lib

INCLUDEPATH += $$PWD/../eca_soleil_zmi4104_lib/x64/Release
DEPENDPATH += $$PWD/../eca_soleil_zmi4104_lib/x64/Release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../eca_soleil_zmi4104_lib/sis1100_zmilib/ -lsis1100w_x64
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../eca_soleil_zmi4104_lib/sis1100_zmilib/ -lsis1100w_x64

INCLUDEPATH += $$PWD/../eca_soleil_zmi4104_lib/sis1100_zmilib
DEPENDPATH += $$PWD/../eca_soleil_zmi4104_lib/sis1100_zmilib
