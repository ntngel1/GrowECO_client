#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
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

#endif // MAINWINDOW_H
