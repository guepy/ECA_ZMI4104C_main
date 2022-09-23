QT       += core gui #// generate undefined reference to _imp_...
# To correct those errors, I append widgets at the end of the line and remove "core"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cesettingsform.cpp \
    dataprocessing.cpp \
    flyscanform.cpp \
    graphsform.cpp \
    main.cpp \
    mainwindow.cpp \
    positionoffsetform.cpp \
    presetpositionform.cpp \
    qcustomplot/qcustomplot.cpp \
    serialoutput.cpp \
    settingsform.cpp

HEADERS += \
    ../eca_soleil_zmi4104_lib/eca_soleil_zmi4104c.h \
    ../eca_soleil_zmi4104_lib/zVME_const.h \
    cesettingsform.h \
    dataprocessing.h \
    flyscanform.h \
    graphsform.h \
    mainwindow.h \
    positionoffsetform.h \
    presetpositionform.h \
    qcustomplot/qcustomplot.h \
    serialoutput.h \
    settingsform.h \
    sis1100w.h \
    sis1100wStat.h \
    sis1100wType.h \
    sis3100.h \
    sis3100_vme_calls.h \
    wingetopt.h

FORMS += \
    cesettingsform.ui \
    flyscanform.ui \
    graphsform.ui \
    mainwindow.ui \
    positionoffsetform.ui \
    presetpositionform.ui \
    serialoutput.ui \
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


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../eca_soleil_zmi4104_lib/release/ -leca_soleil_zmi4104_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../eca_soleil_zmi4104_lib/release/ -leca_soleil_zmi4104_lib

INCLUDEPATH += $$PWD/../eca_soleil_zmi4104_lib/Release
DEPENDPATH += $$PWD/../eca_soleil_zmi4104_lib/Release

win32: LIBS += -L$$PWD/../eca_soleil_zmi4104_lib/sis1100_zmilib/ -lsis1100w

INCLUDEPATH += $$PWD/../eca_soleil_zmi4104_lib/sis1100_zmilib
DEPENDPATH += $$PWD/../eca_soleil_zmi4104_lib/sis1100_zmilib
