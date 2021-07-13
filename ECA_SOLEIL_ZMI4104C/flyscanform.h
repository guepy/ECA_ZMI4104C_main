#ifndef FLYSCANFORM_H
#define FLYSCANFORM_H

#include <QWidget>

namespace Ui {
class FlyscanForm;
}

class FlyscanForm : public QWidget
{
    Q_OBJECT

public:
    explicit FlyscanForm(QWidget *parent = nullptr);
    ~FlyscanForm();

private:
    Ui::FlyscanForm *ui;
};

#endif // FLYSCANFORM_H
