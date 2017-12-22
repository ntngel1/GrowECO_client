#include "mainwindow.h"

#include <QApplication>
#include "servercontroller.h"
#include "exception"
#include "registrationdialog.h"

Server::ServerController server;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
