#ifndef SENSORSUPDATER_H
#define SENSORSUPDATER_H

#include <QObject>
#include <QThread>
#include "serverstructs.h"
#include "servercontroller.h"

class SensorsUpdater : public QObject
{
    Q_OBJECT
public:
    SensorsUpdater(QString name, QString token);

private:
    QString name;
    QString token;

signals:
    void dataReceived(SensorData data);

public slots:
    void update(void);
    void receiveToken(QString token);
};

#endif // SENSORSUPDATER_H
