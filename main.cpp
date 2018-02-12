#include "mainwindow.h"

#include <QApplication>
#include "exception"
#include "devicesettingsdialog.h"
#include "serverstructs.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<SensorData>();
    qRegisterMetaType<DeviceData>();
    ServerController::init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
