#ifndef FLYSCANFORM_H
#define FLYSCANFORM_H

#include <QThread>
#include <QWidget>
namespace Ui {
class FlyscanForm;
}
class FlyscanForm : public QWidget
{
    Q_OBJECT
    unsigned int paramNbr=0;
    unsigned char flyscanModeIndex=0;
public:
    explicit FlyscanForm(QWidget *parent = nullptr);
    ~FlyscanForm();
    double freqValue;
    double  timeValue;
    double sizeValue;
    unsigned int nbrAxis=0;
    char extFolderName[1024];
    char axisTab[4]={0,0,0,0};
    void openForm();
    void closeForm();
    void on_flyscanErrorCode_recieved(int err_code);
    void on_flyscanStatValues_received(unsigned char* axisTab, double* mean, double* stdDev);
    void on_flyscanProcTerm_received();
signals:
    void openThis();
    void closeThis();
    void ramDataFlyscanRequest(double freq, double it, double np, unsigned int na);
    void fifoFlyscanRequest(double freq, double it, double np, unsigned int na);
private slots:
    void on_pushButton_5_clicked();
    void selectFile();
    void on_comboBox_currentIndexChanged(int index);

    void on_itCheckBox_clicked();

    void on_freqCheckBox_clicked();

    void on_npCheckBox_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_StartButton_clicked();

    void on_fifoAxis1_clicked();
    void on_fifoAxis2_clicked();
    void on_fifoAxis3_clicked();
    void on_fifoAxis4_clicked();

private:
    Ui::FlyscanForm *ui;
    int scanParam=0;
};

#endif // FLYSCANFORM_H
