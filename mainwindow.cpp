#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->sensorsDisplayer = new SensorDataUpdaterThread("sensors_displayer");
    this->sensorsDisplayer->w = this;
    this->sensorsDisplayer->setDeviceID("1");
    this->sensorsDisplayer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setSensorValue(SensorType type, int value)
{
    switch (type)
    {
    case GroundHumidity:
        ui->gndHumLabel->setText(QString("%1%").arg(value));
        break;
    case GroundTemperature:
        ui->gndTempLabel->setText(QString("%1°C").arg(value));
        break;
    case AirHumidity:
        ui->airHumLabel->setText(QString("%1%").arg(value));
        break;
    case AirTemperature:
        ui->airTempLabel->setText(QString("%1°C").arg(value));
        break;
    }
}

void MainWindow::on_accountChange_triggered()
{
    Login *l = new Login();
    l->show();
}
