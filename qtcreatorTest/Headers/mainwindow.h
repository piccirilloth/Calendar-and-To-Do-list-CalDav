#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"
#include "Vcalendar.h"
#include "API.h"
#include "createcalendarform.h"
#include <list>

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
    void ProvideContextMenu(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    loginwindow *login;
    API *api;
};
#endif // MAINWINDOW_H
