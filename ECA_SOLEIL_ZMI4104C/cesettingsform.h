#ifndef CESETTINGSFORM_H
#define CESETTINGSFORM_H

#include <QWidget>
#include <array>
#include <complex>
#include <algorithm>
#include <QDebug>
namespace Ui {
class CEsettingsForm;
}

class CEsettingsForm : public QWidget
{
    Q_OBJECT

    std::array<std::complex<double>,7> prevCecParams{0};
    std::array<std::complex<double>,7> curCecParams{0};
    static constexpr const double defCEMinVel = 1.2;
    static constexpr const double defCEMaxVel = 380;
    static constexpr const double defCE0Lim = 1.2;
    static constexpr const double defCENLim = 0;
    bool uscChanged = false;
public:
    explicit CEsettingsForm(QWidget *parent = nullptr);
    ~CEsettingsForm();
    void on_CeParams_received( std::array<std::complex<double>, 14> params);
    uint8_t curCecAxis = 3;
signals:
    void initCeParams(uint8_t axis);
    void enableUsc(uint8_t a, bool b);
    void enableUscStartup(uint8_t a, bool b);
    void updateCeParams(uint8_t axis, int i,std::vector<std::complex<double>> param);
private slots:
    void on_pushButton_5_clicked();

    void on_uscCE0_valueChanged(double arg1);

    void on_uscCEN_valueChanged(double arg1);

    void on_uscCEMeas_valueChanged(double arg1);

    void on_ceMinVel_valueChanged(double arg1);

    void on_ceMaxVel_valueChanged(double arg1);

    void on_ce0Lim_valueChanged(double arg1);

    void on_ceNLim_valueChanged(double arg1);


    void on_defCEMinVel_clicked();

    void on_defCEMaxVel_clicked();

    void on_defCE0Lim_clicked();

    void on_defCENLim_clicked();

    void on_StartButton_clicked();

    void on_uscCE0_img_valueChanged(double arg1);

    void on_uscCEMeas_img_valueChanged(double arg1);

    void on_cecAxis_currentIndexChanged(int index);

    void on_radioButton_2_clicked(bool checked);

    void on_radioButton_clicked(bool checked);

    void on_pushButton_12_clicked();

private:
    Ui::CEsettingsForm *ui;
};

#endif // CESETTINGSFORM_H
