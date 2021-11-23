//
// Created by oscar on 21/11/21.
//

#ifndef QTCREATORTEST_CREATEEVENT_H
#define QTCREATORTEST_CREATEEVENT_H

#include <QDialog>
#include <QMessageBox>
#include "Vevent.h"
#include "Vcalendar.h"
#include "Date.h"

QT_BEGIN_NAMESPACE
namespace Ui { class createEvent; }
QT_END_NAMESPACE

class createEvent : public QDialog {
Q_OBJECT

public:
    explicit createEvent(QWidget *parent = nullptr);

    explicit createEvent(Vevent const &event, Vcalendar const &cal, QWidget *parent = nullptr);

    ~createEvent() override;

private:
    Ui::createEvent *ui;
    bool isUpdate;
    Vevent event;

signals:
    void createEv(std::string const &summary, Date const &createdOn, Date const &endDate, bool isUpdate, std::string const &uid="");

private slots:
    void on_createEvent_2_clicked();
    void on_pushButton_clear_clicked();

};


#endif //QTCREATORTEST_CREATEEVENT_H
