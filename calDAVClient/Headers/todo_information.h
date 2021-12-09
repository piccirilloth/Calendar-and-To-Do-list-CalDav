//
// Created by oscar on 20/11/21.
//

#ifndef QTCREATORTEST_TODO_INFORMATION_H
#define QTCREATORTEST_TODO_INFORMATION_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class todo_information; }
QT_END_NAMESPACE

class todo_information : public QDialog {
Q_OBJECT

public:
    explicit todo_information(QWidget *parent = nullptr, std::string summary="", std::string createdOn="", std::string expDate="", std::string completed="");

    ~todo_information() override;

private:
    Ui::todo_information *ui;
};


#endif //QTCREATORTEST_TODO_INFORMATION_H
