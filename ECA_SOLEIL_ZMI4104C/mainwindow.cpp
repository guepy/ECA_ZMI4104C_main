#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MySlots *flyscan_form=new MySlots;
    connect(this, &MainWindow::openFsForm, flyscan_form, &MySlots::openForm);
    connect(this, &MainWindow::closeFsForm, flyscan_form, &MySlots::closeForm);
    connect(flyscan_form, &MySlots::closeThis, this, &MainWindow::closeFlyscanForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event){
    QPen circlePen;
    int cordx=460, cordy=400, inc=47;
    circlePen.setColor(Qt::black);
    circlePen.setStyle(Qt::SolidLine);
    circlePen.setWidth(3);
    QPainter circlePainter,circlePainter2,circlePainter3,circlePainter4,circlePainter5;
    for(int i=0;i<5;i++){
        circlePainter.begin(this);
        circlePainter.setPen(circlePen);
        circlePainter.setBrush(QColor(Qt::red));
        circlePainter.drawEllipse(QPoint(cordx,cordy),15,15);
        circlePainter.end();
        cordy+=inc;

    }
}

void MainWindow::on_pushButton_13_clicked()
{
    if(!fsForm) openFlyscanForm();
    else reopenFlyscanForm();
}
void MainWindow::openFlyscanForm(){
    printf("Sending openFsForm signal to flyscanform\n");
    emit openFsForm();
    fsForm=1;
}
void MainWindow::closeFlyscanForm(){
    fsForm=0;
}
void MainWindow::reopenFlyscanForm(){
    printf("Sending closeFsForm signal to flyscanform\n");
    emit closeFsForm();
    printf("Sending openFsForm signal to flyscanform\n");
    emit openFsForm();
}

