/********************************************************************************
** Form generated from reading UI file 'createevent.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEEVENT_H
#define UI_CREATEEVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_createEvent
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QTextEdit *textEdit_summary;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit_startDate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit_endDate;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *createEvent_2;
    QPushButton *pushButton_clear;
    QLabel *label;

    void setupUi(QDialog *createEvent)
    {
        if (createEvent->objectName().isEmpty())
            createEvent->setObjectName(QString::fromUtf8("createEvent"));
        createEvent->resize(356, 420);
        layoutWidget = new QWidget(createEvent);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 100, 241, 181));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_5->addWidget(label_5);

        textEdit_summary = new QTextEdit(layoutWidget);
        textEdit_summary->setObjectName(QString::fromUtf8("textEdit_summary"));
        textEdit_summary->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_5->addWidget(textEdit_summary);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_2->addWidget(label_2);

        dateTimeEdit_startDate = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_startDate->setObjectName(QString::fromUtf8("dateTimeEdit_startDate"));

        horizontalLayout_2->addWidget(dateTimeEdit_startDate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_3->addWidget(label_3);

        dateTimeEdit_endDate = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_endDate->setObjectName(QString::fromUtf8("dateTimeEdit_endDate"));

        horizontalLayout_3->addWidget(dateTimeEdit_endDate);


        verticalLayout->addLayout(horizontalLayout_3);

        layoutWidget1 = new QWidget(createEvent);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(70, 280, 241, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        createEvent_2 = new QPushButton(layoutWidget1);
        createEvent_2->setObjectName(QString::fromUtf8("createEvent_2"));

        horizontalLayout->addWidget(createEvent_2);

        pushButton_clear = new QPushButton(layoutWidget1);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        horizontalLayout->addWidget(pushButton_clear);

        label = new QLabel(createEvent);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 40, 191, 51));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Sans Serif\";"));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(createEvent);

        QMetaObject::connectSlotsByName(createEvent);
    } // setupUi

    void retranslateUi(QDialog *createEvent)
    {
        createEvent->setWindowTitle(QCoreApplication::translate("createEvent", "createEvent", nullptr));
        label_5->setText(QCoreApplication::translate("createEvent", "Summary", nullptr));
        label_2->setText(QCoreApplication::translate("createEvent", "Start date", nullptr));
        label_3->setText(QCoreApplication::translate("createEvent", "End date", nullptr));
        createEvent_2->setText(QCoreApplication::translate("createEvent", "Create", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("createEvent", "Clear", nullptr));
        label->setText(QCoreApplication::translate("createEvent", "Create an event", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createEvent: public Ui_createEvent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEVENT_H
