//
// Created by oscar on 23/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_createTodo.h" resolved

#include "Headers/createtodo.h"
#include "../Headers/ui_createtodo.h"

createTodo::createTodo(QWidget *parent) :
        QDialog(parent), ui(new Ui::createTodo) {
    ui->setupUi(this);
    ui->dateTimeEdit_dueDate->setDate(QDate::currentDate());
    ui->dateTimeEdit_dueDate->setCalendarPopup(true);
}

void createTodo::on_pushButton_clear_clicked() {
    ui->textEdit_summary->setText("");
}

void createTodo::on_createTodo_2_clicked() {
    QDateTime now = QDateTime::currentDateTime();
    if(ui->textEdit_summary->toPlainText().isEmpty())
        QMessageBox::information(this, "Error", "The summary field must be filled");
    else if(now >= ui->dateTimeEdit_dueDate->dateTime())
        QMessageBox::information(this, "Error", "The endDate cannot be in the past!");
    else if(ui->textEdit_summary->toPlainText().contains('\n'))
        QMessageBox::information(this, "Error", "The summary cannot contain return characters");
    else {
        Date dueDate, nowD;
        dueDate = ui->dateTimeEdit_dueDate->date().toString("yyyyMMddT").toStdString() + ui->dateTimeEdit_dueDate->time().toString("hhmmssZ").toStdString();
        nowD = now.date().toString("yyyyMMddT").toStdString() + now.time().toString("hhmmssZ").toStdString();
        emit createTd(ui->textEdit_summary->toPlainText().toStdString(), nowD, dueDate);
        this->close();
    }
}

createTodo::~createTodo() {
    delete ui;
}

