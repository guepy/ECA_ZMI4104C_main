#include "graphsform.h"
#include "ui_graphsform.h"

graphsForm::graphsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::graphsForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    position=new double[5];
    initComplete=false;
    axisRange = new double[2];
    axisRange[0] = -1e-10;
    axisRange[1] = 1e-9;
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(5000);
    timerTimeout=10;
    graphNbr=0;
    for(int i=0;i<4;i++)
        isThereAgraph[i]=0;
    setupRealtimeDataDemo(ui->customPlot);
}

void graphsForm::setupRealtimeDataDemo(QCustomPlot *customPlot)
    {
    //---------------Setup function--------------------------------------------

    ui->spinBox->setValue(timerTimeout);
    QPen pen(Qt::darkBlue, 3, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin);

    for(int axisNbr=0;axisNbr<4;axisNbr++){
        switch(axisNbr){
        case 1:
            pen.setColor(Qt::red);
            pen.setStyle(Qt::DashLine);
            break;
        case 2:
            pen.setColor(Qt::green);
            pen.setStyle(Qt::SolidLine);
            break;
        case 3:
            pen.setColor(Qt::gray);
            pen.setStyle(Qt::DashDotDotLine);
            break;
        }

        customPlot->addGraph(); // blue line
        customPlot->graph(axisNbr)->setPen(pen);
        qDebug()<<"graph "<<axisNbr;
    }

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();

    // setup a timer that repeatedly calls graphsForm::refreshGraphs:
    graphTimer = new QTimer(this);
    connect(graphTimer, &QTimer::timeout, this, QOverload<>::of(&graphsForm::refreshGraphs));

}
void graphsForm::refreshGraphs(){
    static QTime time(QTime::currentTime());
    // calculate new data point:
    key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
    // make key axis range scroll with the data (at a constant range size of 20):
    ui->customPlot->xAxis->setRange(key, 20, Qt::AlignRight);

    if (key-lastPointKey>timerTimeout/1000) // at most add point every 100 ms
    {
        for(int i=0;i<4;i++){
            // add data to lines:
            if(isThereAgraph[i]){
                qDebug()<<"axis "<<i+1;
                ui->customPlot->graph(i)->setVisible(true);
                ui->customPlot->graph(i)->addData(key, *(position+i));
            }
            else{
                //ui->customPlot->graph(i)->addData(key, 0);
                ui->customPlot->graph(i)->setVisible(false);
            }
          }
        lastPointKey = key;
        ui->customPlot->yAxis->rescale(true);
        ui->customPlot->replot();

}

}

void graphsForm::on_scaleAxisRequest_recieved(int units){
    /*
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
    /*/
}
/*
void graphsForm:: setAxisRange(double* range){
    axisRange[0]=range[]
}*/
void graphsForm::on_initBoardsComplete_recieved(){
    qDebug()<<"waitInitComplete";
    graphTimer->start(0); // Interval 0 means to refresh as fast as possible
    initComplete=true;
}
void graphsForm::on_initBoardsRequest_recieved(){
    initComplete=false;
    graphTimer->stop(); // Interval 0 means to refresh as fast as possible
}
void graphsForm::updatePosition(double* pos){
    /*for(int i=0; i<5; i++)
        position[i] = pos[i];*/
    position = pos;
}
graphsForm::~graphsForm()
{
    graphTimer->stop();
    emit closeThis();
    qDebug()<<"Close this emitted";
    this->deleteLater();
    delete ui;
}

void graphsForm::closeForm(){
emit closeThis();
qDebug()<<"Close this emitted";
this->deleteLater();
}


void graphsForm::on_checkBox_clicked(bool checked)
{

    if(checked){
        isThereAgraph[0] = 1;

    }
    else{
        isThereAgraph[0] = 0;
    }
}


void graphsForm::on_checkBox_2_clicked(bool checked)
{


    if(checked){
        isThereAgraph[1] = 1;
    }
    else{
        isThereAgraph[1] = 0;
    }
}


void graphsForm::on_checkBox_3_clicked(bool checked)
{
    if(checked){
        isThereAgraph[2] = 1;
    }
    else{
        isThereAgraph[2] = 0;
    }
}

void graphsForm::updateGraphOnAxis(unsigned int graphNbr, unsigned int axisNbr){

}
void graphsForm::graphsForm::on_checkBox_4_clicked(bool checked)
{

    if(checked){
        isThereAgraph[3] = 1;

    }
    else{
        isThereAgraph[3] = 0;
    }
}


void graphsForm::on_spinBox_valueChanged(int arg1)
{
    spinboxVal=arg1;
}


void graphsForm::on_graphsForm_destroyed()
{
    graphTimer->stop();
    this->destroy();
    emit closeThis();
    this->deleteLater();
    delete ui;
}


void graphsForm::on_pushButton_2_clicked()
{
    timerTimeout =spinboxVal;
}


