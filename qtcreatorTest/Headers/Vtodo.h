//
// Created by picci on 27/10/2021.
//

#ifndef QTCREATORTEST_VTODO_H
#define QTCREATORTEST_VTODO_H

#include "Date.h"

class Vtodo {
private:
    string uid;
    string summary;
    Date dtstamp; //creation date
    Date dtstart;
    Date completed;
    Date due; //expiration date, not mandatory
    int priority;
public:
    Vtodo(string uid, string summary, Date dtstamp);
};


#endif //QTCREATORTEST_VTODO_H
