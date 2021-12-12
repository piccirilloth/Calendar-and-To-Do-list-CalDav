/********************************************************************************
** Form generated from reading UI file 'event_information.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENT_INFORMATION_H
#define UI_EVENT_INFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_event_information
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *label_createdOn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_startDate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_startDate_2;
    QLabel *label_endDate;

    void setupUi(QDialog *event_information)
    {
        if (event_information->objectName().isEmpty())
            event_information->setObjectName(QString::fromUtf8("event_information"));
        event_information->resize(549, 337);
        layoutWidget = new QWidget(event_information);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 40, 411, 241));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_5->addWidget(label_6);

        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        horizontalLayout_5->addWidget(textBrowser);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_4->addWidget(label_4);

        label_createdOn = new QLabel(layoutWidget);
        label_createdOn->setObjectName(QString::fromUtf8("label_createdOn"));
        label_createdOn->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_4->addWidget(label_createdOn);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_2->addWidget(label_2);

        label_startDate = new QLabel(layoutWidget);
        label_startDate->setObjectName(QString::fromUtf8("label_startDate"));
        label_startDate->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_2->addWidget(label_startDate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_startDate_2 = new QLabel(layoutWidget);
        label_startDate_2->setObjectName(QString::fromUtf8("label_startDate_2"));
        label_startDate_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_3->addWidget(label_startDate_2);

        label_endDate = new QLabel(layoutWidget);
        label_endDate->setObjectName(QString::fromUtf8("label_endDate"));
        label_endDate->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_3->addWidget(label_endDate);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(event_information);

        QMetaObject::connectSlotsByName(event_information);
    } // setupUi

    void retranslateUi(QDialog *event_information)
    {
        event_information->setWindowTitle(QApplication::translate("event_information", "event_information", nullptr));
        label_6->setText(QApplication::translate("event_information", "Summary", nullptr));
        label_4->setText(QApplication::translate("event_information", "Created on", nullptr));
        label_createdOn->setText(QString());
        label_2->setText(QApplication::translate("event_information", "Start date", nullptr));
        label_startDate->setText(QString());
        label_startDate_2->setText(QApplication::translate("event_information", "End date", nullptr));
        label_endDate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class event_information: public Ui_event_information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENT_INFORMATION_H
