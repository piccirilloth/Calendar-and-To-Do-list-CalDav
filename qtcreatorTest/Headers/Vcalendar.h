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
    explicit Vcalendar(std::string const &response);
    std::string getName();

    const string &getIcsText() const;

    const string &getEtag() const;

    const string &getVersion() const;

    const string &getProdid() const;

    const string &getCalscale() const;

    const list <Vevent> &getEvents() const;

    const list <Vtodo> &getTodos() const;

    friend ostream& operator<<(ostream &os, const Vcalendar &vcal);

};


#endif //QTCREATORTEST_VCALENDAR_H
