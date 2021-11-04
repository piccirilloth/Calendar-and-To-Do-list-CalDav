#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"
#include "Vcalendar.h"
#include "API.h"
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
    void change_login_button();

private:
    Ui::MainWindow *ui;
    loginwindow *login;
    API *api;
};
#endif // MAINWINDOW_H
