#include "registrationdialog.h"
#include "ui_registrationdialog.h"
#include "servercontroller.h"
#include "serverexceptions.h"
#include <QDebug>
#include "logindialog.h"


extern Server::ServerController server;

RegistrationDialog::RegistrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationDialog)
{
    ui->setupUi(this);
}

RegistrationDialog::~RegistrationDialog()
{
    delete ui;
}

void RegistrationDialog::on_cancelButton_clicked()
{
    this->close();
}

void RegistrationDialog::on_registerButton_clicked()
{
    Server::ServerController::RegisterData d;
    d.name = ui->nameEdit->text();
    d.username = ui->usernameEdit->text();
    d.email = ui->emailEdit->text();
    d.password = ui->passwordEdit->text();

    if (d.password != ui->passwordTryEdit->text()) {
        QMessageBox::critical(this, "Ошибка!", "Вы неверно повторили пароль! Попробуйте снова!");
        ui->passwordEdit->clear();
        ui->passwordTryEdit->clear();
        return;
    }

    try {
        server.signUp(d);
    } catch (Server::BadRequestException& e) {
        qDebug() << e.status_code << '\n';
    }
    this->close();
}

void RegistrationDialog::on_loginButton_clicked()
{
    this->close();
    LoginDialog l;
    l.setModal(true);
    l.exec();
}
