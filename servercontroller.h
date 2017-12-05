#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include "restclient-cpp/restclient.h"
#include "restclient-cpp/connection.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <exception>

namespace Server {
class ServerController;
class RequestException;
}

class Server::RequestException : public std::exception
{
public:
    RequestException(const int status_code) throw()
        : status_code(status_code)
    {}

    ~RequestException() throw() {}

    const char* what(void) const throw()
    {
        return (std::string("Request Error: ") + std::to_string(status_code)).c_str();
    }

    const int statusCode()
    {
        return status_code;
    }

private:
    const int status_code;
};

class Server::ServerController
{
public:
    struct SensorsData {
        int GroundTemperature;
        int GroundHumidity;
        int AirTemperature;
        int AirHumidity;
    };

    struct AccountData {
        QString name;
        QString username;
        QString email;
    };

public:
    ServerController(void);
    ~ServerController(void);

    bool signIn(QString login, QString password) throw (Server::RequestException);
    bool isSignedIn();

    AccountData getAccountData(void) throw (Server::RequestException);
    SensorsData getSensorsData(QString deviceID) throw (Server::RequestException);

private:
    RestClient::Connection *connection;
    bool isAuthorized = false;
};


#endif // SERVERCONTROLLER_H
