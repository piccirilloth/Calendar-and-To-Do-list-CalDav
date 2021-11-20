//
// Created by oscar on 20/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_event_information.h" resolved

#include "Headers/event_information.h"
#include "../Headers/ui_event_information.h"


event_information::event_information(QWidget *parent,  std::string summary, std::string createdOn, std::string startDate, std::string endDate) :
        QDialog(parent), ui(new Ui::event_information) {
    ui->setupUi(this);
    ui->lineEdit_createdOn->setText(QString(createdOn.c_str()));
    ui->lineEdit_end->setText(QString(endDate.c_str()));
    ui->lineEdit_start->setText(QString(startDate.c_str()));
    ui->lineEdit_summary->setText(QString(summary.c_str()));
}

event_information::~event_information() {
    delete ui;
}

