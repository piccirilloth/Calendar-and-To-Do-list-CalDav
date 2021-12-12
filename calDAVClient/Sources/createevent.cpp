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
    //connect(ui->pushButton_clear, SIGNAL(clicked(bool)), this, SLOT(on_clear()));
    //connect(ui->createEvent_2, SIGNAL(clicked(bool)), this, SLOT(on_createClicked()));
    ui->dateTimeEdit_startDate->setCalendarPopup(true);
    ui->dateTimeEdit_endDate->setCalendarPopup(true);
    ui->dateTimeEdit_startDate->setDate(QDate::currentDate());
    ui->dateTimeEdit_endDate->setDate(QDate::currentDate());
    isUpdate = false;
}

createEvent::createEvent(const Vevent &event, const Vcalendar &cal, QWidget *parent): QDialog(parent), ui(new Ui::createEvent) {
    ui->setupUi(this);
    ui->dateTimeEdit_startDate->setCalendarPopup(true);
    ui->dateTimeEdit_endDate->setCalendarPopup(true);
    ui->textEdit_summary->setText(QString(event.getSummary().c_str()));
    Date startDate = event.getDtstart();
    ui->dateTimeEdit_startDate->setDate(QDate(startDate[YEAR], startDate[MONTH], startDate[DAY]));
    ui->dateTimeEdit_startDate->setTime(QTime(startDate[HOUR], startDate[MINUTE], startDate[SECOND]));
    Date endDate = event.getDtend();
    ui->dateTimeEdit_endDate->setDate(QDate(endDate[YEAR], endDate[MONTH], endDate[DAY]));
    ui->dateTimeEdit_endDate->setTime(QTime(endDate[HOUR], endDate[MINUTE], endDate[SECOND]));
    ui->createEvent_2->setText("Update");
    ui->label->setText("Update an event");
    this->setWindowTitle("updateEvent");
    isUpdate = true;
    this->event = event;
}

createEvent::~createEvent() {
    delete ui;
}

void createEvent::on_pushButton_clear_clicked() {
    ui->textEdit_summary->setText("");
}

void createEvent::on_createEvent_2_clicked() {
    if(ui->textEdit_summary->toPlainText().isEmpty())
        QMessageBox::information(this, "Error", "The summary field must be filled");
    else if(ui->dateTimeEdit_startDate->date() > ui->dateTimeEdit_endDate->date())
        QMessageBox::information(this, "Error", "The start date must precede the end date");
    else if(ui->dateTimeEdit_startDate->date() == ui->dateTimeEdit_endDate->date() && ui->dateTimeEdit_startDate->time() > ui->dateTimeEdit_endDate->time())
        QMessageBox::information(this, "Error", "The start time must precede the end time");
    else if(ui->textEdit_summary->toPlainText().contains('\n'))
        QMessageBox::information(this, "Error", "The summary cannot contain return characters");
    else {
        Date endDate;
        Date startDate;
        endDate = ui->dateTimeEdit_endDate->date().toString("yyyyMMddT").toStdString() + ui->dateTimeEdit_endDate->time().toString("hhmmssZ").toStdString();
        startDate = ui->dateTimeEdit_startDate->date().toString("yyyyMMddT").toStdString() + ui->dateTimeEdit_startDate->time().toString("hhmmssZ").toStdString();
        if(!isUpdate)
                emit createEv(ui->textEdit_summary->toPlainText().toStdString(), startDate, endDate, isUpdate);
        else
                emit createEv(ui->textEdit_summary->toPlainText().toStdString(), startDate, endDate, isUpdate, event.getUid());
        this->close();
    }
}

