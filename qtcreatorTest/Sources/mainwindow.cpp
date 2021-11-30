#include "../Headers/mainwindow.h"
#include "../Headers/ui_mainwindow.h"
#include <iostream>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), login(nullptr)
{
    std::lock_guard<std::mutex> lg(m); //probably useless
    end = false;
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
    {
        std::lock_guard<std::mutex> lg(endMutex);
        end = true;
    }
    timerThread.join();
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
    connect(login, SIGNAL(&loginwindow::sendSignal), this, SLOT(&MainWindow::on_loginButton_clicked)); //todo: maybe can be deleted
}

void MainWindow::addCalendarNamesToGui() {
    std::list<std::string> l = api->getCalendars(); //get calendar gets a safe access to calendars
    for(std::string const &value : l) {
        if(sharedNameMap.contains(value))
            ui->listWidget_2->addItem(QString(sharedNameMap.at(value).c_str()));
        else
            ui->listWidget_2->addItem(QString(value.c_str()));
    }
}

void MainWindow::afterLogin() {
    std::list<std::string> l = api->getCalendars(); //get calendar gets a safe access to calendars
    std::lock_guard<std::mutex> lg(m);
    for(std::string const &name : l) {
        std::string displayname;
        if(api->isShared(name, std::ref(displayname)))
            sharedNameMap.insert(std::pair<std::string,std::string>(name, displayname));
    }
    ui->listWidget_2->clear();
    ui->listWidget_Events->clear();
    ui->listWidget->clear();
    eventMap.clear();
    todoMap.clear();
    currentCalendar.clear();
    addCalendarNamesToGui();
    ui->loginButton->setText(QString("Change user"));
    ui->createCalendarButton->setEnabled(true);
    ui->textBrowser_calName->setText("");
    ui->pushButton_createTodo->setEnabled(false);
    ui->pushButton_createEvent->setEnabled(false);
    ui->shareCalendarButton->setEnabled(false);
}

void MainWindow::on_createCalendarButton_clicked() {
    CreateCalendarForm create;
    connect(&create, SIGNAL(createCalendar()), SLOT(updateCalendars()));
    create.setModal(true);
    create.exec();
}

void MainWindow::updateCalendars() {
    std::lock_guard<std::mutex> lg(m);
    ui->listWidget_2->clear();
    addCalendarNamesToGui();
}

std::string MainWindow::getRealCalendarName(const std::string &displayname) {
    for(auto const & value : sharedNameMap) {
        if(value.second == displayname)
            return value.first;
    }
    return "";
}

void MainWindow::ProvideContextMenuCal(const QPoint &pos) {
    QPoint item = ui->listWidget_2->mapToGlobal(pos);
    QMenu subMenu;
    subMenu.addAction("Delete");
    QAction* rightClickItem = subMenu.exec(item);
    if (rightClickItem && rightClickItem->text().contains("Delete") )
    {
        std::string displayname = ui->listWidget_2->currentItem()->text().toStdString();
        std::string name;
        if((name = getRealCalendarName(displayname)).empty())
            name = displayname;
        std::list<std::string> list = api->deleteCalendar(name);
        api->clearCalendars();
        std::lock_guard<std::mutex> lg(m);
        std::string str;
        if(!(str = getRealCalendarName(displayname)).empty())
            sharedNameMap.erase(str);

        if (name == currentCalendar.getName()) {
            ui->listWidget->clear();
            ui->listWidget_Events->clear();
            eventMap.clear();
            todoMap.clear(); //todo: create a function clear
            ui->textBrowser_calName->setText("");
            ui->pushButton_createEvent->setEnabled(false);
            ui->pushButton_createTodo->setEnabled(false);
            currentCalendar.clear();
            ui->shareCalendarButton->setEnabled(false);
        }
        for(std::string const &v : list)
            api->addCalendar(v);
        ui->listWidget_2->takeItem(ui->listWidget_2->indexAt(pos).row());
        ui->textBrowser_calName->setText("");
    }
}

void MainWindow::on_dbclick() {
    std::lock_guard<std::mutex> lg(m);
    std::string oldName = currentCalendar.getName();
    QString displayname = ui->listWidget_2->currentItem()->text(); //displayname
    std::string calendarName;
    if((calendarName = getRealCalendarName(displayname.toStdString())).empty())
        calendarName = displayname.toStdString();
    currentCalendar = api->downloadCalendarObjects(calendarName);
    ui->textBrowser_calName->setText(calendarName.c_str());
    if(oldName != currentCalendar.getName()) {
        ui->listWidget->clear();
        ui->listWidget_Events->clear();
    }
    ui->pushButton_createEvent->setEnabled(true);
    ui->pushButton_createTodo->setEnabled(true);
    ui->shareCalendarButton->setEnabled(true);
    selectedDateChange();
}

//todo: add a wrapper of selectedDateChange

