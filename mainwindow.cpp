#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "MfErrNo.h"
#include "Sw_Device.h"
#include "Sw_ISO14443A-3.h"
#include "Sw_Mf_Classic.h"
#include "Tools.h"
#include "TypeDefs.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->readerName->setText("No reader connected");
    ui->readerName->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

ReaderName MyReader;

void MainWindow::on_Connect_clicked(){
    int16_t status = MI_OK;
    MyReader.Type = ReaderCDC;
    MyReader.device = 0;

    status = OpenCOM(&MyReader);

    qDebug() << "OpenCOM" << status ;
    status = Version(&MyReader);
    ui->readerName->setText(MyReader.version);
    ui->readerName->update();
    status = LEDBuzzer(&MyReader, LED_YELLOW_ON);

}

void MainWindow::on_Disconnect_clicked(){

    int16_t status = MI_OK;
    status = LEDBuzzer(&MyReader,LED_OFF);
    status = CloseCOM(&MyReader);
    ui->readerName->setText("No reader connected");
    ui->readerName->update();


}

void MainWindow::on_Quit_clicked(){
    int16_t status = MI_OK;
    status = LEDBuzzer(&MyReader,LED_OFF);
    status = CloseCOM(&MyReader);
    close();
}

void MainWindow::on_ConnectCard_clicked(){
    int16_t status = MI_OK;
    status = LEDBuzzer(&MyReader, BUZZER_ON);
    DELAYS_MS(2);
    status = LEDBuzzer(&MyReader, BUZZER_OFF);
    status = LEDBuzzer(&MyReader, LED_GREEN_ON);

}

