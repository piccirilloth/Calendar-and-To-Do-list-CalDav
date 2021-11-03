//
// Created by nzazzo on 30/10/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_loginwindow.h" resolved

#include "Headers/loginwindow.h"
#include "../Headers/ui_loginwindow.h"


loginwindow::loginwindow(QWidget *parent) :
    QDialog(parent), ui(new Ui::loginwindow) {
    ui->setupUi(this);
    api = new API("192.168.1.6");
}

loginwindow::~loginwindow() {
    delete ui;
    delete api;
}


void loginwindow::on_pushButton_login_clicked() {
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    std::string res = api->login(username.toStdString(), password.toStdString());
    QMessageBox::information(this, "Login", res.c_str());
}