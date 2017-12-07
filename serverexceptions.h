#ifndef SERVEREXCEPTIONS_H
#define SERVEREXCEPTIONS_H

#include <QException>
#include <QMessageBox>

namespace Server {
    class OwnerException;
    class AuthorizingException;
    class BadRequestException;
    class ErrorMessageException;
    class InfoMessageException;
}

class Server::OwnerException  : public QException
{
public:
    OwnerException() {}
    void raise() const {throw *this;}
    OwnerException* clone() const {return new OwnerException(*this);}
};

class Server::AuthorizingException : public QException
{
public:
    AuthorizingException() {}
    void raise() const {throw *this;}
    AuthorizingException* clone() const {return new AuthorizingException(*this);}
};

class Server::BadRequestException : public QException
{
public:
    BadRequestException(int status_code) : status_code(status_code) {}
    void raise() const {throw *this;}
    BadRequestException* clone() const {return new BadRequestException(*this);}

    int status_code;
};

class Server::ErrorMessageException : public QException
{
public:
    ErrorMessageException(QString message) : message(message) {}
    void raise() const {throw *this;}
    ErrorMessageException* clone() const {return new ErrorMessageException(*this);}

    void show(QWidget* parent) {QMessageBox::critical(parent, "Ошибка!", message);}

    QString message;
};

class Server::InfoMessageException : public QException
{
public:
    InfoMessageException(QString message) : message(message) {}
    void raise() const {throw *this;}
    InfoMessageException* clone() const {return new InfoMessageException(*this);}

    void show(QWidget* parent) {QMessageBox::information(parent, "Ошибка!", message);}

    QString message;
};

#endif // SERVEREXCEPTIONS_H
