#ifndef REGISTRATIONDIALOG_H
#define REGISTRATIONDIALOG_H

#include <QDialog>

namespace Ui {
class RegistrationDialog;
}

class RegistrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationDialog(QWidget *parent = 0);
    ~RegistrationDialog();

private slots:
    void on_cancelButton_clicked();

    void on_registerButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::RegistrationDialog *ui;
};

#endif // REGISTRATIONDIALOG_H
