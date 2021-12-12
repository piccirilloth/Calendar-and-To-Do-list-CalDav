/********************************************************************************
** Form generated from reading UI file 'ipaddressform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPADDRESSFORM_H
#define UI_IPADDRESSFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IpAddressForm
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_insert;

    void setupUi(QDialog *IpAddressForm)
    {
        if (IpAddressForm->objectName().isEmpty())
            IpAddressForm->setObjectName(QString::fromUtf8("IpAddressForm"));
        IpAddressForm->resize(303, 175);
        widget = new QWidget(IpAddressForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 40, 221, 91));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        pushButton_insert = new QPushButton(widget);
        pushButton_insert->setObjectName(QString::fromUtf8("pushButton_insert"));

        verticalLayout->addWidget(pushButton_insert);


        retranslateUi(IpAddressForm);

        QMetaObject::connectSlotsByName(IpAddressForm);
    } // setupUi

    void retranslateUi(QDialog *IpAddressForm)
    {
        IpAddressForm->setWindowTitle(QApplication::translate("IpAddressForm", "IpAddressForm", nullptr));
        label->setText(QApplication::translate("IpAddressForm", "IP address of the server", nullptr));
        pushButton_insert->setText(QApplication::translate("IpAddressForm", "insert", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IpAddressForm: public Ui_IpAddressForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPADDRESSFORM_H
