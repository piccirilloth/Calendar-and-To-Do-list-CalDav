//
// Created by oscar on 20/11/21.
//

#ifndef QTCREATORTEST_EVENT_INFORMATION_H
#define QTCREATORTEST_EVENT_INFORMATION_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class event_information; }
QT_END_NAMESPACE

class event_information : public QDialog {
Q_OBJECT

public:
    explicit event_information(QWidget *parent = nullptr, std::string summary="", std::string createdOn="", std::string startDate="", std::string endDate="");

    ~event_information() override;

private:
    Ui::event_information *ui;
};


#endif //QTCREATORTEST_EVENT_INFORMATION_H
