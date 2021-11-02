
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPropertyAnimation"


SIS1100_Device_Struct* dataProcessing::dev = new SIS1100_Device_Struct;
std::mutex dataProcessing::dev_mutex;

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

    settingsForm=new SettingsForm;
    flyscanForm=new FlyscanForm;
    posOffsetForm=new positionOffsetForm;
    presPosForm = new presetPositionForm;
    customplotForm=new graphsForm;
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
    currentCECUnits = 0;
    cecHarwareOn = false;
    ceRatios = new CEratios;
    ceVelMin = 96;
    ceVelMax=31457;
    currentcecAxis = 0;
    //currentColor.append("background-color: ");
    for(int i=0; i<5;i++){
        ledsColor[i] = 0;
        ledsColorPrev[i] = 0;
}

    //*-------------CEC Hardware signals-slots---------------------------------------

    //connect(this, &MainWindow::configureCEChardwareRequest, dataProc, &dataProcessing::on_configureCECHardware_recieved);
    connect(this, &MainWindow::updateCECRatiosRequest, dataProc, &dataProcessing::updateCECRatios);
    //connect(this, &MainWindow::stopCEChardwareRequest, dataProc, &dataProcessing::on_stopCECHardware_recieved);

    //--------------Data processing signals-slots --------------------------------------
    //connect(this, &MainWindow::changeBiasModeRequest, dataProc, &dataProcessing::on_changeBiasModeRequest_recieved);
    connect(this, &MainWindow::resetAxisRequest, dataProc, &dataProcessing::on_resetAxisRequest_recieved);
    connect(dataProc, &dataProcessing::initAxisComplete,this, &MainWindow::on_initAxisComplete_recieved);


    connect(flyscanForm, &FlyscanForm::ramDataFlyscanRequest,this, &MainWindow::on_ramDataFlyscanRequest_recieved);


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
    if(customplotForm_int)
        closeCustomplotForm();

    this->destroy(true,true);
    delete ui;
}

void MainWindow::refresh_screen(){


    qDebug()<<"timer timeout";
    if((dataProcessing::dev_mutex).try_lock()){
        refreshLEDsStatus();
        updateLeftBlockValue();
        updateRightBlockValue();
        updateCECRatios();
        customplotForm->updatePosition(scaledPosition);
        dataProc->getLEDsColor(ledsColor);
        (dataProcessing::dev_mutex).unlock();
    }
    else{
        ui->textBrowser_2->append("Processing some data...");
    }

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
    //ui->ceVWidget->setEnabled(true);
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
    ui->horizontalWidget_3->setEnabled(false);
   // ui->ceVWidget->setEnabled(false);
    ui->textBrowser->setStyleSheet("background-color: red; "
                                    "font: 75 14pt \"MS Shell Dlg 2\";"
                                    "text-align: center;"
                                    "border: 2px solid white;"
                                    "padding: 0 8px;"
                                    "border-radius: 5px");
//*/

    ui->radioButton_2->setStyleSheet("background-color: red;"
                                    "border: 2px solid gray;"
                                    "border-radius: 10px;"
                                    "padding: 0 8px;font: 13pt \"Arial\";");
    QThread* initBoardsThread = new QThread;
    dataProcessing* initWorker = new dataProcessing;
    connect(initWorker, &dataProcessing::initAxisComplete,this, &MainWindow::on_initAxisComplete_recieved);
    //------------------------Init system state display----------
    ui->textBrowser->setText("DISCONNECTED");
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
    flyscanForm=new FlyscanForm;
    //--------------flyscanForm signals-slots --------------------------------------
    connect(flyscanForm, &FlyscanForm::closeThis, this, &MainWindow::closeFlyscanForm);
    connect(this, &MainWindow::closeFlyscanFormRequest, flyscanForm, &FlyscanForm::closeForm);
    connect(flyscanForm, &FlyscanForm::ramDataFlyscanRequest,this, &MainWindow::on_ramDataFlyscanRequest_recieved);
    flyscanForm->show();
    fsForm_int=1;
}

void MainWindow::closeFlyscanForm(){
    fsForm_int=0;
    qDebug()<<"flyscanform closed";
}

void MainWindow::reopenFlyscanForm(){
    closeFlyscanForm();
    emit closeFlyscanFormRequest();
    openFlyscanForm();
}
// --------------------fin--------------------------

