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
public slots:
    void updatePosition(double* pos);
    void on_initBoardsComplete_recieved();
    void on_initBoardsRequest_recieved();
    void on_scaleAxisRequest_recieved(int units);
private slots:
    void refreshGraphs();
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    //void setAxisRange(double* range);
};

#endif // GRAPHSFORM_H
