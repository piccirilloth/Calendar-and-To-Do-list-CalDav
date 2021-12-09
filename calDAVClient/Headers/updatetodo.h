//
// Created by oscar on 23/11/21.
//

#ifndef QTCREATORTEST_UPDATETODO_H
#define QTCREATORTEST_UPDATETODO_H

#include <QDialog>
#include "Date.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class updateTodo; }
QT_END_NAMESPACE

class updateTodo : public QDialog {
Q_OBJECT

public:
    explicit updateTodo(std::string const &summary, Date const &dueDate, Date const &completedDate, Date const &createdOn, QWidget *parent = nullptr);

    ~updateTodo() override;

private:
    Ui::updateTodo *ui;
    Date createdOn;

signals:
    void updateTd(std::string const & summary, Date const & dueDate, bool completed);

private slots:
    void on_updateTodo_2_clicked();
};


#endif //QTCREATORTEST_UPDATETODO_H
