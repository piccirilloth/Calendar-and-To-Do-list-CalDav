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
    IcsParser(std::string const &icsFile);
    IcsParser(Vcalendar const &calendar);
    void getVCalendar(Vcalendar &calendar);
    std::string getIcsFile(Vcalendar const &calendar);

};


#endif //QTCREATORTEST_ICSPARSER_H
