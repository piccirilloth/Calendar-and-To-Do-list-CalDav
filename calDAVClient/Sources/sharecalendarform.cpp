//
// Created by oscar on 24/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_shareCalendarForm.h" resolved

#include "Headers/sharecalendarform.h"
#include "../Headers/ui_sharecalendarform.h"


shareCalendarForm::shareCalendarForm(QWidget *parent) :
        QDialog(parent), ui(new Ui::shareCalendarForm) {
    ui->setupUi(this);
    ui->comboBox->addItem(QString("read-write"));
    ui->comboBox->addItem(QString("read"));
}

shareCalendarForm::~shareCalendarForm() {
    delete ui;
}

void shareCalendarForm::on_shareButton_clicked() {
    if(ui->lineEdit_mailTo->text().isEmpty())
        QMessageBox::information(this, "Error", "mail field must be filled");
    else {
        emit shareCal(ui->lineEdit_mailTo->text().toStdString(), ui->lineEdit_comment->text().toStdString(), ui->comboBox->currentText().toStdString());
        this->close();
    }
}

