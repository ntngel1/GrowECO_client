#include "servercontroller.h"
#include "iostream"

#define SERVER_URL "http://localhost:5000"
using namespace Server;

ServerController::ServerController(void)
{
    RestClient::init();
    connection = new RestClient::Connection(SERVER_URL);
}

ServerController::~ServerController(void)
{}

//TODO Exceptions
bool ServerController::signIn(QString login, QString password) throw (Server::RequestException)
{
    connection->SetBasicAuth(login.toStdString(), password.toStdString());
    connection->SetTimeout(5);

    RestClient::Response res = connection->get("/account/get");
    if (res.code != 200 && res.code != 401) {
        RequestException ex(res.code);
        throw ex;
    }

    if (res.code == 200)
        return true;

    return false;
}

ServerController::AccountData ServerController::getAccountData(void) const throw (Server::RequestException)
{
    RestClient::Response res = connection->get("/account/get");
    if (res.code != 200)
        throw Server::RequestException(res.code);

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(res.body.c_str()));
    QJsonObject json = doc.object();

    ServerController::AccountData data;
    data.name = json.value("name").toString();
    data.email = json.value("email").toString();
    data.username = json.value("username").toString();

    return data;
}

ServerController::SensorsData ServerController::getSensorsData(QString deviceID) const throw (Server::RequestException)
{
    RestClient::Response res = connection->get("/sensors/get/" + deviceID.toStdString());
    if (res.code != 200)
        throw Server::RequestException(res.code);

    QJsonDocument doc = QJsonDocument::fromJson(QByteArray(res.body.c_str()));
    QJsonObject json = doc.object();

    ServerController::SensorsData data;
    data.AirTemperature = json.value("air_temperature").toInt();
    data.AirHumidity = json.value("air_humidity").toInt();
    data.GroundTemperature = json.value("ground_temperature").toInt();
    data.GroundHumidity = json.value("ground_humidity").toInt();

    return data;
}
