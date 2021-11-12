#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT
    int precisionValueIndex_cur=0;
    int intTypeIndex_cur=0;
    int precisionValueIndex_prev=0;
    int intTypeIndex_prev=0;
    int resetFindVelocityIndex_cur=0;
    int resetFindVelocityIndex_prev=5;
    bool updateAv=false;
    int* updateTable;
public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();
    void closeForm();

signals:
    void closeThis();
    void modifyBaseAddressRequest(unsigned int);
    void updateSettingsRequest(int a, int b, int val);
private slots:
    void on_pushButton_5_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_interType_currentIndexChanged(int index);

    void on_precisionVal_currentIndexChanged(int index);

    void on_resetFindVel_currentIndexChanged(int index);

private:
    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
