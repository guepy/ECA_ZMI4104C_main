#ifndef CESETTINGSFORM_H
#define CESETTINGSFORM_H

#include <QWidget>

namespace Ui {
class CEsettingsForm;
}

class CEsettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit CEsettingsForm(QWidget *parent = nullptr);
    ~CEsettingsForm();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::CEsettingsForm *ui;
};

#endif // CESETTINGSFORM_H
