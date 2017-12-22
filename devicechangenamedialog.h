#ifndef DEVICECHANGENAMEDIALOG_H
#define DEVICECHANGENAMEDIALOG_H

#include <QDialog>

namespace Ui {
class DeviceChangeNameDialog;
}

class DeviceChangeNameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceChangeNameDialog(QWidget *parent = 0);
    ~DeviceChangeNameDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DeviceChangeNameDialog *ui;
    QString deviceToken;
};

#endif // DEVICECHANGENAMEDIALOG_H
