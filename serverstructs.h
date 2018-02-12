#ifndef SERVERSTRUCTS_H
#define SERVERSTRUCTS_H

#include <Qt>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

// STRUCTURES FOR GET REQUESTS

struct SensorData {
    quint8 groundHumidity;
    quint8 groundTemperature;

    quint8 airHumidity;
    quint8 airTemperature;

    quint8 water;
    quint16 pressure;

    SensorData(void) {}

    SensorData (QString str) {
        fromJson(str);
    }

    void fromJson(QString str) {
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();

        groundHumidity = json["ground_humidity"].toInt();
        groundTemperature = json["ground_temperature"].toInt();

        airHumidity = json["air_humidity"].toInt();
        airTemperature = json["air_temperature"].toInt();

        water = json["water"].toInt();
        pressure = json["pressure"].toInt();
    }
};

struct AccountData {
    QString name;
    QString username;
    QString email;

    AccountData(void) {}

    AccountData(QString str) {
        fromJson(str);
    }

    void fromJson(QString str) {
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();

        name = json["name"].toString();
        username = json["username"].toString();
        email = json["email"].toString();
    }
};

struct DeviceData {
    QString token;
    QString name;

    DeviceData(void) {}

    DeviceData(QString str) {
        fromJson(str);
    }

    void fromJson(QString str) {
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();

        token = json["token"].toString();
        name = json["name"].toString();
    }

    static QList<DeviceData> fromJsonArray(QString str) {

        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonValue o = doc.object().value("devices");
        QJsonArray jv = o.toArray();

        QList<DeviceData> devices;
        devices.reserve(jv.count());

        for (int i = 0; i < jv.count(); i++) {
            QJsonObject obj = jv.at(i).toObject();

            DeviceData device;
            device.name = obj["name"].toString();
            device.token = obj["token"].toString();

            devices.push_back(device);
        }

        return devices;

        //return QList<DeviceData>();
    }
};

struct ActionData {
    qint16 code;

    ActionData(void) {}

    ActionData(QString str) {
        fromJson(str);
    }

    void fromJson(QString str) {
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();

        code = json["action_code"].toInt();
    }
};

struct SettingsData {
    bool autowateringEnabled;
    quint8 autowateringThreshold;

    SettingsData(void) {}

    SettingsData(QString str) {
        fromJson(str);
    }

    void fromJson(QString str) {
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject json = doc.object();

        autowateringEnabled = json["autowatering_enabled"].toBool();
        autowateringThreshold = json["autowatering_threshold"].toInt();
    }
};


// STRUCTURES FOR POST REQUESTS

struct AccountPostData {
    QString name;
    QString username;
    QString email;
    QString password;

    AccountPostData() {}

    QString toJson(void) {
        QJsonObject json;

        json["name"] = name;
        json["username"] = name;
        json["email"] = email;
        json["password"] = password;

        QJsonDocument doc(json);
        return doc.toJson(QJsonDocument::Compact);
    }
};

struct DevicePostData {
    QString name;

    DevicePostData(void) {}

    QString toJson(void) {
        QJsonObject json;

        json["name"] = name;

        QJsonDocument doc(json);
        return doc.toJson(QJsonDocument::Compact);
    }
};

struct SettingsPostData {
    bool autowateringEnabled;
    quint8 autowateringThreshold;

    SettingsPostData(void) {}

    QString toJson(void) {
        QJsonObject json;

        json["autowatering_enabled"] = autowateringEnabled;
        json["autowatering_threshold"] = autowateringThreshold;

        QJsonDocument doc(json);
        return doc.toJson(QJsonDocument::Compact);
    }
};

struct ActionPostData {
    qint16 code;

    ActionPostData(void) {}

    QString toJson(void) {
        QJsonObject json;

        json["action_code"] = code;

        QJsonDocument doc(json);
        qDebug() << "Action data :" << doc.toJson(QJsonDocument::Compact);
        return doc.toJson(QJsonDocument::Compact);
    }
};

Q_DECLARE_METATYPE(SensorData);
Q_DECLARE_METATYPE(DeviceData);

#endif // SERVERSTRUCTS_H
