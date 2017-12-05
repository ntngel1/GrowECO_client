#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "servercontroller.h"
#include <QDebug>

extern Server::ServerController server;

namespace Ui {
class MainWindow;
}

class SensorDataUpdaterThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum SensorType {
      GroundTemperature,
      GroundHumidity,
      AirTemperature,
      AirHumidity
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setSensorValue(SensorType type, int value);

    SensorDataUpdaterThread *sensorsDisplayer;
private slots:

    void on_accountChange_triggered();

private:
    Ui::MainWindow *ui;
};



class SensorDataUpdaterThread : public QThread
{
public:
    explicit SensorDataUpdaterThread(QString threadName) : name(threadName), device_id("") {}

    void run()
    {
        while (true) {
            if (device_id != "" && server.isSignedIn()) {
                try {
                    Server::ServerController::SensorsData d = server.getSensorsData(device_id);
                    w->setSensorValue(MainWindow::SensorType::AirHumidity, d.AirHumidity);
                    w->setSensorValue(MainWindow::SensorType::AirTemperature, d.AirTemperature);
                    w->setSensorValue(MainWindow::SensorType::GroundHumidity, d.GroundHumidity);
                    w->setSensorValue(MainWindow::SensorType::GroundTemperature, d.GroundTemperature);
                }
                catch (Server::RequestException& ex) {
                    qDebug() << "Error from SensorDataUpdaterThread: " << ex.what() << '\n';
                }
                msleep(1000);
            }
        }
    }

    void setDeviceID(QString device_id)
    {
        this->device_id = device_id;
    }

    MainWindow* w;
private:
    QString name;
    QString device_id;
};

#endif // MAINWINDOW_H
