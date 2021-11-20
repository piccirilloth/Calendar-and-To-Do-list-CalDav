#include "../Headers/mainwindow.h"
#include "../Headers/ui_mainwindow.h"
#include <iostream>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), login(nullptr)
{
    ui->setupUi(this);
    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_Events->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->textBrowser_calName->setText("");
    api = new API();
    connect(ui->listWidget_2, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ProvideContextMenuCal(const QPoint &)));
    connect(ui->listWidget_2, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_dbclick()));
    connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SLOT(selectedDateChange()));
    connect(ui->listWidget_Events, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_dbClickEvent()));
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(on_dbClickTodo()));
    connect(ui->listWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ProvideContextMenuTodo(const QPoint &)));
    connect(ui->listWidget_Events, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ProvideContextMenuEvents(const QPoint &)));
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
    ui->listWidget_Events->clear();
    ui->listWidget->clear();
    eventMap.clear();
    todoMap.clear();
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

void MainWindow::ProvideContextMenuCal(const QPoint &pos) {
    QPoint item = ui->listWidget_2->mapToGlobal(pos);
    QMenu subMenu;
    subMenu.addAction("Delete");
    QAction* rightClickItem = subMenu.exec(item);
    if (rightClickItem && rightClickItem->text().contains("Delete") )
    {
        std::string name = ui->listWidget_2->currentItem()->text().toStdString();
        std::list<std::string> list = api->deleteCalendar(name);
        api->clearCalendars();
        if(name == currentCalendar.getName()) {
            ui->listWidget->clear();
            ui->listWidget_Events->clear();
            eventMap.clear();
            todoMap.clear(); //todo: create a function clear
        }
        for(std::string v : list)
            api->addCalendar(v);
        ui->listWidget_2->takeItem(ui->listWidget_2->indexAt(pos).row());
    }
}

void MainWindow::on_dbclick() {
    std::string oldName = currentCalendar.getName();
    QString calendarName = ui->listWidget_2->currentItem()->text();
    currentCalendar = api->downloadCalendarObjects(calendarName.toStdString());
    ui->textBrowser_calName->setText(currentCalendar.getName().c_str());
    if(oldName != currentCalendar.getName()) {
        ui->listWidget->clear();
        ui->listWidget_Events->clear();
    }
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
    ui->listWidget_Events->clear();
    eventMap.clear();
    int i=0;
    for(const Vevent &ev : events) {
        if(curDate >= ev.getDtstart() && curDate <= ev.getDtend()) {
            ui->listWidget_Events->addItem(QString(ev.getSummary().c_str()));
            eventMap.insert(std::pair<int, std::string>(i, ev.getUid()));
            i++;
        }
    }
    todoMap.clear();
    i=0;
    for(const Vtodo &td : todos) {
        if(static_cast<string>(td.getDtstart()) != "00000000") {
            if (curDate >= td.getDtstart() && curDate <= td.getDue()) {
                ui->listWidget->addItem((QString(td.getSummary().c_str())));
                todoMap.insert(std::pair<int, std::string>(i, td.getUid()));
                i++;
            }
        } else if (curDate <= td.getDue()) {
            ui->listWidget->addItem((QString(td.getSummary().c_str())));
            todoMap.insert(std::pair<int, std::string>(i, td.getUid()));
            i++;
        }
    }
}

void MainWindow::on_dbClickEvent() {
    int index = ui->listWidget_Events->currentIndex().row();
    std::string uid = eventMap.at(index);
    Vevent event;
    for(Vevent const &ev : currentCalendar.getEvents()) {
        if(ev.getUid() == uid)
            event = ev;
    }
    event_information evInfo(nullptr, event.getSummary(), event.getDtstamp().Format(), event.getDtstart().Format(), event.getDtend().Format());
    evInfo.setModal(true);
    evInfo.exec();
}

void MainWindow::on_dbClickTodo() {
    int index = ui->listWidget->currentIndex().row();
    std::string uid = todoMap.at(index);
    Vtodo todo;
    for(Vtodo const &td : currentCalendar.getTodos()) {
        if(td.getUid() == uid)
            todo = td;
    }
    todo_information todoInfo(nullptr, todo.getSummary(), todo.getDtstamp().Format(), todo.getDue().Format(), todo.getCompleted().Format(), todo.getPriority());
    todoInfo.setModal(true);
    todoInfo.exec();
}

void MainWindow::ProvideContextMenuTodo(const QPoint &pos) {
    QPoint item = ui->listWidget->mapToGlobal(pos);
    QMenu subMenu;
    subMenu.addAction("Delete");
    subMenu.addAction("Update");
    QAction* rightClickItem = subMenu.exec(item);
    if (rightClickItem && rightClickItem->text().contains("Delete")) {
        int index = ui->listWidget->currentIndex().row();
        std::string uid = todoMap.at(index);
        api->deleteIcs(uid, currentCalendar.getName());
        currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
        ui->listWidget->clear();
        todoMap.clear();
        int i=0;
        for(Vtodo const &td : currentCalendar.getTodos()) {
            ui->listWidget->addItem(QString(td.getSummary().c_str()));
            todoMap.insert(std::pair<int, std::string>(i, td.getUid()));
            i++;
        }
    } else if(rightClickItem && rightClickItem->text().contains("Update")) {

    }
}

void MainWindow::ProvideContextMenuEvents(const QPoint &pos) {
    QPoint item = ui->listWidget_Events->mapToGlobal(pos);
    QMenu subMenu;
    subMenu.addAction("Delete");
    subMenu.addAction("Update");
    QAction* rightClickItem = subMenu.exec(item);
    if (rightClickItem && rightClickItem->text().contains("Delete")) {
        int index = ui->listWidget_Events->currentIndex().row();
        std::string uid = eventMap.at(index);
        api->deleteIcs(uid, currentCalendar.getName());
        currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
        ui->listWidget_Events->clear();
        eventMap.clear();
        int i=0;
        for(Vevent const &ev : currentCalendar.getEvents()) {
            ui->listWidget_Events->addItem(QString(ev.getSummary().c_str()));
            eventMap.insert(std::pair<int, std::string>(i, ev.getUid()));
            i++;
        }
    } else if(rightClickItem && rightClickItem->text().contains("Update")) {

    }
}
