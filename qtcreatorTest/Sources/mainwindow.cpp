#include "../Headers/mainwindow.h"
#include "../Headers/ui_mainwindow.h"
#include "../Headers/loginwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), login(nullptr)
{
    ui->setupUi(this);
    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    api = new API();
    connect(ui->listWidget_2, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ProvideContextMenu(const QPoint &)));
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
    std::list<std::string> l = api->getCalendars();
    ui->listWidget_2->clear();
    for(std::string value : l)
        ui->listWidget_2->addItem(QString(value.c_str()));
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
    std::list<std::string> l = api->getCalendars();
    ui->listWidget_2->clear();
    for(std::string value : l)
        ui->listWidget_2->addItem(QString(value.c_str()));
}

void MainWindow::ProvideContextMenu(const QPoint &pos) {
    QPoint item = ui->listWidget_2->mapToGlobal(pos);
    QMenu subMenu;
    subMenu.addAction("Delete");
    QAction* rightClickItem = subMenu.exec(item);
    if (rightClickItem && rightClickItem->text().contains("Delete") )
    {
        std::string name = ui->listWidget_2->currentItem()->text().toStdString();
        std::list<std::string> list = api->deleteCalendar(name);
        api->clearCalendars();
        for(std::string v : list)
            api->addCalendar(v); //TODO: complete the Vcalendar constructor
        ui->listWidget_2->takeItem(ui->listWidget_2->indexAt(pos).row());
    }
}

