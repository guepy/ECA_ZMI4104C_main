/********************************************************************************
** Form generated from reading UI file 'cesettingsform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CESETTINGSFORM_H
#define UI_CESETTINGSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CEsettingsForm
{
public:
    QLabel *label_3;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *radioButton_2;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButton;
    QWidget *horizontalWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_12;
    QDoubleSpinBox *uscCE0;
    QPushButton *pushButton;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_13;
    QDoubleSpinBox *uscCEN;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_14;
    QDoubleSpinBox *uscCEMeas;
    QPushButton *pushButton_4;
    QWidget *vWidget_3;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_15;
    QLineEdit *calcuCE0;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_14;
    QSpacerItem *horizontalSpacer_16;
    QLineEdit *calcuCEN;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_17;
    QLineEdit *calcuCEMeas;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_12;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_6;
    QWidget *ceBoundaries;
    QHBoxLayout *horizontalLayout_5;
    QWidget *vWidget_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_18;
    QDoubleSpinBox *ceMinVel;
    QPushButton *pushButton_6;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_16;
    QSpacerItem *horizontalSpacer_19;
    QDoubleSpinBox *ceMaxVel;
    QPushButton *pushButton_7;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_20;
    QDoubleSpinBox *ce0Lim;
    QPushButton *pushButton_8;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_21;
    QDoubleSpinBox *ceNLim;
    QPushButton *pushButton_9;
    QFrame *line;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_22;
    QLineEdit *ce0Min;
    QPushButton *pushButton_10;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_19;
    QSpacerItem *horizontalSpacer_23;
    QLineEdit *ce0Max;
    QPushButton *pushButton_11;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_20;
    QSpacerItem *horizontalSpacer_24;
    QLineEdit *ceNMin;
    QPushButton *pushButton_13;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_21;
    QSpacerItem *horizontalSpacer_25;
    QLineEdit *ceNMax;
    QPushButton *pushButton_14;
    QWidget *ButtonForm;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *StartButton;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_5;

    void setupUi(QWidget *CEsettingsForm)
    {
        if (CEsettingsForm->objectName().isEmpty())
            CEsettingsForm->setObjectName(QString::fromUtf8("CEsettingsForm"));
        CEsettingsForm->resize(787, 731);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CEsettingsForm->sizePolicy().hasHeightForWidth());
        CEsettingsForm->setSizePolicy(sizePolicy);
        CEsettingsForm->setMinimumSize(QSize(200, 50));
        CEsettingsForm->setStyleSheet(QString::fromUtf8("QLabel, QRadioButton{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"QComboBox, QLineEdit{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border-radius:1px;\n"
"border: 2px solid;\n"
"border-color: white;\n"
"}\n"
"QPushButton, QDoubleSpinBox, #ceBoundaries,QToolButton{\n"
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
        label_3 = new QLabel(CEsettingsForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(-290, 240, 729, 23));
        verticalLayoutWidget_3 = new QWidget(CEsettingsForm);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 30, 771, 661));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        label_5->setFont(font);
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Times New Roman\";"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_5);

        widget = new QWidget(verticalLayoutWidget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        horizontalLayout_4 = new QHBoxLayout(widget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setStyleSheet(QString::fromUtf8("\n"
"font: 75 12pt \"MS Shell Dlg 2\";"));

        horizontalLayout_4->addWidget(radioButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        radioButton = new QRadioButton(widget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setStyleSheet(QString::fromUtf8("\n"
"font: 75 12pt \"MS Shell Dlg 2\";"));

        horizontalLayout_4->addWidget(radioButton);


        verticalLayout->addWidget(widget);

        horizontalWidget_2 = new QWidget(verticalLayoutWidget_3);
        horizontalWidget_2->setObjectName(QString::fromUtf8("horizontalWidget_2"));
        sizePolicy1.setHeightForWidth(horizontalWidget_2->sizePolicy().hasHeightForWidth());
        horizontalWidget_2->setSizePolicy(sizePolicy1);
        horizontalWidget_2->setMinimumSize(QSize(8, 200));
        horizontalLayout_6 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_4 = new QLabel(horizontalWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(label_4);


        verticalLayout_2->addLayout(horizontalLayout_7);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_8 = new QLabel(horizontalWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_13->addWidget(label_8);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        uscCE0 = new QDoubleSpinBox(horizontalWidget_2);
        uscCE0->setObjectName(QString::fromUtf8("uscCE0"));
        uscCE0->setMinimumSize(QSize(150, 40));

        horizontalLayout_13->addWidget(uscCE0);

        pushButton = new QPushButton(horizontalWidget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setMinimumSize(QSize(75, 40));

        horizontalLayout_13->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(horizontalWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        uscCEN = new QDoubleSpinBox(horizontalWidget_2);
        uscCEN->setObjectName(QString::fromUtf8("uscCEN"));
        uscCEN->setMinimumSize(QSize(150, 40));

        horizontalLayout_14->addWidget(uscCEN);

        pushButton_3 = new QPushButton(horizontalWidget_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy2.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy2);
        pushButton_3->setMinimumSize(QSize(75, 40));

        horizontalLayout_14->addWidget(pushButton_3);


        verticalLayout_2->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_13 = new QLabel(horizontalWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_15->addWidget(label_13);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        uscCEMeas = new QDoubleSpinBox(horizontalWidget_2);
        uscCEMeas->setObjectName(QString::fromUtf8("uscCEMeas"));
        uscCEMeas->setMinimumSize(QSize(150, 40));

        horizontalLayout_15->addWidget(uscCEMeas);

        pushButton_4 = new QPushButton(horizontalWidget_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy2.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy2);
        pushButton_4->setMinimumSize(QSize(75, 40));

        horizontalLayout_15->addWidget(pushButton_4);


        verticalLayout_2->addLayout(horizontalLayout_15);


        horizontalLayout_6->addLayout(verticalLayout_2);

        vWidget_3 = new QWidget(horizontalWidget_2);
        vWidget_3->setObjectName(QString::fromUtf8("vWidget_3"));
        vWidget_3->setStyleSheet(QString::fromUtf8("#vWidget_3{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(vWidget_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(vWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_9 = new QLabel(vWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_16->addWidget(label_9);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_15);

        calcuCE0 = new QLineEdit(vWidget_3);
        calcuCE0->setObjectName(QString::fromUtf8("calcuCE0"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(calcuCE0->sizePolicy().hasHeightForWidth());
        calcuCE0->setSizePolicy(sizePolicy3);
        calcuCE0->setMinimumSize(QSize(130, 35));

        horizontalLayout_16->addWidget(calcuCE0);


        verticalLayout_5->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_14 = new QLabel(vWidget_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_17->addWidget(label_14);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_16);

        calcuCEN = new QLineEdit(vWidget_3);
        calcuCEN->setObjectName(QString::fromUtf8("calcuCEN"));
        sizePolicy3.setHeightForWidth(calcuCEN->sizePolicy().hasHeightForWidth());
        calcuCEN->setSizePolicy(sizePolicy3);
        calcuCEN->setMinimumSize(QSize(130, 35));

        horizontalLayout_17->addWidget(calcuCEN);


        verticalLayout_5->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_15 = new QLabel(vWidget_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_18->addWidget(label_15);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_17);

        calcuCEMeas = new QLineEdit(vWidget_3);
        calcuCEMeas->setObjectName(QString::fromUtf8("calcuCEMeas"));
        sizePolicy3.setHeightForWidth(calcuCEMeas->sizePolicy().hasHeightForWidth());
        calcuCEMeas->setSizePolicy(sizePolicy3);
        calcuCEMeas->setMinimumSize(QSize(130, 35));

        horizontalLayout_18->addWidget(calcuCEMeas);


        verticalLayout_5->addLayout(horizontalLayout_18);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        pushButton_12 = new QPushButton(vWidget_3);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        sizePolicy.setHeightForWidth(pushButton_12->sizePolicy().hasHeightForWidth());
        pushButton_12->setSizePolicy(sizePolicy);
        pushButton_12->setMinimumSize(QSize(0, 30));

        horizontalLayout->addWidget(pushButton_12);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout);


        horizontalLayout_6->addWidget(vWidget_3);


        verticalLayout->addWidget(horizontalWidget_2);

        label_6 = new QLabel(verticalLayoutWidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_6);

        ceBoundaries = new QWidget(verticalLayoutWidget_3);
        ceBoundaries->setObjectName(QString::fromUtf8("ceBoundaries"));
        sizePolicy1.setHeightForWidth(ceBoundaries->sizePolicy().hasHeightForWidth());
        ceBoundaries->setSizePolicy(sizePolicy1);
        ceBoundaries->setMinimumSize(QSize(0, 200));
        ceBoundaries->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_5 = new QHBoxLayout(ceBoundaries);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        vWidget_4 = new QWidget(ceBoundaries);
        vWidget_4->setObjectName(QString::fromUtf8("vWidget_4"));
        vWidget_4->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_6 = new QVBoxLayout(vWidget_4);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_10 = new QLabel(vWidget_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_19->addWidget(label_10);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_18);

        ceMinVel = new QDoubleSpinBox(vWidget_4);
        ceMinVel->setObjectName(QString::fromUtf8("ceMinVel"));
        ceMinVel->setMinimumSize(QSize(150, 40));

        horizontalLayout_19->addWidget(ceMinVel);

        pushButton_6 = new QPushButton(vWidget_4);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy2.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy2);
        pushButton_6->setMinimumSize(QSize(0, 30));

        horizontalLayout_19->addWidget(pushButton_6);


        verticalLayout_6->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_16 = new QLabel(vWidget_4);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_20->addWidget(label_16);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_19);

        ceMaxVel = new QDoubleSpinBox(vWidget_4);
        ceMaxVel->setObjectName(QString::fromUtf8("ceMaxVel"));
        ceMaxVel->setMinimumSize(QSize(150, 40));

        horizontalLayout_20->addWidget(ceMaxVel);

        pushButton_7 = new QPushButton(vWidget_4);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy2.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy2);
        pushButton_7->setMinimumSize(QSize(0, 30));

        horizontalLayout_20->addWidget(pushButton_7);


        verticalLayout_6->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_17 = new QLabel(vWidget_4);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_21->addWidget(label_17);

        horizontalSpacer_20 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_20);

        ce0Lim = new QDoubleSpinBox(vWidget_4);
        ce0Lim->setObjectName(QString::fromUtf8("ce0Lim"));
        ce0Lim->setMinimumSize(QSize(150, 40));

        horizontalLayout_21->addWidget(ce0Lim);

        pushButton_8 = new QPushButton(vWidget_4);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        sizePolicy2.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy2);
        pushButton_8->setMinimumSize(QSize(0, 30));

        horizontalLayout_21->addWidget(pushButton_8);


        verticalLayout_6->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_18 = new QLabel(vWidget_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_22->addWidget(label_18);

        horizontalSpacer_21 = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_21);

        ceNLim = new QDoubleSpinBox(vWidget_4);
        ceNLim->setObjectName(QString::fromUtf8("ceNLim"));
        ceNLim->setMinimumSize(QSize(150, 40));

        horizontalLayout_22->addWidget(ceNLim);

        pushButton_9 = new QPushButton(vWidget_4);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        sizePolicy2.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy2);
        pushButton_9->setMinimumSize(QSize(0, 30));

        horizontalLayout_22->addWidget(pushButton_9);


        verticalLayout_6->addLayout(horizontalLayout_22);


        horizontalLayout_5->addWidget(vWidget_4);

        line = new QFrame(ceBoundaries);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy2.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy2);
        line->setMinimumSize(QSize(5, 0));
        QFont font1;
        font1.setPointSize(14);
        line->setFont(font1);
        line->setLineWidth(10);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line);

        widget1 = new QWidget(ceBoundaries);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_11 = new QLabel(widget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_23->addWidget(label_11);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_22);

        ce0Min = new QLineEdit(widget1);
        ce0Min->setObjectName(QString::fromUtf8("ce0Min"));
        sizePolicy3.setHeightForWidth(ce0Min->sizePolicy().hasHeightForWidth());
        ce0Min->setSizePolicy(sizePolicy3);
        ce0Min->setMinimumSize(QSize(130, 35));

        horizontalLayout_23->addWidget(ce0Min);

        pushButton_10 = new QPushButton(widget1);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        sizePolicy2.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy2);
        pushButton_10->setMinimumSize(QSize(75, 40));

        horizontalLayout_23->addWidget(pushButton_10);


        verticalLayout_3->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_19 = new QLabel(widget1);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_24->addWidget(label_19);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_23);

        ce0Max = new QLineEdit(widget1);
        ce0Max->setObjectName(QString::fromUtf8("ce0Max"));
        sizePolicy3.setHeightForWidth(ce0Max->sizePolicy().hasHeightForWidth());
        ce0Max->setSizePolicy(sizePolicy3);
        ce0Max->setMinimumSize(QSize(130, 35));

        horizontalLayout_24->addWidget(ce0Max);

        pushButton_11 = new QPushButton(widget1);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        sizePolicy2.setHeightForWidth(pushButton_11->sizePolicy().hasHeightForWidth());
        pushButton_11->setSizePolicy(sizePolicy2);
        pushButton_11->setMinimumSize(QSize(75, 40));

        horizontalLayout_24->addWidget(pushButton_11);


        verticalLayout_3->addLayout(horizontalLayout_24);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_20 = new QLabel(widget1);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_25->addWidget(label_20);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_24);

        ceNMin = new QLineEdit(widget1);
        ceNMin->setObjectName(QString::fromUtf8("ceNMin"));
        sizePolicy3.setHeightForWidth(ceNMin->sizePolicy().hasHeightForWidth());
        ceNMin->setSizePolicy(sizePolicy3);
        ceNMin->setMinimumSize(QSize(130, 35));

        horizontalLayout_25->addWidget(ceNMin);

        pushButton_13 = new QPushButton(widget1);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        sizePolicy2.setHeightForWidth(pushButton_13->sizePolicy().hasHeightForWidth());
        pushButton_13->setSizePolicy(sizePolicy2);
        pushButton_13->setMinimumSize(QSize(75, 40));

        horizontalLayout_25->addWidget(pushButton_13);


        verticalLayout_3->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        label_21 = new QLabel(widget1);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_26->addWidget(label_21);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_25);

        ceNMax = new QLineEdit(widget1);
        ceNMax->setObjectName(QString::fromUtf8("ceNMax"));
        sizePolicy3.setHeightForWidth(ceNMax->sizePolicy().hasHeightForWidth());
        ceNMax->setSizePolicy(sizePolicy3);
        ceNMax->setMinimumSize(QSize(130, 35));

        horizontalLayout_26->addWidget(ceNMax);

        pushButton_14 = new QPushButton(widget1);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        sizePolicy2.setHeightForWidth(pushButton_14->sizePolicy().hasHeightForWidth());
        pushButton_14->setSizePolicy(sizePolicy2);
        pushButton_14->setMinimumSize(QSize(75, 40));

        horizontalLayout_26->addWidget(pushButton_14);


        verticalLayout_3->addLayout(horizontalLayout_26);


        horizontalLayout_5->addWidget(widget1);


        verticalLayout->addWidget(ceBoundaries);

        ButtonForm = new QWidget(verticalLayoutWidget_3);
        ButtonForm->setObjectName(QString::fromUtf8("ButtonForm"));
        sizePolicy1.setHeightForWidth(ButtonForm->sizePolicy().hasHeightForWidth());
        ButtonForm->setSizePolicy(sizePolicy1);
        ButtonForm->setMinimumSize(QSize(200, 40));
        ButtonForm->setMaximumSize(QSize(16777215, 400));
        ButtonForm->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_11 = new QHBoxLayout(ButtonForm);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_11 = new QSpacerItem(100, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);

        pushButton_2 = new QPushButton(ButtonForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy4);
        pushButton_2->setMinimumSize(QSize(0, 50));
        pushButton_2->setStyleSheet(QString::fromUtf8("background: rgb(107, 107, 159);\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_8);

        StartButton = new QPushButton(ButtonForm);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        sizePolicy4.setHeightForWidth(StartButton->sizePolicy().hasHeightForWidth());
        StartButton->setSizePolicy(sizePolicy4);
        StartButton->setMinimumSize(QSize(0, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(9);
        font2.setKerning(true);
        StartButton->setFont(font2);
        StartButton->setStyleSheet(QString::fromUtf8("background:green;\n"
"color: white;"));

        horizontalLayout_11->addWidget(StartButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_9);

        pushButton_5 = new QPushButton(ButtonForm);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy4.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy4);
        pushButton_5->setMinimumSize(QSize(0, 50));
        pushButton_5->setStyleSheet(QString::fromUtf8("background:red;\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_5);


        verticalLayout->addWidget(ButtonForm);


        retranslateUi(CEsettingsForm);

        QMetaObject::connectSlotsByName(CEsettingsForm);
    } // setupUi

    void retranslateUi(QWidget *CEsettingsForm)
    {
        CEsettingsForm->setWindowTitle(QCoreApplication::translate("CEsettingsForm", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("CEsettingsForm", "CE Boundaries", nullptr));
        label_5->setText(QCoreApplication::translate("CEsettingsForm", "Cyclic Errors Compensation Parameters", nullptr));
        radioButton_2->setText(QCoreApplication::translate("CEsettingsForm", "Use USC for next corrections", nullptr));
        radioButton->setText(QCoreApplication::translate("CEsettingsForm", "Use USC at startup", nullptr));
        label_4->setText(QCoreApplication::translate("CEsettingsForm", "user supply coefficients(USC)", nullptr));
        label_8->setText(QCoreApplication::translate("CEsettingsForm", "CE C0", nullptr));
        pushButton->setText(QCoreApplication::translate("CEsettingsForm", "Reset", nullptr));
        label_12->setText(QCoreApplication::translate("CEsettingsForm", "CE CN", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CEsettingsForm", "Reset", nullptr));
        label_13->setText(QCoreApplication::translate("CEsettingsForm", "CE C1", nullptr));
        pushButton_4->setText(QCoreApplication::translate("CEsettingsForm", "Reset", nullptr));
        label_2->setText(QCoreApplication::translate("CEsettingsForm", "Calculated coefficients", nullptr));
        label_9->setText(QCoreApplication::translate("CEsettingsForm", "CE0", nullptr));
        label_14->setText(QCoreApplication::translate("CEsettingsForm", "CE N", nullptr));
        label_15->setText(QCoreApplication::translate("CEsettingsForm", "Meas", nullptr));
        pushButton_12->setText(QCoreApplication::translate("CEsettingsForm", "Update", nullptr));
        label_6->setText(QCoreApplication::translate("CEsettingsForm", "CE Boundaries", nullptr));
        label_10->setText(QCoreApplication::translate("CEsettingsForm", "CE Min Vel", nullptr));
        pushButton_6->setText(QCoreApplication::translate("CEsettingsForm", "Default", nullptr));
        label_16->setText(QCoreApplication::translate("CEsettingsForm", "CE Max Vel", nullptr));
        pushButton_7->setText(QCoreApplication::translate("CEsettingsForm", "Default", nullptr));
        label_17->setText(QCoreApplication::translate("CEsettingsForm", "CE 0 Limit", nullptr));
        pushButton_8->setText(QCoreApplication::translate("CEsettingsForm", "Default", nullptr));
        label_18->setText(QCoreApplication::translate("CEsettingsForm", "CE N Limit", nullptr));
        pushButton_9->setText(QCoreApplication::translate("CEsettingsForm", "Default", nullptr));
        label_11->setText(QCoreApplication::translate("CEsettingsForm", "CE0 Min", nullptr));
        pushButton_10->setText(QCoreApplication::translate("CEsettingsForm", "Reset", nullptr));
        label_19->setText(QCoreApplication::translate("CEsettingsForm", "CE 0 Max", nullptr));
        pushButton_11->setText(QCoreApplication::translate("CEsettingsForm", "Reset", nullptr));
        label_20->setText(QCoreApplication::translate("CEsettingsForm", "CE N Min", nullptr));
        pushButton_13->setText(QCoreApplication::translate("CEsettingsForm", "Reset", nullptr));
        label_21->setText(QCoreApplication::translate("CEsettingsForm", "CE N Max", nullptr));
        pushButton_14->setText(QCoreApplication::translate("CEsettingsForm", "Reset", nullptr));
        pushButton_2->setText(QCoreApplication::translate("CEsettingsForm", "Apply", nullptr));
        StartButton->setText(QCoreApplication::translate("CEsettingsForm", "OK", nullptr));
        pushButton_5->setText(QCoreApplication::translate("CEsettingsForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CEsettingsForm: public Ui_CEsettingsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CESETTINGSFORM_H
