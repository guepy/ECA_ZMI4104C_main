/********************************************************************************
** Form generated from reading UI file 'graphsform.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHSFORM_H
#define UI_GRAPHSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_graphsForm
{
public:
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QWidget *horizontalWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QWidget *selectAxisWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QSpacerItem *verticalSpacer_3;
    QCustomPlot *customPlot;
    QHBoxLayout *horizontalLayout_2;
    QWidget *verticalWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelAxis;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout;
    QLabel *dataAxis;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QWidget *graphsForm)
    {
        if (graphsForm->objectName().isEmpty())
            graphsForm->setObjectName(QString::fromUtf8("graphsForm"));
        graphsForm->resize(869, 658);
        graphsForm->setMinimumSize(QSize(0, 40));
        graphsForm->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}\n"
"QPushButton, QToolButton{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border: 2px solid gray;\n"
"padding: 0 8px;\n"
"border-radius:10px;\n"
"text-align: center;\n"
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
"}\n"
"#graphsForm{\n"
"background-color: rgb(94, 94, 94);\n"
"}"));
        horizontalLayout_5 = new QHBoxLayout(graphsForm);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalWidget_3 = new QWidget(graphsForm);
        horizontalWidget_3->setObjectName(QString::fromUtf8("horizontalWidget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalWidget_3->sizePolicy().hasHeightForWidth());
        horizontalWidget_3->setSizePolicy(sizePolicy);
        horizontalWidget_3->setStyleSheet(QString::fromUtf8("#horizontalWidget_3{\n"
"border: 1px solid;\n"
"	background-color:rgb(182, 182, 182);\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(horizontalWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(horizontalWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        spinBox = new QSpinBox(horizontalWidget_3);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy1);
        spinBox->setMinimumSize(QSize(100, 35));

        horizontalLayout->addWidget(spinBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_5 = new QLabel(horizontalWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        horizontalSpacer = new QSpacerItem(200, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(horizontalWidget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(80, 40));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color:rgb(108, 255, 137)"));

        horizontalLayout->addWidget(pushButton_2);


        horizontalLayout_3->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(horizontalWidget_3);

        selectAxisWidget = new QWidget(graphsForm);
        selectAxisWidget->setObjectName(QString::fromUtf8("selectAxisWidget"));
        sizePolicy.setHeightForWidth(selectAxisWidget->sizePolicy().hasHeightForWidth());
        selectAxisWidget->setSizePolicy(sizePolicy);
        selectAxisWidget->setMinimumSize(QSize(0, 60));
        selectAxisWidget->setStyleSheet(QString::fromUtf8("#selectAxisWidget{\n"
"border: 1px solid;\n"
"	background-color:rgb(240, 255, 216);\n"
"    border: 2px solid gray;\n"
"    border-radius: 10px;\n"
"}\n"
"QCheckBox{\n"
"font: 75 12pt \"MS Shell Dlg 2\";\n"
"border-radius:5px;\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(selectAxisWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(selectAxisWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(label_6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        checkBox = new QCheckBox(selectAxisWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_4->addWidget(checkBox);

        checkBox_2 = new QCheckBox(selectAxisWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_4->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(selectAxisWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_4->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(selectAxisWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_4->addWidget(checkBox_4);


        verticalLayout_3->addWidget(selectAxisWidget);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        customPlot = new QCustomPlot(graphsForm);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy3);
        customPlot->setMinimumSize(QSize(830, 440));

        verticalLayout_3->addWidget(customPlot);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalWidget_2 = new QWidget(graphsForm);
        verticalWidget_2->setObjectName(QString::fromUtf8("verticalWidget_2"));
        sizePolicy1.setHeightForWidth(verticalWidget_2->sizePolicy().hasHeightForWidth());
        verticalWidget_2->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(verticalWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelAxis = new QLabel(verticalWidget_2);
        labelAxis->setObjectName(QString::fromUtf8("labelAxis"));
        labelAxis->setMinimumSize(QSize(0, 35));
        labelAxis->setStyleSheet(QString::fromUtf8("color: rgb(255, 170, 0)"));

        verticalLayout_2->addWidget(labelAxis);


        horizontalLayout_2->addWidget(verticalWidget_2);

        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        dataAxis = new QLabel(graphsForm);
        dataAxis->setObjectName(QString::fromUtf8("dataAxis"));
        sizePolicy.setHeightForWidth(dataAxis->sizePolicy().hasHeightForWidth());
        dataAxis->setSizePolicy(sizePolicy);
        dataAxis->setMinimumSize(QSize(40, 40));
        dataAxis->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(dataAxis);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        retranslateUi(graphsForm);

        QMetaObject::connectSlotsByName(graphsForm);
    } // setupUi

    void retranslateUi(QWidget *graphsForm)
    {
        graphsForm->setWindowTitle(QCoreApplication::translate("graphsForm", "Graphs", nullptr));
        label_3->setText(QCoreApplication::translate("graphsForm", "Refresh time", nullptr));
        label_5->setText(QCoreApplication::translate("graphsForm", "ms", nullptr));
        pushButton_2->setText(QCoreApplication::translate("graphsForm", "Apply", nullptr));
        label_6->setText(QCoreApplication::translate("graphsForm", "Select Axis : ", nullptr));
        checkBox->setText(QCoreApplication::translate("graphsForm", "Axis1", nullptr));
        checkBox_2->setText(QCoreApplication::translate("graphsForm", "Axis2", nullptr));
        checkBox_3->setText(QCoreApplication::translate("graphsForm", "Axis3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("graphsForm", "Axis4", nullptr));
        labelAxis->setText(QCoreApplication::translate("graphsForm", "Axis : ", nullptr));
        dataAxis->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class graphsForm: public Ui_graphsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHSFORM_H
