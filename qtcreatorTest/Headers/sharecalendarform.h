//
// Created by oscar on 24/11/21.
//

#ifndef QTCREATORTEST_SHARECALENDARFORM_H
#define QTCREATORTEST_SHARECALENDARFORM_H

#include <QDialog>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class shareCalendarForm; }
QT_END_NAMESPACE

class shareCalendarForm : public QDialog {
Q_OBJECT

public:
    explicit shareCalendarForm(QWidget *parent = nullptr);

    ~shareCalendarForm() override;

private:
    Ui::shareCalendarForm *ui;

signals:
    void shareCal(std::string const &displayName, std::string const &email, std::string const &comment);

private slots:
    void on_shareButton_clicked();
};


#endif //QTCREATORTEST_SHARECALENDARFORM_H
