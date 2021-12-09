//
// Created by oscar on 23/11/21.
//

#ifndef QTCREATORTEST_CREATETODO_H
#define QTCREATORTEST_CREATETODO_H

#include <QDialog>
#include <QMessageBox>
#include "Date.h"

QT_BEGIN_NAMESPACE
namespace Ui { class createTodo; }
QT_END_NAMESPACE

class createTodo : public QDialog {
Q_OBJECT

public:
    explicit createTodo(QWidget *parent = nullptr);

    ~createTodo() override;

private:
    Ui::createTodo *ui;

private slots:
    void on_createTodo_2_clicked();
    void on_pushButton_clear_clicked();

signals:
    void createTd(std::string const &summary, Date const &createdOn, Date const &dueDate);
};


#endif //QTCREATORTEST_CREATETODO_H
