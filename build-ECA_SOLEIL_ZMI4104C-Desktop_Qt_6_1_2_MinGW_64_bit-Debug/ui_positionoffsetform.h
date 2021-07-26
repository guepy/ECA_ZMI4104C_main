/********************************************************************************
** Form generated from reading UI file 'positionoffsetform.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITIONOFFSETFORM_H
#define UI_POSITIONOFFSETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_positionOffsetForm
{
public:
    QWidget *vWidget_2;
    QVBoxLayout *verticalLayout_4;
    QRadioButton *radioButton_2;
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
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_15;
    QLineEdit *lineEdit_14;
    QWidget *ButtonForm;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_2;
    QPushButton *StartButton;
    QPushButton *pushButton_5;

    void setupUi(QWidget *positionOffsetForm)
    {
        if (positionOffsetForm->objectName().isEmpty())
            positionOffsetForm->setObjectName(QString::fromUtf8("positionOffsetForm"));
        positionOffsetForm->resize(405, 364);
        positionOffsetForm->setStyleSheet(QString::fromUtf8("QLabel, QRadioButton{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"QComboBox, QLineEdit{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border-radius:1px;\n"
"border: 2px solid;\n"
"border-color: white;\n"
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
        vWidget_2 = new QWidget(positionOffsetForm);
        vWidget_2->setObjectName(QString::fromUtf8("vWidget_2"));
        vWidget_2->setGeometry(QRect(50, 30, 301, 231));
        vWidget_2->setStyleSheet(QString::fromUtf8("#vWidget_2{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(vWidget_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        radioButton_2 = new QRadioButton(vWidget_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setStyleSheet(QString::fromUtf8("\n"
"font: 75 14pt \"MS Shell Dlg 2\";"));

        verticalLayout_4->addWidget(radioButton_2);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_8 = new QLabel(vWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_13->addWidget(label_8);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        lineEdit_11 = new QLineEdit(vWidget_2);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_11->sizePolicy().hasHeightForWidth());
        lineEdit_11->setSizePolicy(sizePolicy);
        lineEdit_11->setMinimumSize(QSize(130, 35));

        horizontalLayout_13->addWidget(lineEdit_11);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(vWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        lineEdit_12 = new QLineEdit(vWidget_2);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        sizePolicy.setHeightForWidth(lineEdit_12->sizePolicy().hasHeightForWidth());
        lineEdit_12->setSizePolicy(sizePolicy);
        lineEdit_12->setMinimumSize(QSize(130, 35));

        horizontalLayout_14->addWidget(lineEdit_12);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_13 = new QLabel(vWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_15->addWidget(label_13);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        lineEdit_13 = new QLineEdit(vWidget_2);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        sizePolicy.setHeightForWidth(lineEdit_13->sizePolicy().hasHeightForWidth());
        lineEdit_13->setSizePolicy(sizePolicy);
        lineEdit_13->setMinimumSize(QSize(130, 35));

        horizontalLayout_15->addWidget(lineEdit_13);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_9 = new QLabel(vWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_16->addWidget(label_9);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_15);

        lineEdit_14 = new QLineEdit(vWidget_2);
        lineEdit_14->setObjectName(QString::fromUtf8("lineEdit_14"));
        sizePolicy.setHeightForWidth(lineEdit_14->sizePolicy().hasHeightForWidth());
        lineEdit_14->setSizePolicy(sizePolicy);
        lineEdit_14->setMinimumSize(QSize(130, 35));

        horizontalLayout_16->addWidget(lineEdit_14);


        verticalLayout_4->addLayout(horizontalLayout_16);

        ButtonForm = new QWidget(positionOffsetForm);
        ButtonForm->setObjectName(QString::fromUtf8("ButtonForm"));
        ButtonForm->setGeometry(QRect(0, 290, 401, 51));
        ButtonForm->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_11 = new QHBoxLayout(ButtonForm);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_11 = new QSpacerItem(150, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);

        pushButton_2 = new QPushButton(ButtonForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setStyleSheet(QString::fromUtf8("background: rgb(107, 107, 159);\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_2);

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

        horizontalLayout_11->addWidget(StartButton);

        pushButton_5 = new QPushButton(ButtonForm);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setStyleSheet(QString::fromUtf8("background:red;\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_5);


        retranslateUi(positionOffsetForm);

        QMetaObject::connectSlotsByName(positionOffsetForm);
    } // setupUi

    void retranslateUi(QWidget *positionOffsetForm)
    {
        positionOffsetForm->setWindowTitle(QCoreApplication::translate("positionOffsetForm", "Form", nullptr));
        radioButton_2->setText(QCoreApplication::translate("positionOffsetForm", "Enable position offsets", nullptr));
        label_8->setText(QCoreApplication::translate("positionOffsetForm", "Axis 1", nullptr));
        label_12->setText(QCoreApplication::translate("positionOffsetForm", "Axis 2", nullptr));
        label_13->setText(QCoreApplication::translate("positionOffsetForm", "Axis 3", nullptr));
        label_9->setText(QCoreApplication::translate("positionOffsetForm", "Axis 4", nullptr));
        pushButton_2->setText(QCoreApplication::translate("positionOffsetForm", "Apply", nullptr));
        StartButton->setText(QCoreApplication::translate("positionOffsetForm", "OK", nullptr));
        pushButton_5->setText(QCoreApplication::translate("positionOffsetForm", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class positionOffsetForm: public Ui_positionOffsetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITIONOFFSETFORM_H
