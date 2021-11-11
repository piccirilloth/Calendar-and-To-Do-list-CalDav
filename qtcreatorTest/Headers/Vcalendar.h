//
// Created by picci on 27/10/2021.
//

#ifndef QTCREATORTEST_VCALENDAR_H
#define QTCREATORTEST_VCALENDAR_H

#include "Date.h"
#include "Vevent.h"
#include "Vtodo.h"
#include <list>

class Vcalendar {
private:
    std::string icsText;
    std::string name;
    std::string etag;
    std::string version;
    std::string prodid;
    std::string calscale;
    std::list<Vevent> events;
    std::list<Vtodo> todos;
public:
    Vcalendar(std::string const &obj);
    std::string getName();
};


#endif //QTCREATORTEST_VCALENDAR_H
