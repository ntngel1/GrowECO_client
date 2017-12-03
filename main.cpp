#include "mainwindow.h"
#include <QApplication>
#include "servercontroller.h"
#include "exception"
#include "iostream"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Server::ServerController server;
    try
    {
        server.signIn("", "");
        Server::ServerController::SensorsData data = server.getSensorsData("");
        w.setSensorValue(MainWindow::SensorType::AirHumidity, data.AirHumidity);
        w.setSensorValue(MainWindow::SensorType::AirTemperature, data.AirTemperature);
        w.setSensorValue(MainWindow::SensorType::GroundHumidity, data.GroundHumidity);
        w.setSensorValue(MainWindow::SensorType::GroundTemperature, data.GroundTemperature);
    }
    catch (Server::RequestException& ex)
    {
        std::cout << "test: " << ex.what() << std::endl;
    }


    return a.exec();
}
