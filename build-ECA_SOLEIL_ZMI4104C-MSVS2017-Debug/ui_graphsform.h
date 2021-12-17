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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_graphsForm
{
public:
    QCustomPlot *customPlot;
    QWidget *horizontalWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QComboBox *leftBlockUnits;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QTextEdit *textEdit_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QWidget *selectAxisWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;

    void setupUi(QWidget *graphsForm)
    {
        if (graphsForm->objectName().isEmpty())
            graphsForm->setObjectName(QString::fromUtf8("graphsForm"));
        graphsForm->resize(869, 512);
        graphsForm->setMinimumSize(QSize(0, 40));
        graphsForm->setStyleSheet(QString::fromUtf8("QLabel{\n"
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
"}\n"
"\n"
"QPushButton#resetButtonAxis1,#resetButtonAxis2,#resetButtonAxis3,#resetButtonAxis4,#resetButtonAllAxis,#resetCEerrorsButton{\n"
"background:rgb(161, 0, 0);\n"
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
"}"));
        customPlot = new QCustomPlot(graphsForm);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(20, 190, 831, 271));
        horizontalWidget_3 = new QWidget(graphsForm);
        horizontalWidget_3->setObjectName(QString::fromUtf8("horizontalWidget_3"));
        horizontalWidget_3->setGeometry(QRect(100, 30, 654, 51));
        horizontalLayout_3 = new QHBoxLayout(horizontalWidget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(horizontalWidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        leftBlockUnits = new QComboBox(horizontalWidget_3);
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
        leftBlockUnits->setMinimumSize(QSize(110, 35));

        horizontalLayout_2->addWidget(leftBlockUnits);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(horizontalWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(0, 35));

        horizontalLayout->addWidget(label_3);

        textEdit_3 = new QTextEdit(horizontalWidget_3);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textEdit_3->sizePolicy().hasHeightForWidth());
        textEdit_3->setSizePolicy(sizePolicy2);
        textEdit_3->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(textEdit_3);

        label_5 = new QLabel(horizontalWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        horizontalSpacer = new QSpacerItem(200, 10, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(horizontalWidget_3);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 40));

        horizontalLayout->addWidget(pushButton_2);


        horizontalLayout_3->addLayout(horizontalLayout);

        selectAxisWidget = new QWidget(graphsForm);
        selectAxisWidget->setObjectName(QString::fromUtf8("selectAxisWidget"));
        selectAxisWidget->setGeometry(QRect(60, 90, 773, 41));
        selectAxisWidget->setStyleSheet(QString::fromUtf8("font: 75 12pt \"MS Shell Dlg 2\";"));
        horizontalLayout_4 = new QHBoxLayout(selectAxisWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(selectAxisWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy3);
        label_6->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 75 14pt \"MS Shell Dlg 2\";\n"
"}"));

        horizontalLayout_4->addWidget(label_6);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        checkBox = new QCheckBox(selectAxisWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_4->addWidget(checkBox);

        checkBox_3 = new QCheckBox(selectAxisWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout_4->addWidget(checkBox_3);

        checkBox_2 = new QCheckBox(selectAxisWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_4->addWidget(checkBox_2);

        checkBox_4 = new QCheckBox(selectAxisWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_4->addWidget(checkBox_4);


        retranslateUi(graphsForm);

        QMetaObject::connectSlotsByName(graphsForm);
    } // setupUi

    void retranslateUi(QWidget *graphsForm)
    {
        graphsForm->setWindowTitle(QCoreApplication::translate("graphsForm", "Graphs", nullptr));
        label_4->setText(QCoreApplication::translate("graphsForm", "units", nullptr));
        leftBlockUnits->setItemText(0, QCoreApplication::translate("graphsForm", "mm", nullptr));
        leftBlockUnits->setItemText(1, QCoreApplication::translate("graphsForm", "\302\265m", nullptr));
        leftBlockUnits->setItemText(2, QCoreApplication::translate("graphsForm", "nm", nullptr));
        leftBlockUnits->setItemText(3, QCoreApplication::translate("graphsForm", "cm", nullptr));

        label_3->setText(QCoreApplication::translate("graphsForm", "Refresh time", nullptr));
        label_5->setText(QCoreApplication::translate("graphsForm", "ms", nullptr));
        pushButton_2->setText(QCoreApplication::translate("graphsForm", "Apply", nullptr));
        label_6->setText(QCoreApplication::translate("graphsForm", "Select Axis : ", nullptr));
        checkBox->setText(QCoreApplication::translate("graphsForm", "Axis1", nullptr));
        checkBox_3->setText(QCoreApplication::translate("graphsForm", "Axis2", nullptr));
        checkBox_2->setText(QCoreApplication::translate("graphsForm", "Axis3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("graphsForm", "Axis4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class graphsForm: public Ui_graphsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHSFORM_H