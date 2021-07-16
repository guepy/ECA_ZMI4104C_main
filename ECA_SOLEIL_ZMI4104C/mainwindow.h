#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "myslots.h"
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
    void initialize_FsForm_Ptr();
signals:
    void openFsForm();
    void closeFsForm();
public slots:
    void on_pushButton_13_clicked();
    void openFlyscanForm();
    void closeFlyscanForm();
    void reopenFlyscanForm();
private slots:

private:
    Ui::MainWindow *ui;
};
static int fsForm=0;
#endif // MAINWINDOW_H
