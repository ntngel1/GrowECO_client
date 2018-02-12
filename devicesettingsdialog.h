#ifndef DEVICESETTINGSDIALOG_H
#define DEVICESETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class DeviceSettingsDialog;
}

class DeviceSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceSettingsDialog(QWidget *parent = 0);
    ~DeviceSettingsDialog();

private slots:
    void on_autowatering_threshold_valueChanged(int value);

    void on_buttonBox_accepted();

private:
    Ui::DeviceSettingsDialog *ui;
};

#endif // DEVICESETTINGSDIALOG_H
