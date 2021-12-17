/********************************************************************************
** Form generated from reading UI file 'flyscanform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLYSCANFORM_H
#define UI_FLYSCANFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlyscanForm
{
public:
    QWidget *SettingsForm;
    QVBoxLayout *verticalLayout;
    QWidget *horizontalWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *freqCheckBox;
    QSpinBox *spinBox_3;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QCheckBox *itCheckBox;
    QSpinBox *spinBox_2;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *npCheckBox;
    QSpinBox *spinBox;
    QWidget *horizontalWidget_21;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *NbrOfAxisWidget;
    QSpacerItem *horizontalSpacer_14;
    QWidget *selectAxisWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *fifoAxis1;
    QCheckBox *fifoAxis2;
    QCheckBox *fifoAxis3;
    QCheckBox *fifoAxis4;
    QWidget *horizontalWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QLineEdit *saveFile;
    QPushButton *pushButton;
    QWidget *ButtonForm;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *StartButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QWidget *statForm;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_7;
    QTextBrowser *display;
    QWidget *horizontalWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_16;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_14;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_8;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *meanAxis1;
    QTextBrowser *meanAxis2;
    QTextBrowser *meanAxis3;
    QTextBrowser *meanAxis4;
    QSpacerItem *horizontalSpacer_15;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *stdDevAxis1;
    QTextBrowser *stdDevAxis2;
    QTextBrowser *stdDevAxis3;
    QTextBrowser *stdDevAxis4;
    QSpacerItem *horizontalSpacer_12;

    void setupUi(QWidget *FlyscanForm)
    {
        if (FlyscanForm->objectName().isEmpty())
            FlyscanForm->setObjectName(QString::fromUtf8("FlyscanForm"));
        FlyscanForm->resize(834, 850);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/flyscan.png"), QSize(), QIcon::Normal, QIcon::Off);
        FlyscanForm->setWindowIcon(icon);
        FlyscanForm->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"QComboBox{\n"
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
"#FlyscanForm{\n"
"border: 1px solid;\n"
"	background-color:rgb(182, 182, 182);\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
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
"QComboBox, QLineEdit, #saveFile, QSpinBox{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"}\n"
"QComboBox, QLineEdit, QTextBrowser, QSpinBox{\n"
"border-radius:5px;\n"
"border:  2px solid white;\n"
"}"));
        SettingsForm = new QWidget(FlyscanForm);
        SettingsForm->setObjectName(QString::fromUtf8("SettingsForm"));
        SettingsForm->setGeometry(QRect(20, 260, 791, 251));
        SettingsForm->setStyleSheet(QString::fromUtf8("#SettingsForm{\n"
"border: 5px solid;\n"
"border-color: white;\n"
"	background-color: rgb(176, 207, 202);\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"}"));
        verticalLayout = new QVBoxLayout(SettingsForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalWidget_2 = new QWidget(SettingsForm);
        horizontalWidget_2->setObjectName(QString::fromUtf8("horizontalWidget_2"));
        horizontalWidget_2->setStyleSheet(QString::fromUtf8("QCheckBox{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"QLabel{\n"
"\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        freqCheckBox = new QCheckBox(horizontalWidget_2);
        freqCheckBox->setObjectName(QString::fromUtf8("freqCheckBox"));

        horizontalLayout_2->addWidget(freqCheckBox);

        spinBox_3 = new QSpinBox(horizontalWidget_2);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinBox_3->sizePolicy().hasHeightForWidth());
        spinBox_3->setSizePolicy(sizePolicy);
        spinBox_3->setMinimumSize(QSize(120, 35));

        horizontalLayout_2->addWidget(spinBox_3);

        label_6 = new QLabel(horizontalWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        itCheckBox = new QCheckBox(horizontalWidget_2);
        itCheckBox->setObjectName(QString::fromUtf8("itCheckBox"));

        horizontalLayout_2->addWidget(itCheckBox);

        spinBox_2 = new QSpinBox(horizontalWidget_2);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        sizePolicy.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy);
        spinBox_2->setMinimumSize(QSize(120, 35));

        horizontalLayout_2->addWidget(spinBox_2);

        label_7 = new QLabel(horizontalWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(label_7);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        npCheckBox = new QCheckBox(horizontalWidget_2);
        npCheckBox->setObjectName(QString::fromUtf8("npCheckBox"));

        horizontalLayout_2->addWidget(npCheckBox);

        spinBox = new QSpinBox(horizontalWidget_2);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        sizePolicy.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy);
        spinBox->setMinimumSize(QSize(120, 35));

        horizontalLayout_2->addWidget(spinBox);


        verticalLayout->addWidget(horizontalWidget_2);

        horizontalWidget_21 = new QWidget(SettingsForm);
        horizontalWidget_21->setObjectName(QString::fromUtf8("horizontalWidget_21"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalWidget_21->sizePolicy().hasHeightForWidth());
        horizontalWidget_21->setSizePolicy(sizePolicy1);
        horizontalLayout_6 = new QHBoxLayout(horizontalWidget_21);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_13);

        label_9 = new QLabel(horizontalWidget_21);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);
        label_9->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(label_9);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        comboBox = new QComboBox(horizontalWidget_21);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(180, 35));

        horizontalLayout_6->addWidget(comboBox);

        horizontalSpacer_6 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        label_11 = new QLabel(horizontalWidget_21);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(label_11);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        NbrOfAxisWidget = new QComboBox(horizontalWidget_21);
        NbrOfAxisWidget->addItem(QString());
        NbrOfAxisWidget->addItem(QString());
        NbrOfAxisWidget->addItem(QString());
        NbrOfAxisWidget->addItem(QString());
        NbrOfAxisWidget->setObjectName(QString::fromUtf8("NbrOfAxisWidget"));
        sizePolicy.setHeightForWidth(NbrOfAxisWidget->sizePolicy().hasHeightForWidth());
        NbrOfAxisWidget->setSizePolicy(sizePolicy);
        NbrOfAxisWidget->setMinimumSize(QSize(60, 35));

        horizontalLayout_6->addWidget(NbrOfAxisWidget);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_14);


        verticalLayout->addWidget(horizontalWidget_21);

        selectAxisWidget = new QWidget(SettingsForm);
        selectAxisWidget->setObjectName(QString::fromUtf8("selectAxisWidget"));
        selectAxisWidget->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_3 = new QHBoxLayout(selectAxisWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(selectAxisWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_3->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        fifoAxis1 = new QCheckBox(selectAxisWidget);
        fifoAxis1->setObjectName(QString::fromUtf8("fifoAxis1"));

        horizontalLayout_3->addWidget(fifoAxis1);

        fifoAxis2 = new QCheckBox(selectAxisWidget);
        fifoAxis2->setObjectName(QString::fromUtf8("fifoAxis2"));

        horizontalLayout_3->addWidget(fifoAxis2);

        fifoAxis3 = new QCheckBox(selectAxisWidget);
        fifoAxis3->setObjectName(QString::fromUtf8("fifoAxis3"));

        horizontalLayout_3->addWidget(fifoAxis3);

        fifoAxis4 = new QCheckBox(selectAxisWidget);
        fifoAxis4->setObjectName(QString::fromUtf8("fifoAxis4"));

        horizontalLayout_3->addWidget(fifoAxis4);


        verticalLayout->addWidget(selectAxisWidget);

        horizontalWidget_4 = new QWidget(SettingsForm);
        horizontalWidget_4->setObjectName(QString::fromUtf8("horizontalWidget_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(horizontalWidget_4->sizePolicy().hasHeightForWidth());
        horizontalWidget_4->setSizePolicy(sizePolicy3);
        horizontalWidget_4->setMinimumSize(QSize(0, 50));
        horizontalWidget_4->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_4 = new QHBoxLayout(horizontalWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_8 = new QLabel(horizontalWidget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);
        label_8->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_4->addWidget(label_8);

        saveFile = new QLineEdit(horizontalWidget_4);
        saveFile->setObjectName(QString::fromUtf8("saveFile"));
        saveFile->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(saveFile);

        pushButton = new QPushButton(horizontalWidget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(100, 40));

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout->addWidget(horizontalWidget_4);

        ButtonForm = new QWidget(FlyscanForm);
        ButtonForm->setObjectName(QString::fromUtf8("ButtonForm"));
        ButtonForm->setGeometry(QRect(20, 790, 801, 51));
        ButtonForm->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_5 = new QHBoxLayout(ButtonForm);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(420, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        StartButton = new QPushButton(ButtonForm);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        sizePolicy1.setHeightForWidth(StartButton->sizePolicy().hasHeightForWidth());
        StartButton->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        font.setKerning(true);
        StartButton->setFont(font);
        StartButton->setStyleSheet(QString::fromUtf8("background:green;\n"
"color: white;"));

        horizontalLayout_5->addWidget(StartButton);

        pushButton_4 = new QPushButton(ButtonForm);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setStyleSheet(QString::fromUtf8("background: red;\n"
"color: black;"));

        horizontalLayout_5->addWidget(pushButton_4);

        pushButton_5 = new QPushButton(ButtonForm);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setStyleSheet(QString::fromUtf8("background:red;\n"
"color: white;"));

        horizontalLayout_5->addWidget(pushButton_5);

        statForm = new QWidget(FlyscanForm);
        statForm->setObjectName(QString::fromUtf8("statForm"));
        statForm->setGeometry(QRect(20, 520, 791, 51));
        statForm->setStyleSheet(QString::fromUtf8("#statForm{\n"
"border: 2px solid;\n"
"	background-color:rgb(255, 246, 202);\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"}"));
        horizontalLayout_7 = new QHBoxLayout(statForm);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_9 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        label_10 = new QLabel(statForm);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("\n"
"color: blue;"));

        horizontalLayout_7->addWidget(label_10);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        label_12 = new QLabel(statForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("\n"
"color: blue;"));

        horizontalLayout_7->addWidget(label_12);

        horizontalSpacer_11 = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        pushButton_7 = new QPushButton(FlyscanForm);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(250, 20, 331, 61));
        pushButton_7->setStyleSheet(QString::fromUtf8("\n"
"font: 75 28pt \"Times New Roman\";\n"
"border: 2px solid gray;\n"
"padding: 0 8px;\n"
"border-radius:10px;\n"
"background-color:rgb(248, 243, 175);\n"
"text-align: cente"));
        display = new QTextBrowser(FlyscanForm);
        display->setObjectName(QString::fromUtf8("display"));
        display->setGeometry(QRect(20, 90, 791, 161));
        horizontalWidget = new QWidget(FlyscanForm);
        horizontalWidget->setObjectName(QString::fromUtf8("horizontalWidget"));
        horizontalWidget->setGeometry(QRect(20, 580, 791, 181));
        horizontalWidget->setStyleSheet(QString::fromUtf8("#horizontalWidget{\n"
"background-color: rgb(215, 222, 255);\n"
"border: 2px solid;\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"    padding: 0 8px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(horizontalWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_16 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_16);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(horizontalWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(80, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(9);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        verticalLayout_4->addWidget(label);

        label_4 = new QLabel(horizontalWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setFont(font1);
        label_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        verticalLayout_4->addWidget(label_4);

        label_14 = new QLabel(horizontalWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy2.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy2);
        label_14->setMinimumSize(QSize(80, 0));
        label_14->setFont(font1);
        label_14->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        verticalLayout_4->addWidget(label_14);

        label_13 = new QLabel(horizontalWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy2.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy2);
        label_13->setMinimumSize(QSize(80, 0));
        label_13->setFont(font1);
        label_13->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        verticalLayout_4->addWidget(label_13);


        horizontalLayout->addLayout(verticalLayout_4);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        verticalWidget = new QWidget(horizontalWidget);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setStyleSheet(QString::fromUtf8("\n"
"font: 75 12pt \"MS Shell Dlg 2\";"));
        verticalLayout_2 = new QVBoxLayout(verticalWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        meanAxis1 = new QTextBrowser(verticalWidget);
        meanAxis1->setObjectName(QString::fromUtf8("meanAxis1"));

        verticalLayout_2->addWidget(meanAxis1);

        meanAxis2 = new QTextBrowser(verticalWidget);
        meanAxis2->setObjectName(QString::fromUtf8("meanAxis2"));

        verticalLayout_2->addWidget(meanAxis2);

        meanAxis3 = new QTextBrowser(verticalWidget);
        meanAxis3->setObjectName(QString::fromUtf8("meanAxis3"));

        verticalLayout_2->addWidget(meanAxis3);

        meanAxis4 = new QTextBrowser(verticalWidget);
        meanAxis4->setObjectName(QString::fromUtf8("meanAxis4"));

        verticalLayout_2->addWidget(meanAxis4);


        horizontalLayout->addWidget(verticalWidget);

        horizontalSpacer_15 = new QSpacerItem(150, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_15);

        verticalWidget_2 = new QWidget(horizontalWidget);
        verticalWidget_2->setObjectName(QString::fromUtf8("verticalWidget_2"));
        verticalWidget_2->setStyleSheet(QString::fromUtf8("\n"
"font: 75 12pt \"MS Shell Dlg 2\";"));
        verticalLayout_3 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        stdDevAxis1 = new QTextBrowser(verticalWidget_2);
        stdDevAxis1->setObjectName(QString::fromUtf8("stdDevAxis1"));

        verticalLayout_3->addWidget(stdDevAxis1);

        stdDevAxis2 = new QTextBrowser(verticalWidget_2);
        stdDevAxis2->setObjectName(QString::fromUtf8("stdDevAxis2"));

        verticalLayout_3->addWidget(stdDevAxis2);

        stdDevAxis3 = new QTextBrowser(verticalWidget_2);
        stdDevAxis3->setObjectName(QString::fromUtf8("stdDevAxis3"));

        verticalLayout_3->addWidget(stdDevAxis3);

        stdDevAxis4 = new QTextBrowser(verticalWidget_2);
        stdDevAxis4->setObjectName(QString::fromUtf8("stdDevAxis4"));

        verticalLayout_3->addWidget(stdDevAxis4);


        horizontalLayout->addWidget(verticalWidget_2);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);


        retranslateUi(FlyscanForm);

        QMetaObject::connectSlotsByName(FlyscanForm);
    } // setupUi

    void retranslateUi(QWidget *FlyscanForm)
    {
        FlyscanForm->setWindowTitle(QCoreApplication::translate("FlyscanForm", "Flyscan", nullptr));
        freqCheckBox->setText(QCoreApplication::translate("FlyscanForm", "Freq", nullptr));
        label_6->setText(QCoreApplication::translate("FlyscanForm", "Hz", nullptr));
        itCheckBox->setText(QCoreApplication::translate("FlyscanForm", "Int time", nullptr));
        label_7->setText(QCoreApplication::translate("FlyscanForm", "\302\265s", nullptr));
        npCheckBox->setText(QCoreApplication::translate("FlyscanForm", "Nbr_Pts", nullptr));
        label_9->setText(QCoreApplication::translate("FlyscanForm", "Method", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("FlyscanForm", "RAM DATA Flyscan", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("FlyscanForm", "FIFO Flyscan", nullptr));

        label_11->setText(QCoreApplication::translate("FlyscanForm", "Nbr_axis", nullptr));
        NbrOfAxisWidget->setItemText(0, QCoreApplication::translate("FlyscanForm", "1", nullptr));
        NbrOfAxisWidget->setItemText(1, QCoreApplication::translate("FlyscanForm", "2", nullptr));
        NbrOfAxisWidget->setItemText(2, QCoreApplication::translate("FlyscanForm", "3", nullptr));
        NbrOfAxisWidget->setItemText(3, QCoreApplication::translate("FlyscanForm", "4", nullptr));

        label_5->setText(QCoreApplication::translate("FlyscanForm", "Select Axis : ", nullptr));
        fifoAxis1->setText(QCoreApplication::translate("FlyscanForm", "Axis1", nullptr));
        fifoAxis2->setText(QCoreApplication::translate("FlyscanForm", "Axis2", nullptr));
        fifoAxis3->setText(QCoreApplication::translate("FlyscanForm", "Axis3", nullptr));
        fifoAxis4->setText(QCoreApplication::translate("FlyscanForm", "Axis4", nullptr));
        label_8->setText(QCoreApplication::translate("FlyscanForm", "Save folder", nullptr));
        pushButton->setText(QCoreApplication::translate("FlyscanForm", "Browse", nullptr));
        StartButton->setText(QCoreApplication::translate("FlyscanForm", "Start scan", nullptr));
        pushButton_4->setText(QCoreApplication::translate("FlyscanForm", "Stop scan", nullptr));
        pushButton_5->setText(QCoreApplication::translate("FlyscanForm", "Cancel", nullptr));
        label_10->setText(QCoreApplication::translate("FlyscanForm", "Mean", nullptr));
        label_12->setText(QCoreApplication::translate("FlyscanForm", "Standard deviation", nullptr));
        pushButton_7->setText(QCoreApplication::translate("FlyscanForm", "Continuous scan", nullptr));
        label->setText(QCoreApplication::translate("FlyscanForm", "Axis1", nullptr));
        label_4->setText(QCoreApplication::translate("FlyscanForm", "Axis2", nullptr));
        label_14->setText(QCoreApplication::translate("FlyscanForm", "Axis3", nullptr));
        label_13->setText(QCoreApplication::translate("FlyscanForm", "Axis4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlyscanForm: public Ui_FlyscanForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLYSCANFORM_H
