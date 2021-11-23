/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QCalendarWidget *calendarWidget;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QPushButton *loginButton;
    QPushButton *createCalendarButton;
    QListWidget *listWidget_Events;
    QLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QTextBrowser *textBrowser_calName;
    QPushButton *pushButton_createTodo;
    QPushButton *pushButton_createEvent;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1317, 510);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        calendarWidget = new QCalendarWidget(centralwidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        calendarWidget->setGeometry(QRect(290, 0, 521, 471));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(820, 50, 241, 381));
        listWidget_2 = new QListWidget(centralwidget);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));
        listWidget_2->setGeometry(QRect(10, 110, 261, 331));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(10, 10, 261, 41));
        loginButton->setStyleSheet(QString::fromUtf8("font: 87 14pt \"SF Pro\";"));
        createCalendarButton = new QPushButton(centralwidget);
        createCalendarButton->setObjectName(QString::fromUtf8("createCalendarButton"));
        createCalendarButton->setEnabled(false);
        createCalendarButton->setGeometry(QRect(10, 60, 261, 41));
        createCalendarButton->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));
        createCalendarButton->setFlat(false);
        listWidget_Events = new QListWidget(centralwidget);
        listWidget_Events->setObjectName(QString::fromUtf8("listWidget_Events"));
        listWidget_Events->setGeometry(QRect(1070, 50, 241, 381));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(820, 10, 241, 31));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"Lohit Telugu\";\n"
"font: 14pt \"Sans Serif\";"));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(1070, 10, 241, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Lohit Telugu\";\n"
"font: 14pt \"Sans Serif\";"));
        label_2->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 440, 261, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        textBrowser_calName = new QTextBrowser(layoutWidget);
        textBrowser_calName->setObjectName(QString::fromUtf8("textBrowser_calName"));

        horizontalLayout->addWidget(textBrowser_calName);

        pushButton_createTodo = new QPushButton(centralwidget);
        pushButton_createTodo->setObjectName(QString::fromUtf8("pushButton_createTodo"));
        pushButton_createTodo->setEnabled(false);
        pushButton_createTodo->setGeometry(QRect(820, 440, 241, 31));
        pushButton_createEvent = new QPushButton(centralwidget);
        pushButton_createEvent->setObjectName(QString::fromUtf8("pushButton_createEvent"));
        pushButton_createEvent->setEnabled(false);
        pushButton_createEvent->setGeometry(QRect(1070, 440, 241, 31));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Calendar", nullptr));
        loginButton->setText(QApplication::translate("MainWindow", "Login", nullptr));
        createCalendarButton->setText(QApplication::translate("MainWindow", "Create a calendar", nullptr));
        label->setText(QApplication::translate("MainWindow", "ToDo", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Events", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Current calendar", nullptr));
        pushButton_createTodo->setText(QApplication::translate("MainWindow", "Create a Todo", nullptr));
        pushButton_createEvent->setText(QApplication::translate("MainWindow", "Create a Event", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
