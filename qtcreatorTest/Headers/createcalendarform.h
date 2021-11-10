//
// Created by oscar on 10/11/21.
//

#ifndef QTCREATORTEST_CREATECALENDARFORM_H
#define QTCREATORTEST_CREATECALENDARFORM_H

#include <QDialog>
#include "API.h"


QT_BEGIN_NAMESPACE
namespace Ui { class CreateCalendarForm; }
QT_END_NAMESPACE

class CreateCalendarForm : public QDialog {
Q_OBJECT

public:
    explicit CreateCalendarForm(QWidget *parent = nullptr);

    ~CreateCalendarForm() override;

private:
    Ui::CreateCalendarForm *ui;
    API *api;

signals:
    void createCalendar();

private slots:
    void on_pushButton_create_clicked();
};


#endif //QTCREATORTEST_CREATECALENDARFORM_H
