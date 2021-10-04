
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"


SIS1100_Device_Struct* dataProcessing::dev = new SIS1100_Device_Struct;

int dataProcessing::currentBiasMode=0;

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
    graphsform = new graphsForm;
    dataProc = new dataProcessing;
    ledsColor = new int[5];
    ledsColorPrev = new int[5];
    velocity= new double[4];position= new double[4];mTime= new double[4];
    scaledPosition = new double[4];
    APDGain= new double[4];
    OptPwr= new double[4];
    SSIav= new double[4];
    scaledAPDGain= new double[4];
    scaledOptPwr= new double[4];
    scaledSSIav= new double[4];
    leftBlockIndex = 0;
    rightBlockIndex = 0;
    scaledValueLeftBlock= new double[4];
    scaledValueRightBlock= new double[4];
    currentLeftBlockUnits =0;
    currentRightBlockUnits =0;
    //currentColor.append("background-color: ");
    for(int i=0; i<5;i++){
        ledsColor[i] = 0;
        ledsColorPrev[i] = 0;
}
    //--------------graphsForm signals-slots --------------------------------------
    connect(this, &MainWindow::initComplete, graphsform, &graphsForm::on_initBoardsComplete_recieved);
    connect(this, &MainWindow::initBoardsRequest, graphsform, &graphsForm::on_initBoardsRequest_recieved);
    connect(this, &MainWindow::scaleAxisRequest, graphsform, &graphsForm::on_scaleAxisRequest_recieved);

    //--------------Data processing signals-slots --------------------------------------
    //connect(this, &MainWindow::changeBiasModeRequest, dataProc, &dataProcessing::on_changeBiasModeRequest_recieved);
    connect(this, &MainWindow::resetAxisRequest, dataProc, &dataProcessing::on_resetAxisRequest_recieved);
    connect(dataProc, &dataProcessing::initAxisComplete,this, &MainWindow::on_initAxisComplete_recieved);
    //*
    gtimer = new QTimer(this);
    connect(gtimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::refresh_screen));
    //timer->setSingleShot(true);
    gtimer->setInterval(100);
    startApp =0;
//*/

    //-----------------------LED's color on Axis--------------------------
    //dataProc->refreshLEDsStatus(ledsColor);
    //---------------------init system boards-----------------------------

    //*/
    initBoards();

}

MainWindow::~MainWindow()
{
    gtimer->stop();

    // --------------close continuous acquisition form if open---------------------------
    if(fsForm_int)
        closeFlyscanForm();
    // --------------close menu setings form if open--------------------------------

    if(sfForm_int)
        closeSettingsForm();
    // --------------close preset position form if open---------------------------
    if(presPosForm_int)
        closePresetPositionForm();
    // --------------close position offset form if open---------------------------
    if(posOffForm_int)
        closePositionOffsetForm();
    // --------------close graphs button form if open---------------------------
    if(graphsForm_int)
        closeGraphsForm();

    this->destroy(true,true);
    delete ui;
}

void MainWindow::refresh_screen(){


    qDebug()<<"timer timeout";    
    dataProc->getLEDsColor(ledsColor);
    refreshLEDsStatus();
    updateLeftBlockValue();
    updateRightBlockValue();
    graphsform->updatePosition(scaledPosition);
}
void MainWindow::updateLeftBlockValue(){

    selectLeftBlockValue(leftBlockIndex);
    ui->displayPositionAxis1->setText(QString::number(scaledValueLeftBlock[0]));
    ui->displayPositionAxis1->setAlignment(Qt::AlignCenter);
    ui->displayPositionAxis2->setText(QString::number(scaledValueLeftBlock[1]));
    ui->displayPositionAxis2->setAlignment(Qt::AlignCenter);
    ui->displayPositionAxis3->setText(QString::number(scaledValueLeftBlock[2]));
    ui->displayPositionAxis3->setAlignment(Qt::AlignCenter);
    //ui->displayPositionAxis3->setStyleSheet("text-align: center;");
    ui->displayPositionAxis4->setText(QString::number(scaledValueLeftBlock[3]));
    ui->displayPositionAxis4->setAlignment(Qt::AlignCenter);
}

