#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "servercontroller.h"
#include "registrationdialog.h"
#include "QDebug"

extern Server::ServerController server;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
        QString login = ui->loginEdit->text();
        QString password = ui->passwordEdit->text();

        if (login == "" || password == "") {
            QMessageBox::warning(this, "Внимание!", "Логин или пароль не могут отсутствовать!");
            return;
        }

        try {
            server.signIn(ui->loginEdit->text(), ui->passwordEdit->text());
        } catch (Server::AuthorizingException& e) {
            QMessageBox::critical(this, "Ошибка!", "Неверный логин или пароль!");
            return;
        } catch (Server::NotFoundException& e) {
            QMessageBox::critical(this, "Ошибка!", "Проверьте ваше интернет-соединение!");
            return;
        } catch (Server::BadRequestException& e) {
            qDebug() << "Непредвиденная ошибка: " << e.status_code;
            QMessageBox::critical(this, "Ошибка!", "Проверьте ваше интернет-соединение!");
            return;
        }

        QMessageBox::information(this, "Успех!", "Вы успешно авторизовались!");
        this->close();

}

void LoginDialog::on_cancelButton_clicked()
{
    this->close();
}

void LoginDialog::on_registerButton_clicked()
{
    this->close();
    RegistrationDialog r;
    r.setModal(true);
    r.exec();
}
