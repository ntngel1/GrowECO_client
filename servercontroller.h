#ifndef SERVERCONTROLLER_H
#define SERVERCONTROLLER_H

#include "restclient-cpp/restclient.h"
#include "restclient-cpp/connection.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <exception>

#include "serverstructs.h"
#include "serverexceptions.h"

class ServerController
{
public:
    static void init(void);

    static bool signIn(QString login, QString password);
    static bool signUp(AccountPostData d);
    static void logout(void);
    static bool isSignedIn(void);

    static AccountData getAccountData(void);
    static QList<DeviceData> getDevices(void);
    static QString getDeviceRegToken(void);
    static SensorData getSensorData(QString token);
    static SettingsData getSettingsData(QString token);

    static void createAction(QString token, ActionPostData data);

    static void updateDevice(QString token, DevicePostData data);
    static void updateSettings(QString token, SettingsPostData data);

private:

    static void checkResponse(int code) throw (AuthorizingException);

    static RestClient::Connection *connection;
    static bool isAuthorized;

    ServerController(void);
    ~ServerController(void);
};


#endif // SERVERCONTROLLER_H
