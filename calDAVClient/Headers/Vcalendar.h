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
    std::string name;
    std::string version;
    std::string prodid;
    std::string calscale;
    std::list<Vevent> events;
    std::list<Vtodo> todos;
    std::string organizer;
    long nextUid;
public:
    explicit Vcalendar(std::string const &name, std::string const &prodId, std::string const &version);
    Vcalendar();

    std::string getName() const;

    void addEvent(Vevent const &event);

    void addTodo(Vtodo const &todo);

    long getNextUid() const;

    void setNextUid(long nextUid);

    const string &getVersion() const;

    const string &getProdid() const;

    const string &getCalscale() const;

    const list <Vevent> &getEvents() const;

    const list <Vtodo> &getTodos() const;

    friend ostream& operator<<(ostream &os, const Vcalendar &vcal);

    void setName(const string &name);

    void setVersion(const string &version);

    const string &getOrganizer() const;

    void setOrganizer(const string &organizer);

    void setProdid(const string &prodid);

    void setCalscale(const string &calscale);

    void setEvents(const list <Vevent> &events);

    void setTodos(const list <Vtodo> &todos);
    
    void clear();


};


#endif //QTCREATORTEST_VCALENDAR_H
