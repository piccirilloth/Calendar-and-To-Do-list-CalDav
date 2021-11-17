//
// Created by oscar on 30/10/21.
//

#ifndef QTCREATORTEST_API_H
#define QTCREATORTEST_API_H

#include <iostream>
#include <sstream>
#include "../curlpp-0.8.1/include/curlpp/cURLpp.hpp"
#include "../curlpp-0.8.1/include/curlpp/Easy.hpp"
#include "../curlpp-0.8.1/include/curlpp/Options.hpp"
#include "../curlpp-0.8.1/include/curlpp/Exception.hpp"
#include "Vcalendar.h"
#include "IcsParser.h"

class API {
private:
    static std::string IPADDRESS;
    static std::string username;
    static std::string password;
    static bool loggedIn;
    static std::list<std::string> calendarNames;
public:
    void addCalendar(std::string cal) {
        calendarNames.push_back(cal);
    }

    std::list<std::string> getCalendars() {
        return calendarNames;
    }

    void clearCalendars() {
        calendarNames.clear();
    }

    const std::string &getIpaddress() const {
        return IPADDRESS;
    }

    void setIpaddress(const std::string &ipaddress) {
        IPADDRESS = ipaddress;
    }

    const std::string &getUsername() const {
        return username;
    }

    void setUsername(const std::string &username) {
        API::username = username;
    }

    const std::string &getPassword() const {
        return password;
    }

    void setPassword(const std::string &password) {
        API::password = password;
    }

    bool isLoggedIn() const {
        return loggedIn;
    }

    void setLoggedIn(bool loggedIn) {
        API::loggedIn = loggedIn;
    }

    //void createEmptyIcs(std::string const &calendarName);

    std::list<std::string> getNames(std::string const &result);

public:
    API();
    std::string login(std::string const &username, std::string const &password);
    std::list<std::string> retrieveAllCalendars();
    void createEmptyCalendar(std::string const &calendarName);
    Vcalendar downloadCalendarObjects(std::string const &calendarName);
    std::list<std::string> deleteCalendar(std::string const &name);
};


#endif //QTCREATORTEST_API_H