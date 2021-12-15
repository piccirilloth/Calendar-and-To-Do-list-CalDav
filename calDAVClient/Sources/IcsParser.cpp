//
// Created by oscar on 12/11/21.
//

#include "Headers/IcsParser.h"

#include <utility>

IcsParser::IcsParser(std::string icsFile): icsFile(std::move(icsFile)) { }
IcsParser::IcsParser() { }

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
    COMPLETED,
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
    else if (input == "COMPLETED")
        return COMPLETED;
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

            case COMPLETED:
                tmp = getAttributeValue(resp, pos);
                res.setCompleted(tmp);
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

    if (pos != std::string::npos) {
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
                        if((pos = icsFile.find("VCALENDAR", pos)) == std::string::npos)
                            end = true;
                        else
                            pos += 10;
                        break;
                    }
                    break;

                default :
                    getAttributeValue(icsFile, &pos);
            }
        }
    }
    long max = -1;
    for(const Vevent& ev : calendar.getEvents()) {
        long v = std::stol(ev.getUid());
        if(v > max)
            max = v;
    }
    for(const Vtodo& td : calendar.getTodos()) {
        long v = std::stol(td.getUid());
        if(v > max)
            max = v;
    }
    calendar.setNextUid(max+1);
}

std::string IcsParser::getIcsFileVevent(const Vcalendar &calendar, const std::string &uid) {
    Vevent event;
    bool found = false;
    for(const Vevent& ev : calendar.getEvents())
        if(ev.getUid() == uid) {
            found = true;
            event = ev;
        }
    if(!found)
        return ""; //error
    std::string retValue = "BEGIN:VCALENDAR\r\n";
    if(!calendar.getVersion().empty())
        retValue.append("VERSION:" + calendar.getVersion() + "\r\n");
    if(!calendar.getProdid().empty())
        retValue.append("PRODID:" + calendar.getProdid() + "\r\n");
    retValue.append("BEGIN:VEVENT\r\n");
    if(!event.getUid().empty())
        retValue.append("UID:" + event.getUid() + "\r\n");
    if(!event.getSequence().empty())
        retValue.append("SEQUENCE:" + event.getSequence() + "\r\n");
    if(static_cast<std::string>(event.getDtstamp()) != "00000000")
        retValue.append("DTSTAMP:" + static_cast<std::string>(event.getDtstamp()) + "\r\n");
    if(static_cast<std::string>(event.getDtstart()) != "00000000")
        retValue.append("DTSTART:" + static_cast<std::string>(event.getDtstart()) + "\r\n");
    if(static_cast<std::string>(event.getDtend()) != "00000000")
        retValue.append("DTEND:" + static_cast<std::string>(event.getDtend()) + "\r\n");
    if(!event.getTransp().empty())
        retValue.append("TRANSP:" + event.getTransp() + "\r\n");
    if(!event.getSummary().empty())
        retValue.append("SUMMARY:" + event.getSummary() + "\r\n");
    retValue.append("END:VEVENT\r\n");
    retValue.append("END:VCALENDAR\r\n");
    return retValue;
}

std::string IcsParser::getIcsFileVtodo(const Vcalendar &calendar, const std::string &uid) {
    Vtodo todo;
    bool found = false;
    for(const Vtodo& td : calendar.getTodos())
        if(td.getUid() == uid) {
            found = true;
            todo = td;
        }
    if(!found)
        return "";
    std::string retValue = "BEGIN:VCALENDAR\r\n";
    if(!calendar.getVersion().empty())
        retValue.append("VERSION:" + calendar.getVersion() + "\r\n");
    if(!calendar.getProdid().empty())
        retValue.append("PRODID:" + calendar.getProdid() + "\r\n");
    retValue.append("BEGIN:VTODO\r\n");
    if(!todo.getUid().empty())
        retValue.append("UID:" + todo.getUid() + "\r\n");
    if(static_cast<std::string>(todo.getDtstamp()) != "00000000")
        retValue.append("DTSTAMP:" + static_cast<std::string>(todo.getDtstamp()) + "\r\n");
    if(static_cast<std::string>(todo.getDtstart()) != "00000000")
        retValue.append("DTSTART:" + static_cast<std::string>(todo.getDue()) + "\r\n");
    if(static_cast<std::string>(todo.getDue()) != "00000000")
        retValue.append("DTDUE:" + static_cast<std::string>(todo.getDtstart()) + "\r\n");
    if(static_cast<std::string>(todo.getCompleted()) != "00000000")
        retValue.append("DTCOMPLETED:" + static_cast<std::string>(todo.getCompleted()) + "\r\n");
    if(!todo.getSummary().empty())
        retValue.append("SUMMARY:" + todo.getSummary() + "\r\n");
    retValue.append("END:VTODO\r\n");
    retValue.append("END:VCALENDAR\r\n");
    return retValue;
}



