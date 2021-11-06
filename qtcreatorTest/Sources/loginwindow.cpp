//
// Created by nzazzo on 30/10/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_loginwindow.h" resolved

#include "Headers/loginwindow.h"
#include "../Headers/ui_loginwindow.h"


loginwindow::loginwindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::loginwindow) {
    ui->setupUi(this);
    api = new API();
}

loginwindow::~loginwindow() {
    delete ui;
    delete api;
}


void loginwindow::on_pushButton_login_clicked() {
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    std::string res = api->login(username.toStdString(), password.toStdString());
    if(username.toStdString().empty() || password.toStdString().empty())
        QMessageBox::information(this, "Error", "Username, password or calendar name cannot be left empty");
    else if(res.find("Username or password was incorrect") != std::string::npos)
        QMessageBox::information(this, "Error", "Username or password are incorrect");
    else if(res.find("Principal with name") != std::string::npos)
        QMessageBox::information(this, "Error", "Username or password are incorrect");
    else {
        //QMessageBox::information(this, "Error", res.c_str());
        api->setUsername(username.toStdString());
        api->setPassword(password.toStdString());
        api->setLoggedIn(true);
        api->clearCalendars();
        std::list<std::string> names = api->retrieveAllCalendars();
        for(std::string value : names)
            api->addCalendar(Vcalendar(value));
        emit changeUser();
        this->close();
    }
}