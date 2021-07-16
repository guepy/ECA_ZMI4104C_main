/********************************************************************************
** Form generated from reading UI file 'settingsform.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSFORM_H
#define UI_SETTINGSFORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsForm
{
public:
    QTabWidget *settingsTab;
    QWidget *tab;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_27;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label;
    QLineEdit *lineEdit_14;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_15;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_18;
    QComboBox *comboBox_5;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_19;
    QSpacerItem *horizontalSpacer_19;
    QComboBox *comboBox_8;
    QWidget *tab_2;
    QWidget *vWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *lineEdit_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit_2;
    QWidget *tab_3;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QLineEdit *lineEdit_3;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_7;
    QLineEdit *lineEdit_4;
    QWidget *tab_4;
    QWidget *verticalWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *lineEdit_8;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *lineEdit_9;
    QWidget *verticalWidget_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_26;
    QSpacerItem *horizontalSpacer_17;
    QComboBox *comboBox_7;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_15;
    QComboBox *comboBox_4;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_25;
    QSpacerItem *horizontalSpacer_16;
    QComboBox *comboBox_9;
    QWidget *tab_5;
    QWidget *clockForm;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_21;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_10;
    QLineEdit *lineEdit_10;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_20;
    QWidget *tab_6;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_24;
    QSpacerItem *horizontalSpacer_24;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_23;
    QLabel *label_23;
    QSpacerItem *horizontalSpacer_25;
    QSpinBox *spinBox_2;
    QWidget *tab_7;
    QWidget *vWidget_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_12;
    QLineEdit *lineEdit_11;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *lineEdit_12;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_14;
    QLineEdit *lineEdit_13;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_21;
    QLineEdit *lineEdit_15;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_22;
    QSpacerItem *horizontalSpacer_22;
    QLineEdit *lineEdit_16;
    QWidget *ButtonForm;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_2;
    QPushButton *StartButton;
    QPushButton *pushButton_5;
    QTextEdit *textEdit;

    void setupUi(QWidget *SettingsForm)
    {
        if (SettingsForm->objectName().isEmpty())
            SettingsForm->setObjectName(QString::fromUtf8("SettingsForm"));
        SettingsForm->resize(709, 723);
        QFont font;
        font.setBold(true);
        SettingsForm->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/settings_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        SettingsForm->setWindowIcon(icon);
        SettingsForm->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"}\n"
"QComboBox, QLineEdit{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border-radius:1px;\n"
"border: 2px solid;\n"
"}\n"
"QPushButton, QToolButton{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border: 2px solid gray;\n"
"padding: 0 8px;\n"
"border-radius:10px;\n"
"text-align: center;\n"
"}\n"
"QRadioButton{\n"
"font: 75 10pt \"MS Shell Dlg 2\";\n"
"}\n"
"QTabWidget{\n"
"color: red;\n"
"}"));
        settingsTab = new QTabWidget(SettingsForm);
        settingsTab->setObjectName(QString::fromUtf8("settingsTab"));
        settingsTab->setGeometry(QRect(10, 0, 691, 511));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingsTab->sizePolicy().hasHeightForWidth());
        settingsTab->setSizePolicy(sizePolicy);
        settingsTab->setStyleSheet(QString::fromUtf8("#tab_4,#tab_5,#tab_3,#tab_2,#tab_6,#tab_7{\n"
"background-color: rgb(240, 240, 240);\n"
"}\n"
""));
        settingsTab->setIconSize(QSize(16, 35));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalWidget = new QWidget(tab);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        verticalWidget->setGeometry(QRect(20, 20, 451, 231));
        verticalWidget->setStyleSheet(QString::fromUtf8("#verticalWidget{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(verticalWidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_27 = new QLabel(verticalWidget);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_22->addWidget(label_27);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_20);

        label = new QLabel(verticalWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_22->addWidget(label);

        lineEdit_14 = new QLineEdit(verticalWidget);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_14->sizePolicy().hasHeightForWidth());
        lineEdit_14->setSizePolicy(sizePolicy1);
        lineEdit_14->setMinimumSize(QSize(70, 35));

        horizontalLayout_22->addWidget(lineEdit_14);


        verticalLayout_7->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_15 = new QLabel(verticalWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_21->addWidget(label_15);

        comboBox = new QComboBox(verticalWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(230, 35));

        horizontalLayout_21->addWidget(comboBox);


        verticalLayout_7->addLayout(horizontalLayout_21);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_16 = new QLabel(verticalWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_19->addWidget(label_16);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_18);

        comboBox_5 = new QComboBox(verticalWidget);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        sizePolicy1.setHeightForWidth(comboBox_5->sizePolicy().hasHeightForWidth());
        comboBox_5->setSizePolicy(sizePolicy1);
        comboBox_5->setMinimumSize(QSize(80, 35));

        horizontalLayout_19->addWidget(comboBox_5);


        verticalLayout_7->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_19 = new QLabel(verticalWidget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_20->addWidget(label_19);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_19);

        comboBox_8 = new QComboBox(verticalWidget);
        comboBox_8->addItem(QString());
        comboBox_8->addItem(QString());
        comboBox_8->setObjectName(QString::fromUtf8("comboBox_8"));
        sizePolicy1.setHeightForWidth(comboBox_8->sizePolicy().hasHeightForWidth());
        comboBox_8->setSizePolicy(sizePolicy1);
        comboBox_8->setMinimumSize(QSize(70, 35));

        horizontalLayout_20->addWidget(comboBox_8);


        verticalLayout_7->addLayout(horizontalLayout_20);

        settingsTab->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        vWidget = new QWidget(tab_2);
        vWidget->setObjectName(QString::fromUtf8("vWidget"));
        vWidget->setGeometry(QRect(20, 30, 481, 191));
        vWidget->setStyleSheet(QString::fromUtf8("#vWidget{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout = new QVBoxLayout(vWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(vWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lineEdit = new QLineEdit(vWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMinimumSize(QSize(130, 35));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(vWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        lineEdit_5 = new QLineEdit(vWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy1.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy1);
        lineEdit_5->setMinimumSize(QSize(130, 35));

        horizontalLayout_2->addWidget(lineEdit_5);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(vWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        lineEdit_6 = new QLineEdit(vWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        sizePolicy1.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy1);
        lineEdit_6->setMinimumSize(QSize(130, 35));

        horizontalLayout_3->addWidget(lineEdit_6);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(vWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        lineEdit_2 = new QLineEdit(vWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setMinimumSize(QSize(130, 35));

        horizontalLayout_4->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_4);

        settingsTab->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalWidget_2 = new QWidget(tab_3);
        verticalWidget_2->setObjectName(QString::fromUtf8("verticalWidget_2"));
        verticalWidget_2->setGeometry(QRect(20, 50, 351, 81));
        verticalWidget_2->setStyleSheet(QString::fromUtf8("#verticalWidget_2{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        radioButton = new QRadioButton(verticalWidget_2);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setStyleSheet(QString::fromUtf8("font: 75 11pt \"MS Shell Dlg 2\";"));

        horizontalLayout_6->addWidget(radioButton);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(verticalWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_5->addWidget(label_6);

        lineEdit_3 = new QLineEdit(verticalWidget_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        lineEdit_3->setMinimumSize(QSize(130, 35));

        horizontalLayout_5->addWidget(lineEdit_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        label_7 = new QLabel(verticalWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        lineEdit_4 = new QLineEdit(verticalWidget_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy1);
        lineEdit_4->setMinimumSize(QSize(130, 35));

        horizontalLayout_5->addWidget(lineEdit_4);


        verticalLayout_2->addLayout(horizontalLayout_5);

        settingsTab->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalWidget_3 = new QWidget(tab_4);
        verticalWidget_3->setObjectName(QString::fromUtf8("verticalWidget_3"));
        verticalWidget_3->setGeometry(QRect(20, 30, 431, 141));
        verticalWidget_3->setStyleSheet(QString::fromUtf8("#verticalWidget_3{border: 1px solid;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(verticalWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_9 = new QLabel(verticalWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_7->addWidget(label_9);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        lineEdit_7 = new QLineEdit(verticalWidget_3);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy1.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy1);
        lineEdit_7->setMinimumSize(QSize(130, 35));

        horizontalLayout_7->addWidget(lineEdit_7);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_10 = new QLabel(verticalWidget_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_8->addWidget(label_10);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_8);

        lineEdit_8 = new QLineEdit(verticalWidget_3);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        sizePolicy1.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy1);
        lineEdit_8->setMinimumSize(QSize(130, 35));

        horizontalLayout_8->addWidget(lineEdit_8);


        verticalLayout_3->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_11 = new QLabel(verticalWidget_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_9->addWidget(label_11);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_9);

        lineEdit_9 = new QLineEdit(verticalWidget_3);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));
        sizePolicy1.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy1);
        lineEdit_9->setMinimumSize(QSize(130, 35));

        horizontalLayout_9->addWidget(lineEdit_9);


        verticalLayout_3->addLayout(horizontalLayout_9);

        verticalWidget_4 = new QWidget(tab_4);
        verticalWidget_4->setObjectName(QString::fromUtf8("verticalWidget_4"));
        verticalWidget_4->setGeometry(QRect(20, 200, 431, 131));
        verticalWidget_4->setStyleSheet(QString::fromUtf8("#verticalWidget_4{border: 1px solid;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(verticalWidget_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_26 = new QLabel(verticalWidget_4);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_18->addWidget(label_26);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_17);

        comboBox_7 = new QComboBox(verticalWidget_4);
        comboBox_7->addItem(QString());
        comboBox_7->addItem(QString());
        comboBox_7->setObjectName(QString::fromUtf8("comboBox_7"));
        sizePolicy1.setHeightForWidth(comboBox_7->sizePolicy().hasHeightForWidth());
        comboBox_7->setSizePolicy(sizePolicy1);
        comboBox_7->setMinimumSize(QSize(70, 35));

        horizontalLayout_18->addWidget(comboBox_7);


        verticalLayout_5->addLayout(horizontalLayout_18);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_14 = new QLabel(verticalWidget_4);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_16->addWidget(label_14);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_15);

        comboBox_4 = new QComboBox(verticalWidget_4);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        sizePolicy1.setHeightForWidth(comboBox_4->sizePolicy().hasHeightForWidth());
        comboBox_4->setSizePolicy(sizePolicy1);
        comboBox_4->setMinimumSize(QSize(70, 35));

        horizontalLayout_16->addWidget(comboBox_4);


        verticalLayout_5->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_25 = new QLabel(verticalWidget_4);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_17->addWidget(label_25);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_16);

        comboBox_9 = new QComboBox(verticalWidget_4);
        comboBox_9->addItem(QString());
        comboBox_9->addItem(QString());
        comboBox_9->setObjectName(QString::fromUtf8("comboBox_9"));
        sizePolicy1.setHeightForWidth(comboBox_9->sizePolicy().hasHeightForWidth());
        comboBox_9->setSizePolicy(sizePolicy1);
        comboBox_9->setMinimumSize(QSize(70, 35));

        horizontalLayout_17->addWidget(comboBox_9);


        verticalLayout_5->addLayout(horizontalLayout_17);

        settingsTab->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        clockForm = new QWidget(tab_5);
        clockForm->setObjectName(QString::fromUtf8("clockForm"));
        clockForm->setGeometry(QRect(20, 40, 321, 111));
        clockForm->setStyleSheet(QString::fromUtf8("#clockForm{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(clockForm);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_21 = new QLabel(clockForm);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_12->addWidget(label_21);

        radioButton_2 = new QRadioButton(clockForm);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        horizontalLayout_12->addWidget(radioButton_2);

        radioButton_3 = new QRadioButton(clockForm);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        horizontalLayout_12->addWidget(radioButton_3);


        verticalLayout_6->addLayout(horizontalLayout_12);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_18 = new QLabel(clockForm);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_10->addWidget(label_18);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        lineEdit_10 = new QLineEdit(clockForm);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        sizePolicy1.setHeightForWidth(lineEdit_10->sizePolicy().hasHeightForWidth());
        lineEdit_10->setSizePolicy(sizePolicy1);
        lineEdit_10->setMinimumSize(QSize(130, 35));

        horizontalLayout_10->addWidget(lineEdit_10);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);

        label_20 = new QLabel(clockForm);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setStyleSheet(QString::fromUtf8("font: 75 11pt \"MS Shell Dlg 2\";"));

        horizontalLayout_10->addWidget(label_20);


        verticalLayout_6->addLayout(horizontalLayout_10);

        settingsTab->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        horizontalLayoutWidget = new QWidget(tab_6);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 30, 581, 41));
        horizontalLayout_25 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(0, 0, 0, 0);
        label_24 = new QLabel(horizontalLayoutWidget);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_25->addWidget(label_24);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_24);

        spinBox = new QSpinBox(horizontalLayoutWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMinimumSize(QSize(60, 35));

        horizontalLayout_25->addWidget(spinBox);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_23);

        label_23 = new QLabel(horizontalLayoutWidget);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_25->addWidget(label_23);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_25);

        spinBox_2 = new QSpinBox(horizontalLayoutWidget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        sizePolicy1.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy1);
        spinBox_2->setMinimumSize(QSize(50, 35));

        horizontalLayout_25->addWidget(spinBox_2);

        settingsTab->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        vWidget_2 = new QWidget(tab_7);
        vWidget_2->setObjectName(QString::fromUtf8("vWidget_2"));
        vWidget_2->setGeometry(QRect(10, 20, 481, 241));
        vWidget_2->setStyleSheet(QString::fromUtf8("#vWidget_2{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(vWidget_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_8 = new QLabel(vWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_13->addWidget(label_8);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        lineEdit_11 = new QLineEdit(vWidget_2);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        sizePolicy1.setHeightForWidth(lineEdit_11->sizePolicy().hasHeightForWidth());
        lineEdit_11->setSizePolicy(sizePolicy1);
        lineEdit_11->setMinimumSize(QSize(130, 35));

        horizontalLayout_13->addWidget(lineEdit_11);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(vWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        lineEdit_12 = new QLineEdit(vWidget_2);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        sizePolicy1.setHeightForWidth(lineEdit_12->sizePolicy().hasHeightForWidth());
        lineEdit_12->setSizePolicy(sizePolicy1);
        lineEdit_12->setMinimumSize(QSize(130, 35));

        horizontalLayout_14->addWidget(lineEdit_12);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_13 = new QLabel(vWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_15->addWidget(label_13);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        lineEdit_13 = new QLineEdit(vWidget_2);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        sizePolicy1.setHeightForWidth(lineEdit_13->sizePolicy().hasHeightForWidth());
        lineEdit_13->setSizePolicy(sizePolicy1);
        lineEdit_13->setMinimumSize(QSize(130, 35));

        horizontalLayout_15->addWidget(lineEdit_13);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_17 = new QLabel(vWidget_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_23->addWidget(label_17);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_21);

        lineEdit_15 = new QLineEdit(vWidget_2);
        lineEdit_15->setObjectName(QString::fromUtf8("lineEdit_15"));
        sizePolicy1.setHeightForWidth(lineEdit_15->sizePolicy().hasHeightForWidth());
        lineEdit_15->setSizePolicy(sizePolicy1);
        lineEdit_15->setMinimumSize(QSize(130, 35));

        horizontalLayout_23->addWidget(lineEdit_15);


        verticalLayout_4->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_22 = new QLabel(vWidget_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_24->addWidget(label_22);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_22);

        lineEdit_16 = new QLineEdit(vWidget_2);
        lineEdit_16->setObjectName(QString::fromUtf8("lineEdit_16"));
        sizePolicy1.setHeightForWidth(lineEdit_16->sizePolicy().hasHeightForWidth());
        lineEdit_16->setSizePolicy(sizePolicy1);
        lineEdit_16->setMinimumSize(QSize(130, 35));

        horizontalLayout_24->addWidget(lineEdit_16);


        verticalLayout_4->addLayout(horizontalLayout_24);

        settingsTab->addTab(tab_7, QString());
        ButtonForm = new QWidget(SettingsForm);
        ButtonForm->setObjectName(QString::fromUtf8("ButtonForm"));
        ButtonForm->setGeometry(QRect(20, 660, 681, 51));
        ButtonForm->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_11 = new QHBoxLayout(ButtonForm);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_11 = new QSpacerItem(350, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);

        pushButton_2 = new QPushButton(ButtonForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy2);
        pushButton_2->setStyleSheet(QString::fromUtf8("background: rgb(107, 107, 159);\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_2);

        StartButton = new QPushButton(ButtonForm);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        sizePolicy2.setHeightForWidth(StartButton->sizePolicy().hasHeightForWidth());
        StartButton->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("MS Shell Dlg 2")});
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setKerning(true);
        StartButton->setFont(font1);
        StartButton->setStyleSheet(QString::fromUtf8("background:green;\n"
"color: white;"));

        horizontalLayout_11->addWidget(StartButton);

        pushButton_5 = new QPushButton(ButtonForm);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy2.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy2);
        pushButton_5->setStyleSheet(QString::fromUtf8("background:red;\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_5);

        textEdit = new QTextEdit(SettingsForm);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 520, 671, 131));

        retranslateUi(SettingsForm);

        settingsTab->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(SettingsForm);
    } // setupUi

    void retranslateUi(QWidget *SettingsForm)
    {
        SettingsForm->setWindowTitle(QCoreApplication::translate("SettingsForm", "Settings", nullptr));
        label_27->setText(QCoreApplication::translate("SettingsForm", "Base address", nullptr));
        label->setText(QCoreApplication::translate("SettingsForm", "0x", nullptr));
        label_15->setText(QCoreApplication::translate("SettingsForm", "Interferometer type", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SettingsForm", "Single Pass Interferometer", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SettingsForm", "Double Pass Interferometer", nullptr));

        label_16->setText(QCoreApplication::translate("SettingsForm", "Precision", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("SettingsForm", "32 bits", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("SettingsForm", "37 bits", nullptr));

        label_19->setText(QCoreApplication::translate("SettingsForm", "Reset find velocity", nullptr));
        comboBox_8->setItemText(0, QCoreApplication::translate("SettingsForm", "OFF", nullptr));
        comboBox_8->setItemText(1, QCoreApplication::translate("SettingsForm", "ON", nullptr));

        settingsTab->setTabText(settingsTab->indexOf(tab), QCoreApplication::translate("SettingsForm", "General ", nullptr));
        label_3->setText(QCoreApplication::translate("SettingsForm", "APD Gain L2 Set", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsForm", "APD BIAS DAC", nullptr));
        label_4->setText(QCoreApplication::translate("SettingsForm", "APD Sig RMS L2 Set", nullptr));
        label_5->setText(QCoreApplication::translate("SettingsForm", "APD OPT PWR  L2 Set", nullptr));
        settingsTab->setTabText(settingsTab->indexOf(tab_2), QCoreApplication::translate("SettingsForm", "Signal", nullptr));
        radioButton->setText(QCoreApplication::translate("SettingsForm", "Enable Glitch Filter", nullptr));
        label_6->setText(QCoreApplication::translate("SettingsForm", "Kp", nullptr));
        label_7->setText(QCoreApplication::translate("SettingsForm", "Kv", nullptr));
        settingsTab->setTabText(settingsTab->indexOf(tab_3), QCoreApplication::translate("SettingsForm", "Digital Filter", nullptr));
        label_9->setText(QCoreApplication::translate("SettingsForm", "SSI Squeltch", nullptr));
        label_10->setText(QCoreApplication::translate("SettingsForm", "Gain  min", nullptr));
        label_11->setText(QCoreApplication::translate("SettingsForm", "Gain max", nullptr));
        label_26->setText(QCoreApplication::translate("SettingsForm", "Auto Gain adjust  mode", nullptr));
        comboBox_7->setItemText(0, QCoreApplication::translate("SettingsForm", "OFF", nullptr));
        comboBox_7->setItemText(1, QCoreApplication::translate("SettingsForm", "ON", nullptr));

        label_14->setText(QCoreApplication::translate("SettingsForm", "Gain control min", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("SettingsForm", "OFF", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("SettingsForm", "ON", nullptr));

        label_25->setText(QCoreApplication::translate("SettingsForm", "Gain control max", nullptr));
        comboBox_9->setItemText(0, QCoreApplication::translate("SettingsForm", "OFF", nullptr));
        comboBox_9->setItemText(1, QCoreApplication::translate("SettingsForm", "ON", nullptr));

        settingsTab->setTabText(settingsTab->indexOf(tab_4), QCoreApplication::translate("SettingsForm", "APD Settings", nullptr));
        label_21->setText(QCoreApplication::translate("SettingsForm", "Type", nullptr));
        radioButton_2->setText(QCoreApplication::translate("SettingsForm", "SCLK1", nullptr));
        radioButton_3->setText(QCoreApplication::translate("SettingsForm", "SCLK2", nullptr));
        label_18->setText(QCoreApplication::translate("SettingsForm", "Frequency", nullptr));
        label_20->setText(QCoreApplication::translate("SettingsForm", "Hz", nullptr));
        settingsTab->setTabText(settingsTab->indexOf(tab_5), QCoreApplication::translate("SettingsForm", "Clock", nullptr));
        label_24->setText(QCoreApplication::translate("SettingsForm", "Vetor", nullptr));
        label_23->setText(QCoreApplication::translate("SettingsForm", "Level", nullptr));
        settingsTab->setTabText(settingsTab->indexOf(tab_6), QCoreApplication::translate("SettingsForm", "Interrupts", nullptr));
        label_8->setText(QCoreApplication::translate("SettingsForm", "GSE Target Gain", nullptr));
        label_12->setText(QCoreApplication::translate("SettingsForm", "GSE Actual Gain", nullptr));
        label_13->setText(QCoreApplication::translate("SettingsForm", "GSE Sig RMS Gain", nullptr));
        label_17->setText(QCoreApplication::translate("SettingsForm", "GSE Meas DC Low", nullptr));
        label_22->setText(QCoreApplication::translate("SettingsForm", "GSE Meas DC High", nullptr));
        settingsTab->setTabText(settingsTab->indexOf(tab_7), QCoreApplication::translate("SettingsForm", "Diagnostics", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SettingsForm", "Apply", nullptr));
        StartButton->setText(QCoreApplication::translate("SettingsForm", "OK", nullptr));
        pushButton_5->setText(QCoreApplication::translate("SettingsForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsForm: public Ui_SettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSFORM_H
