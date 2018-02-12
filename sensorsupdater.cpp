#include "sensorsupdater.h"

SensorsUpdater::SensorsUpdater(QString name, QString token) : name(name), token(token)
{
}

void SensorsUpdater::update()
{
    while (true) {
        if (ServerController::isSignedIn() && token != "") {
            SensorData data = ServerController::getSensorData(token);
            emit dataReceived(data);
            QThread::sleep(1);
        }
    }
}

void SensorsUpdater::receiveToken(QString token)
{
    this->token = token;
}
