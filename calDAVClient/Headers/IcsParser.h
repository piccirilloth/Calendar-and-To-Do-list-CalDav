//
// Created by oscar on 12/11/21.
//

#ifndef QTCREATORTEST_ICSPARSER_H
#define QTCREATORTEST_ICSPARSER_H
#include <iostream>
#include "Vcalendar.h"

class IcsParser {
private:
    std::string icsFile;
public:
    IcsParser();
    IcsParser(std::string icsFile);
    void getVCalendar(Vcalendar &calendar);
    std::string getIcsFileVevent(Vcalendar const &calendar, const std::string &uid);
    std::string getIcsFileVtodo(Vcalendar const &calendar, const std::string &uid);
};


#endif //QTCREATORTEST_ICSPARSER_H
