/********************************************************************************
** Form generated from reading UI file 'todo_information.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODO_INFORMATION_H
#define UI_TODO_INFORMATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_todo_information
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLabel *label_createdOn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *label_expDate;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLabel *label_completedOn;

    void setupUi(QDialog *todo_information)
    {
        if (todo_information->objectName().isEmpty())
            todo_information->setObjectName(QString::fromUtf8("todo_information"));
        todo_information->resize(473, 385);
        layoutWidget = new QWidget(todo_information);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 60, 341, 271));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_5->addWidget(label_5);

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

        label_expDate = new QLabel(layoutWidget);
        label_expDate->setObjectName(QString::fromUtf8("label_expDate"));
        label_expDate->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_2->addWidget(label_expDate);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_3->addWidget(label_3);

        label_completedOn = new QLabel(layoutWidget);
        label_completedOn->setObjectName(QString::fromUtf8("label_completedOn"));
        label_completedOn->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_3->addWidget(label_completedOn);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(todo_information);

        QMetaObject::connectSlotsByName(todo_information);
    } // setupUi

    void retranslateUi(QDialog *todo_information)
    {
        todo_information->setWindowTitle(QApplication::translate("todo_information", "todo_information", nullptr));
        label_5->setText(QApplication::translate("todo_information", "Summary", nullptr));
        label_4->setText(QApplication::translate("todo_information", "Created on", nullptr));
        label_createdOn->setText(QApplication::translate("todo_information", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("todo_information", "Expiration date", nullptr));
        label_expDate->setText(QApplication::translate("todo_information", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("todo_information", "Completed on", nullptr));
        label_completedOn->setText(QApplication::translate("todo_information", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class todo_information: public Ui_todo_information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODO_INFORMATION_H
