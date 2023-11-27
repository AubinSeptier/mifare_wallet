#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPixmap>

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
    QPixmap pixmap_logo(":/assets/assets/Odalid_Logo_120x60.jpg");
    int logo_width = ui->logo->width();
    int logo_height = ui->logo->height();
    ui->logo->setPixmap(pixmap_logo.scaled(logo_width, logo_height, Qt::KeepAspectRatio));
    QPixmap pixmap_mifare(":/assets/assets/Mifare_Logo.jpg");
    int mifare_width = ui->mifare->width();
    int mifare_height = ui->mifare->height();
    ui->mifare->setPixmap(pixmap_mifare.scaled(mifare_width, mifare_height, Qt::KeepAspectRatio));
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
    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[12];
    uint16_t uid_len = 12;
    int16_t status = MI_OK;
    status = LEDBuzzer(&MyReader, BUZZER_ON);
    DELAYS_MS(2);
    status = LEDBuzzer(&MyReader, BUZZER_OFF);
    status = ISO14443_3_A_PollCard(&MyReader, atq, sak, uid, &uid_len);
    qDebug() << status << "aaa";

    status = readCard();
    if(status != MI_OK){
        ui->errorLabel->setText(GetErrorMessage(status));
    }
    else {
        status = LEDBuzzer(&MyReader, LED_RED_ON);
        ui->errorLabel->setText("");
    }

}

void MainWindow::on_Pay_clicked(){
    int16_t status = MI_OK;
    status = LEDBuzzer(&MyReader, BUZZER_ON);
    DELAYS_MS(2);
    status = LEDBuzzer(&MyReader, BUZZER_OFF);
    DELAYS_MS(100);
    status = LEDBuzzer(&MyReader, BUZZER_ON);
    DELAYS_MS(2);
    status = LEDBuzzer(&MyReader, BUZZER_OFF);
}


int16_t MainWindow::readCard(){
    int16_t status = MI_OK;
    uint8_t data[240] = {0};

    //reading identity
    uint8_t sect = 2;
    memset(data, 0x00, 240);
    status = Mf_Classic_Read_Sector(&MyReader, TRUE, sect, data, AuthKeyA, 2);

    if(status != MI_OK){
        ui->errorLabel->setText(GetErrorMessage(status));
        return status;
    }
    else{
        uint8_t bloc_count = 3;
        for (uint8_t bloc = 0;bloc < bloc_count ;bloc++ ) {
            QString name = "";
            for(uint8_t offset = 0;offset < 16; offset++){
                if(data[16*bloc + offset] >= ' '){
                    char character = static_cast<char>(data[16*bloc + offset]);
                    name += character;
                }
        }
            if(bloc==2)
            ui->surnameEdit->setText(name);
            if(bloc==1)
            ui->nameEdit->setText(name);

        }
    }


    //reading units
    uint32_t value;
    sect = 3;

    uint8_t bloc = 13;
    status = Mf_Classic_Read_Value(&MyReader, TRUE, bloc, &value,AuthKeyA, 3);
    if(status != MI_OK){
        ui->errorLabel->setText(GetErrorMessage(status));
        return status;
    }
    else {
        qDebug() << value ;
        ui->unitNumberBox->setText(QString::number(value));
    }

    return status;
}

