/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionBoard_Infos;
    QAction *actionAbout_2;
    QAction *actionBoard_Infos_2;
    QWidget *centralwidget;
    QPushButton *pushButton_7;
    QPushButton *pushButton_13;
    QWidget *horizontalLayoutWidget_16;
    QHBoxLayout *horizontalLayout_16;
    QTextEdit *textEdit;
    QLabel *label_9;
    QTextEdit *SysStatusEdit;
    QPushButton *pushButton_8;
    QWidget *CE_form;
    QHBoxLayout *horizontalLayout_9;
    QWidget *verticalWidget_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_14;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_15;
    QComboBox *comboBox_6;
    QToolButton *toolButton_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *lineEdit_6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_18;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *lineEdit_8;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_10;
    QSpacerItem *horizontalSpacer_14;
    QTextEdit *textEdit_3;
    QWidget *MeasForm;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_17;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLCDNumber *lcdNumber_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLCDNumber *lcdNumber_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLCDNumber *lcdNumber_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QWidget *horizontalWidget_15;
    QHBoxLayout *horizontalLayout_20;
    QLineEdit *lineEdit_10;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButton_15;
    QWidget *horizontalWidget_17;
    QHBoxLayout *horizontalLayout_22;
    QLineEdit *lineEdit_12;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *pushButton_17;
    QWidget *horizontalWidget_16;
    QHBoxLayout *horizontalLayout_21;
    QLineEdit *lineEdit_11;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_16;
    QWidget *horizontalWidget_18;
    QHBoxLayout *horizontalLayout_23;
    QLineEdit *lineEdit_13;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButton_18;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_15;
    QWidget *SettingsForm;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_11;
    QSpacerItem *horizontalSpacer_17;
    QPushButton *pushButton_12;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_8;
    QComboBox *comboBox_3;
    QToolButton *toolButton;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QComboBox *comboBox_4;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_8;
    QWidget *horizontalWidget_14;
    QHBoxLayout *horizontalLayout_2;
    QMenuBar *menubar;
    QMenu *menuSettings;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(827, 884);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(70, 35));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/logo_soleil_min.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"QComboBox, QLineEdit{\n"
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
"#MainWindow{\n"
"background-image: url(:/images/VueAerienneSynchrotronSOLEIL_mod);\n"
"	border-color: rgb(85, 170, 255);\n"
"	border-top-color:rgb(85, 170, 255);\n"
"}"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionBoard_Infos = new QAction(MainWindow);
        actionBoard_Infos->setObjectName(QString::fromUtf8("actionBoard_Infos"));
        actionAbout_2 = new QAction(MainWindow);
        actionAbout_2->setObjectName(QString::fromUtf8("actionAbout_2"));
        actionBoard_Infos_2 = new QAction(MainWindow);
        actionBoard_Infos_2->setObjectName(QString::fromUtf8("actionBoard_Infos_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        pushButton_7 = new QPushButton(centralwidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(40, 40, 151, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("\n"
"background: blue;\n"
"color: white;"));
        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(610, 800, 191, 41));
        pushButton_13->setStyleSheet(QString::fromUtf8("background:rgb(59, 118, 177);\n"
"color: white;"));
        horizontalLayoutWidget_16 = new QWidget(centralwidget);
        horizontalLayoutWidget_16->setObjectName(QString::fromUtf8("horizontalLayoutWidget_16"));
        horizontalLayoutWidget_16->setGeometry(QRect(30, 120, 771, 111));
        horizontalLayout_16 = new QHBoxLayout(horizontalLayoutWidget_16);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(horizontalLayoutWidget_16);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        horizontalLayout_16->addWidget(textEdit);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(550, 50, 71, 20));
        SysStatusEdit = new QTextEdit(centralwidget);
        SysStatusEdit->setObjectName(QString::fromUtf8("SysStatusEdit"));
        SysStatusEdit->setGeometry(QRect(620, 40, 161, 41));
        pushButton_8 = new QPushButton(centralwidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(500, 800, 101, 41));
        pushButton_8->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";\n"
