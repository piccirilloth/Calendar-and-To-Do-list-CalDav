#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "QMessageBox"
#include "Headers/API.h"

QT_BEGIN_NAMESPACE
namespace Ui { class loginwindow; }
QT_END_NAMESPACE

class loginwindow : public QDialog {
Q_OBJECT

public:
    loginwindow(QWidget *parent = nullptr);

    ~loginwindow();

private:
    Ui::loginwindow *ui;
    API *api;

signals:
    void changeUser(std::string username);

private slots:
    void on_pushButton_login_clicked();
};

#endif // LOGINWINDOW_H