void MainWindow::selectedDateChange() {
    std::string selectedDate = ui->calendarWidget->selectedDate().toString("yyyyMMdd").toStdString();
    Date curDate;
    curDate = selectedDate;
    std::list<Vevent> events = currentCalendar.getEvents();
    std::list<Vtodo> todos = currentCalendar.getTodos();
    ui->listWidget->clear();
    ui->listWidget_Events->clear();
    if(events.empty() && todos.empty())
        return;
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
        if(static_cast<string>(td.getDtstamp()) != "00000000") {
            if (curDate <= td.getDue()) {
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
    std::lock_guard<std::mutex> lg(m);
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
    std::lock_guard<std::mutex> lg(m);
    int index = ui->listWidget->currentIndex().row();
    std::string uid = todoMap.at(index);
    Vtodo todo;
    for(Vtodo const &td : currentCalendar.getTodos()) {
        if(td.getUid() == uid) //todo: use getTodoByUid
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
        std::lock_guard<std::mutex> lg(m);
        int index = ui->listWidget->currentIndex().row();
        std::string uid = todoMap.at(index);
        long status = api->deleteIcs(uid, currentCalendar.getName());
        if(status == 0)
            QMessageBox::information(this, "error", "failed to connect to the server");
        else if(status == 404)
            QMessageBox::information(this, "error", "the resource does not exist");
        else {
            currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
            ui->listWidget->clear();
            todoMap.clear();
            /*int i=0;
            for(Vtodo const &td : currentCalendar.getTodos()) {
                todoMap.insert(std::pair<int, std::string>(i, td.getUid()));
                i++;
            }*/
            selectedDateChange();
        }
    } else if(rightClickItem && rightClickItem->text().contains("Update")) {
        std::lock_guard<std::mutex> lg(m);
        int index = ui->listWidget->currentIndex().row();
        std::string uid = todoMap.at(index);
        std::optional<Vtodo> todo = getTodoByUid(uid);
        if(todo.has_value()) {
            updateTodo td(todo.value().getSummary(), todo.value().getDue(), todo.value().getCompleted());
            connect(&td, SIGNAL(updateTd(const std::string &, const Date &, bool)),
                    SLOT(updateTodo_slot(const std::string &, const Date &, bool)));
            td.setModal(true);
            td.exec();
        } else
            QMessageBox::information(this, "Error", "The todo does not exist");
    }
}

std::optional<Vtodo> MainWindow::getTodoByUid(std::string const &uid) {
    for(Vtodo const & td: currentCalendar.getTodos())
        if(td.getUid() == uid)
            return td;
    return std::nullopt;
}

void MainWindow::ProvideContextMenuEvents(const QPoint &pos) {
    QPoint item = ui->listWidget_Events->mapToGlobal(pos);
    QMenu subMenu;
    subMenu.addAction("Delete");
    subMenu.addAction("Update");
    QAction* rightClickItem = subMenu.exec(item);
    if (rightClickItem && rightClickItem->text().contains("Delete")) {
        std::lock_guard<std::mutex> lg(m);
        int index = ui->listWidget_Events->currentIndex().row();
        std::string uid = eventMap.at(index);
        long status = api->deleteIcs(uid, currentCalendar.getName());
        if(status == 0)
            QMessageBox::information(this, "error", "failed to connect to the server");
        else if(status == 404)
            QMessageBox::information(this, "error", "the resource does not exist");
        else {
            currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
            eventMap.clear();
            /*int i=0;
            for(Vevent const &ev : currentCalendar.getEvents()) {
                eventMap.insert(std::pair<int, std::string>(i, ev.getUid()));
                i++;
            }*/
            selectedDateChange();
        }
    } else if(rightClickItem && rightClickItem->text().contains("Update")) {
        std::lock_guard<std::mutex> lg(m);
        int index = ui->listWidget_Events->currentIndex().row();
        std::string uid = eventMap.at(index);
        std::optional<Vevent> event = getEvetByUid(uid);
        if(event.has_value()) {
            createEvent update(event.value(), currentCalendar);
            connect(&update, SIGNAL(createEv(std::string const &, Date const &, Date const &, bool, std::string const &)), SLOT(updateEvents(std::string const &, Date const &, Date const &, bool, std::string const &)));
            update.setModal(true);
            update.exec();
        }
        else
            QMessageBox::information(this, "Error", "The event does not exist");
    }
}

std::optional<Vevent> MainWindow::getEvetByUid(std::string const &uid) {
    for(Vevent const & ev: currentCalendar.getEvents())
        if(ev.getUid() == uid)
            return ev;
    return std::nullopt;
}

void MainWindow::on_pushButton_createEvent_clicked() {
    createEvent mod(nullptr);
    connect(&mod, SIGNAL(createEv(std::string const &, Date const &, Date const &, bool, std::string const &)), SLOT(updateEvents(std::string const &, Date const &, Date const &, bool, std::string const &)));
    mod.setModal(true);
    mod.exec();
}

void MainWindow::updateEvents(std::string const &summary, Date const &startDate, Date const &endDate, bool isUpdate, std::string const & uid) {
    if(isUpdate) {
        long status = api->updateEvent(summary, startDate, endDate, uid, currentCalendar);
        if(status == 0)
            QMessageBox::information(this, "Error", "connection with server failed");
        else if(status == 404)
            QMessageBox::information(this, "Error", "resource not found");
        else if(status == 415)
            QMessageBox::information(this, "Error", "request format not valid");
    }
    else {
        currentCalendar = api->downloadCalendarObjects(currentCalendar.getName()); //to have the last uid updated
        if(currentCalendar.getNextUid() == 0) { //first ics
            currentCalendar.setProdid("-//Sabre//Sabre VObject 4.2.2//EN");
            currentCalendar.setVersion("2.0");
        }
        long status = api->createEvent(summary, startDate, endDate, currentCalendar);
        if(status == 0)
            QMessageBox::information(this, "Error", "connection with server failed");
    }
    /*int i=0;
    eventMap.clear();
    for(Vevent const &ev : currentCalendar.getEvents()) {
        eventMap.insert(std::pair<int, std::string>(i, ev.getUid()));
        i++;
    }*/
    currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
    selectedDateChange();
}

void MainWindow::on_pushButton_createTodo_clicked() {
    createTodo mod(nullptr);
    connect(&mod, SIGNAL(createTd(std::string const &, Date const &)), SLOT(createTodo_slot(std::string const &, Date const &)));
    mod.setModal(true);
    mod.exec();
}

void MainWindow::createTodo_slot(const std::string &summary, const Date &dueDate) {
    currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
    if(currentCalendar.getNextUid() == 0) { //first ics
        currentCalendar.setProdid("-//Sabre//Sabre VObject 4.2.2//EN");
        currentCalendar.setVersion("2.0");
    }
    long status = api->createTodo(summary, dueDate, currentCalendar);
    if(status == 0)
        QMessageBox::information(this, "Error", "connection with server failed");
    else {/*int i=0;
    todoMap.clear();
    for(Vtodo const &td : currentCalendar.getTodos()) {
        todoMap.insert(std::pair<int, std::string>(i, td.getUid()));
        i++;
    }*/
        currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
        selectedDateChange();
    }
}

void MainWindow::updateTodo_slot(const std::string &summary, const Date &dueDate, bool completed) {
    int index = ui->listWidget->currentIndex().row();
    std::string uid = todoMap.at(index);
    std::optional<Vtodo> todo = getTodoByUid(uid);
    long status = api->updateTodo(summary, dueDate, completed, currentCalendar, todo.value().getCompleted(), uid);
    if(status == 0)
        QMessageBox::information(this, "Error", "connection with server failed");
    else if(status == 404)
        QMessageBox::information(this, "Error", "resource not found");
    else if(status == 415)
        QMessageBox::information(this, "Error", "request format not valid");
    else {
        todoMap.clear();
        /*int i=0;
        for(Vtodo const &td : currentCalendar.getTodos()) {
            todoMap.insert(std::pair<int, std::string>(i, td.getUid()));
            i++;
        }*/
        currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
        selectedDateChange();
    }
}

void MainWindow::on_shareCalendarButton_clicked() {
    shareCalendarForm mod;
    connect(&mod, SIGNAL(shareCal(const std::string &, const std::string &, const std::string &)), this,
            SLOT(shareCalendar_slot(const std::string &, const std::string &, const std::string &)));
    mod.setModal(true);
    mod.exec();
}

void MainWindow::shareCalendar_slot(const std::string &displayName, const std::string &email, const std::string &comment) {
    std::lock_guard<std::mutex> lg(m);
    long status = api->shareCalendar(displayName, email, comment, currentCalendar.getName());
    if(status == 0)
        QMessageBox::information(this, "Error", "connection with the server failed");
    if(status == 403)
        QMessageBox::information(this, "Error", "You are not allowed to share this calendar");
    if(status == 500)
        QMessageBox::information(this, "Error", "Internal server error");
}

void MainWindow::synchronizeCalendarList() {
    timerThread = std::thread([this]() {
        bool exit = false;
        while(!exit) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            if(api->isLoggedIn())
                timerElapsed();
            std::lock_guard<std::mutex> ul(endMutex);
            if(end)
                exit = true;
        }
    });
}

void MainWindow::timerElapsed() {
    std::thread checkCalendarList([this](){
        std::list<std::string> names = api->retrieveAllCalendars(); // retrieve the list of calendar names from the server
        std::list<std::string> oldNames = api->getCalendars();
        for(std::string const &newName : names) {
            bool diff = true;
            for(std::string const &oldName : oldNames) {
                if(oldName == newName)
                    diff = false;
            }
            if(diff) {
                api->addCalendar(newName);
                {
                    std::string displayname;
                    api->isShared(newName, std::ref(displayname));
                    std::lock_guard<std::mutex> lg(m);
                    sharedNameMap.insert(std::pair<std::string,std::string>(newName, displayname));
                    ui->listWidget_2->addItem(displayname.c_str());
                }
            }
        }
    });

    std::thread checkCurrentCalendar([this](){
        std::lock_guard<std::mutex> lg(this->m);
        if(!ui->textBrowser_calName->toPlainText().isEmpty()){
            currentCalendar = api->downloadCalendarObjects(currentCalendar.getName());
            selectedDateChange();
        }
    });
    checkCalendarList.join();
    checkCurrentCalendar.join();
}