void MainWindow::updateRightBlockValue(){

    selectRightBlockValue(rightBlockIndex);
    ui->displayOptPwrAxis1->setText(QString::number(scaledValueRightBlock[0]));
    ui->displayOptPwrAxis1->setAlignment(Qt::AlignCenter);
    ui->displayOptPwrAxis2->setText(QString::number(scaledValueRightBlock[1]));
    ui->displayOptPwrAxis2->setAlignment(Qt::AlignCenter);
    ui->displayOptPwrAxis3->setText(QString::number(scaledValueRightBlock[2]));
    ui->displayOptPwrAxis3->setAlignment(Qt::AlignCenter);
    //ui->displayPositionAxis3->setStyleSheet("text-align: center;");
    ui->displayOptPwrAxis4->setText(QString::number(scaledValueRightBlock[3]));
    ui->displayOptPwrAxis4->setAlignment(Qt::AlignCenter);
}

void MainWindow::refreshLEDsStatus(){

    qDebug()<<"refreshLEDsStatus\n";
    for(int i=0; i<5;i++){
        if(ledsColor[i] != ledsColorPrev[i]){
            ledsColorPrev[i]= ledsColor[i];
            switch(i){
            case 0:
                ui->led1->setStyleSheet( QString::fromStdString(ledsColorString[ledsColor[i]]));
                break;
            case 1:
                ui->led2->setStyleSheet( QString::fromStdString(ledsColorString[ledsColor[i]]));
                break;
            case 2:
                ui->led3->setStyleSheet( QString::fromStdString(ledsColorString[ledsColor[i]]));
                break;
            case 3:
                ui->led4->setStyleSheet( QString::fromStdString(ledsColorString[ledsColor[i]]));
                break;
            case 4:
                ui->led5->setStyleSheet( QString::fromStdString(ledsColorString[ledsColor[i]]));
                break;
            default:
                break;
            }
        }
}
}
void MainWindow::onBoardsInitializationComplete(){
    ui->textBrowser_2->append("initialization complete");

    //ReadSamplePosition32(dev,3,position)";
    qDebug()<<"onBoardsInitializationComplete\n";
    ui->textBrowser->setText("CONNECTED");
    ui->textBrowser->setStyleSheet("background-color: rgb(37, 255, 81); "
                                    "font: 75 14pt \"MS Shell Dlg 2\";"
                                    "text-align: center;"
                                    "border: 2px solid white;"
                                    "padding: 0 8px;"
                                    "border-radius: 5px");
    ui->textBrowser->setAlignment(Qt::AlignCenter);
    for(int i=0; i<5;i++){
        ledsColor[i] = 0;
        //ledsColorPrev[i] = 0;
}
    refreshLEDsStatus();
    //*
    //ui->MeasForm->setEnabled(true);
    ui->CE_form->setEnabled(true);
    ui->SettingsForm->setEnabled(true);
    ui->horizontalWidget->setEnabled(true);
    //*/
}

// Initialize ZMI button
void MainWindow::on_pushButton_7_clicked()
{
    for(int i=0; i<5;i++)
        ledsColor[i] = 0;
    refreshLEDsStatus();
    initBoards();
    //*/

}
void MainWindow::initBoards()
{
    //*
    gtimer->stop();
    emit initBoardsRequest(); // notice the graph about boards initialization
    ui->MeasForm->setEnabled(false);
    ui->CE_form->setEnabled(false);
    ui->SettingsForm->setEnabled(false);
    ui->horizontalWidget->setEnabled(false);
//*/
    QThread* initBoardsThread = new QThread;
    dataProcessing* initWorker = new dataProcessing;
    connect(initWorker, &dataProcessing::initAxisComplete,this, &MainWindow::on_initAxisComplete_recieved);
    //------------------------Init system state display----------
    ui->textBrowser->setText("DISCONNECTED");
    ui->textBrowser->setStyleSheet("background-color: red; "
                                    "font: 75 14pt \"MS Shell Dlg 2\";"
                                    "text-align: center;"
                                    "border: 2px solid white;"
                                    "padding: 0 8px;"
                                    "border-radius: 5px");
    ui->textBrowser->setAlignment(Qt::AlignCenter);
    ui->textBrowser_2->append("Initializing VME system...");
    initWorker->moveToThread(initBoardsThread);
    connect(initBoardsThread, &QThread::started, initWorker, &dataProcessing::on_initBoardsRequest_recieved);
    connect(initWorker, &dataProcessing::initBoardsDone, initBoardsThread, &QThread::quit);
    connect(initWorker, &dataProcessing::initBoardsDone, this, &MainWindow::onBoardsInitializationComplete);
    connect(initBoardsThread, &QThread::finished, initWorker,  &dataProcessing::deleteLater);
    initBoardsThread->start();
}
void MainWindow::on_resetButtonAxis1_clicked()
{
    ui->textBrowser_2->append("Reseting axis 1...");
    scaledPosition[0]=0.0;
    emit resetAxisRequest(1);
}