// --------------menu bar setings---------------------------
void MainWindow::on_m_settingsMenu_clicked(QAction*)
{
    if(!sfForm_int) openSettingsForm();
    else reopenSettingsForm();
}
void MainWindow::openSettingsForm(){

    settingsForm=new SettingsForm;
    //--------------flyscanForm signals-slots --------------------------------------
    connect(settingsForm, &SettingsForm::closeThis, this, &MainWindow::closeSettingsForm);
    connect(this, &MainWindow::closeSettingsFormRequest, settingsForm, &SettingsForm::closeForm);
    settingsForm->show();
    sfForm_int=1;
}
void MainWindow::closeSettingsForm(){
    sfForm_int=0;
    qDebug()<<"Settingsform closed";
}
void MainWindow::reopenSettingsForm(){
    closeSettingsForm();
    emit closeSettingsFormRequest();
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

    posOffsetForm=new positionOffsetForm;
    //*-------------Offset position signals-slots---------------------------------------
    connect(posOffsetForm, &positionOffsetForm::closeThis, this, &MainWindow::closePositionOffsetForm);
    connect(this, &MainWindow::closePositionOffsetFormRequest, posOffsetForm, &positionOffsetForm::closeForm);
    connect(this, &MainWindow::OffsetPosChanged, dataProc, &dataProcessing::on_OffsetPosition_Changed);
    connect(posOffsetForm, &positionOffsetForm::OffsetPosChanged,this, &MainWindow::on_OffsetPos_Changed);

    posOffsetForm->show();
    posOffForm_int=1;
}
void MainWindow::closePositionOffsetForm(){
    posOffForm_int=0;
    qDebug()<<"PositionOffset form closed";
}
void MainWindow::reopenPositionOffsetForm(){
    closePositionOffsetForm();
    emit closePositionOffsetFormRequest();
    openPositionOffsetForm();
}
//--------------------fin------------------------------------



// --------------- Plot graphs button -----------------------
void MainWindow::on_pushButton_8_clicked()
{
    if(!customplotForm_int) openCustomplotForm();
    else reopenCustomplotForm();
}

void MainWindow::openCustomplotForm(){

    customplotForm=new graphsForm;
    //--------------graphsForm signals-slots --------------------------------------
    connect(customplotForm, &graphsForm::closeThis, this, &MainWindow::closeCustomplotForm);
    connect(this, &MainWindow::closeCustomplotFormRequest, customplotForm, &graphsForm::closeForm);
    connect(this, &MainWindow::initComplete, customplotForm, &graphsForm::on_initBoardsComplete_recieved);
    connect(this, &MainWindow::initBoardsRequest, customplotForm, &graphsForm::on_initBoardsRequest_recieved);
    connect(this, &MainWindow::scaleAxisRequest, customplotForm, &graphsForm::on_scaleAxisRequest_recieved);

    customplotForm->show();
    customplotForm_int=1;
}
void MainWindow::closeCustomplotForm(){
    customplotForm_int=0;
    qDebug()<<"Customplot form closed";
}
void MainWindow::reopenCustomplotForm(){
    closeCustomplotForm();
    emit closeCustomplotFormRequest();
    openCustomplotForm();
}
//--------------------fin------------------------------------

