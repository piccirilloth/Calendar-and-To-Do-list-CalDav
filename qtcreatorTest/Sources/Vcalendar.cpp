//
// Created by picci on 27/10/2021.
//

#include <iostream>
#include "Headers/Vcalendar.h"

Vcalendar::Vcalendar() {
    name = "";
}

Vcalendar::Vcalendar(std::string const &name, std::string const &prodId, std::string const version): name(name), prodid(prodId), version(version) { }

void Vcalendar::addEvent(const Vevent &event) {
    events.push_back(event);
}

void Vcalendar::addTodo(const Vtodo &todo) {
    todos.push_back(todo);
}

std::string Vcalendar::getName() const {
    return name;
}

const string &Vcalendar::getIcsText() const {
    return icsText;
}

const string &Vcalendar::getEtag() const {
    return etag;
}

const string &Vcalendar::getVersion() const {
    return version;
}

const string &Vcalendar::getProdid() const {
    return prodid;
}

const string &Vcalendar::getCalscale() const {
    return calscale;
}

const list<Vevent> &Vcalendar::getEvents() const {
    return events;
}

const list<Vtodo> &Vcalendar::getTodos() const {
    return todos;
}

void Vcalendar::setIcsText(const string &icsText) {
    Vcalendar::icsText = icsText;
}

void Vcalendar::setName(const string &name) {
    Vcalendar::name = name;
}

void Vcalendar::setEtag(const string &etag) {
    Vcalendar::etag = etag;
}

void Vcalendar::setVersion(const string &version) {
    Vcalendar::version = version;
}

void Vcalendar::setProdid(const string &prodid) {
    Vcalendar::prodid = prodid;
}

void Vcalendar::setCalscale(const string &calscale) {
    Vcalendar::calscale = calscale;
}

void Vcalendar::setEvents(const list<Vevent> &events) {
    Vcalendar::events = events;
}

void Vcalendar::setTodos(const list<Vtodo> &todos) {
    Vcalendar::todos = todos;
}

ostream &operator<<(ostream &os, const Vcalendar &vcal) {
    os << "VERSION:" << vcal.getVersion() << '\n';
    os << "CALSCALE:" << vcal.getCalscale() << '\n';
    os << "PRODID:" << vcal.getProdid() << '\n';
    for (Vtodo todo: vcal.getTodos())
        os << todo.getUid() << '\n';
    for (Vevent event: vcal.getEvents())
        os << event.getUid() << '\n';
    return os;
}

long Vcalendar::getNextUid() const {
    return nextUid;
}

void Vcalendar::setNextUid(long nextUid) {
    Vcalendar::nextUid = nextUid;
}

void Vcalendar::clear() {
    todos.clear();
    events.clear();
}

const string &Vcalendar::getOrganizer() const {
    return organizer;
}

void Vcalendar::setOrganizer(const string &organizer) {
    Vcalendar::organizer = organizer;
}
