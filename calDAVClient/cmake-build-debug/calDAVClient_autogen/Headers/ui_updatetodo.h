/********************************************************************************
** Form generated from reading UI file 'updatetodo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATETODO_H
#define UI_UPDATETODO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updateTodo
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QLineEdit *lineEdit_summary;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit_dueDate;
    QLabel *label;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *updateTodo_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QRadioButton *checkBox_completed;

    void setupUi(QDialog *updateTodo)
    {
        if (updateTodo->objectName().isEmpty())
            updateTodo->setObjectName(QString::fromUtf8("updateTodo"));
        updateTodo->resize(400, 415);
        layoutWidget = new QWidget(updateTodo);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 90, 241, 121));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_5->addWidget(label_5);

        lineEdit_summary = new QLineEdit(layoutWidget);
        lineEdit_summary->setObjectName(QString::fromUtf8("lineEdit_summary"));
        lineEdit_summary->setEnabled(true);

        horizontalLayout_5->addWidget(lineEdit_summary);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_2->addWidget(label_2);

        dateTimeEdit_dueDate = new QDateTimeEdit(layoutWidget);
        dateTimeEdit_dueDate->setObjectName(QString::fromUtf8("dateTimeEdit_dueDate"));

        horizontalLayout_2->addWidget(dateTimeEdit_dueDate);


        verticalLayout->addLayout(horizontalLayout_2);

        label = new QLabel(updateTodo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 30, 191, 51));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Sans Serif\";"));
        label->setAlignment(Qt::AlignCenter);
        layoutWidget_2 = new QWidget(updateTodo);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(80, 260, 241, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        updateTodo_2 = new QPushButton(layoutWidget_2);
        updateTodo_2->setObjectName(QString::fromUtf8("updateTodo_2"));

        horizontalLayout->addWidget(updateTodo_2);

        layoutWidget1 = new QWidget(updateTodo);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(80, 210, 241, 51));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_3->addWidget(label_3);

        checkBox_completed = new QRadioButton(layoutWidget1);
        checkBox_completed->setObjectName(QString::fromUtf8("checkBox_completed"));
        checkBox_completed->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_3->addWidget(checkBox_completed);


        retranslateUi(updateTodo);

        QMetaObject::connectSlotsByName(updateTodo);
    } // setupUi

    void retranslateUi(QDialog *updateTodo)
    {
        updateTodo->setWindowTitle(QApplication::translate("updateTodo", "updateTodo", nullptr));
        label_5->setText(QApplication::translate("updateTodo", "Summary", nullptr));
        label_2->setText(QApplication::translate("updateTodo", "Due", nullptr));
        label->setText(QApplication::translate("updateTodo", "Update a todo", nullptr));
        updateTodo_2->setText(QApplication::translate("updateTodo", "Update", nullptr));
        label_3->setText(QApplication::translate("updateTodo", "Completed", nullptr));
        checkBox_completed->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class updateTodo: public Ui_updateTodo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATETODO_H
