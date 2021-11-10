#include "../Headers/mainwindow.h"
#include "../Headers/ui_mainwindow.h"
#include "../Headers/loginwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), login(nullptr)
{
    ui->setupUi(this);
    api = new API();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete login;
    delete api;
}

void MainWindow::on_loginButton_clicked()
{
    login = new loginwindow();
    connect(login, SIGNAL(changeUser()), this, SLOT(afterLogin()));
    login->setModal(true);
    login->exec();
}

void MainWindow::setUpPage() {
    connect(login, SIGNAL(&loginwindow::sendSignal), this, SLOT(&MainWindow::on_loginButton_clicked));
}

void MainWindow::afterLogin() {
    std::list<Vcalendar> l = api->getCalendars();
    ui->listWidget_2->clear();
    for(Vcalendar value : l)
        ui->listWidget_2->addItem(QString(value.getXml().c_str()));
    ui->loginButton->setText(QString("Change user"));
    ui->createCalendarButton->setEnabled(true);
}

void MainWindow::on_createCalendarButton_clicked() {
    CreateCalendarForm create;
    connect(&create, SIGNAL(createCalendar()), SLOT(updateCalendars()));
    create.setModal(true);
    create.exec();
}

void MainWindow::updateCalendars() {
    std::list<Vcalendar> l = api->getCalendars();
    ui->listWidget_2->clear();
    for(Vcalendar value : l)
        ui->listWidget_2->addItem(QString(value.getXml().c_str()));
}

