#include "servercontroller.h"

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

    switch (res.code) {
        case 200:
            isAuthorized = true;
            return true;

        case 401:
            isAuthorized = false;
            return false;

        default:
            RequestException ex(res.code);
            throw ex;
    }
}

bool ServerController::isSignedIn()
{
    return isAuthorized;
}

ServerController::AccountData ServerController::getAccountData(void) throw (Server::RequestException)
{
    RestClient::Response res = connection->get("/account/get");

    if (res.code == 401) {
        isAuthorized = false;
        throw Server::RequestException(res.code);
    }

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

ServerController::SensorsData ServerController::getSensorsData(QString deviceID) throw (Server::RequestException)
{
    RestClient::Response res = connection->get("/sensors/get/" + deviceID.toStdString());

    if (res.code == 401) {
        isAuthorized = false;
        throw Server::RequestException(res.code);
    }

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
