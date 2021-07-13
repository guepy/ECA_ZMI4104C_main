#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flyscanform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event){
    QPen circlePen;
    int cordx=420, cordy=350, inc=47;
    circlePen.setColor(Qt::black);
    circlePen.setStyle(Qt::SolidLine);
    circlePen.setWidth(3);
    QPainter circlePainter,circlePainter2,circlePainter3,circlePainter4,circlePainter5;
    for(int i=0;i<10;i++){
        circlePainter.begin(this);
        circlePainter.setPen(circlePen);
        circlePainter.setBrush(QColor(Qt::red));
        circlePainter.drawEllipse(QPoint(cordx,cordy),15,15);
        circlePainter.end();
        cordy+=inc;
        if(i==4) {
            cordx=490;
            cordy=350;
        }
    }
}

void MainWindow::on_toolButton_2_triggered(QAction *arg1)
{

}


void MainWindow::on_pushButton_13_clicked()
{
    FlyscanForm w;
    w.show();
    w.setVisible(true);
}

