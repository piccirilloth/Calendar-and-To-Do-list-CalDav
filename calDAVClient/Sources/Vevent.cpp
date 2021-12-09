//
// Created by picci on 27/10/2021.
//

#include "Headers/Vevent.h"

const string &Vevent::getUid() const {
    return uid;
}

void Vevent::setUid(const string &uid) {
    Vevent::uid = uid;
}

const string &Vevent::getSequence() const {
    return sequence;
}

void Vevent::setSequence(const string &sequence) {
    Vevent::sequence = sequence;
}

const Date &Vevent::getDtstamp() const {
    return dtstamp;
}

void Vevent::setDtstamp(const Date &dtstamp) {
    Vevent::dtstamp = dtstamp;
}

const Date &Vevent::getDtstart() const {
    return dtstart;
}

void Vevent::setDtstart(const Date &dtstart) {
    Vevent::dtstart = dtstart;
}

const Date &Vevent::getDtend() const {
    return dtend;
}

void Vevent::setDtend(const Date &dtend) {
    Vevent::dtend = dtend;
}

const string &Vevent::getTransp() const {
    return transp;
}

void Vevent::setTransp(const string &transp) {
    Vevent::transp = transp;
}

const string &Vevent::getSummary() const {
    return summary;
}

void Vevent::setSummary(const string &summary) {
    Vevent::summary = summary;
}

const string &Vevent::getDuration() const {
    return duration;
}

void Vevent::setDuration(const string &duration) {
    Vevent::duration = duration;
}
