//
// Created by picci on 27/10/2021.
//

#include <iostream>
#include "Headers/Vcalendar.h"

//ToDo cambiare icsText con xml

enum CalendarAttributes {
    VERSION,
    CALSCALE,
    PRODID,
    BEGIN,
    ENDCALENDAR,
    NOCALENDARATTR
};

enum TodoAttributes {
    UID,
    SUMMARY,
    DUE,
    DTSTAMP,
    ENDTODO,
    NOTODOATTR
};

CalendarAttributes resolveCalendarOption(const std::string &input) {
    if (input == "VERSION")
        return VERSION;
    else if (input == "CALSCALE")
        return CALSCALE;
    else if (input == "PRODID")
        return PRODID;
    else if (input == "BEGIN")
        return BEGIN;
    else if (input == "END")
        return ENDCALENDAR;

    return NOCALENDARATTR;
}

TodoAttributes resolveTodoOption(const std::string &input) {
    if (input == "UID")
        return UID;
    else if (input == "SUMMARY")
        return SUMMARY;
    else if (input == "DUE")
        return DUE;
    else if (input == "DTSTAMP")
        return DTSTAMP;
    else if (input == "END")
        return ENDTODO;
    return NOTODOATTR;
}

std::string getAttributeValue(const std::string &resp, int *pos) {
    std::string tmp;
    while (resp[*pos] != '\n') {
        tmp.push_back(resp[*pos]);
        (*pos)++;
    }
    (*pos)++;
    return tmp;
}

Vtodo getNextTodo(const std::string &resp, int *pos) {
    Vtodo res;
    bool end = false;
    std::string attribute;
    std::string value;
    while (!end) {
        attribute = "";
        while (resp[*pos] != ':') {
            attribute.push_back(resp[*pos]);
            (*pos)++;
        }
        (*pos)++;
        Date tmp;
        switch(resolveTodoOption(attribute)) {
            case UID :
                res.setUid(getAttributeValue(resp, pos));
                std::cout << '\t' << attribute << ':' << res.getUid() << '\n';
                break;

            case SUMMARY :

                res.setSummary(getAttributeValue(resp, pos));
                std::cout << '\t' << attribute << ':' << res.getSummary() << '\n';
                break;
            case DUE :

                tmp = getAttributeValue(resp, pos);
                res.setDue(tmp);
                std::cout << '\t' << attribute << ':' << res.getDue() << '\n';

                break;

            case DTSTAMP :
                tmp = getAttributeValue(resp, pos);
                res.setDtstamp(tmp);
                std::cout << '\t' << attribute << ':' << res.getDtstamp() << '\n';
                break;

            case ENDTODO :
                end = true;
                break;

            default :
                getAttributeValue(resp, pos);
        }
    }
    return res;
}



Vcalendar::Vcalendar(std::string const &response) {
    //icsText = response; //TODO: change name with icsText
    std::string attribute;
    std::string value;
    bool end = false;
    int pos = response.find("VCALENDAR");

    if (pos != std::string::npos) { //ToDo fixare while anzichè if
        pos += 10;
        while (!end) {
            attribute = "";
            while (response[pos] != ':')
                attribute.push_back(response[pos++]);
            pos++;
            switch(resolveCalendarOption(attribute)) {
                case VERSION :
                    value = getAttributeValue(response, &pos);
                    version = value;
                    std::cout << value << '\n';
                    break;

                case CALSCALE :
                    value = getAttributeValue(response, &pos);
                    calscale = value;
                    std::cout << value << '\n';
                    break;

                case PRODID :
                    value = getAttributeValue(response, &pos);
                    prodid = value;
                    std::cout << value << '\n';
                    break;

                case BEGIN :
                    value = getAttributeValue(response, &pos);
                    if (value == "VTODO")
                        todos.push_back(getNextTodo(response, &pos));
                    break;

                case ENDCALENDAR :
                    value = getAttributeValue(response, &pos);
                    if (value == "VCALENDAR") {
                        end = true;
                        std::cout << attribute << ':' << value << '\n';
                        break;
                    }
                    std::cout << attribute << ':' << value << '\n';
                    break;

                default :
                    getAttributeValue(response, &pos);
            }
        }
    }
}

std::string Vcalendar::getName() {
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

ostream& operator<<(ostream &os, const Vcalendar &vcal) {
    os << "VERSION:" << vcal.getVersion() << '\n';
    os << "CALSCALE:" << vcal.getCalscale() << '\n';
    os << "PRODID:" << vcal.getProdid() << '\n';
    for (Vtodo todo : vcal.getTodos())
        os << todo << '\n';
    return os;
}
