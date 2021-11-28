//
// Created by oscar on 20/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_todo_information.h" resolved

#include "Headers/todo_information.h"
#include "../Headers/ui_todo_information.h"


todo_information::todo_information(QWidget *parent, std::string summary, std::string createdOn, std::string expDate, std::string completed, int priority) :
        QDialog(parent), ui(new Ui::todo_information) {
    ui->setupUi(this);
    ui->label_summary->setText(QString(summary.c_str()));
    ui->label_createdOn->setText(QString(createdOn.c_str()));
    ui->label_expDate->setText(QString(expDate.c_str()));
    if(completed == "0000/00/00")
        ui->label_completedOn->setText(QString("Not completed"));
    else
        ui->label_completedOn->setText(QString(completed.c_str()));
    /*if(priority == -1)
        ui->lineEdit_priority->setText(QString("/"));
    else
        ui->lineEdit_priority->setText(QString(priority));*/
}

todo_information::~todo_information() {
    delete ui;
}

