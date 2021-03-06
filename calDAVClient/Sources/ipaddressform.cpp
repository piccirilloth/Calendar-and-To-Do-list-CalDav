//
// Created by oscar on 09/12/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_IpAddressForm.h" resolved

#include "Headers/ipaddressform.h"
#include "../Headers/ui_ipaddressform.h"


IpAddressForm::IpAddressForm(QWidget *parent) :
        QDialog(parent), ui(new Ui::IpAddressForm) {
    ui->setupUi(this);
    this->setWindowFlags( (Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint) & ~Qt::WindowCloseButtonHint );
    ui->lineEdit->setText("192.168.1.10");
}

IpAddressForm::~IpAddressForm() {
    delete ui;
}

void IpAddressForm::on_pushButton_insert_clicked() {
    std::regex regex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    API *api = new API;
    if(!std::regex_match(ui->lineEdit->text().toStdString(), regex))
        QMessageBox::information(this, "Error", "A valid IP address must be inserted");
    else if(!api->isReachable(ui->lineEdit->text().toStdString()))
            QMessageBox::information(this, "Error", "The host is unreachable");
    else {
        api->setIpaddress(ui->lineEdit->text().toStdString());
        this->close();
    }
}
