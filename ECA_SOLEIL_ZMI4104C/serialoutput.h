#ifndef SERIALOUTPUT_H
#define SERIALOUTPUT_H

#include <QWidget>
#include <iostream>
#include "../eca_soleil_zmi4104_lib/eca_soleil_zmi4104c.h"
namespace Ui {
class serialOutput;
}

class serialOutput : public QWidget
{
    Q_OBJECT

public:
    explicit serialOutput(QWidget *parent = nullptr);
    ~serialOutput();
    void closeForm();
    void on_sampleFreq_received(uint32_t freq);

signals:
    void updateParams(int i, std::complex<double> params);
    void configureSerialOutput(SCLK clk, SerialOutputDriver sdo, SerialDataPositionSize sdps, BitWindow bw , uint32_t sampFreq);
    void startSerialOutput();
    void stopSerialOutput();
    void closeThis();
private slots:
    void on_serialClockIn_currentIndexChanged(int index);
    void on_serialDriverOutput_currentIndexChanged(int index);

    void on_bitWindow_currentIndexChanged(int index);

    void on_precision_currentIndexChanged(int index);

    void on_configureSerialOutput_clicked();

    void on_stopSerialOutput_clicked();

    void on_startSerialOutput_clicked();
    void on_serialBusSamplingFreq_valueChanged(int arg1);

private:
    Ui::serialOutput *ui;
    SCLK curSerialClkIn = SCLK::SCLK0;
    BitWindow curSerialBitWindow = BitWindow::BW1;
    SerialDataPositionSize curSerialPrecision = SerialDataPositionSize::P32;
    SerialOutputDriver curSerialDriverOutput = SerialOutputDriver::P2Z;
    uint32_t curSampFreq = 10000;
};

#endif // SERIALOUTPUT_H
