#include "login.h"
#include "ui_login.h"
#include "servercontroller.h"
#include <QMessageBox>

extern Server::ServerController server;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    QMessageBox m;

    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();
    bool isSignedIn = false;

    if (login == "" || password == "") {
        m.setText("Логин или пароль не может отсутствовать!");
        m.exec();
        return;
    }

    try {
        isSignedIn = server.signIn(ui->loginEdit->text(), ui->passwordEdit->text());
    } catch (...) {
        m.setText("Ошибка запроса! Проверьте свое интернет-соединение!");
        m.exec();
        return;
    }

    if (isSignedIn) {
        m.setText("Вы успешно авторизовались!");
        this->close();
    } else {
        m.setText("Неверный логин или пароль!");
    }
    m.exec();
}
