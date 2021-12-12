/********************************************************************************
** Form generated from reading UI file 'sharecalendarform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHARECALENDARFORM_H
#define UI_SHARECALENDARFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_shareCalendarForm
{
public:
    QLabel *label;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *shareButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_comment;
    QWidget *layoutWidget_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_mailTo;

    void setupUi(QDialog *shareCalendarForm)
    {
        if (shareCalendarForm->objectName().isEmpty())
            shareCalendarForm->setObjectName(QString::fromUtf8("shareCalendarForm"));
        shareCalendarForm->resize(400, 345);
        label = new QLabel(shareCalendarForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 20, 191, 51));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Sans Serif\";"));
        label->setAlignment(Qt::AlignCenter);
        layoutWidget_2 = new QWidget(shareCalendarForm);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(90, 250, 241, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        shareButton = new QPushButton(layoutWidget_2);
        shareButton->setObjectName(QString::fromUtf8("shareButton"));

        horizontalLayout->addWidget(shareButton);

        layoutWidget = new QWidget(shareCalendarForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 200, 241, 51));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_comment = new QLineEdit(layoutWidget);
        lineEdit_comment->setObjectName(QString::fromUtf8("lineEdit_comment"));
        lineEdit_comment->setEnabled(true);

        horizontalLayout_3->addWidget(lineEdit_comment);

        layoutWidget_3 = new QWidget(shareCalendarForm);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(90, 80, 241, 121));
        verticalLayout = new QVBoxLayout(layoutWidget_3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_5->addWidget(label_5);

        comboBox = new QComboBox(layoutWidget_3);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_5->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Sans Serif\";"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_mailTo = new QLineEdit(layoutWidget_3);
        lineEdit_mailTo->setObjectName(QString::fromUtf8("lineEdit_mailTo"));
        lineEdit_mailTo->setEnabled(true);

        horizontalLayout_2->addWidget(lineEdit_mailTo);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(shareCalendarForm);

        QMetaObject::connectSlotsByName(shareCalendarForm);
    } // setupUi

    void retranslateUi(QDialog *shareCalendarForm)
    {
        shareCalendarForm->setWindowTitle(QApplication::translate("shareCalendarForm", "shareCalendarForm", nullptr));
        label->setText(QApplication::translate("shareCalendarForm", "Share a calendar", nullptr));
        shareButton->setText(QApplication::translate("shareCalendarForm", "Share", nullptr));
        label_3->setText(QApplication::translate("shareCalendarForm", "Comment", nullptr));
        label_5->setText(QApplication::translate("shareCalendarForm", "Access policy", nullptr));
        label_2->setText(QApplication::translate("shareCalendarForm", "Share with", nullptr));
    } // retranslateUi

};

namespace Ui {
    class shareCalendarForm: public Ui_shareCalendarForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHARECALENDARFORM_H
