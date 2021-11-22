//
// Created by oscar on 21/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_createEvent.h" resolved

#include <iostream>
#include "Headers/createevent.h"
#include "../Headers/ui_createevent.h"


createEvent::createEvent(QWidget *parent) :
        QDialog(parent), ui(new Ui::createEvent) {
    ui->setupUi(this);
    connect(ui->pushButton_clear, SIGNAL(clicked(bool)), this, SLOT(on_clear()));
    connect(ui->createEvent_2, SIGNAL(clicked(bool)), this, SLOT(on_createClicked()));
    ui->dateTimeEdit_startDate->setCalendarPopup(true);
    ui->dateTimeEdit_endDate->setCalendarPopup(true);
    ui->dateTimeEdit_startDate->setDate(QDate::currentDate());
    ui->dateTimeEdit_endDate->setDate(QDate::currentDate());
}

createEvent::~createEvent() {
    delete ui;
}

void createEvent::on_clear() {
    ui->lineEdit_summary->setText("");
    std::cout << ui->dateTimeEdit_endDate->date().toString("yyyyMMddT").toStdString() + ui->dateTimeEdit_endDate->time().toString("hhmmssZ").toStdString() <<'\n';
}

void createEvent::on_createClicked() {
    if(ui->lineEdit_summary->text().isEmpty())
        QMessageBox::information(this, "Error", "The summary field must be filled");
    Date endDate;
    Date startDate;
    endDate = ui->dateTimeEdit_endDate->date().toString("yyyyMMddT").toStdString() + ui->dateTimeEdit_endDate->time().toString("hhmmssZ").toStdString();
    startDate = ui->dateTimeEdit_startDate->date().toString("yyyyMMddT").toStdString() + ui->dateTimeEdit_startDate->time().toString("hhmmssZ").toStdString();
    emit createEv(ui->lineEdit_summary->text().toStdString(), startDate, endDate);
}

