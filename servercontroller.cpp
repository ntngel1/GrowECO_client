#include <QDebug>
#include "servercontroller.h"

#define SERVER_URL "https://groweco-dev.herokuapp.com"

#define IF_FILLED(x) if(x!="")

bool ServerController::isAuthorized = false;
RestClient::Connection* ServerController::connection = new RestClient::Connection(SERVER_URL);

ServerController::ServerController(void)
{
    RestClient::init();
    connection = new RestClient::Connection(SERVER_URL);
    connection->AppendHeader("Content-Type", "application/json");
}

ServerController::~ServerController(void)
{

}

void ServerController::init(void)
{
    RestClient::init();
    connection = new RestClient::Connection(SERVER_URL);
    connection->AppendHeader("Content-Type", "application/json");
}

void ServerController::checkResponse(int code) throw (AuthorizingException)
{
    switch (code) {
        case 200:
            return;
            break;
        case 401:
            isAuthorized = false;
            throw AuthorizingException();
            break;
        default:
            qDebug() << "Error! Code: " << code;
            break;
    }
}

bool ServerController::signIn(QString login, QString password)
{
    connection->SetBasicAuth(login.toStdString(), password.toStdString());
    connection->SetTimeout(5);

    RestClient::Response res = connection->get("/user/get");

    try {
        checkResponse(res.code);
    } catch (AuthorizingException) {
        return false;
    }

    isAuthorized = true;
    return true;
}

bool ServerController::signUp(AccountPostData data)
{
    QString json = data.toJson();
    RestClient::Response res = connection->post("/user/create", json.toStdString());

    checkResponse(res.code);

    return true;
}

void ServerController::logout(void)
{
    connection->SetBasicAuth("","");
    isAuthorized = false;
}

bool ServerController::isSignedIn(void)
{
    return isAuthorized;
}

AccountData ServerController::getAccountData(void)
{
}

SensorData ServerController::getSensorData(QString token)
{
    RestClient::Response res = connection->get("/sensors/get/" + token.toStdString());

    checkResponse(res.code);

    SensorData data;
    data.fromJson(res.body.c_str());

    return data;
}

SettingsData ServerController::getSettingsData(QString token)
{
    RestClient::Response res = connection->get("/settings/get/" + token.toStdString());

    SettingsData data;
    data.fromJson(res.body.c_str());

    return data;
}

QList<DeviceData> ServerController::getDevices(void)
{
    RestClient::Response res = connection->get("/device/get_devices");

    checkResponse(res.code);

    QList<DeviceData> data;
    data = DeviceData::fromJsonArray(res.body.c_str());

    return data;
}

QString ServerController::getDeviceRegToken()
{
    RestClient::Response res = connection->get("/device/create_slot");

    checkResponse(res.code);

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(res.body.c_str()));
    QJsonObject json = doc.object();

    return json["token"].toString();
}

void ServerController::createAction(QString token, ActionPostData data)
{
    QString json = data.toJson();
    RestClient::Response res = connection->post("/actions/create/"+ token.toStdString(), json.toStdString());

    checkResponse(res.code);
}

void ServerController::updateDevice(QString token, DevicePostData data)
{
    QString json = data.toJson();
    RestClient::Response res = connection->put("/device/update/"+token.toStdString(), json.toStdString());

    checkResponse(res.code);
}

void ServerController::updateSettings(QString token, SettingsPostData data)
{
    QString json = data.toJson();
    RestClient::Response res = connection->put("/settings/update/"+token.toStdString(), json.toStdString());

    checkResponse(res.code);
}
