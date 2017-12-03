#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
