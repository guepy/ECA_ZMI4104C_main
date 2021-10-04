#ifndef POSITIONOFFSETFORM_H
#define POSITIONOFFSETFORM_H

#include <QWidget>
#include <QRegExpValidator>
namespace Ui {
class positionOffsetForm;
}

class positionOffsetForm : public QWidget
{
    Q_OBJECT

public:
    explicit positionOffsetForm(QWidget *parent = nullptr);
    ~positionOffsetForm();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::positionOffsetForm *ui;
};

#endif // POSITIONOFFSETFORM_H
