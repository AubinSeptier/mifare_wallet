#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Connect_clicked();
    void on_Disconnect_clicked();
    void on_Quit_clicked();
    void on_ConnectCard_clicked();
    void on_Pay_clicked();

private:
    Ui::MainWindow *ui;
    int16_t readCard();
};
#endif // MAINWINDOW_H
