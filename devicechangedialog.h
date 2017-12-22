#ifndef DEVICECHANGEDIALOG_H
#define DEVICECHANGEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QVector>

#include "idevicehandler.h"
#include "servercontroller.h"

namespace Ui {
class DeviceChangeDialog;
}

class DeviceChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceChangeDialog(QWidget *parent = 0, IDeviceHandler* deviceHandler = 0);
    ~DeviceChangeDialog();

private slots:
    void on_deviceList_itemDoubleClicked(QListWidgetItem *item);

    void on_buttonBox_accepted();

private:
    Ui::DeviceChangeDialog *ui;
    QVector<Server::ServerController::DeviceData> devices;
    IDeviceHandler* deviceHandler;
};

#endif // DEVICECHANGEDIALOG_H
