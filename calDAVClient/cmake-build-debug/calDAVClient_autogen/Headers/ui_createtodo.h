/********************************************************************************
** Form generated from reading UI file 'createtodo.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETODO_H
#define UI_CREATETODO_H

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

class Ui_createTodo
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QTextEdit *textEdit_summary;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QDateTimeEdit *dateTimeEdit_dueDate;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *createTodo_2;
    QPushButton *pushButton_clear;
    QLabel *label;

    void setupUi(QDialog *createTodo)
    {
        if (createTodo->objectName().isEmpty())
            createTodo->setObjectName(QString::fromUtf8("createTodo"));
        createTodo->resize(343, 380);
        layoutWidget = new QWidget(createTodo);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 120, 241, 121));
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

        horizontalLayout_5->addWidget(textEdit_summary);


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

        layoutWidget_2 = new QWidget(createTodo);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(50, 240, 241, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        createTodo_2 = new QPushButton(layoutWidget_2);
        createTodo_2->setObjectName(QString::fromUtf8("createTodo_2"));

        horizontalLayout->addWidget(createTodo_2);

        pushButton_clear = new QPushButton(layoutWidget_2);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        horizontalLayout->addWidget(pushButton_clear);

        label = new QLabel(createTodo);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 60, 191, 51));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Sans Serif\";"));
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(createTodo);

        QMetaObject::connectSlotsByName(createTodo);
    } // setupUi

    void retranslateUi(QDialog *createTodo)
    {
        createTodo->setWindowTitle(QCoreApplication::translate("createTodo", "createTodo", nullptr));
        label_5->setText(QCoreApplication::translate("createTodo", "Summary", nullptr));
        textEdit_summary->setHtml(QCoreApplication::translate("createTodo", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("createTodo", "Due", nullptr));
        createTodo_2->setText(QCoreApplication::translate("createTodo", "Create", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("createTodo", "Clear", nullptr));
        label->setText(QCoreApplication::translate("createTodo", "Create a todo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createTodo: public Ui_createTodo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETODO_H
