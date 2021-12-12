/********************************************************************************
** Form generated from reading UI file 'createcalendarform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECALENDARFORM_H
#define UI_CREATECALENDARFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateCalendarForm
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_calendarName;
    QPushButton *pushButton_create;

    void setupUi(QDialog *CreateCalendarForm)
    {
        if (CreateCalendarForm->objectName().isEmpty())
            CreateCalendarForm->setObjectName(QString::fromUtf8("CreateCalendarForm"));
        CreateCalendarForm->resize(232, 122);
        widget = new QWidget(CreateCalendarForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 20, 191, 81));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_calendarName = new QLineEdit(widget);
        lineEdit_calendarName->setObjectName(QString::fromUtf8("lineEdit_calendarName"));

        horizontalLayout->addWidget(lineEdit_calendarName);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_create = new QPushButton(widget);
        pushButton_create->setObjectName(QString::fromUtf8("pushButton_create"));

        verticalLayout->addWidget(pushButton_create);


        retranslateUi(CreateCalendarForm);

        QMetaObject::connectSlotsByName(CreateCalendarForm);
    } // setupUi

    void retranslateUi(QDialog *CreateCalendarForm)
    {
        CreateCalendarForm->setWindowTitle(QApplication::translate("CreateCalendarForm", "CreateCalendarForm", nullptr));
        label->setText(QApplication::translate("CreateCalendarForm", "Name:", nullptr));
        pushButton_create->setText(QApplication::translate("CreateCalendarForm", "Create", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateCalendarForm: public Ui_CreateCalendarForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECALENDARFORM_H
