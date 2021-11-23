//
// Created by oscar on 21/11/21.
//

#ifndef QTCREATORTEST_CREATEEVENT_H
#define QTCREATORTEST_CREATEEVENT_H

#include <QDialog>
#include <QMessageBox>
#include "Date.h"

QT_BEGIN_NAMESPACE
namespace Ui { class createEvent; }
QT_END_NAMESPACE

class createEvent : public QDialog {
Q_OBJECT

public:
    explicit createEvent(QWidget *parent = nullptr);

    ~createEvent() override;

private:
    Ui::createEvent *ui;

signals:
    void createEv(std::string const &summary, Date const &createdOn, Date const &endDate);

private slots:
    void on_createEvent_2_clicked();
    void on_pushButton_clear_clicked();

};


#endif //QTCREATORTEST_CREATEEVENT_H
