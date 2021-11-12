//
// Created by picci on 27/10/2021.
//

#ifndef QTCREATORTEST_VEVENT_H
#define QTCREATORTEST_VEVENT_H

#include "Date.h"

class Vevent {
private:
    Date dtstamp; //creation date
    Date dtstart; //date when the event starts
    string uid;
    string summary;
    string description;
    // string description;
    Date dtend;
public:
    Vevent();
};


#endif //QTCREATORTEST_VEVENT_H
