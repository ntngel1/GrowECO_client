#include "servercontroller.h"

#define SERVER_URL "http://localhost:5000"
using namespace Server;


#include <QDebug>

ServerController::ServerController(void)
{
    RestClient::init();
    connection = new RestClient::Connection(SERVER_URL);
    connection->AppendHeader("Content-Type", "application/json");
}

ServerController::~ServerController(void)
{}

void ServerController::checkResponseCode(int code) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException)
{
    switch (code) {
        case 200:
            return;
            break;
        case 401:
            isAuthorized = false;
            throw Server::AuthorizingException();
            break;
        case 404:
            throw Server::NotFoundException();
            break;
        default:
            throw Server::BadRequestException(code);
    }
}

QString ServerController::deviceDataToJSON(ServerController::DeviceData data) const
{
    QJsonObject json;

    if (data.name != "")
        json["name"] = data.name;

    QJsonDocument doc(json);
    return doc.toJson(QJsonDocument::Compact);
}

//TODO Exceptions
bool ServerController::signIn(QString login, QString password) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException)
{
    connection->SetBasicAuth(login.toStdString(), password.toStdString());
    connection->SetTimeout(5);

    RestClient::Response res = connection->get("/account/get");
    checkResponseCode(res.code);

    isAuthorized = true;
    return true;
}

bool ServerController::signUp(ServerController::RegisterData d) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException,
                                                                       Server::ErrorMessageException)
{
    QJsonObject json;
    json["name"] = d.name;
    json["username"] = d.username;
    json["email"] = d.email;
    json["password"] = d.password;
    QJsonDocument doc(json);
    RestClient::Response res = connection->post("/account/register", doc.toJson(QJsonDocument::Compact).toStdString());

    checkResponseCode(res.code);
    if (res.code == 400) {

    }
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

ServerController::AccountData ServerController::getAccountData(void) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException)
{
    RestClient::Response res = connection->get("/account/get");

    checkResponseCode(res.code);

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(res.body.c_str()));
    QJsonObject json = doc.object();

    ServerController::AccountData data;
    data.name = json.value("name").toString();
    data.email = json.value("email").toString();
    data.username = json.value("username").toString();

    return data;
}

ServerController::SensorsData ServerController::getSensorsData(QString deviceID) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException)
{
    RestClient::Response res = connection->get("/sensors/get/" + deviceID.toStdString());

    checkResponseCode(res.code);

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(res.body.c_str()));
    QJsonObject json = doc.object();

    ServerController::SensorsData data;
    data.AirTemperature = json.value("air_temperature").toInt();
    data.AirHumidity = json.value("air_humidity").toInt();
    data.GroundTemperature = json.value("ground_temperature").toInt();
    data.GroundHumidity = json.value("ground_humidity").toInt();

    return data;
}

QVector<ServerController::DeviceData> ServerController::getDevices(void) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException)
{
    RestClient::Response res = connection->get("/device/get_devices");

    checkResponseCode(res.code);

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(res.body.c_str()));
    QJsonArray json = doc.array();
    QVector<ServerController::DeviceData> devices;
    devices.reserve(json.count());
    for (uint i = 0; i < devices.capacity(); i++) {
        QJsonObject device = json.at(i).toObject();
        ServerController::DeviceData d;
        d.deviceID = device["device_id"].toString();
        d.name = device["name"].toString();
        devices.push_back(d);
    }

    return devices;
}

QString ServerController::getDeviceRegToken() throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException)
{
    RestClient::Response res = connection->get("/device/create_slot");

    checkResponseCode(res.code);

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(res.body.c_str()));
    QJsonObject json = doc.object();

    return json["token"].toString();
}

void ServerController::updateDevice(QString token, ServerController::DeviceData data) throw (Server::AuthorizingException, Server::NotFoundException, Server::BadRequestException)
{
    QString json = deviceDataToJSON(data);
    RestClient::Response res = connection->put("/device/update/"+token.toStdString(), json.toStdString());

    checkResponseCode(res.code);
}
