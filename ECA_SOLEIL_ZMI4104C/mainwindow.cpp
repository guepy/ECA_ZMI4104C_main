
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

// --------------menu setings---------------------------
    QMenuBar *pMenuBar = new QMenuBar(this);
    setMenuBar(pMenuBar);
    m_settingsMenu= new QMenu("Settings", this);
    a_openMenu = new QAction("Settings", this);
    m_settingsMenu->addAction(a_openMenu);
    this->menuBar()->addMenu(m_settingsMenu);
    connect(m_settingsMenu, SIGNAL(triggered(QAction*)), this, SLOT(on_m_settingsMenu_clicked(QAction*)));

    setForm=new SettingsForm;
    flyscanForm=new FlyscanForm;
    posOffsetForm=new positionOffsetForm;
    presPositionForm = new presetPositionForm;

}

MainWindow::~MainWindow()
{
    this->destroy(true,true);
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
        circlePainter.setBrush(QColor(Qt::black));
        circlePainter.drawEllipse(QPoint(cordx,cordy),15,15);
        circlePainter.end();
        cordy+=inc;

    }
}
//-------Bouton continuous acquisition----------------
void MainWindow::on_pushButton_13_clicked()
{
    if(!fsForm_int) openFlyscanForm();
    else reopenFlyscanForm();
}
void MainWindow::openFlyscanForm(){
    flyscanForm->show();
    fsForm_int=1;
}
void MainWindow::closeFlyscanForm(){
    fsForm_int=0;
    flyscanForm->close();
}
void MainWindow::reopenFlyscanForm(){
    flyscanForm->close();
    flyscanForm->show();
}
// --------------------fin--------------------------

// --------------menu bar setings---------------------------
void MainWindow::on_m_settingsMenu_clicked(QAction*)
{
    if(!sfForm_int) openSettingsForm();
    else reopenSettingsForm();
}
void MainWindow::openSettingsForm(){
    setForm->show();
    sfForm_int=1;
}
void MainWindow::closeSettingsForm(){
    sfForm_int=0;
    setForm->close();
}
void MainWindow::reopenSettingsForm(){
    closeSettingsForm();
    openSettingsForm();
}
//--------------------fin------------------------------------

// --------Bouton set position offset-----------------------
void MainWindow::on_pushButton_11_clicked()
{
    if(!posOffForm_int) openPositionOffsetForm();
    else reopenPositionOffsetForm();
}
void MainWindow::openPositionOffsetForm(){
    posOffsetForm->show();
    posOffForm_int=1;
}
void MainWindow::closePositionOffsetForm(){
    posOffForm_int=0;
    posOffsetForm->close();
}
void MainWindow::reopenPositionOffsetForm(){
    posOffsetForm->close();
    posOffsetForm->show();
}
//--------------------fin------------------------------------


// -------------Bouton preset position-----------------------
void MainWindow::on_pushButton_12_clicked()
{
    if(!presPosForm_int) openPresetPositionForm();
    else reopenPresetPositionForm();
}
void MainWindow::openPresetPositionForm(){
    presPositionForm->show();
    presPosForm_int=1;
}
void MainWindow::closePresetPositionForm(){
    presPosForm_int=0;
    presPositionForm->close();
}
void MainWindow::reopenPresetPositionForm(){
    presPositionForm->close();
    presPositionForm->show();
}
//--------------------fin------------------------------------


void MainWindow::on_toolButton_2_clicked()
{
    CEsettingsForm* cecForm=new CEsettingsForm;
    cecForm->show();
}

