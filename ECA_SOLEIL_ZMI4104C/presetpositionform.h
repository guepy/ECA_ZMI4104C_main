#ifndef PRESETPOSITIONFORM_H
#define PRESETPOSITIONFORM_H

#include <QWidget>

namespace Ui {
class presetPositionForm;
}

class presetPositionForm : public QWidget
{
    Q_OBJECT

public:
    explicit presetPositionForm(QWidget *parent = nullptr);
    ~presetPositionForm();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::presetPositionForm *ui;
};

#endif // PRESETPOSITIONFORM_H
