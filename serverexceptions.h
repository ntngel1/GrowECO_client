#ifndef SERVEREXCEPTIONS_H
#define SERVEREXCEPTIONS_H

#include <QException>

class AuthorizingException : public QException
{
public:
    AuthorizingException(void) {}
    void raise(void) const {throw *this;}
    AuthorizingException* clone(void) const {return new AuthorizingException(*this);}
};

class InvalidTokenException : public QException
{
    InvalidTokenException(void) {}
    void raise(void) const {throw *this;}
    InvalidTokenException* clone(void) const {return new InvalidTokenException(*this);}
};

#endif // SERVEREXCEPTIONS_H
