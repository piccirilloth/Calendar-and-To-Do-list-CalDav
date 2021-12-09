//
// Created by oscar on 10/11/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_CreateCalendarForm.h" resolved

#include "Headers/createcalendarform.h"
#include "../Headers/ui_createcalendarform.h"
#include <QMessageBox>

CreateCalendarForm::CreateCalendarForm(QWidget *parent) :
        QDialog(parent), ui(new Ui::CreateCalendarForm) {
    ui->setupUi(this);
    api = new API();
}

CreateCalendarForm::~CreateCalendarForm() {
    delete ui;
}

void CreateCalendarForm::on_pushButton_create_clicked() {
    QString name = ui->lineEdit_calendarName->text();
    if(name.toStdString().empty())
        QMessageBox::information(this, "Error", "the name cannot be left empty");
    if(name.toStdString().size() > 30)
        QMessageBox::information(this, "Error", "maximum name size: 30");
    if(name.toStdString().find(' ') != std::string::npos ||  name.toStdString().find('<') != std::string::npos || name.toStdString().find('>') != std::string::npos)
        QMessageBox::information(this, "Error", "the name cannot contain spaces, '<' or '>'");
    else {
        std::list<std::string> l = api->getCalendars();
        bool flag = false;
        for(std::string v : l)
            if(v == name.toStdString())
                flag = true;
        if(flag)
            QMessageBox::information(this, "Error", "duplicated name");
        else
        {
            long status = api->createEmptyCalendar(name.toStdString());
            if(status == 0) {
                QMessageBox::information(this, "Error", "error in the communication with the server");
            } else {
                std::list<std::string> names = api->retrieveAllCalendars();
                api->clearCalendars();
                for (std::string value: names)
                    api->addCalendar(value);
                emit createCalendar();
                this->close();
            }
        }
    }
}

