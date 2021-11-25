#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"
#include "Vcalendar.h"
#include "API.h"
#include "createcalendarform.h"
#include <list>
#include <map>
#include "IcsParser.h"
#include "event_information.h"
#include "todo_information.h"
#include "createevent.h"
#include "createtodo.h"
#include "updatetodo.h"
#include "sharecalendarform.h"
#include <QTimer>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUpPage();
    void synchronizeCalendarList();

private slots:
    void on_loginButton_clicked();
    void afterLogin();
    void on_createCalendarButton_clicked();
    void updateCalendars();
    void ProvideContextMenuCal(const QPoint &pos);
    void on_dbclick();
    void selectedDateChange();
    void on_dbClickEvent();
    void on_dbClickTodo();
    void ProvideContextMenuTodo(const QPoint &pos);
    void ProvideContextMenuEvents(const QPoint &pos);
    void on_pushButton_createEvent_clicked();
    void updateEvents(std::string const &summary, Date const &startDate, Date const &endDate, bool isUpdate, std::string const & uid="");
    void on_pushButton_createTodo_clicked();
    void createTodo_slot(std::string const &summary, Date const &dueDate);
    void updateTodo_slot(std::string const &summary, Date const &dueDate, bool completed);
    void on_shareCalendarButton_clicked();
    void shareCalendar_slot(std::string const &displayName, std::string const &email, std::string const &comment);

private:
    Ui::MainWindow *ui;
    loginwindow *login;
    API *api;
    Vcalendar currentCalendar;
    std::map<int, std::string> eventMap;
    std::map<int, std::string> todoMap;
    std::mutex m;
    bool end;
    std::mutex endMutex;
    std::thread timerThread;

    std::optional<Vevent> getEvetByUid(std::string const &uid);
    std::optional<Vtodo> getTodoByUid(std::string const &uid);
    void timerElapsed();
};
#endif // MAINWINDOW_H
