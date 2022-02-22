#ifndef POSITIONOFFSETFORM_H
#define POSITIONOFFSETFORM_H

#include <QWidget>
#include <QRegExpValidator>
#include <QDebug>
namespace Ui {
class positionOffsetForm;
}

class positionOffsetForm : public QWidget
{
    Q_OBJECT

public:
    explicit positionOffsetForm(QWidget *parent = nullptr);
    ~positionOffsetForm();
    void closeForm();
signals:
    void OffsetPosChanged(double* offsetPos);
    void closeThis();
private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_okButton_clicked();

    void getPosOffsetValues(double* valPtr);
    void on_leftBlockUnits_currentIndexChanged(int index);

private:
    Ui::positionOffsetForm *ui;
    int currentUnits;
    double* posOffsetValue;
    bool alreadyApplied;
};

static const double unitsCoeffs[4]{
    1,
    1e-3,
    1e-6,
    10,
};

#endif // POSITIONOFFSETFORM_H
