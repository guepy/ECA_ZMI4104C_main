/********************************************************************************
** Form generated from reading UI file 'presetpositionform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRESETPOSITIONFORM_H
#define UI_PRESETPOSITIONFORM_H

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

class Ui_presetPositionForm
{
public:
    QWidget *ButtonForm;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *applyButton;
    QPushButton *okButton;
    QPushButton *pushButton_5;
    QLabel *label;
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
    QLineEdit *presPosAxis1;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_13;
    QLineEdit *presPosAxis2;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_14;
    QLineEdit *presPosAxis3;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_15;
    QLineEdit *presPosAxis4;

    void setupUi(QWidget *presetPositionForm)
    {
        if (presetPositionForm->objectName().isEmpty())
            presetPositionForm->setObjectName(QString::fromUtf8("presetPositionForm"));
        presetPositionForm->resize(549, 426);
        presetPositionForm->setStyleSheet(QString::fromUtf8("QLabel{\n"
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
        ButtonForm = new QWidget(presetPositionForm);
        ButtonForm->setObjectName(QString::fromUtf8("ButtonForm"));
        ButtonForm->setGeometry(QRect(110, 360, 401, 51));
        ButtonForm->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_11 = new QHBoxLayout(ButtonForm);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_11 = new QSpacerItem(150, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_11);

        applyButton = new QPushButton(ButtonForm);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(applyButton->sizePolicy().hasHeightForWidth());
        applyButton->setSizePolicy(sizePolicy);
        applyButton->setStyleSheet(QString::fromUtf8("background: rgb(107, 107, 159);\n"
"color: white;"));

        horizontalLayout_11->addWidget(applyButton);

        okButton = new QPushButton(ButtonForm);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        sizePolicy.setHeightForWidth(okButton->sizePolicy().hasHeightForWidth());
        okButton->setSizePolicy(sizePolicy);
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
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setStyleSheet(QString::fromUtf8("background:red;\n"
"color: white;"));

        horizontalLayout_11->addWidget(pushButton_5);

        label = new QLabel(presetPositionForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 300, 351, 31));
        label->setStyleSheet(QString::fromUtf8("\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"color: red;"));
        vWidget_2 = new QWidget(presetPositionForm);
        vWidget_2->setObjectName(QString::fromUtf8("vWidget_2"));
        vWidget_2->setGeometry(QRect(40, 40, 411, 231));
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
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(leftBlockUnits->sizePolicy().hasHeightForWidth());
        leftBlockUnits->setSizePolicy(sizePolicy1);
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

        presPosAxis1 = new QLineEdit(vWidget_2);
        presPosAxis1->setObjectName(QString::fromUtf8("presPosAxis1"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(presPosAxis1->sizePolicy().hasHeightForWidth());
        presPosAxis1->setSizePolicy(sizePolicy2);
        presPosAxis1->setMinimumSize(QSize(130, 35));

        horizontalLayout_13->addWidget(presPosAxis1);


        verticalLayout_4->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(vWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        presPosAxis2 = new QLineEdit(vWidget_2);
        presPosAxis2->setObjectName(QString::fromUtf8("presPosAxis2"));
        sizePolicy2.setHeightForWidth(presPosAxis2->sizePolicy().hasHeightForWidth());
        presPosAxis2->setSizePolicy(sizePolicy2);
        presPosAxis2->setMinimumSize(QSize(130, 35));

        horizontalLayout_14->addWidget(presPosAxis2);


        verticalLayout_4->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_13 = new QLabel(vWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_15->addWidget(label_13);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_14);

        presPosAxis3 = new QLineEdit(vWidget_2);
        presPosAxis3->setObjectName(QString::fromUtf8("presPosAxis3"));
        sizePolicy2.setHeightForWidth(presPosAxis3->sizePolicy().hasHeightForWidth());
        presPosAxis3->setSizePolicy(sizePolicy2);
        presPosAxis3->setMinimumSize(QSize(130, 35));

        horizontalLayout_15->addWidget(presPosAxis3);


        verticalLayout_4->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_9 = new QLabel(vWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_16->addWidget(label_9);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_15);

        presPosAxis4 = new QLineEdit(vWidget_2);
        presPosAxis4->setObjectName(QString::fromUtf8("presPosAxis4"));
        sizePolicy2.setHeightForWidth(presPosAxis4->sizePolicy().hasHeightForWidth());
        presPosAxis4->setSizePolicy(sizePolicy2);
        presPosAxis4->setMinimumSize(QSize(130, 35));

        horizontalLayout_16->addWidget(presPosAxis4);


        verticalLayout_4->addLayout(horizontalLayout_16);


        retranslateUi(presetPositionForm);

        QMetaObject::connectSlotsByName(presetPositionForm);
    } // setupUi

    void retranslateUi(QWidget *presetPositionForm)
    {
        presetPositionForm->setWindowTitle(QCoreApplication::translate("presetPositionForm", "Form", nullptr));
        applyButton->setText(QCoreApplication::translate("presetPositionForm", "Apply", nullptr));
        okButton->setText(QCoreApplication::translate("presetPositionForm", "OK", nullptr));
        pushButton_5->setText(QCoreApplication::translate("presetPositionForm", "Cancel", nullptr));
        label->setText(QCoreApplication::translate("presetPositionForm", "TextLabel", nullptr));
        radioButton_2->setText(QCoreApplication::translate("presetPositionForm", "Enable position offsets", nullptr));
        label_2->setText(QCoreApplication::translate("presetPositionForm", "units", nullptr));
        leftBlockUnits->setItemText(0, QCoreApplication::translate("presetPositionForm", "mm", nullptr));
        leftBlockUnits->setItemText(1, QCoreApplication::translate("presetPositionForm", "\302\265m", nullptr));
        leftBlockUnits->setItemText(2, QCoreApplication::translate("presetPositionForm", "nm", nullptr));
        leftBlockUnits->setItemText(3, QCoreApplication::translate("presetPositionForm", "cm", nullptr));

        label_8->setText(QCoreApplication::translate("presetPositionForm", "Axis 1", nullptr));
        label_12->setText(QCoreApplication::translate("presetPositionForm", "Axis 2", nullptr));
        label_13->setText(QCoreApplication::translate("presetPositionForm", "Axis 3", nullptr));
        label_9->setText(QCoreApplication::translate("presetPositionForm", "Axis 4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class presetPositionForm: public Ui_presetPositionForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESETPOSITIONFORM_H
