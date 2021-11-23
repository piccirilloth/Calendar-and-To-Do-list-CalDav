//
// Created by oscar on 23/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_updateTodo.h" resolved

#include "Headers/updatetodo.h"
#include "../Headers/ui_updatetodo.h"


updateTodo::updateTodo(std::string const &summary, Date const &dueDate, Date const &completedDate, QWidget *parent) :
        QDialog(parent), ui(new Ui::updateTodo) {
    ui->setupUi(this);
    ui->dateTimeEdit_dueDate->setCalendarPopup(true);
    Date temp = dueDate;
    ui->lineEdit_summary->setText(summary.c_str());
    ui->dateTimeEdit_dueDate->setDate(QDate(temp[YEAR], temp[MONTH], temp[DAY]));
    ui->dateTimeEdit_dueDate->setTime(QTime(temp[HOUR], temp[MINUTE], temp[SECOND]));
    if(static_cast<std::string>(completedDate) == "00000000")
        ui->checkBox_completed->setChecked(false);
    else
        ui->checkBox_completed->setChecked(true);
}

void updateTodo::on_updateTodo_2_clicked() {
    if(ui->lineEdit_summary->text().isEmpty())
        QMessageBox::information(this, "Error", "The summary field must be filled");
    else {
        Date dueDate;
        dueDate = ui->dateTimeEdit_dueDate->date().toString("yyyyMMddT").toStdString() + ui->dateTimeEdit_dueDate->time().toString("hhmmssZ").toStdString();
        emit updateTd(ui->lineEdit_summary->text().toStdString(), dueDate, ui->checkBox_completed->isChecked());
        this->close();
    }
}

updateTodo::~updateTodo() {
    delete ui;
}

