#include "graphsform.h"
#include "ui_graphsform.h"


graphsForm::graphsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphsForm)
{
    ui->setupUi(this);
    position=new double[5];
    initComplete=false;
    axisRange = new double[2];
    axisRange[0] = -1e-9;
    axisRange[1] = 1e-9;
    setupRealtimeDataDemo(ui->customPlot);
}

void graphsForm::setupRealtimeDataDemo(QCustomPlot *customPlot)
    {
    //---------------Setup function--------------------------------------------

    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    //customPlot->yAxis->setRange(axisRange[0], axisRange[1]);
    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis,SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls graphsForm::refreshGraphs:
    graphTimer = new QTimer(this);
    connect(graphTimer, &QTimer::timeout, this, QOverload<>::of(&graphsForm::refreshGraphs));
    //graphTimer->setInterval(100);
    graphTimer->start(100); // Interval 0 means to refresh as fast as possible

}
void graphsForm::refreshGraphs(){
    static QTime time(QTime::currentTime());
    //ui->customPlot->yAxis->rescale(true);
    // calculate two new data points:
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;

        ;//wait for boards initialization to complete
    if(initComplete){
        if (key-lastPointKey > 0.1) // at most add point every 100 ms
        {

          // add data to lines:
            qDebug()<<"position is "<<*(position+2);
            lastPointKey = key;
          ui->customPlot->graph(0)->addData(key, *(position+2));//qSin(key)+qrand()/(double)RAND_MAX*1*qSin(key/0.3843));
          //ui->customPlot->graph(1)->addData(key, qCos(key)+qrand()/(double)RAND_MAX*0.5*qSin(key/0.4364));
          // rescale value (vertical) axis to fit the current data:
          //dHigh=ui->customPlot->yAxis2->range().upper;
          //dLow=ui->customPlot->yAxis2->range().lower;
          //ui->customPlot->graph(0)->setAdaptiveSampling(true);
        }
        // make key axis range scroll with the data (at a constant range size of 8):
        ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
        ui->customPlot->graph(0)->rescaleValueAxis(true);
        //ui->customPlot->yAxis->setRange(dLow,dHigh);
        ui->customPlot->replot();

        // calculate frames per second:
        static double lastFpsKey;
        static int frameCount;
        ++frameCount;
        if (key-lastFpsKey > 2) // average fps over 2 seconds
        {
          /*ui->statusBar->showMessage(
                QString("%1 FPS, Total Data points: %2")
                .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
                , 0);*/
          lastFpsKey = key;
          frameCount = 0;
        }
    }
}

void graphsForm::on_scaleAxisRequest_recieved(int units){
    switch (units) {
        case 0:
        ui->customPlot->yAxis->setRange(-axisRange[0], axisRange[1]);//mm
        break;
        case 1:
        ui->customPlot->yAxis->setRange(-axisRange[0]*1000, axisRange[1]*1000); //µm
        break;
        case 2:
        ui->customPlot->yAxis->setRange(-axisRange[0]*1000000, axisRange[1]*1000000); //nm
        break;
        case 3:
        ui->customPlot->yAxis->setRange(-axisRange[0]*0.1, axisRange[1]*0.1);//cm
        break;
        default:
        break;

    }
}
/*
void graphsForm:: setAxisRange(double* range){
    axisRange[0]=range[]
}*/
void graphsForm::on_initBoardsComplete_recieved(){
    qDebug()<<"waitInitComplete\n";
    initComplete=true;
}
void graphsForm::on_initBoardsRequest_recieved(){
    initComplete=false;
}
void graphsForm::updatePosition(double* pos){
    /*for(int i=0; i<5; i++)
        position[i] = pos[i];*/
    position = pos;
}
graphsForm::~graphsForm()
{
    graphTimer->stop();
    this->destroy(true,true);
    delete ui;
}

void graphsForm::closeForm(){
emit closeThis();
qDebug()<<"Close this emitted";
this->deleteLater();
}
