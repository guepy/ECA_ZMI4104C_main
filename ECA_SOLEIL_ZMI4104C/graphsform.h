#ifndef GRAPHSFORM_H
#define GRAPHSFORM_H

#include <qcustomplot/qcustomplot.h>

#include <QWidget>
namespace Ui {
class graphsForm;
}

class graphsForm : public QWidget
{
    Q_OBJECT

public:
    explicit graphsForm(QWidget *parent = nullptr);
    ~graphsForm();
    double dHigh=0.0, dLow=0.0;
    void closeForm();
signals:
    void closeThis();
private:
    Ui::graphsForm *ui;
    //QCustomPlot* customPlot;
    QTimer* graphTimer;
    double *position;
    bool initComplete;
    double* axisRange;
    bool isThereAgraph[4];
    unsigned int axisGraphNbr[4];
    unsigned int graphNbr;
    unsigned int timerTimeout;
    unsigned int spinboxVal;
    double key;

public slots:
    void updatePosition(double* pos);
    void on_initBoardsComplete_recieved();
    void on_initBoardsRequest_recieved();
    void on_scaleAxisRequest_recieved(int units);
private slots:
    void refreshGraphs();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    //void setAxisRange(double* range);
    void on_checkBox_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_checkBox_3_clicked(bool checked);
    void on_spinBox_valueChanged(int arg1);
    void on_graphsForm_destroyed();
    void on_pushButton_2_clicked();
    void on_checkBox_4_clicked(bool checked);
    void updateGraphOnAxis(unsigned int graphNbr,unsigned int axisNbr);
};

#endif // GRAPHSFORM_H
