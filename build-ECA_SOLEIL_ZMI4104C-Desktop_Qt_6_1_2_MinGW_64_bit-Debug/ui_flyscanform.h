/********************************************************************************
** Form generated from reading UI file 'flyscanform.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
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
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QWidget *horizontalWidget_21;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_7;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer_14;
    QWidget *horizontalWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QWidget *horizontalWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QListView *listView;
    QWidget *ButtonForm;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_2;
    QPushButton *StartButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QWidget *statForm;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_9;
    QLineEdit *lineEdit_5;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_10;
    QLineEdit *lineEdit_6;
    QSpacerItem *horizontalSpacer_11;

    void setupUi(QWidget *FlyscanForm)
    {
        if (FlyscanForm->objectName().isEmpty())
            FlyscanForm->setObjectName(QString::fromUtf8("FlyscanForm"));
        FlyscanForm->resize(834, 701);
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
"}"));
        SettingsForm = new QWidget(FlyscanForm);
        SettingsForm->setObjectName(QString::fromUtf8("SettingsForm"));
        SettingsForm->setGeometry(QRect(20, 230, 791, 251));
        SettingsForm->setStyleSheet(QString::fromUtf8("#SettingsForm{\n"
"border: 5px solid;\n"
"border-color: white;\n"
"}"));
        verticalLayout = new QVBoxLayout(SettingsForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalWidget_2 = new QWidget(SettingsForm);
        horizontalWidget_2->setObjectName(QString::fromUtf8("horizontalWidget_2"));
        horizontalWidget_2->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_2 = new QHBoxLayout(horizontalWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(horizontalWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(horizontalWidget_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        label_6 = new QLabel(horizontalWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 75 10pt \"MS Shell Dlg 2\";"));

        horizontalLayout_2->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_3 = new QLabel(horizontalWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_2->addWidget(label_3);

        lineEdit_2 = new QLineEdit(horizontalWidget_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        label_7 = new QLabel(horizontalWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font: 75 10pt \"MS Shell Dlg 2\";"));

        horizontalLayout_2->addWidget(label_7);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_4 = new QLabel(horizontalWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_3 = new QLineEdit(horizontalWidget_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setMinimumSize(QSize(100, 25));

        horizontalLayout_2->addWidget(lineEdit_3);


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
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy3);
        comboBox->setMinimumSize(QSize(180, 35));

        horizontalLayout_6->addWidget(comboBox);

        horizontalSpacer_6 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);

        label_11 = new QLabel(horizontalWidget_21);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy3.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy3);
        label_11->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_6->addWidget(label_11);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        comboBox_2 = new QComboBox(horizontalWidget_21);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        sizePolicy3.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy3);
        comboBox_2->setMinimumSize(QSize(60, 35));

        horizontalLayout_6->addWidget(comboBox_2);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_14);


        verticalLayout->addWidget(horizontalWidget_21);

        horizontalWidget_3 = new QWidget(SettingsForm);
        horizontalWidget_3->setObjectName(QString::fromUtf8("horizontalWidget_3"));
        horizontalWidget_3->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_3 = new QHBoxLayout(horizontalWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(horizontalWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_3->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        checkBox = new QCheckBox(horizontalWidget_3);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_3->addWidget(checkBox);

        checkBox_3 = new QCheckBox(horizontalWidget_3);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_3->addWidget(checkBox_3);

        checkBox_2 = new QCheckBox(horizontalWidget_3);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_3->addWidget(checkBox_2);

        checkBox_4 = new QCheckBox(horizontalWidget_3);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_3->addWidget(checkBox_4);


        verticalLayout->addWidget(horizontalWidget_3);

        horizontalWidget_4 = new QWidget(SettingsForm);
        horizontalWidget_4->setObjectName(QString::fromUtf8("horizontalWidget_4"));
        horizontalWidget_4->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_4 = new QHBoxLayout(horizontalWidget_4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_8 = new QLabel(horizontalWidget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_4->addWidget(label_8);

        lineEdit_4 = new QLineEdit(horizontalWidget_4);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        horizontalLayout_4->addWidget(lineEdit_4);

        pushButton = new QPushButton(horizontalWidget_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy3.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy3);
        pushButton->setMinimumSize(QSize(100, 40));

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout->addWidget(horizontalWidget_4);

        listView = new QListView(FlyscanForm);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(20, 90, 791, 131));
        ButtonForm = new QWidget(FlyscanForm);
        ButtonForm->setObjectName(QString::fromUtf8("ButtonForm"));
        ButtonForm->setGeometry(QRect(20, 640, 801, 51));
        ButtonForm->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_5 = new QHBoxLayout(ButtonForm);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_6 = new QPushButton(ButtonForm);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy1.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy1);
        pushButton_6->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";\n"
"background:rgb(85, 85, 0);\n"
"color: white;"));

        horizontalLayout_5->addWidget(pushButton_6);

        horizontalSpacer_4 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        pushButton_2 = new QPushButton(ButtonForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setStyleSheet(QString::fromUtf8("background: rgb(107, 107, 159);\n"
"color: white;"));

        horizontalLayout_5->addWidget(pushButton_2);

        StartButton = new QPushButton(ButtonForm);
        StartButton->setObjectName(QString::fromUtf8("StartButton"));
        sizePolicy1.setHeightForWidth(StartButton->sizePolicy().hasHeightForWidth());
        StartButton->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("MS Shell Dlg 2")});
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
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

        horizontalLayoutWidget = new QWidget(FlyscanForm);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 20, 811, 35));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setStyleSheet(QString::fromUtf8("font: 75 20pt \"MS Shell Dlg 2\";"));

        horizontalLayout->addWidget(label);

        statForm = new QWidget(FlyscanForm);
        statForm->setObjectName(QString::fromUtf8("statForm"));
        statForm->setGeometry(QRect(20, 500, 791, 51));
        statForm->setStyleSheet(QString::fromUtf8("#statForm{\n"
"border: 2px solid;\n"
"border-color:white;\n"
"}"));
        horizontalLayout_7 = new QHBoxLayout(statForm);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_12);

        label_10 = new QLabel(statForm);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("\n"
"color: blue;"));

        horizontalLayout_7->addWidget(label_10);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);

        lineEdit_5 = new QLineEdit(statForm);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy3.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy3);
        lineEdit_5->setMinimumSize(QSize(80, 35));

        horizontalLayout_7->addWidget(lineEdit_5);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        label_12 = new QLabel(statForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("\n"
"color: blue;"));

        horizontalLayout_7->addWidget(label_12);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_10);

        lineEdit_6 = new QLineEdit(statForm);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        sizePolicy3.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy3);
        lineEdit_6->setMinimumSize(QSize(80, 35));

        horizontalLayout_7->addWidget(lineEdit_6);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);


        retranslateUi(FlyscanForm);

        QMetaObject::connectSlotsByName(FlyscanForm);
    } // setupUi

    void retranslateUi(QWidget *FlyscanForm)
    {
        FlyscanForm->setWindowTitle(QCoreApplication::translate("FlyscanForm", "Flyscan", nullptr));
        label_2->setText(QCoreApplication::translate("FlyscanForm", "Frequency", nullptr));
        label_6->setText(QCoreApplication::translate("FlyscanForm", "Hz", nullptr));
        label_3->setText(QCoreApplication::translate("FlyscanForm", "Integration time", nullptr));
        label_7->setText(QCoreApplication::translate("FlyscanForm", "ms", nullptr));
        label_4->setText(QCoreApplication::translate("FlyscanForm", "Nbr of points", nullptr));
        label_9->setText(QCoreApplication::translate("FlyscanForm", "Method", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("FlyscanForm", "RAM DATA Flyscan", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("FlyscanForm", "FIFO Flyscan", nullptr));

        label_11->setText(QCoreApplication::translate("FlyscanForm", "Nbr of axis", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("FlyscanForm", "1", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("FlyscanForm", "2", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("FlyscanForm", "3", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("FlyscanForm", "4", nullptr));

        label_5->setText(QCoreApplication::translate("FlyscanForm", "Select Axis : ", nullptr));
        checkBox->setText(QCoreApplication::translate("FlyscanForm", "Axis1", nullptr));
        checkBox_3->setText(QCoreApplication::translate("FlyscanForm", "Axis2", nullptr));
        checkBox_2->setText(QCoreApplication::translate("FlyscanForm", "Axis3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("FlyscanForm", "Axis4", nullptr));
        label_8->setText(QCoreApplication::translate("FlyscanForm", "Save folder", nullptr));
        pushButton->setText(QCoreApplication::translate("FlyscanForm", "Browse", nullptr));
        pushButton_6->setText(QCoreApplication::translate("FlyscanForm", "Plot graphs", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FlyscanForm", "Apply", nullptr));
        StartButton->setText(QCoreApplication::translate("FlyscanForm", "Start scan", nullptr));
        pushButton_4->setText(QCoreApplication::translate("FlyscanForm", "Stop scan", nullptr));
        pushButton_5->setText(QCoreApplication::translate("FlyscanForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("FlyscanForm", "Continuous scan", nullptr));
        label_10->setText(QCoreApplication::translate("FlyscanForm", "Moyenne", nullptr));
        label_12->setText(QCoreApplication::translate("FlyscanForm", "Ecart type", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlyscanForm: public Ui_FlyscanForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLYSCANFORM_H