void MainWindow::on_resetButtonAxis2_clicked()
{

    ui->textBrowser_2->append("Reseting axis 2...");
    scaledPosition[1]=0.0;
    emit resetAxisRequest(2);
}

void MainWindow::on_resetButtonAxis3_clicked()
{

    ui->textBrowser_2->append("Reseting axis 3...");
    scaledPosition[2]=0.0;
    emit resetAxisRequest(3);
}

void MainWindow::on_resetButtonAxis4_clicked()
{

    ui->textBrowser_2->append("Reseting axis 4...");
    scaledPosition[3]=0.0;
    emit resetAxisRequest(4);
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



// --------------- Plot graphs button -----------------------
void MainWindow::on_pushButton_8_clicked()
{
    if(!graphsForm_int) openGraphsForm();
    else reopenGraphsForm();
}
void MainWindow::openGraphsForm(){
    graphsform->show();
    graphsForm_int=true;
}
void MainWindow::closeGraphsForm(){
    graphsForm_int=0;
    graphsform->close();
}
void MainWindow::reopenGraphsForm(){
    graphsform->close();
    graphsform->show();
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

//------------------Reset all axis button----------------------------

void MainWindow::on_resetButtonAllAxis_clicked()
{

    ui->textBrowser_2->append("Reseting all axis...");
    emit resetAxisRequest(5);
}
//---------init axis xomplete signal recieved from data processing--------------
void MainWindow::on_initAxisComplete_recieved()
{
    gtimer->start();
    char str[200];
    sprintf(str,"Bias mode has been switched to %s", biasMode[dataProcessing::currentBiasMode]);
    ui->textBrowser_2->append(str);
    ui->MeasForm->setEnabled(true);
    emit initComplete();
}

//----------------BIAS MODE SELECTION---------------------------
void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    gtimer->stop();
    ui->textBrowser_2->append("Switching bias mode...");
    ui->textBrowser_2->append("Initializing axis...");
    ui->MeasForm->setEnabled(false);
    dataProcessing::currentBiasMode = index;
    dataProcessing* initWorker = new dataProcessing;
    QThread *initAxisThread = new QThread;
    //initWorker->currentBiasMode = index;
    //initWorker->dev=dataProc->dev;
    //dataProc->on_changeBiasModeRequest_recieved(index); very slow
    //emit changeBiasModeRequest(index);
    initWorker->moveToThread(initAxisThread);
    //A slot can be connected to a given signal if the signal has at least as many arguments as the slot
    connect(initAxisThread, &QThread::started, initWorker, &dataProcessing::on_changeBiasModeRequest_recieved);
    connect(initWorker, &dataProcessing::initAxisComplete, this, &MainWindow::on_initAxisComplete_recieved);
    connect(initWorker, &dataProcessing::initAxisComplete, initAxisThread, &QThread::quit);
    connect(initAxisThread, &QThread::finished, initWorker,  &dataProcessing::deleteLater);
    initAxisThread->start();
    //qDebug()<<"6";

}

//---------------Select units in the left block-----------------------------------
void MainWindow::on_leftBlockUnits_currentIndexChanged(int index)
{
    currentLeftBlockUnits=index;

    emit scaleAxisRequest(index);

}

void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    leftBlockIndex = index;
    qDebug()<<"comboBox_4_currentIndexChanged";
    switch (index) {
    case 0:
        ui->leftBlockUnits->setItemText(0,QString::fromStdString("mm"));
        ui->leftBlockUnits->setItemText(1,QString::fromStdString("µm"));
        ui->leftBlockUnits->setItemText(2,QString::fromStdString("nm"));
        ui->leftBlockUnits->setItemText(3,QString::fromStdString("cm"));
        break;
    case 1:
        ui->leftBlockUnits->setItemText(0,QString::fromStdString("mm/s"));
        ui->leftBlockUnits->setItemText(1,QString::fromStdString("µm/s"));
        ui->leftBlockUnits->setItemText(2,QString::fromStdString("nm/s"));
        ui->leftBlockUnits->setItemText(3,QString::fromStdString("cm/s"));
        break;
    case 2:
        ui->leftBlockUnits->setItemText(0,QString::fromStdString("ms"));
        ui->leftBlockUnits->setItemText(1,QString::fromStdString("µs"));
        ui->leftBlockUnits->setItemText(2,QString::fromStdString("ns"));
        ui->leftBlockUnits->setItemText(3,QString::fromStdString("cs"));
        break;
    default:
        break;
    }
    selectLeftBlockValue(index);
}


