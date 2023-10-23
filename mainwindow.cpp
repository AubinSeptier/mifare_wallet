#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include "MfErrNo.h"
#include "Sw_Device.h"
#include "Sw_ISO14443A-3.h"
#include "Sw_Mf_Classic.h"
#include "TypeDefs.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

}

