#ifndef PRESETPOSITIONFORM_H
#define PRESETPOSITIONFORM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class presetPositionForm;
}

class presetPositionForm : public QWidget
{
    Q_OBJECT

public:
    int currentUnits;
    explicit presetPositionForm(QWidget *parent = nullptr);
    ~presetPositionForm();
    void closeForm();

private slots:
    void on_pushButton_5_clicked();
    void on_okButton_clicked();
    void on_applyButton_clicked();
    void getPresPosValues(double* valPtr);
    void on_leftBlockUnits_currentIndexChanged(int index);

    void on_radioButton_2_clicked(bool checked);

signals:
    void PresetPosChanged(double* presPosPtr);
    void closeThis();
private:
    Ui::presetPositionForm *ui;
    double* presPosValue;
    bool alreadyApplied;
};

static const double unitsCoeffs1[5]{
    1,
    1e-3,
    1e-6,
    1e1,
    1e3
};

#endif // PRESETPOSITIONFORM_H
