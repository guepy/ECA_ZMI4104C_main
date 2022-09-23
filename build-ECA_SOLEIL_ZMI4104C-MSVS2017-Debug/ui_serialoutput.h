/********************************************************************************
** Form generated from reading UI file 'serialoutput.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALOUTPUT_H
#define UI_SERIALOUTPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialOutput
{
public:
    QWidget *seroutGlobal;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *verticalSpacer_3;
    QWidget *horizontalWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSpacerItem *horizontalSpacer_8;
    QComboBox *serialClockIn;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *serialDriverOutput;
    QSpacerItem *verticalSpacer_6;
    QWidget *horizontalWidget_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_12;
    QSpinBox *serialBusSamplingFreq;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *verticalSpacer;
    QWidget *horizontalWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *bitWindow;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QComboBox *precision;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *startSerialOutput;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *stopSerialOutput;
    QSpacerItem *horizontalSpacer;
    QPushButton *configureSerialOutput;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *serialOutput)
    {
        if (serialOutput->objectName().isEmpty())
            serialOutput->setObjectName(QString::fromUtf8("serialOutput"));
        serialOutput->resize(693, 428);
        serialOutput->setMinimumSize(QSize(693, 428));
        serialOutput->setStyleSheet(QString::fromUtf8("\n"
"QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"QComboBox, QLineEdit, QSpinBox{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border-radius:5px;\n"
"}\n"
"QPushButton, QToolButton{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border: 2px solid gray;\n"
"padding: 0 8px;\n"
"border-radius:10px;\n"
"text-align: center;\n"
"}\n"
"#serialOuput{\n"
"background-color:red;\n"
"	border-color: rgb(85, 170, 255);\n"
"	border-top-color:rgb(85, 170, 255);\n"
"}\n"
"	#ceVWidget{\n"
"	background-color:rgb(134, 186, 255);\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"}\n"
"QPushButton#resetButtonAxis1,#resetButtonAxis2,#resetButtonAxis3,#resetButtonAxis4,#resetButtonAllAxis,#resetCEerrorsButton{\n"
"background:rgb(198, 114, 92);\n"
"color: white;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border:  2px solid white;\n"
"border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"border:  2px solid white;\n"
"border-radius: 10px;\n"
"}\n"
"#seroutGlobal{\n"
"border: 1px solid;\n"
"	bac"
                        "kground-color:rgb(177, 177, 177);\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"}\n"
""));
        seroutGlobal = new QWidget(serialOutput);
        seroutGlobal->setObjectName(QString::fromUtf8("seroutGlobal"));
        seroutGlobal->setGeometry(QRect(9, 9, 675, 410));
        verticalLayout = new QVBoxLayout(seroutGlobal);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        label_5 = new QLabel(seroutGlobal);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(100, 50));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(25);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(9);
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("\n"
"font: 75 25pt \"Times New Roman\";"));

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalWidget_3 = new QWidget(seroutGlobal);
        horizontalWidget_3->setObjectName(QString::fromUtf8("horizontalWidget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalWidget_3->sizePolicy().hasHeightForWidth());
        horizontalWidget_3->setSizePolicy(sizePolicy1);
        horizontalLayout_3 = new QHBoxLayout(horizontalWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(horizontalWidget_3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        serialClockIn = new QComboBox(horizontalWidget_3);
        serialClockIn->addItem(QString());
        serialClockIn->addItem(QString());
        serialClockIn->setObjectName(QString::fromUtf8("serialClockIn"));
        sizePolicy.setHeightForWidth(serialClockIn->sizePolicy().hasHeightForWidth());
        serialClockIn->setSizePolicy(sizePolicy);
        serialClockIn->setMinimumSize(QSize(0, 40));

        horizontalLayout_3->addWidget(serialClockIn);

        horizontalSpacer_6 = new QSpacerItem(80, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        label_2 = new QLabel(horizontalWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        serialDriverOutput = new QComboBox(horizontalWidget_3);
        serialDriverOutput->addItem(QString());
        serialDriverOutput->addItem(QString());
        serialDriverOutput->setObjectName(QString::fromUtf8("serialDriverOutput"));
        sizePolicy.setHeightForWidth(serialDriverOutput->sizePolicy().hasHeightForWidth());
        serialDriverOutput->setSizePolicy(sizePolicy);
        serialDriverOutput->setMinimumSize(QSize(0, 40));

        horizontalLayout_3->addWidget(serialDriverOutput);


        verticalLayout->addWidget(horizontalWidget_3);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        horizontalWidget_4 = new QWidget(seroutGlobal);
        horizontalWidget_4->setObjectName(QString::fromUtf8("horizontalWidget_4"));
        sizePolicy1.setHeightForWidth(horizontalWidget_4->sizePolicy().hasHeightForWidth());
        horizontalWidget_4->setSizePolicy(sizePolicy1);
        horizontalLayout_5 = new QHBoxLayout(horizontalWidget_4);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(horizontalWidget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_12);

        serialBusSamplingFreq = new QSpinBox(horizontalWidget_4);
        serialBusSamplingFreq->setObjectName(QString::fromUtf8("serialBusSamplingFreq"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(serialBusSamplingFreq->sizePolicy().hasHeightForWidth());
        serialBusSamplingFreq->setSizePolicy(sizePolicy2);
        serialBusSamplingFreq->setMinimumSize(QSize(0, 40));
        serialBusSamplingFreq->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(serialBusSamplingFreq);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_13);


        verticalLayout->addWidget(horizontalWidget_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalWidget_2 = new QWidget(seroutGlobal);
        horizontalWidget_2->setObjectName(QString::fromUtf8("horizontalWidget_2"));
        sizePolicy1.setHeightForWidth(horizontalWidget_2->sizePolicy().hasHeightForWidth());
        horizontalWidget_2->setSizePolicy(sizePolicy1);
        horizontalWidget_2->setMinimumSize(QSize(0, 50));
        horizontalLayout_2 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(horizontalWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        bitWindow = new QComboBox(horizontalWidget_2);
        bitWindow->addItem(QString());
        bitWindow->addItem(QString());
        bitWindow->addItem(QString());
        bitWindow->addItem(QString());
        bitWindow->addItem(QString());
        bitWindow->addItem(QString());
        bitWindow->addItem(QString());
        bitWindow->addItem(QString());
        bitWindow->setObjectName(QString::fromUtf8("bitWindow"));
        sizePolicy1.setHeightForWidth(bitWindow->sizePolicy().hasHeightForWidth());
        bitWindow->setSizePolicy(sizePolicy1);
        bitWindow->setMinimumSize(QSize(0, 40));

        horizontalLayout_2->addWidget(bitWindow);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        label_3 = new QLabel(horizontalWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        precision = new QComboBox(horizontalWidget_2);
        precision->addItem(QString());
        precision->addItem(QString());
        precision->setObjectName(QString::fromUtf8("precision"));
        sizePolicy1.setHeightForWidth(precision->sizePolicy().hasHeightForWidth());
        precision->setSizePolicy(sizePolicy1);
        precision->setMinimumSize(QSize(80, 40));

        horizontalLayout_2->addWidget(precision);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addWidget(horizontalWidget_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        widget = new QWidget(seroutGlobal);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        widget->setMinimumSize(QSize(0, 50));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_9 = new QSpacerItem(140, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        startSerialOutput = new QPushButton(widget);
        startSerialOutput->setObjectName(QString::fromUtf8("startSerialOutput"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(startSerialOutput->sizePolicy().hasHeightForWidth());
        startSerialOutput->setSizePolicy(sizePolicy4);
        startSerialOutput->setStyleSheet(QString::fromUtf8("background-color: rgb(20, 175, 64);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(startSerialOutput);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        stopSerialOutput = new QPushButton(widget);
        stopSerialOutput->setObjectName(QString::fromUtf8("stopSerialOutput"));
        sizePolicy4.setHeightForWidth(stopSerialOutput->sizePolicy().hasHeightForWidth());
        stopSerialOutput->setSizePolicy(sizePolicy4);
        stopSerialOutput->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 34, 93);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(stopSerialOutput);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        configureSerialOutput = new QPushButton(widget);
        configureSerialOutput->setObjectName(QString::fromUtf8("configureSerialOutput"));
        sizePolicy4.setHeightForWidth(configureSerialOutput->sizePolicy().hasHeightForWidth());
        configureSerialOutput->setSizePolicy(sizePolicy4);
        configureSerialOutput->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 235, 153);\n"
""));

        horizontalLayout->addWidget(configureSerialOutput);


        verticalLayout->addWidget(widget);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);


        retranslateUi(serialOutput);

        QMetaObject::connectSlotsByName(serialOutput);
    } // setupUi

    void retranslateUi(QWidget *serialOutput)
    {
        serialOutput->setWindowTitle(QCoreApplication::translate("serialOutput", "serialOutput", nullptr));
        label_5->setText(QCoreApplication::translate("serialOutput", "Configure serial output", nullptr));
        label->setText(QCoreApplication::translate("serialOutput", "Serial clock In", nullptr));
        serialClockIn->setItemText(0, QCoreApplication::translate("serialOutput", "SCLK0", nullptr));
        serialClockIn->setItemText(1, QCoreApplication::translate("serialOutput", "SCLK1", nullptr));

        label_2->setText(QCoreApplication::translate("serialOutput", "Driver Output", nullptr));
        serialDriverOutput->setItemText(0, QCoreApplication::translate("serialOutput", "P2z", nullptr));
        serialDriverOutput->setItemText(1, QCoreApplication::translate("serialOutput", "P2d", nullptr));

        label_6->setText(QCoreApplication::translate("serialOutput", "Sampling Frequency", nullptr));
        label_4->setText(QCoreApplication::translate("serialOutput", "Position bit Window", nullptr));
        bitWindow->setItemText(0, QCoreApplication::translate("serialOutput", "BW1", nullptr));
        bitWindow->setItemText(1, QCoreApplication::translate("serialOutput", "BW2", nullptr));
        bitWindow->setItemText(2, QCoreApplication::translate("serialOutput", "BW4", nullptr));
        bitWindow->setItemText(3, QCoreApplication::translate("serialOutput", "BW8", nullptr));
        bitWindow->setItemText(4, QCoreApplication::translate("serialOutput", "BW16", nullptr));
        bitWindow->setItemText(5, QCoreApplication::translate("serialOutput", "BW32", nullptr));
        bitWindow->setItemText(6, QCoreApplication::translate("serialOutput", "BWhalf", nullptr));
        bitWindow->setItemText(7, QCoreApplication::translate("serialOutput", "BWquater", nullptr));

        label_3->setText(QCoreApplication::translate("serialOutput", "Position precision", nullptr));
        precision->setItemText(0, QCoreApplication::translate("serialOutput", "32 Bits", nullptr));
        precision->setItemText(1, QCoreApplication::translate("serialOutput", "37 Bits", nullptr));

        startSerialOutput->setText(QCoreApplication::translate("serialOutput", "Start ", nullptr));
        stopSerialOutput->setText(QCoreApplication::translate("serialOutput", "Stop", nullptr));
        configureSerialOutput->setText(QCoreApplication::translate("serialOutput", "Apply", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serialOutput: public Ui_serialOutput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALOUTPUT_H
