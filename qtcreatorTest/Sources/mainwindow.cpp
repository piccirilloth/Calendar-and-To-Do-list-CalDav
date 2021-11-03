#include "../Headers/mainwindow.h"
#include "../Headers/ui_mainwindow.h"
#include "../Headers/loginwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    loginwindow login;
    login.setModal(true);
    login.exec();
}

