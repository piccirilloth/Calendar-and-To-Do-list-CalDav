//
// Created by oscar on 21/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_createEvent.h" resolved

#include "Headers/createevent.h"
#include "../Headers/ui_createevent.h"


createEvent::createEvent(QWidget *parent) :
        QDialog(parent), ui(new Ui::createEvent) {
    ui->setupUi(this);
    connect(ui->pushButton_clear, SIGNAL(clicked(bool)), this, SLOT(on_clear()));
    connect(ui->createEvent_2, SIGNAL(clicked(bool)), this, SLOT(on_createClicked()));
}

createEvent::~createEvent() {
    delete ui;
}

void createEvent::on_clear() {
    ui->lineEdit_createdOn->setText("");
    ui->lineEdit_summary->setText("");
    ui->lineEdit_start->setText("");
    ui->lineEdit_end->setText("");
}

void createEvent::on_createClicked() {
    // todo: implement checks on input data
    emit createEv();
}

