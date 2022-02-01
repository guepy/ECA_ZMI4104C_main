/********************************************************************************
** Form generated from reading UI file 'positionoffsetform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITIONOFFSETFORM_H
#define UI_POSITIONOFFSETFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *leftBlockUnits;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_12;
    QLineEdit *offPosAxis1;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *offPosAxis2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_14;
    QLineEdit *offPosAxis3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_15;
    QLineEdit *offPosAxis4;
    QWidget *ButtonForm;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pushButton_2;
    QPushButton *okButton;
    QPushButton *pushButton_5;
    QLabel *label;

    void setupUi(QWidget *positionOffsetForm)
    {
        if (positionOffsetForm->objectName().isEmpty())
            positionOffsetForm->setObjectName(QString::fromUtf8("positionOffsetForm"));
        positionOffsetForm->resize(545, 405);
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
        vWidget_2->setGeometry(QRect(50, 30, 411, 231));
        vWidget_2->setStyleSheet(QString::fromUtf8("#vWidget_2{\n"
"border: 1px solid;\n"
"}"));
        verticalLayout_4 = new QVBoxLayout(vWidget_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_2 = new QRadioButton(vWidget_2);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setStyleSheet(QString::fromUtf8("\n"
"font: 75 14pt \"MS Shell Dlg 2\";"));

        horizontalLayout->addWidget(radioButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(vWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        leftBlockUnits = new QComboBox(vWidget_2);
        leftBlockUnits->addItem(QString());
        leftBlockUnits->addItem(QString());
        leftBlockUnits->addItem(QString());
        leftBlockUnits->addItem(QString());
        leftBlockUnits->setObjectName(QString::fromUtf8("leftBlockUnits"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftBlockUnits->sizePolicy().hasHeightForWidth());
        leftBlockUnits->setSizePolicy(sizePolicy);
        leftBlockUnits->setMinimumSize(QSize(80, 35));

        horizontalLayout->addWidget(leftBlockUnits);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_8 = new QLabel(vWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_13->addWidget(label_8);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        offPosAxis1 = new QLineEdit(vWidget_2);
        offPosAxis1->setObjectName(QString::fromUtf8("offPosAxis1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(offPosAxis1->sizePolicy().hasHeightForWidth());
        offPosAxis1->setSizePolicy(sizePolicy1);
        offPosAxis1->setMinimumSize(QSize(130, 35));

        horizontalLayout_13->addWidget(offPosAxis1);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(vWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        offPosAxis2 = new QLineEdit(vWidget_2);
        offPosAxis2->setObjectName(QString::fromUtf8("offPosAxis2"));
        sizePolicy1.setHeightForWidth(offPosAxis2->sizePolicy().hasHeightForWidth());
        offPosAxis2->setSizePolicy(sizePolicy1);
        offPosAxis2->setMinimumSize(QSize(130, 35));

        horizontalLayout_14->addWidget(offPosAxis2);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_13 = new QLabel(vWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_15->addWidget(label_13);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        offPosAxis3 = new QLineEdit(vWidget_2);
        offPosAxis3->setObjectName(QString::fromUtf8("offPosAxis3"));
        sizePolicy1.setHeightForWidth(offPosAxis3->sizePolicy().hasHeightForWidth());
        offPosAxis3->setSizePolicy(sizePolicy1);
        offPosAxis3->setMinimumSize(QSize(130, 35));

        horizontalLayout_15->addWidget(offPosAxis3);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_9 = new QLabel(vWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_16->addWidget(label_9);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_15);

        offPosAxis4 = new QLineEdit(vWidget_2);
        offPosAxis4->setObjectName(QString::fromUtf8("offPosAxis4"));
        sizePolicy1.setHeightForWidth(offPosAxis4->sizePolicy().hasHeightForWidth());
        offPosAxis4->setSizePolicy(sizePolicy1);
        offPosAxis4->setMinimumSize(QSize(130, 35));

        horizontalLayout_16->addWidget(offPosAxis4);


        verticalLayout_4->addLayout(horizontalLayout_16);

        ButtonForm = new QWidget(positionOffsetForm);
        ButtonForm->setObjectName(QString::fromUtf8("ButtonForm"));
        ButtonForm->setGeometry(QRect(130, 340, 401, 51));
        ButtonForm->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_11 = new QHBoxLayout(ButtonForm);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_11 = new QSpacerItem(150, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

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

        okButton = new QPushButton(ButtonForm);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        sizePolicy2.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        font.setKerning(true);
        okButton->setFont(font);
        okButton->setStyleSheet(QString::fromUtf8("background:green;\n"
"color: white;"));

        horizontalLayout_11->addWidget(okButton);

        pushButton_5 = new QPushButton(ButtonForm);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy2.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy2);
        pushButton_5->setStyleSheet(QString::fromUtf8("background:red;\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_5);

        label = new QLabel(positionOffsetForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 290, 351, 31));
        label->setStyleSheet(QString::fromUtf8("\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"color: red;"));

        retranslateUi(positionOffsetForm);

        QMetaObject::connectSlotsByName(positionOffsetForm);
    } // setupUi

    void retranslateUi(QWidget *positionOffsetForm)
    {
        positionOffsetForm->setWindowTitle(QCoreApplication::translate("positionOffsetForm", "Form", nullptr));
        radioButton_2->setText(QCoreApplication::translate("positionOffsetForm", "Enable position offsets", nullptr));
        label_2->setText(QCoreApplication::translate("positionOffsetForm", "units", nullptr));
        leftBlockUnits->setItemText(0, QCoreApplication::translate("positionOffsetForm", "mm", nullptr));
        leftBlockUnits->setItemText(1, QCoreApplication::translate("positionOffsetForm", "\302\265m", nullptr));
        leftBlockUnits->setItemText(2, QCoreApplication::translate("positionOffsetForm", "nm", nullptr));
        leftBlockUnits->setItemText(3, QCoreApplication::translate("positionOffsetForm", "cm", nullptr));

        label_8->setText(QCoreApplication::translate("positionOffsetForm", "Axis 1", nullptr));
        label_12->setText(QCoreApplication::translate("positionOffsetForm", "Axis 2", nullptr));
        label_13->setText(QCoreApplication::translate("positionOffsetForm", "Axis 3", nullptr));
        label_9->setText(QCoreApplication::translate("positionOffsetForm", "Axis 4", nullptr));
        pushButton_2->setText(QCoreApplication::translate("positionOffsetForm", "Apply", nullptr));
        okButton->setText(QCoreApplication::translate("positionOffsetForm", "OK", nullptr));
        pushButton_5->setText(QCoreApplication::translate("positionOffsetForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("positionOffsetForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class positionOffsetForm: public Ui_positionOffsetForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITIONOFFSETFORM_H
