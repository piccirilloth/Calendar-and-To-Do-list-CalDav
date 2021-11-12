//
// Created by oscar on 12/11/21.
//

#include "Headers/IcsParser.h"

IcsParser::IcsParser(const std::string &icsFile): icsFile(icsFile) { }

enum CalendarAttributes {
    VERSION,
    CALSCALE,
    PRODID,
    BEGIN,
    ENDCALENDAR,
    NOCALENDARATTR
};

enum TodoAttributes {
    UID_TODO,
    SUMMARY_TODO,
    DUE,
    DTSTAMP_TODO,
    ENDTODO,
    NOTODOATTR
};

enum EventAttributes {
    UID_EVENT,
    SEQUENCE,
    DTSTAMP_EVENT,
    DTSTART,
    DTEND,
    TRANSP,
    SUMMARY_EVENT,
    DURATION,
    ENDEVENT,
    NOEVENTATTR
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
        return UID_TODO;
    else if (input == "SUMMARY")
        return SUMMARY_TODO;
    else if (input == "DUE")
        return DUE;
    else if (input == "DTSTAMP")
        return DTSTAMP_TODO;
    else if (input == "END")
        return ENDTODO;
    return NOTODOATTR;
}

EventAttributes resolveEventOption(const std::string &input) {
    if(input == "UID")
        return UID_EVENT;
    else if(input == "SEQUENCE")
        return SEQUENCE;
    else if(input == "DTSTAMP")
        return DTSTAMP_EVENT;
    else if(input == "DTSTART")
        return DTSTART;
    else if(input == "DTEND")
        return DTEND;
    else if(input == "TRANSP")
        return TRANSP;
    else if(input == "SUMMARY")
        return SUMMARY_EVENT;
    else if(input == "DURATION")
        return DURATION;
    else if(input == "END")
        return ENDEVENT;
    return NOEVENTATTR;
}

std::string getAttributeValue(const std::string &resp, int *pos) {
    std::string tmp;
    while (resp[*pos] != '\n') {
        tmp.push_back(resp[*pos]);
        (*pos)++;
    }
    (*pos)++; // \n
    return tmp;
}

Vevent getNextEvent(const std::string &resp, int *pos) {
    Vevent res;
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
        switch (resolveEventOption(attribute)) {
            case UID_EVENT :
                res.setUid(getAttributeValue(resp, pos));
                break;

            case SUMMARY_EVENT :
                res.setSummary(getAttributeValue(resp, pos));
                break;

            case SEQUENCE :
                res.setSequence(getAttributeValue(resp, pos));
                break;

            case DTSTAMP_EVENT :
                tmp = getAttributeValue(resp, pos);
                res.setDtstamp(tmp);
                break;

            case DTSTART :
                tmp = getAttributeValue(resp, pos);
                res.setDtstart(tmp);
                break;

            case DTEND:
                tmp = getAttributeValue(resp, pos);
                res.setDtend(tmp);
                break;

            case TRANSP:
                res.setTransp(getAttributeValue(resp, pos));
                break;

            case DURATION:
                res.setDuration(getAttributeValue(resp, pos));
                break;

            case ENDEVENT :
                end = true;
                getAttributeValue(resp, pos);
                break;

            default :
                getAttributeValue(resp, pos);
        }
    }
    return res;
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
        switch (resolveTodoOption(attribute)) {
            case UID_TODO :
                res.setUid(getAttributeValue(resp, pos));
                break;

            case SUMMARY_TODO :
                res.setSummary(getAttributeValue(resp, pos));
                break;

            case DUE :
                tmp = getAttributeValue(resp, pos);
                res.setDue(tmp);
                break;

            case DTSTAMP_TODO :
                tmp = getAttributeValue(resp, pos);
                res.setDtstamp(tmp);
                break;

            case ENDTODO :
                end = true;
                getAttributeValue(resp, pos);
                break;

            default :
                getAttributeValue(resp, pos);
        }
    }
    return res;
}

void IcsParser::getVCalendar(Vcalendar &calendar) {
    std::string attribute;
    std::string value;
    bool end = false;
    int pos = icsFile.find("VCALENDAR");

    if (pos != std::string::npos) { //ToDo fixare while anzichè if
        pos += 10;
        while (!end) {
            attribute = "";
            while (icsFile[pos] != ':')
                attribute.push_back(icsFile[pos++]);
            pos++; // \n
            switch (resolveCalendarOption(attribute)) {
                case VERSION :
                    value = getAttributeValue(icsFile, &pos);
                    calendar.setVersion(value);
                    break;

                case CALSCALE :
                    value = getAttributeValue(icsFile, &pos);
                    calendar.setCalscale(value);
                    break;

                case PRODID :
                    value = getAttributeValue(icsFile, &pos);
                    calendar.setProdid(value);
                    break;

                case BEGIN :
                    value = getAttributeValue(icsFile, &pos);
                    if (value == "VTODO")
                        calendar.addTodo(getNextTodo(icsFile, &pos));
                    else if(value == "VEVENT")
                        calendar.addEvent(getNextEvent(icsFile, &pos));
                    break;

                case ENDCALENDAR :
                    value = getAttributeValue(icsFile, &pos);
                    if (value == "VCALENDAR") {
                        end = true;
                        break;
                    }
                    break;

                default :
                    getAttributeValue(icsFile, &pos);
            }
        }
    }
}


