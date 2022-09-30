#include "serialoutput.h"
#include "ui_serialoutput.h"

serialOutput::serialOutput(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialOutput)
{
    ui->setupUi(this);

    ui->serialBusSamplingFreq->setMaximum(7e5);
    ui->serialBusSamplingFreq->setMinimum(152);

}

serialOutput::~serialOutput()
{
    delete ui;
}

void serialOutput::on_serialClockIn_currentIndexChanged(int index)
{
    curSerialClkIn = static_cast<SCLK>(index);
}


void serialOutput::on_serialDriverOutput_currentIndexChanged(int index)
{
    curSerialDriverOutput = static_cast<SerialOutputDriver>(index);
}


void serialOutput::on_bitWindow_currentIndexChanged(int index)
{
    curSerialBitWindow = static_cast<BitWindow>(index);
}


void serialOutput::on_precision_currentIndexChanged(int index)
{
    curSerialPrecision = static_cast<SerialDataPositionSize>(index);
}


void serialOutput::on_configureSerialOutput_clicked()
{
    emit configureSerialOutput(curSerialClkIn, curSerialDriverOutput, curSerialPrecision, curSerialBitWindow, curSampFreq);
}


void serialOutput::on_stopSerialOutput_clicked()
{
    emit stopSerialOutput();
}
void serialOutput::on_sampleFreq_received(uint32_t freq){
    curSampFreq = freq;
    ui->serialBusSamplingFreq->setValue(freq);
}

void serialOutput::on_startSerialOutput_clicked()
{
    emit startSerialOutput();
    emit configureSerialOutput(curSerialClkIn, curSerialDriverOutput, curSerialPrecision, curSerialBitWindow, curSampFreq);
}

void serialOutput::closeForm(){
    emit closeThis();
    this->deleteLater();
}


void serialOutput::on_serialBusSamplingFreq_valueChanged(int arg1)
{
    curSampFreq = static_cast<uint32_t>(arg1);
}

