#include "../Headers/mainwindow.h"
#include "../Headers/ui_mainwindow.h"
#include "../Headers/loginwindow.h"
#include <iostream>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), login(nullptr)
{
    ui->setupUi(this);
    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    api = new API();
    connect(ui->listWidget_2, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ProvideContextMenu(const QPoint &)));
    connect(ui->listWidget_2, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_dbclick()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(selectedDateChange()));
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
            api->addCalendar(v);
        ui->listWidget_2->takeItem(ui->listWidget_2->indexAt(pos).row());
    }
}

void MainWindow::on_dbclick() {
    QString calendarName = ui->listWidget_2->currentItem()->text();
    currentCalendar = api->downloadCalendarObjects(calendarName.toStdString());
    ui->listWidget->clear();
    /*for(Vevent ev : currentCalendar.getEvents()) //todo: change here for manage events and todos
        ui->listWidget->addItem(QString(ev.getSummary().c_str()));
    for(Vtodo td : currentCalendar.getTodos())
        ui->listWidget->addItem(QString(td.getSummary().c_str()));*/
}

void MainWindow::selectedDateChange() {
    std::string selectedDate = ui->calendarWidget->selectedDate().toString("yyyyMMdd").toStdString();
    Date curDate;
    curDate = selectedDate;
    std::list<Vevent> events = currentCalendar.getEvents();
    std::list<Vtodo> todos = currentCalendar.getTodos();
    if(events.empty() && todos.empty())
        return;
    ui->listWidget->clear();
    for(const Vevent &ev : events) {
        if(curDate >= ev.getDtstart() && curDate <= ev.getDtend())
            ui->listWidget->addItem(QString(ev.getSummary().c_str()));
    }

    for(const Vtodo &td : todos) {
        if(static_cast<string>(td.getDtstart()) != "00000000") {
            if (curDate >= td.getDtstart() && curDate <= td.getDue())
                ui->listWidget->addItem((QString(td.getSummary().c_str())));
        } else if (curDate <= td.getDue())
                ui->listWidget->addItem((QString(td.getSummary().c_str())));


    }

}
