//
// Created by oscar on 09/12/21.
//

#ifndef QTCREATORTEST_IPADDRESSFORM_H
#define QTCREATORTEST_IPADDRESSFORM_H

#include <QDialog>
#include <regex>
#include <QMessageBox>
#include "API.h"

QT_BEGIN_NAMESPACE
namespace Ui { class IpAddressForm; }
QT_END_NAMESPACE

class IpAddressForm : public QDialog {
Q_OBJECT

public:
    explicit IpAddressForm(QWidget *parent = nullptr);

    ~IpAddressForm() override;

private:
    Ui::IpAddressForm *ui;

private slots:
    void on_pushButton_insert_clicked();
};


#endif //QTCREATORTEST_IPADDRESSFORM_H