//---------------Select the value to print in the left block-----------------------------------
void MainWindow::selectLeftBlockValue(int index){

    qDebug()<<"updateLeftBlockValue";
    switch (index) {
        case 0:
            dataProc->updatePVT(0,position);
            for(int i=0; i<4; i++){
                scaledPosition[i] = position[i]*displayUnitsCoeffs[currentLeftBlockUnits];
                scaledValueLeftBlock[i] = scaledPosition[i];
            }
        break;
        case 1:
            dataProc->updatePVT(0,position);
            dataProc->updatePVT(1,velocity);
            for(int i=0; i<4; i++){
                scaledPosition[i] = position[i]*displayUnitsCoeffs[currentLeftBlockUnits];
                scaledValueLeftBlock[i] = velocity[i]*displayUnitsCoeffs[currentLeftBlockUnits];
            }
            break;
        case 2:
            dataProc->updatePVT(0,position);
            dataProc->updatePVT(2,mTime);
            for(int i=0; i<4; i++){
                scaledPosition[i] = position[i]*displayUnitsCoeffs[currentLeftBlockUnits];
                scaledValueLeftBlock[i] = mTime[i]*displayUnitsCoeffs[currentLeftBlockUnits];
            }
            break;
        default:
            break;
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    rightBlockIndex = index;
    qDebug()<<"comboBox_currentIndexChanged";
    switch (index) {
    case 0:
        ui->rightBlockUnits->setItemText(0,QString::fromStdString("µW"));
        ui->rightBlockUnits->setItemText(1,QString::fromStdString("nW"));
        ui->rightBlockUnits->setItemText(2,QString::fromStdString("pW"));
        ui->rightBlockUnits->setItemText(3,QString::fromStdString("mW"));
        break;
    case 1:
        ui->rightBlockUnits->setItemText(0,QString::fromStdString(""));
        ui->rightBlockUnits->setItemText(1,QString::fromStdString(""));
        ui->rightBlockUnits->setItemText(2,QString::fromStdString(""));
        ui->rightBlockUnits->setItemText(3,QString::fromStdString(""));
        break;
    default:
        ui->rightBlockUnits->setItemText(0,QString::fromStdString("mV"));
        ui->rightBlockUnits->setItemText(1,QString::fromStdString("µV"));
        ui->rightBlockUnits->setItemText(2,QString::fromStdString("nV"));
        ui->rightBlockUnits->setItemText(3,QString::fromStdString("V"));
        break;
    }
    selectLeftBlockValue(index);
}

//---------------Select the value to print in the right block-----------------------------------
void MainWindow::selectRightBlockValue(int index){

    qDebug()<<"updaterightBlockValue";

    switch (index) {
        case 0: //Print optical power
            dataProc->updateOAS(0,OptPwr);
            qDebug()<<"optical power is"<<*OptPwr;
            for(int i=0; i<4; i++){
                scaledOptPwr[i] = OptPwr[i]*displayUnitsCoeffs[currentRightBlockUnits];
                scaledValueRightBlock[i] = scaledOptPwr[i];
            }
        break;
        case 1: //Print APD gain
            dataProc->updateOAS(1,APDGain);
            for(int i=0; i<4; i++){
                scaledAPDGain[i] = APDGain[i]*displayUnitsCoeffs[currentRightBlockUnits];
                scaledValueRightBlock[i] = scaledAPDGain[i];
            }
            break;
        case 2: //Print SSI average
            dataProc->updateOAS(2,SSIav);
            for(int i=0; i<4; i++){
                scaledSSIav[i] = SSIav[i]*displayUnitsCoeffs[currentRightBlockUnits];
                scaledValueRightBlock[i] = scaledSSIav[i];
            }
            break;
        default:
            break;
    }
}

//---------------Select units in the right block-----------------------------------
void MainWindow::on_rightBlockUnits_currentIndexChanged(int index)
{
    currentRightBlockUnits=index;
    if(index>=3)
        currentRightBlockUnits=4;
    if(rightBlockIndex==1){
        currentRightBlockUnits=0;
        qDebug()<<"APD gain doesn't have any units";
    }
}

