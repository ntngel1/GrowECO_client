#ifndef DEVICEREGISTERDIALOG_H
#define DEVICEREGISTERDIALOG_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QClipboard>
#include <QMessageBox>

#include "servercontroller.h"

namespace Ui {
class DeviceRegisterDialog;
}

class DeviceRegisterDialogThread;

class DeviceRegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceRegisterDialog(QWidget *parent = 0);
    ~DeviceRegisterDialog();

    void setToken(QString token);
private slots:
    void on_copyButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::DeviceRegisterDialog *ui;
    QString currentToken;
};

#endif // DEVICEREGISTERDIALOG_H
