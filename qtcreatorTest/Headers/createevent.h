//
// Created by oscar on 21/11/21.
//

#ifndef QTCREATORTEST_CREATEEVENT_H
#define QTCREATORTEST_CREATEEVENT_H

#include <QDialog>


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
    void createEv();

private slots:
    void on_createClicked();
    void on_clear();

};


#endif //QTCREATORTEST_CREATEEVENT_H
