#include "devicechangedialog.h"
#include "ui_devicechangedialog.h"
#include "serverexceptions.h"

#include <QMessageBox>
#include <QDebug>

DeviceChangeDialog::DeviceChangeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceChangeDialog)
{
    ui->setupUi(this);
    devices = ServerController::getDevices();
    for (uint i = 0; i < devices.count(); i++) {
        ui->deviceList->insertItem(i, devices[i].name);
    }
}

DeviceChangeDialog::~DeviceChangeDialog()
{
    delete ui;
}

void DeviceChangeDialog::on_deviceList_itemDoubleClicked(QListWidgetItem *item)
{
    int selectedRowIndex = ui->deviceList->selectionModel()->selectedIndexes()[0].row();
    emit deviceChanged(devices[selectedRowIndex]);
    this->close();
}

void DeviceChangeDialog::on_buttonBox_accepted()
{
    if (!ui->deviceList->selectionModel()->hasSelection()) {
        return;
    }

    int selectedRowIndex = ui->deviceList->selectionModel()->selectedIndexes()[0].row();
    emit deviceChanged(devices[selectedRowIndex]);
    this->close();
}