"background:rgb(85, 85, 0);\n"
"color: white;"));
        CE_form = new QWidget(centralwidget);
        CE_form->setObjectName(QString::fromUtf8("CE_form"));
        CE_form->setGeometry(QRect(30, 600, 771, 191));
        CE_form->setStyleSheet(QString::fromUtf8("#CE_form{\n"
"border: 1px solid;\n"
"}"));
        horizontalLayout_9 = new QHBoxLayout(CE_form);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalWidget_3 = new QWidget(CE_form);
        verticalWidget_3->setObjectName(QString::fromUtf8("verticalWidget_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(verticalWidget_3->sizePolicy().hasHeightForWidth());
        verticalWidget_3->setSizePolicy(sizePolicy1);
        verticalWidget_3->setMinimumSize(QSize(300, 0));
        verticalLayout_3 = new QVBoxLayout(verticalWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_14 = new QLabel(verticalWidget_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy2);

        horizontalLayout_19->addWidget(label_14);

        radioButton_2 = new QRadioButton(verticalWidget_3);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(30);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy3);
        radioButton_2->setStyleSheet(QString::fromUtf8("font: 13pt \"Arial\";"));

        horizontalLayout_19->addWidget(radioButton_2);

        radioButton = new QRadioButton(verticalWidget_3);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        sizePolicy3.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy3);
        radioButton->setStyleSheet(QString::fromUtf8("font: 13pt \"Arial\";"));

        horizontalLayout_19->addWidget(radioButton);


        verticalLayout_3->addLayout(horizontalLayout_19);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_15 = new QLabel(verticalWidget_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy2.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy2);
        label_15->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Arial\";"));

        horizontalLayout_15->addWidget(label_15);

        comboBox_6 = new QComboBox(verticalWidget_3);
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->addItem(QString());
        comboBox_6->setObjectName(QString::fromUtf8("comboBox_6"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(comboBox_6->sizePolicy().hasHeightForWidth());
        comboBox_6->setSizePolicy(sizePolicy4);
        comboBox_6->setMinimumSize(QSize(90, 21));

        horizontalLayout_15->addWidget(comboBox_6);

        toolButton_2 = new QToolButton(verticalWidget_3);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setStyleSheet(QString::fromUtf8("background:rgb(59, 118, 177);\n"
"color: white;"));

        horizontalLayout_15->addWidget(toolButton_2);


        verticalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_11 = new QLabel(verticalWidget_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Arial\";\n"
"text-align: center;"));

        horizontalLayout_12->addWidget(label_11);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_19);

        lineEdit_6 = new QLineEdit(verticalWidget_3);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy5);
        lineEdit_6->setMinimumSize(QSize(200, 30));

        horizontalLayout_12->addWidget(lineEdit_6);


        verticalLayout_3->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_12 = new QLabel(verticalWidget_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Arial\";\n"
"text-align: center;"));

        horizontalLayout_13->addWidget(label_12);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_18);

        lineEdit_7 = new QLineEdit(verticalWidget_3);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        sizePolicy5.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy5);
        lineEdit_7->setMinimumSize(QSize(200, 30));

        horizontalLayout_13->addWidget(lineEdit_7);


        verticalLayout_3->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_18 = new QLabel(verticalWidget_3);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Arial\";\n"
