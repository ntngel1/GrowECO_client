#include "devicechangenamedialog.h"
#include "ui_devicechangenamedialog.h"
#include "servercontroller.h"

extern Server::ServerController server;

DeviceChangeNameDialog::DeviceChangeNameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceChangeNameDialog)
{
    ui->setupUi(this);
    deviceToken = server.getDevices().last().deviceID;
}

DeviceChangeNameDialog::~DeviceChangeNameDialog()
{
    delete ui;
}

void DeviceChangeNameDialog::on_buttonBox_accepted()
{
    Server::ServerController::DeviceData data;
    data.name = this->ui->nameEdit->text();
    server.updateDevice(deviceToken, data);
    this->close();
}
