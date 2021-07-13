#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
private slots:
    void on_toolButton_2_triggered(QAction *arg1);

    void on_pushButton_13_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
