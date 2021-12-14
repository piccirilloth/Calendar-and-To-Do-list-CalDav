/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_7;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QPushButton *loginButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *createCalendarButton;
    QPushButton *shareCalendarButton;
    QListWidget *listWidget_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLabel *label_calendar;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *label_organizer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLabel *label_user;
    QCalendarWidget *calendarWidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QListWidget *listWidget;
    QPushButton *pushButton_createTodo;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QListWidget *listWidget_Events;
    QPushButton *pushButton_createEvent;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1152, 419);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_7 = new QHBoxLayout(centralwidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setStyleSheet(QString::fromUtf8("font: 87 14pt \"SF Pro\";"));

        verticalLayout_2->addWidget(loginButton);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        createCalendarButton = new QPushButton(centralwidget);
        createCalendarButton->setObjectName(QString::fromUtf8("createCalendarButton"));
        createCalendarButton->setEnabled(false);
        createCalendarButton->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));
        createCalendarButton->setFlat(false);

        horizontalLayout_4->addWidget(createCalendarButton);

        shareCalendarButton = new QPushButton(centralwidget);
        shareCalendarButton->setObjectName(QString::fromUtf8("shareCalendarButton"));
        shareCalendarButton->setEnabled(false);
        shareCalendarButton->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));
        shareCalendarButton->setFlat(false);

        horizontalLayout_4->addWidget(shareCalendarButton);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_2);

        listWidget_2 = new QListWidget(centralwidget);
        listWidget_2->setObjectName(QString::fromUtf8("listWidget_2"));

        verticalLayout_3->addWidget(listWidget_2);


        verticalLayout_6->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        label_calendar = new QLabel(centralwidget);
        label_calendar->setObjectName(QString::fromUtf8("label_calendar"));

        horizontalLayout->addWidget(label_calendar);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        label_organizer = new QLabel(centralwidget);
        label_organizer->setObjectName(QString::fromUtf8("label_organizer"));

        horizontalLayout_3->addWidget(label_organizer);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        label_user = new QLabel(centralwidget);
        label_user->setObjectName(QString::fromUtf8("label_user"));

        horizontalLayout_2->addWidget(label_user);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_6->addLayout(verticalLayout);


        horizontalLayout_6->addLayout(verticalLayout_6);

        calendarWidget = new QCalendarWidget(centralwidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));

        horizontalLayout_6->addWidget(calendarWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"Lohit Telugu\";\n"
"font: 14pt \"Sans Serif\";"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_4->addWidget(listWidget);

        pushButton_createTodo = new QPushButton(centralwidget);
        pushButton_createTodo->setObjectName(QString::fromUtf8("pushButton_createTodo"));
        pushButton_createTodo->setEnabled(false);

        verticalLayout_4->addWidget(pushButton_createTodo);


        horizontalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Lohit Telugu\";\n"
"font: 14pt \"Sans Serif\";"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_2);

        listWidget_Events = new QListWidget(centralwidget);
        listWidget_Events->setObjectName(QString::fromUtf8("listWidget_Events"));

        verticalLayout_5->addWidget(listWidget_Events);

        pushButton_createEvent = new QPushButton(centralwidget);
        pushButton_createEvent->setObjectName(QString::fromUtf8("pushButton_createEvent"));
        pushButton_createEvent->setEnabled(false);

        verticalLayout_5->addWidget(pushButton_createEvent);


        horizontalLayout_5->addLayout(verticalLayout_5);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        horizontalLayout_7->addLayout(horizontalLayout_6);

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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Calendar", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        createCalendarButton->setText(QCoreApplication::translate("MainWindow", "Create", nullptr));
        shareCalendarButton->setText(QCoreApplication::translate("MainWindow", "Share", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Current calendar", nullptr));
        label_calendar->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "Calendar organizer", nullptr));
        label_organizer->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Current user", nullptr));
        label_user->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "ToDo", nullptr));
        pushButton_createTodo->setText(QCoreApplication::translate("MainWindow", "Create a Todo", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Events", nullptr));
        pushButton_createEvent->setText(QCoreApplication::translate("MainWindow", "Create a Event", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
