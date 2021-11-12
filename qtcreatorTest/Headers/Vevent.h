//
// Created by picci on 27/10/2021.
//

#ifndef QTCREATORTEST_VEVENT_H
#define QTCREATORTEST_VEVENT_H

#include "Date.h"

class Vevent {
private:
    std::string uid;
    std::string sequence;
    Date dtstamp; //creation date
    Date dtstart; //date when the event starts
    Date dtend;
    std::string transp;
    std::string summary;
    std::string duration;
public:
    Vevent() {};

    const string &getUid() const;

    void setUid(const string &uid);

    const string &getSequence() const;

    void setSequence(const string &sequence);

    const Date &getDtstamp() const;

    void setDtstamp(const Date &dtstamp);

    const Date &getDtstart() const;

    void setDtstart(const Date &dtstart);

    const Date &getDtend() const;

    void setDtend(const Date &dtend);

    const string &getTransp() const;

    void setTransp(const string &transp);

    const string &getSummary() const;

    void setSummary(const string &summary);

    const string &getDuration() const;

    void setDuration(const string &duration);
};


#endif //QTCREATORTEST_VEVENT_H
