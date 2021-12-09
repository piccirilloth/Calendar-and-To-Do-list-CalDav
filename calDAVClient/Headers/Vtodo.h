//
// Created by picci on 27/10/2021.
//

#ifndef QTCREATORTEST_VTODO_H
#define QTCREATORTEST_VTODO_H

#include "Date.h"
#include <iostream>

class Vtodo {

public:
    Vtodo() {};

    Vtodo(string uid, string summary, Date dtstamp);

    const string &getUid() const;

    void setUid(const string &uid);

    const string &getSummary() const;

    void setSummary(const string &summary);

    const Date &getDtstamp() const;

    void setDtstamp(const Date &dtstamp);

    const Date &getDtstart() const;

    void setDtstart(const Date &dtstart);

    const Date &getCompleted() const;

    void setCompleted(const Date &completed);

    const Date &getDue() const;

    void setDue(const Date &due);

    friend ostream& operator << (ostream &os, const Vtodo &vtodo);

private:
    string uid;
    string summary;
    Date dtstamp; //creation date
    Date dtstart;
    Date completed;
    Date due; //expiration date, not mandatory

};


#endif //QTCREATORTEST_VTODO_H