"text-align: center;"));

        horizontalLayout_14->addWidget(label_18);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_9);

        lineEdit_8 = new QLineEdit(verticalWidget_3);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        sizePolicy5.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy5);
        lineEdit_8->setMinimumSize(QSize(200, 30));

        horizontalLayout_14->addWidget(lineEdit_8);


        verticalLayout_3->addLayout(horizontalLayout_14);


        horizontalLayout_9->addWidget(verticalWidget_3);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_13 = new QLabel(CE_form);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy2.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy2);

        horizontalLayout_10->addWidget(label_13);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);

        pushButton_10 = new QPushButton(CE_form);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setMinimumSize(QSize(0, 30));
        pushButton_10->setStyleSheet(QString::fromUtf8("background:rgb(161, 0, 0);\n"
"color: white;"));

        horizontalLayout_10->addWidget(pushButton_10);

        horizontalSpacer_14 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_14);


        verticalLayout_6->addLayout(horizontalLayout_10);

        textEdit_3 = new QTextEdit(CE_form);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));

        verticalLayout_6->addWidget(textEdit_3);


        horizontalLayout_9->addLayout(verticalLayout_6);

        MeasForm = new QWidget(centralwidget);
        MeasForm->setObjectName(QString::fromUtf8("MeasForm"));
        MeasForm->setGeometry(QRect(30, 340, 771, 251));
        MeasForm->setStyleSheet(QString::fromUtf8("#MeasForm{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_8 = new QVBoxLayout(MeasForm);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        verticalWidget = new QWidget(MeasForm);
        verticalWidget->setObjectName(QString::fromUtf8("verticalWidget"));
        sizePolicy4.setHeightForWidth(verticalWidget->sizePolicy().hasHeightForWidth());
        verticalWidget->setSizePolicy(sizePolicy4);
        verticalWidget->setMinimumSize(QSize(350, 200));
        verticalLayout = new QVBoxLayout(verticalWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label = new QLabel(verticalWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(80, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("MS Shell Dlg 2")});
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_7->addWidget(label);

        lcdNumber = new QLCDNumber(verticalWidget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        sizePolicy.setHeightForWidth(lcdNumber->sizePolicy().hasHeightForWidth());
        lcdNumber->setSizePolicy(sizePolicy);

        horizontalLayout_7->addWidget(lcdNumber);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(verticalWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(80, 0));
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_5->addWidget(label_4);

        lcdNumber_2 = new QLCDNumber(verticalWidget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        sizePolicy.setHeightForWidth(lcdNumber_2->sizePolicy().hasHeightForWidth());
        lcdNumber_2->setSizePolicy(sizePolicy);

        horizontalLayout_5->addWidget(lcdNumber_2);


        horizontalLayout_4->addLayout(horizontalLayout_5);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(verticalWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setMinimumSize(QSize(80, 0));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_3->addWidget(label_5);

        lcdNumber_3 = new QLCDNumber(verticalWidget);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        sizePolicy.setHeightForWidth(lcdNumber_3->sizePolicy().hasHeightForWidth());
        lcdNumber_3->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lcdNumber_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(verticalWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setMinimumSize(QSize(80, 0));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout->addWidget(label_6);

        lcdNumber_4 = new QLCDNumber(verticalWidget);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));
        sizePolicy.setHeightForWidth(lcdNumber_4->sizePolicy().hasHeightForWidth());
        lcdNumber_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lcdNumber_4);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_17->addWidget(verticalWidget);

        horizontalSpacer = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalWidget_15 = new QWidget(MeasForm);
        horizontalWidget_15->setObjectName(QString::fromUtf8("horizontalWidget_15"));
        sizePolicy4.setHeightForWidth(horizontalWidget_15->sizePolicy().hasHeightForWidth());
        horizontalWidget_15->setSizePolicy(sizePolicy4);
        horizontalWidget_15->setMinimumSize(QSize(0, 40));
        horizontalLayout_20 = new QHBoxLayout(horizontalWidget_15);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        lineEdit_10 = new QLineEdit(horizontalWidget_15);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));
        sizePolicy4.setHeightForWidth(lineEdit_10->sizePolicy().hasHeightForWidth());
        lineEdit_10->setSizePolicy(sizePolicy4);
        lineEdit_10->setMinimumSize(QSize(0, 30));

        horizontalLayout_20->addWidget(lineEdit_10);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_10);

        pushButton_15 = new QPushButton(horizontalWidget_15);
        pushButton_15->setObjectName(QString::fromUtf8("pushButton_15"));
        sizePolicy4.setHeightForWidth(pushButton_15->sizePolicy().hasHeightForWidth());
        pushButton_15->setSizePolicy(sizePolicy4);
        pushButton_15->setMinimumSize(QSize(75, 35));
        pushButton_15->setStyleSheet(QString::fromUtf8("background:rgb(161, 0, 0);\n"
"color: white;"));

        horizontalLayout_20->addWidget(pushButton_15);


        verticalLayout_2->addWidget(horizontalWidget_15);

        horizontalWidget_17 = new QWidget(MeasForm);
        horizontalWidget_17->setObjectName(QString::fromUtf8("horizontalWidget_17"));
        sizePolicy4.setHeightForWidth(horizontalWidget_17->sizePolicy().hasHeightForWidth());
        horizontalWidget_17->setSizePolicy(sizePolicy4);
        horizontalWidget_17->setMinimumSize(QSize(0, 40));
        horizontalLayout_22 = new QHBoxLayout(horizontalWidget_17);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        lineEdit_12 = new QLineEdit(horizontalWidget_17);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        sizePolicy4.setHeightForWidth(lineEdit_12->sizePolicy().hasHeightForWidth());
        lineEdit_12->setSizePolicy(sizePolicy4);
        lineEdit_12->setMinimumSize(QSize(0, 30));

        horizontalLayout_22->addWidget(lineEdit_12);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_12);

        pushButton_17 = new QPushButton(horizontalWidget_17);
        pushButton_17->setObjectName(QString::fromUtf8("pushButton_17"));
        sizePolicy4.setHeightForWidth(pushButton_17->sizePolicy().hasHeightForWidth());
        pushButton_17->setSizePolicy(sizePolicy4);
        pushButton_17->setMinimumSize(QSize(75, 35));
        pushButton_17->setStyleSheet(QString::fromUtf8("background:rgb(161, 0, 0);\n"
"color: white;"));

        horizontalLayout_22->addWidget(pushButton_17);


        verticalLayout_2->addWidget(horizontalWidget_17);

        horizontalWidget_16 = new QWidget(MeasForm);
        horizontalWidget_16->setObjectName(QString::fromUtf8("horizontalWidget_16"));
        sizePolicy4.setHeightForWidth(horizontalWidget_16->sizePolicy().hasHeightForWidth());
        horizontalWidget_16->setSizePolicy(sizePolicy4);
        horizontalWidget_16->setMinimumSize(QSize(75, 35));
        horizontalLayout_21 = new QHBoxLayout(horizontalWidget_16);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        lineEdit_11 = new QLineEdit(horizontalWidget_16);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        sizePolicy4.setHeightForWidth(lineEdit_11->sizePolicy().hasHeightForWidth());
        lineEdit_11->setSizePolicy(sizePolicy4);
        lineEdit_11->setMinimumSize(QSize(0, 30));

        horizontalLayout_21->addWidget(lineEdit_11);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_11);

        pushButton_16 = new QPushButton(horizontalWidget_16);
        pushButton_16->setObjectName(QString::fromUtf8("pushButton_16"));
        sizePolicy4.setHeightForWidth(pushButton_16->sizePolicy().hasHeightForWidth());
        pushButton_16->setSizePolicy(sizePolicy4);
        pushButton_16->setMinimumSize(QSize(75, 35));
        pushButton_16->setStyleSheet(QString::fromUtf8("background:rgb(161, 0, 0);\n"
"color: white;"));

        horizontalLayout_21->addWidget(pushButton_16);


        verticalLayout_2->addWidget(horizontalWidget_16);

        horizontalWidget_18 = new QWidget(MeasForm);
        horizontalWidget_18->setObjectName(QString::fromUtf8("horizontalWidget_18"));
        sizePolicy4.setHeightForWidth(horizontalWidget_18->sizePolicy().hasHeightForWidth());
        horizontalWidget_18->setSizePolicy(sizePolicy4);
        horizontalWidget_18->setMinimumSize(QSize(0, 40));
        horizontalLayout_23 = new QHBoxLayout(horizontalWidget_18);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        lineEdit_13 = new QLineEdit(horizontalWidget_18);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        sizePolicy4.setHeightForWidth(lineEdit_13->sizePolicy().hasHeightForWidth());
        lineEdit_13->setSizePolicy(sizePolicy4);
        lineEdit_13->setMinimumSize(QSize(0, 30));

        horizontalLayout_23->addWidget(lineEdit_13);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_13);

        pushButton_18 = new QPushButton(horizontalWidget_18);
        pushButton_18->setObjectName(QString::fromUtf8("pushButton_18"));
        sizePolicy4.setHeightForWidth(pushButton_18->sizePolicy().hasHeightForWidth());
        pushButton_18->setSizePolicy(sizePolicy4);
        pushButton_18->setMinimumSize(QSize(75, 35));
        pushButton_18->setStyleSheet(QString::fromUtf8("background:rgb(161, 0, 0);\n"
"color: white;"));

        horizontalLayout_23->addWidget(pushButton_18);


        verticalLayout_2->addWidget(horizontalWidget_18);


        horizontalLayout_17->addLayout(verticalLayout_2);


        verticalLayout_8->addLayout(horizontalLayout_17);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_5 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        label_7 = new QLabel(MeasForm);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy2.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy2);

        horizontalLayout_8->addWidget(label_7);

        horizontalSpacer_4 = new QSpacerItem(375, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        pushButton_6 = new QPushButton(MeasForm);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy4.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy4);
        pushButton_6->setMinimumSize(QSize(80, 35));
        pushButton_6->setStyleSheet(QString::fromUtf8("background:rgb(161, 0, 0);\n"
"color: white;"));

        horizontalLayout_8->addWidget(pushButton_6);

        horizontalSpacer_15 = new QSpacerItem(4, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_15);


        verticalLayout_8->addLayout(horizontalLayout_8);

        SettingsForm = new QWidget(centralwidget);
        SettingsForm->setObjectName(QString::fromUtf8("SettingsForm"));
        SettingsForm->setGeometry(QRect(30, 240, 771, 91));
        SettingsForm->setStyleSheet(QString::fromUtf8("#SettingsForm{\n"
"border: 1px solid;\n"
"color: blue;\n"
"}"));
        verticalLayout_9 = new QVBoxLayout(SettingsForm);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        pushButton_11 = new QPushButton(SettingsForm);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setMinimumSize(QSize(0, 35));
        pushButton_11->setStyleSheet(QString::fromUtf8("background:rgb(81, 81, 122);\n"
"color:white;"));

        horizontalLayout_11->addWidget(pushButton_11);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_17);

        pushButton_12 = new QPushButton(SettingsForm);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setMinimumSize(QSize(0, 35));
        pushButton_12->setStyleSheet(QString::fromUtf8("background:rgb(81, 81, 122);\n"
"color:white;"));

        horizontalLayout_11->addWidget(pushButton_12);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_16);

        label_8 = new QLabel(SettingsForm);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy2.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy2);

        horizontalLayout_11->addWidget(label_8);

        comboBox_3 = new QComboBox(SettingsForm);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setMinimumSize(QSize(0, 30));
        comboBox_3->setStyleSheet(QString::fromUtf8("background:rgb(85, 85, 0);\n"
"color:yellow;\n"
"text-align: center;"));

        horizontalLayout_11->addWidget(comboBox_3);

        toolButton = new QToolButton(SettingsForm);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setMinimumSize(QSize(50, 25));
        toolButton->setStyleSheet(QString::fromUtf8("background:rgb(59, 118, 177);\n"
"color: white;"));

        horizontalLayout_11->addWidget(toolButton);


        verticalLayout_9->addLayout(horizontalLayout_11);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(8, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_2 = new QLabel(SettingsForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(70, 0));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Arial\";"));

        horizontalLayout_6->addWidget(label_2);

        comboBox_4 = new QComboBox(SettingsForm);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        sizePolicy4.setHeightForWidth(comboBox_4->sizePolicy().hasHeightForWidth());
        comboBox_4->setSizePolicy(sizePolicy4);
        comboBox_4->setMinimumSize(QSize(150, 35));

        horizontalLayout_6->addWidget(comboBox_4);

        label_3 = new QLabel(SettingsForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMinimumSize(QSize(50, 0));
        label_3->setStyleSheet(QString::fromUtf8("font: 75 12pt \"Arial\";"));

        horizontalLayout_6->addWidget(label_3);

        comboBox_2 = new QComboBox(SettingsForm);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        sizePolicy4.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy4);
        comboBox_2->setMinimumSize(QSize(60, 35));

        horizontalLayout_6->addWidget(comboBox_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        pushButton_9 = new QPushButton(SettingsForm);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        sizePolicy4.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy4);
        pushButton_9->setMinimumSize(QSize(100, 35));
        pushButton_9->setStyleSheet(QString::fromUtf8("background:rgb(59, 118, 177);\n"
"color: white;"));

        horizontalLayout_6->addWidget(pushButton_9);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        comboBox = new QComboBox(SettingsForm);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(60);
        sizePolicy6.setVerticalStretch(60);
        sizePolicy6.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy6);
        comboBox->setMinimumSize(QSize(120, 35));

        horizontalLayout_6->addWidget(comboBox);

        horizontalSpacer_8 = new QSpacerItem(130, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout_9->addLayout(horizontalLayout_6);

        horizontalWidget_14 = new QWidget(centralwidget);
        horizontalWidget_14->setObjectName(QString::fromUtf8("horizontalWidget_14"));
        horizontalWidget_14->setGeometry(QRect(280, 10, 231, 101));
        horizontalWidget_14->setStyleSheet(QString::fromUtf8("background-image: url(:/images/logo_soleil_min);"));
        horizontalLayout_2 = new QHBoxLayout(horizontalWidget_14);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 827, 21));
        menubar->setStyleSheet(QString::fromUtf8(""));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout_2);
        menuHelp->addAction(actionBoard_Infos_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ZMI4104C_ECA_Soft", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionBoard_Infos->setText(QCoreApplication::translate("MainWindow", "Board Infos", nullptr));
        actionAbout_2->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionBoard_Infos_2->setText(QCoreApplication::translate("MainWindow", "Board Infos", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Initialize ZMI", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "Continuous acquisition", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "State", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Plot graphs", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "CE Compensation", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "OFF", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "ON", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "units", nullptr));
        comboBox_6->setItemText(0, QCoreApplication::translate("MainWindow", "percent", nullptr));
        comboBox_6->setItemText(1, QCoreApplication::translate("MainWindow", "dB", nullptr));
        comboBox_6->setItemText(2, QCoreApplication::translate("MainWindow", "nmRMS", nullptr));

        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "CE N ratio", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "CE 0 ratio", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Meas Signal", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "CE Status", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "Reset CE errors", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Axis1", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Axis2", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Axis3", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Axis4", nullptr));
        pushButton_15->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pushButton_18->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Reference", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Reset All", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "Set position offsets", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "Preset positions", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Bias Mode", nullptr));
        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "OFF", nullptr));
        comboBox_3->setItemText(1, QCoreApplication::translate("MainWindow", "Constant Voltage", nullptr));
        comboBox_3->setItemText(2, QCoreApplication::translate("MainWindow", "Constant Gain", nullptr));
        comboBox_3->setItemText(3, QCoreApplication::translate("MainWindow", "Constant Opt Pwr", nullptr));
        comboBox_3->setItemText(4, QCoreApplication::translate("MainWindow", "SSI RMS Adjust ", nullptr));

        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "Position", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", "Velocity", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "Time", nullptr));
        comboBox_4->setItemText(3, QCoreApplication::translate("MainWindow", "FFT", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "units", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "\302\265m", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "mm", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "cm", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "dm", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "m", nullptr));

        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "APD Gain", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Opt Power", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "SSI", nullptr));

        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
