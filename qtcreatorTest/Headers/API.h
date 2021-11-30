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
#include "../curlpp-0.8.1/include/curlpp/Infos.hpp"
#include "Vcalendar.h"
#include "IcsParser.h"
#include <QDate>
#include <mutex>
#include <condition_variable>

class API {
private:
    static std::string IPADDRESS;
    static std::string username;
    static std::string password;
    static bool loggedIn;
    static std::list<std::string> calendarNames;
    std::mutex m;
    //std::condition_variable cv;
public:
    void addCalendar(std::string cal) {
        std::lock_guard<std::mutex> lg(m);
        calendarNames.push_back(cal);
    }

    std::list<std::string> getCalendars() {
        std::lock_guard<std::mutex> lg(m);
        return calendarNames;
    }

    void clearCalendars() {
        std::lock_guard<std::mutex> lg(m);
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
    std::string lockResource(std::string const &calendarName, const std::string &icsName = "");
    void unlockResource(std::string const &calendarName, std::string const &token, const std::string &icsName = "");

public:
    API();
    std::string login(std::string const &username, std::string const &password);
    void setParamsAfterLogin(std::string const &user, std::string const &pwd, std::string const &resposne);
    std::list<std::string> retrieveAllCalendars();
    long createEmptyCalendar(std::string const &calendarName);
    Vcalendar downloadCalendarObjects(std::string const &calendarName);
    std::list<std::string> deleteCalendar(std::string const &name);
    long deleteIcs(std::string const &uid, std::string const &calName);
    long createEvent(std::string const &summary, Date const &startDate, Date const &endDate, Vcalendar const &cal);
    long updateEvent(std::string const &summary, Date const &startDate, Date const &endDate, std::string const &uid, Vcalendar const &cal);
    long createTodo(std::string const &summary, std::string const &dueDate, Vcalendar const &cal);
    long updateTodo(std::string const &summary, Date const &dueDate, bool completed, Vcalendar const &cal, Date const & oldComplete, std::string const &uid);
    long shareCalendar(std::string const &displayName, std::string const &mail, std::string const &comment, const std::string &calendarName);
    bool isShared(std::string const &calendarName, std::string &displayName);
};


#endif //QTCREATORTEST_API_H