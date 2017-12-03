#include "mainwindow.h"
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
    try
    {
        server.signIn("", "");
    }
    catch (Server::RequestException& ex)
    {
        std::cout << "excep: " << ex.what() << std::endl;
    }
    SensorDataUpdaterThread thr("test_thr");
    thr.w = &w;
    thr.start();


    return a.exec();
}
