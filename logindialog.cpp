#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include "servercontroller.h"

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
        bool isSignedIn = false;

        if (login == "" || password == "") {
            QMessageBox::warning(this, "Внимание!", "Логин или пароль не может отсутствовать!");
            return;
        }

        try {
            isSignedIn = server.signIn(ui->loginEdit->text(), ui->passwordEdit->text());
        } catch (...) {
            return;
        }

        if (isSignedIn) {
            QMessageBox::information(this, "Успех!", "Вы успешно авторизовались!");
            this->close();
        } else {
            QMessageBox::critical(this, "Ошибка!", "Неверный логин или пароль!");
        }

}
