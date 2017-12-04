#include "mainwindow.h"
#include "login.h"

#include <QApplication>
#include "servercontroller.h"
#include "exception"
#include "iostream"
#include <QThread>

Server::ServerController server;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    SensorDataUpdaterThread thr("test_thr");
    thr.w = &w;
    thr.setDeviceID("1");
    thr.start();


    return a.exec();
}
