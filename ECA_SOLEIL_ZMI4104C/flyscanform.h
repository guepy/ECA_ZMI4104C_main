#ifndef FLYSCANFORM_H
#define FLYSCANFORM_H

#include <QWidget>
namespace Ui {
class FlyscanForm;
}
class FlyscanForm : public QWidget
{
    Q_OBJECT
    unsigned int paramNbr=0;
public:
    explicit FlyscanForm(QWidget *parent = nullptr);
    ~FlyscanForm();
    void openForm();
    void closeForm();
signals:
    void openThis();
    void closeThis();
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

private:
    Ui::FlyscanForm *ui;
    int freqValue=0;
    int timeValue=0;
    int sizeValue=0;
    int scanParam=0;
};

#endif // FLYSCANFORM_H