// -------------Bouton preset position-----------------------
void MainWindow::on_pushButton_12_clicked()
{
    if(!presPosForm_int) openPresetPositionForm();
    else reopenPresetPositionForm();
}
void MainWindow::openPresetPositionForm(){

    presPosForm=new presetPositionForm;

    //*-------------Preset position signals-slots---------------------------------------
    connect(presPosForm, &presetPositionForm::closeThis, this, &MainWindow::closePresetPositionForm);
    connect(this, &MainWindow::closePresetPositionFormRequest, presPosForm, &presetPositionForm::closeForm);
    connect(this, &MainWindow::PresetPosChanged, dataProc, &dataProcessing::on_PresetPosition_Changed);
    connect(presPosForm, &presetPositionForm::PresetPosChanged,this, &MainWindow::on_PresetPos_Changed);

    presPosForm->show();
    presPosForm_int=1;
}
void MainWindow::closePresetPositionForm(){
    presPosForm_int=0;
    qDebug()<<"Customplot form closed";
}
void MainWindow::reopenPresetPositionForm(){
    closePresetPositionForm();
    emit closePresetPositionFormRequest();
    openPresetPositionForm();
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
void MainWindow::on_OffsetPos_Changed(double* OffPosPtr){
    emit OffsetPosChanged(OffPosPtr);
}

void MainWindow::on_PresetPos_Changed(double* PresPosPtr){
    emit PresetPosChanged(PresPosPtr);
}

void MainWindow::on_radioButton_clicked()
{

    ui->textBrowser_3->setTextColor(QColor("green"));
    ui->textBrowser_3->append("Cyclic errors compensation activated");
    ui->textBrowser_3->setTextColor(QColor("dark"));
    ui->textBrowser_3->append("1-Start the motor for a displacement of at least 5s then press Enter. CEC hardware need to observe the motion at startup "
"in order to determine correct CE coefficients \n");
    ui->textBrowser_3->append("2- Next, check the axis to configure ce compensation on");
    ui->textBrowser_3->append("3-Then select in the list, the axis to display cec ratios on");
    ui->radioButton->setStyleSheet("background-color: green;"
                                    "border: 2px solid gray;"
                                    "border-radius: 10px;"
                                    "padding: 0 8px;font: 13pt \"Arial\";");
    ui->radioButton_2->setStyleSheet("background-color: rgb(236, 236, 236);"
                                    "border: 2px solid gray;"
                                    "border-radius: 10px;"
                                    "padding: 0 8px;font: 13pt \"Arial\";");

    cecHarwareOn=true;
    ui->horizontalWidget_3->setEnabled(true);
    ui->CE_form->setEnabled(true);
}
void MainWindow::updateCECRatios(){

    if(cecHarwareOn){
        if(currentcecAxis){
            emit updateCECRatiosRequest(currentcecAxis, ceRatios, currentCECUnits);
            ui->ce0Ratio->setText(QString::number(ceRatios->CE0ratio));
            ui->ceNRatio->setText(QString::number(ceRatios->CENratio));
            ui->measSig->setText(QString::number(ceRatios->measSignal));
        }
    }
}

void MainWindow::on_ceUnits_currentIndexChanged(int index)
{
    currentCECUnits=index;
    updateCECRatios();
}


void MainWindow::on_radioButton_2_clicked()
{
    for(int i=1; i<5; i++){
        emit stopCEChardwareRequest(i);
    }
    ui->textBrowser_3->setTextColor(QColor("red"));
    ui->textBrowser_3->append("Halting cyclic errors compensation...");
    ui->radioButton->setStyleSheet("background-color: rgb(236, 236, 236);border: 1px solid;"
                                    "border: 2px solid gray;"
                                    "border-radius: 10px;"
                                    "padding: 0 8px;font: 13pt \"Arial\";");
    ui->radioButton_2->setStyleSheet("background-color: red;"
                                    "border: 2px solid gray;"
                                    "border-radius: 10px;"
                                    "padding: 0 8px;font: 13pt \"Arial\";");
    cecHarwareOn=false;
    ui->horizontalWidget_3->setEnabled(false);
    ui->CE_form->setEnabled(false);
    ui->ceDisplayAxis->clear();
    ui->cecAxis1->setCheckState(Qt::Unchecked);
    ui->cecAxis2->setCheckState(Qt::Unchecked);
    ui->cecAxis3->setCheckState(Qt::Unchecked);
    ui->cecAxis4->setCheckState(Qt::Unchecked);
}


void MainWindow::processCecAxisClickedEvent(int axis, int* axisListIndex, QCheckBox* cecAxisCheckBox)
{
    char str[200];
    bool failed =false;
    dataProcessing *worker = new dataProcessing;
    if(cecAxisCheckBox->isChecked()){
        //emit configureCEChardwareRequest(axis,ceVelMin,ceVelMax);
        (dataProcessing::dev_mutex).lock();
        if(worker->on_configureCECHardware_recieved(axis,ceVelMin,ceVelMax)!= RET_SUCCESS){
            failed=true;
        }
        (dataProcessing::dev_mutex).unlock();
        if(failed){
            ui->textBrowser_3->setTextColor(QColor("red"));
            sprintf(str,"CEC configuration failed on axis %d", axis);
            ui->textBrowser_3->append(str);
            cecAxisCheckBox->setCheckState(Qt::Unchecked);
        }
        else{
            ui->textBrowser_3->setTextColor(QColor("green"));
            sprintf(str,"CE compensation succesfully configure on axis %d...", axis);
            ui->textBrowser_3->append(str);
            sprintf(str,"Axis%d", axis);
            ui->ceDisplayAxis->addItem(str);
        }


        *axisListIndex = ui->ceDisplayAxis->count() -1;
    }
    else{
        sprintf(str,"Halting CE compensation on axis %d...", axis);
        (dataProcessing::dev_mutex).lock();
        if(worker->on_stopCECHardware_recieved(axis)!= RET_SUCCESS){
            failed=true;
        }
        (dataProcessing::dev_mutex).unlock();
        if(failed){
            ui->textBrowser_3->setTextColor(QColor("red"));
            sprintf(str,"Halting CE compensation on axis %d failed", axis);
            ui->textBrowser_3->append(str);
            //emit stopCEChardwareRequest(axis);
        }
        else{
            ui->textBrowser_3->setTextColor(QColor("red"));
            sprintf(str,"CE compensation halted on axis %d", axis);
            ui->textBrowser_3->append(str);
            //emit stopCEChardwareRequest(axis);
            ui->ceDisplayAxis->removeItem(*axisListIndex);
        }

        }
    qDebug()<<"exiting thread";
}

void MainWindow::cecAxisClickedThreadEvent(int axis, int* axisListIndex, QCheckBox* cecAxisCheckBox)
{
    qDebug()<<"Starting cec config thread";
    std::thread cecThread(&MainWindow::processCecAxisClickedEvent,this,axis, axisListIndex, cecAxisCheckBox);
    cecThread.detach();
    qDebug()<<"exiting";
}

void MainWindow::on_cecAxis1_clicked()
{
    static int axis1ListIndex=-1;
    cecAxisClickedThreadEvent(1, &axis1ListIndex, ui->cecAxis1);
}
void MainWindow::on_cecAxis2_clicked()
{
    static int axis2ListIndex=-1;
    cecAxisClickedThreadEvent(2, &axis2ListIndex, ui->cecAxis2);

}

void MainWindow::on_cecAxis3_clicked()
{
    static int axis3ListIndex=-1;
    cecAxisClickedThreadEvent(3, &axis3ListIndex, ui->cecAxis3);
}


void MainWindow::on_cecAxis4_clicked()
{
    static int axis4ListIndex=-1;
    cecAxisClickedThreadEvent(4, &axis4ListIndex, ui->cecAxis4);
}


void MainWindow::on_ceDisplayAxis_currentIndexChanged(int index)
{
    if(!(ui->ceDisplayAxis->currentText().compare(QString::fromStdString("Axis1"))))
            currentcecAxis=1;
    if(!(ui->ceDisplayAxis->currentText().compare(QString::fromStdString("Axis2"))))
            currentcecAxis=2;
    if(!(ui->ceDisplayAxis->currentText().compare(QString::fromStdString("Axis3"))))
           currentcecAxis=3;
    if(!(ui->ceDisplayAxis->currentText().compare(QString::fromStdString("Axis4"))))
          currentcecAxis=4;
}

void MainWindow::on_ramDataFlyscanRequest_recieved(double freq, double time, double size, unsigned int nbr){
    qDebug()<<"MainWindow::on_ramDataFlyscanRequest_recieved";
    dataProcessing* flyscanWorker = new dataProcessing;
    QThread *flyscanAxisThread = new QThread;
    flyscanWorker->flyscanFreqValue=freq;
    flyscanWorker->flyscanTimeValue=time;
    flyscanWorker->flyscanSizeValue=size;
    flyscanWorker->ramDataFlyscanAxis=nbr;
    strcpy_s(flyscanWorker->flyscanPath, flyscanForm->extFolderName);
    qDebug()<<flyscanWorker->flyscanPath;
    flyscanWorker->moveToThread(flyscanAxisThread);
    //A slot can be connected to a given signal if the signal has at least as many arguments as the slot
    connect(flyscanAxisThread, &QThread::started, flyscanWorker, &dataProcessing::on_configureFlyscanRequest_recieved);
    //connect(flyscanWorker, &dataProcessing::flyscanProcTerm, this, &MainWindow::on_initAxisComplete_recieved);
    connect(flyscanWorker, &dataProcessing::flyscanProcTerm, flyscanAxisThread, &QThread::quit);
    connect(flyscanAxisThread, &QThread::finished, flyscanWorker,  &dataProcessing::deleteLater);
    flyscanAxisThread->start();

}

void MainWindow::configureFlyscanThreadEvent(){
    qDebug()<<"Starting ram data flyscan thread event";

    qDebug()<<"exiting";
}

void MainWindow::startRamDataFlyscan(double freq, double time, double size, unsigned int nbr){
/*
    dataProcessing *worker = new dataProcessing;
    //dataProcessing::dev_mutex.lock();
    worker->on_configureFlyscanRequest_recieved(freq,time, size,nbr);
    //dataProcessing::dev_mutex.unlock();
    */
}
