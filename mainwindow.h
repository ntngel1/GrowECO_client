#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <Qstring>
#include "servercontroller.h"
#include <QDebug>

extern Server::ServerController server;

namespace Ui {
class MainWindow;
class SensorDataUpdaterThread;
}

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
private:
    Ui::MainWindow *ui;
};



class SensorDataUpdaterThread : public QThread
{
public:
    explicit SensorDataUpdaterThread(QString threadName) : name(threadName) {}

    void run()
    {
        while (true) {
            try
            {
                Server::ServerController::SensorsData d = server.getSensorsData("");
                w->setSensorValue(MainWindow::SensorType::AirHumidity, d.AirHumidity);
            }
            catch (Server::RequestException& ex)
            {
                qDebug() << "excep: " << ex.what() << '\n';
            }
            msleep(1000);
        }
    }
    MainWindow* w;
private:
    QString name;
};

#endif // MAINWINDOW_H
