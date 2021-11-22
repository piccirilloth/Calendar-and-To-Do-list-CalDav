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
    void on_createEvent();
    void updateEvents(std::string const &summary, Date const &createdOn, Date const &endDate);

private:
    Ui::MainWindow *ui;
    loginwindow *login;
    API *api;
    Vcalendar currentCalendar;
    std::map<int, std::string> eventMap;
    std::map<int, std::string> todoMap;
};
#endif // MAINWINDOW_H
