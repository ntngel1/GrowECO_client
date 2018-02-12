#include "devicesettingsdialog.h"
#include "ui_devicesettingsdialog.h"
#include "servercontroller.h"
#include <QMessageBox>

extern QString currentToken;

DeviceSettingsDialog::DeviceSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceSettingsDialog)
{
    ui->setupUi(this);
    if (currentToken == "") {
        QMessageBox::warning(this, "Внимание!", "Вы не выбрали устройство!");
        QMetaObject::invokeMethod(this, "close", Qt::QueuedConnection);
    }
    SettingsData data = ServerController::getSettingsData(currentToken);
    ui->autowatering_enabled->setChecked(data.autowateringEnabled);
    ui->autowatering_threshold->setValue(data.autowateringThreshold);
    ui->threshold_perc->setText(QString::number(data.autowateringThreshold) + "%");

    qDebug() << "Threshold = " << data.autowateringThreshold;
}

DeviceSettingsDialog::~DeviceSettingsDialog()
{
    delete ui;
}

void DeviceSettingsDialog::on_autowatering_threshold_valueChanged(int value)
{
    ui->threshold_perc->setText(QString::number(value) + "%");
}

void DeviceSettingsDialog::on_buttonBox_accepted()
{
    SettingsPostData data;
    data.autowateringEnabled = ui->autowatering_enabled->isChecked();
    data.autowateringThreshold = ui->autowatering_threshold->value();
    ServerController::updateSettings(currentToken, data);
    this->close();
}
