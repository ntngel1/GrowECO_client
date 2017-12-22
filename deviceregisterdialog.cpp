#include "deviceregisterdialog.h"
#include "ui_deviceregisterdialog.h"

extern Server::ServerController server;

DeviceRegisterDialog::DeviceRegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceRegisterDialog)
{
    ui->setupUi(this);
    currentToken = server.getDeviceRegToken();
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
    if (server.isSignedIn()) {
        QString serverToken = server.getDeviceRegToken();
        if (serverToken != currentToken) {
            QMessageBox::information(this, "Успех!", "Вы успешно привязали устройство!");
            DeviceChangeNameDialog d;
            d.setModal(true);
            d.exec();
            this->close();
        }
    }
}
