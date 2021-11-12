//
// Created by picci on 27/10/2021.
//

#include "Headers/Vtodo.h"


Vtodo::Vtodo(string uid, string summary, Date dtstamp): uid(uid), summary(summary), dtstamp(dtstamp) { }

const string &Vtodo::getUid() const {
    return uid;
}

void Vtodo::setUid(const string &uid) {
    Vtodo::uid = uid;
}

const string &Vtodo::getSummary() const {
    return summary;
}

void Vtodo::setSummary(const string &summary) {
    Vtodo::summary = summary;
}

const Date &Vtodo::getDtstamp() const {
    return dtstamp;
}

void Vtodo::setDtstamp(const Date &dtstamp) {
    Vtodo::dtstamp = dtstamp;
}

const Date &Vtodo::getDtstart() const {
    return dtstart;
}

void Vtodo::setDtstart(const Date &dtstart) {
    Vtodo::dtstart = dtstart;
}

const Date &Vtodo::getCompleted() const {
    return completed;
}

void Vtodo::setCompleted(const Date &completed) {
    Vtodo::completed = completed;
}

const Date &Vtodo::getDue() const {
    return due;
}

void Vtodo::setDue(const Date &due) {
    Vtodo::due = due;
}

int Vtodo::getPriority() const {
    return priority;
}

void Vtodo::setPriority(int priority) {
    Vtodo::priority = priority;
}

ostream& operator << (ostream &os, const Vtodo &vtodo) {
    os << "ano";
    return os;
}

