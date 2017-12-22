#include "devicechangedialog.h"
#include "ui_devicechangedialog.h"
#include "serverexceptions.h"

#include <QMessageBox>
#include <QDebug>

extern Server::ServerController server;

DeviceChangeDialog::DeviceChangeDialog(QWidget *parent, IDeviceHandler *deviceHandler) :
    QDialog(parent),
    ui(new Ui::DeviceChangeDialog),
    deviceHandler(deviceHandler)
{
    ui->setupUi(this);
    try {
        devices = server.getDevices();
        for (uint i = 0; i < devices.count(); i++) {
            ui->deviceList->insertItem(i, devices[i].name);
        }
    } catch (Server::AuthorizingException& e) {
        QMessageBox::critical(this, "Ошибка!", "Вы не можете выбрать устройство, так как вы не авторизованы!");
        return;
    } catch (Server::NotFoundException& e) {
        QMessageBox::critical(this, "Ошибка!", "Проверьте ваше интернет-соединение!");
        return;
    }

}

DeviceChangeDialog::~DeviceChangeDialog()
{
    delete ui;
}

void DeviceChangeDialog::on_deviceList_itemDoubleClicked(QListWidgetItem *item)
{
    int selectedRowIndex = ui->deviceList->selectionModel()->selectedIndexes()[0].row();
    deviceHandler->setDeviceID(devices[selectedRowIndex].deviceID);
    this->close();
}

void DeviceChangeDialog::on_buttonBox_accepted()
{
    if (!ui->deviceList->selectionModel()->hasSelection()) {
        return;
    }

    int selectedRowIndex = ui->deviceList->selectionModel()->selectedIndexes()[0].row();
    deviceHandler->setDeviceID(devices[selectedRowIndex].deviceID);
    this->close();
}
