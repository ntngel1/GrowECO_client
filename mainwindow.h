#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "servercontroller.h"
#include <QDebug>
#include "sensorsupdater.h"

namespace Ui {
class MainWindow;
}

class SensorDataUpdaterThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_accountChange_triggered();

    void on_signUp_triggered();

    void on_deviceChange_triggered();

    void on_quit_triggered();

    void on_deviceRegister_triggered();

    void on_waterButton_clicked();

    void on_deviceSettings_triggered();

    void deviceChanged(DeviceData data);
    void sensorsDataChanged(SensorData data);

signals:
    void updateTokenInUpdater(QString token);

private:
    Ui::MainWindow *ui;

    QThread *sensorsUpdaterThread;
    SensorsUpdater *sensorsUpdater;
};

#endif // MAINWINDOW_H
