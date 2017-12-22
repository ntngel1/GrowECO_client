#ifndef SERVEREXCEPTIONS_H
#define SERVEREXCEPTIONS_H

#include <QException>
#include <QMessageBox>

namespace Server {
    class AuthorizingException;
    class BadRequestException;
    class ErrorMessageException;
    class NotFoundException;
}

class Server::AuthorizingException : public QException
{
public:
    AuthorizingException(void) {}
    void raise(void) const {throw *this;}
    AuthorizingException* clone(void) const {return new AuthorizingException(*this);}
};

class Server::BadRequestException : public QException
{
public:
    BadRequestException(int status_code) : status_code(status_code) {}
    void raise(void) const {throw *this;}
    BadRequestException* clone(void) const {return new BadRequestException(*this);}

    void show(QWidget* parent) {QMessageBox::critical
                (parent, "Ошибка!", "Ошибка запроса к серверу! Response Code: " + QString(status_code));
    }

    int status_code;
};

class Server::ErrorMessageException : public QException
{
public:
    ErrorMessageException(QString jsonText) {} // TODO GETTING DATA FROM JSON TO EXCEPTION
    void raise(void) const {throw *this;}
    ErrorMessageException* clone(void) const {return new ErrorMessageException(*this);}

    void show(QWidget* parent) {QMessageBox::critical(parent, "Ошибка!", message);}

    QString message;
    QString jsonText;
    int errorCode;
};

class Server::NotFoundException : public QException
{
public:
    NotFoundException(void) {}
    void raise(void) const {throw *this;}
    NotFoundException* clone(void) const {return new NotFoundException(*this);}
    void show(QWidget* parent) {QMessageBox::critical(parent, "Ошибка!", "Проверьте интернет-соединение!");}
};

#endif // SERVEREXCEPTIONS_H
