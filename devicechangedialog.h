#ifndef DEVICECHANGEDIALOG_H
#define DEVICECHANGEDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QList>

#include "servercontroller.h"
#include "serverstructs.h"

namespace Ui {
class DeviceChangeDialog;
}

class DeviceChangeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceChangeDialog(QWidget *parent = 0);
    ~DeviceChangeDialog();

signals:
    void deviceChanged(DeviceData data);

private slots:
    void on_deviceList_itemDoubleClicked(QListWidgetItem *item);

    void on_buttonBox_accepted();

private:
    Ui::DeviceChangeDialog *ui;
    QList<DeviceData> devices;
};

#endif // DEVICECHANGEDIALOG_H
