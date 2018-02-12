#include "deviceregisterdialog.h"
#include "ui_deviceregisterdialog.h"

DeviceRegisterDialog::DeviceRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceRegisterDialog)
{
    ui->setupUi(this);
    currentToken = ServerController::getDeviceRegToken();
    setToken(currentToken);
}

DeviceRegisterDialog::~DeviceRegisterDialog()
{
    delete ui;
}

void DeviceRegisterDialog::setToken(QString token)
{
    this->ui->tokenLabel->setText(token);
}

void DeviceRegisterDialog::on_copyButton_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();

    clipboard->setText(this->ui->tokenLabel->text());
}

void DeviceRegisterDialog::on_refreshButton_clicked()
{
    if (ServerController::isSignedIn()) {
        QString serverToken = ServerController::getDeviceRegToken();
        if (serverToken != currentToken) {
            QMessageBox::information(this, "Успех!", "Вы успешно привязали устройство!");
            this->close();
        }
    }
}
