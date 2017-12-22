#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include "restclient-cpp/restclient.h"
#include "restclient-cpp/connection.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <exception>

#include "serverexceptions.h"

namespace Server {
class ServerController;
}

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

    struct RegisterData {
        QString name;
        QString username;
        QString email;
        QString password;
    };

    struct DeviceData {
        QString deviceID;
        QString name;
    };

public:
    ServerController(void);
    ~ServerController(void);

    bool signIn(QString login, QString password) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException);
    bool signUp(RegisterData d) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException, Server::ErrorMessageException);
    void logout(void);
    bool isSignedIn(void);

    AccountData getAccountData(void) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException);
    SensorsData getSensorsData(QString deviceID) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException);
    QVector<DeviceData> getDevices(void) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException);
    QString getDeviceRegToken(void) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException);

    void updateDevice(QString token, DeviceData data) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException);

private:
    void checkResponseCode(int code) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException);

    QString deviceDataToJSON(DeviceData data) const;
    QString registerDataToJSON(RegisterData data) const;
    QString AccountDataToJSON(AccountData data) const;

    RestClient::Connection *connection;
    bool isAuthorized = false;
};


#endif // SERVERCONTROLLER_H
