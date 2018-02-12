#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "registrationdialog.h"
#include "devicechangedialog.h"
#include "deviceregisterdialog.h"
#include "devicesettingsdialog.h"
#include "servercontroller.h"

QString currentToken = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QThread *sensorsUpdaterThread = new QThread();
    SensorsUpdater *sensorsUpdater = new SensorsUpdater("sensors_updater", "");
    sensorsUpdater->moveToThread(sensorsUpdaterThread);

    connect(sensorsUpdaterThread, SIGNAL (started()), sensorsUpdater, SLOT (update()));
    connect(sensorsUpdater, SIGNAL (dataReceived(SensorData)), this, SLOT(sensorsDataChanged(SensorData)));
    connect(this, SIGNAL (updateTokenInUpdater(QString)) , sensorsUpdater, SLOT (receiveToken(QString)), Qt::DirectConnection);

    sensorsUpdaterThread->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_accountChange_triggered()
{
    LoginDialog l;
    l.setModal(true);
    l.exec();
}

void MainWindow::on_signUp_triggered()
{
    RegistrationDialog r;
    r.setModal(true);
    r.exec();
}

void MainWindow::on_deviceChange_triggered()
{
    DeviceChangeDialog d(NULL);
    connect(&d, SIGNAL (deviceChanged(DeviceData)) , this, SLOT (deviceChanged(DeviceData)));
    d.setModal(true);
    d.exec();
}

void MainWindow::on_quit_triggered()
{
    ServerController::logout();
}

void MainWindow::on_deviceRegister_triggered()
{
    DeviceRegisterDialog d;
    d.setModal(true);
    d.exec();
}

void MainWindow::on_waterButton_clicked()
{
    ActionPostData data;
    data.code = 1;
    ServerController::createAction(currentToken, data);
}

void MainWindow::on_deviceSettings_triggered()
{
    DeviceSettingsDialog d;
    d.setModal(true);
    d.exec();
}

void MainWindow::deviceChanged(DeviceData data)
{
    currentToken = data.token;
    emit updateTokenInUpdater(data.token);
    qDebug() << "TOken is " << data.token;
}

void MainWindow::sensorsDataChanged(SensorData data)
{
    ui->airHumLabel->setText(QString::number(data.airHumidity) + "%");
    ui->airTempLabel->setText(QString::number(data.airTemperature) + "°C");
    ui->gndHumLabel->setText(QString::number(data.groundHumidity) + "%");
    ui->gndTempLabel->setText(QString::number(data.groundTemperature) + "°C");
    ui->pressureLabel->setText(QString::number(data.pressure));
    ui->waterBar->setValue(data.water);
}
