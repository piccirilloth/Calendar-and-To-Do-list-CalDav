//
// Created by oscar on 30/10/21.
//

#include "Headers/API.h"

std::string API::IPADDRESS = "192.168.1.7";
std::string API::username = "";
std::string API::password = "";
bool API::loggedIn = false;
std::list<std::string> API::calendarNames;

API::API() {}

std::string API::login(std::string const &username, std::string const &password) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Depth: 1");
    headers.push_back("Prefer: return-minimal");
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    body = "<d:propfind xmlns:d=\"DAV:\" xmlns:cs=\"http://calendarserver.org/ns/\" xmlns:c=\"urn:ietf:params:icsText:ns:caldav\">\n"
           "  <d:prop>\n"
           "     <d:resourcetype />\n"
           "     <d:displayname />\n"
           "     <cs:getctag />\n"
           "     <c:supported-calendar-component-set />\n"
           "  </d:prop>\n"
           "</d:propfind>";
    try {
        handle.setOpt(curlpp::Options::Url(std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PROPFIND"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return str.str();
}

void API::setParamsAfterLogin(const std::string &user, const std::string &pwd, std::string const &response) {
    {
        std::lock_guard<std::mutex> lg(m);
        IcsParser parser(response);
        API::username = user;
        API::password = pwd;
        API::loggedIn = true;
    }
    clearCalendars(); //todo: add a function in api to set these parameters
    std::list<std::string> names = retrieveAllCalendars(); //return only calendar names

    for(std::string const &value : names) {
        addCalendar(value);
    }
}

std::list<std::string> API::retrieveAllCalendars() {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    std::list<std::string> calendarNames;

    headers.push_back("Depth: 1");
    headers.push_back("Prefer: return-minimal");
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    body = "<d:propfind xmlns:d=\"DAV:\" xmlns:cs=\"http://calendarserver.org/ns/\" xmlns:c=\"urn:ietf:params:icsText:ns:caldav\">\n"
           "  <d:prop>\n"
           "     <d:resourcetype />\n"
           "     <d:displayname />\n"
           "     <cs:getctag />\n"
           "     <c:supported-calendar-component-set />\n"
           "  </d:prop>\n"
           "</d:propfind>";
    try {
        handle.setOpt(curlpp::Options::Url(std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PROPFIND"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::string res = str.str();
        calendarNames = getNames(res);
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return calendarNames;
}

std::list<std::string> API::getNames(std::string const &result) {
    std::list<std::string> calendarNames;
    int pos = -1;
    std::string link = "calendarserver.php/calendars/" + username + "/";
    const char *response = result.data();
    int len = link.length();
    while((pos = result.find(link, pos+1)) != std::string::npos) {
        std::string name = "";
        int i=pos;
        if(response[i+len] == '<')
            continue;
        while(response[i+len] != '/') {
            name.push_back(response[i + len]);
            i++;
        }
        if(name != "inbox" && name != "outbox")
            calendarNames.push_back(name);
    }
    return calendarNames;
}

void API::createEmptyCalendar(std::string const &calendarName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName)));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_DIGEST));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("MKCALENDAR"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << str.str() << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}

/*void API::createEmptyIcs(std::string const &calendarName) {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/calendar; charset=utf-8");
    body = "BEGIN:VCALENDAR\r\n"
           "VERSION:2.0\r\n"
           "CALSCALE:GREGORIAN\r\n"
           "END:VCALENDAR\r\n";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName + "/cal.ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PUT"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}*/

std::list<std::string> API::deleteCalendar(const std::string &name) {
    {
        std::lock_guard<std::mutex> lg(m);
        curlpp::Cleanup init;
        curlpp::Easy handle;
        std::ostringstream str;
        try {
            handle.setOpt(curlpp::Options::Url(
                    std::string(
                            "http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + name +
                            "/")));
            handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
            handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
            handle.setOpt(new curlpp::Options::CustomRequest("DELETE"));
            handle.setOpt(curlpp::Options::WriteStream(&str));
            handle.perform();
        }
        catch (cURLpp::RuntimeError &e) {
            std::cout << e.what() << std::endl;
        }
        catch (cURLpp::LogicError &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return retrieveAllCalendars();
}

Vcalendar API::downloadCalendarObjects(std::string const &calendarName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    headers.push_back("Depth: 1");
    headers.push_back("Prefer: return-minimal");
    body = "<c:calendar-query xmlns:d=\"DAV:\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\">\n"
           "    <d:prop>\n"
           "        <d:getetag />\n"
           "        <c:calendar-data />\n"
           "    </d:prop>\n"
           "    <c:filter>\n"
           "        <c:comp-filter name=\"VCALENDAR\" />\n"
           "    </c:filter>\n"
           "</c:calendar-query>";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName)));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("REPORT"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    IcsParser parser(str.str());
    Vcalendar ret;
    parser.getVCalendar(std::ref(ret));
    ret.setName(calendarName);
    return ret;
}

void API::deleteIcs(const std::string &uid, std::string const &calName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::ostringstream str;
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calName + "/" + uid + ".ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("DELETE"));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}

void API::createEvent(const std::string &summary, const Date &startDate, const Date &endDate, Vcalendar const &cal) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/calendar; charset=utf-8");
    Date now;
    now.SetToNow();
    body = "BEGIN:VCALENDAR\r\n"
           "VERSION:" + cal.getVersion() + "\r\n"
           "PRODID:" + cal.getProdid() +"\r\n"
           "BEGIN:VEVENT\r\n"
           "SEQUENCE:0\r\n"
           "UID:" + std::to_string(cal.getNextUid()) + "\r\n"
           "DTSTAMP:" + static_cast<std::string>(now) + "\r\n"
           "DTSTART:" + static_cast<std::string>(startDate) +"\r\n"
           "DTEND:" + static_cast<std::string>(endDate) + "\r\n"
           "TRANSP:OPAQUE\r\n"
           "SUMMARY:" + summary + "\r\n"
           "END:VEVENT\r\n"
           "END:VCALENDAR\r\n";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + cal.getName() + "/" + std::to_string(cal.getNextUid()) + ".ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PUT"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << str.str() << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}

void API::updateEvent(std::string const &summary, Date const &startDate, Date const &endDate, std::string const &uid, Vcalendar const &cal) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/calendar; charset=utf-8");
    Date now;
    now.SetToNow();
    body =  "BEGIN:VCALENDAR\r\n"
            "VERSION:" + cal.getVersion() + "\r\n"
            "PRODID:" + cal.getProdid() +"\r\n"
            "BEGIN:VEVENT\r\n"
            "SEQUENCE:0\r\n"
            "UID:" + uid + "\r\n"
            "DTSTAMP:" + static_cast<std::string>(now) + "\r\n"
            "DTSTART:" + static_cast<std::string>(startDate) +"\r\n"
            "DTEND:" + static_cast<std::string>(endDate) + "\r\n"
            "TRANSP:OPAQUE\r\n"
            "SUMMARY:" + summary + "\r\n"
            "END:VEVENT\r\n"
            "END:VCALENDAR\r\n";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + cal.getName() + "/" + uid + ".ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PUT"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << str.str() << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}

void API::createTodo(const std::string &summary, const std::string &dueDate, const Vcalendar &cal) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/calendar; charset=utf-8");
    Date now;
    now.SetToNow();
    body = "BEGIN:VCALENDAR\r\n"
           "VERSION:" + cal.getVersion() + "\r\n"
           "PRODID:" + cal.getProdid() + "\r\n"
           "BEGIN:VTODO\r\n"
           "UID:" + std::to_string(cal.getNextUid()) + "\r\n"
           "SUMMARY:" + summary + "\r\n"
           "DUE:" + static_cast<std::string>(dueDate) + "\r\n"
           "DTSTAMP:" + static_cast<std::string>(now) + "\r\n"
           "END:VTODO\r\n"
           "END:VCALENDAR\r\n";                                                                                                                                                                                                                                                            "END:VCALENDAR\r\n";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + cal.getName() + "/" + std::to_string(cal.getNextUid()) + ".ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PUT"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << str.str() << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}

void API::updateTodo(const std::string &summary, const Date &dueDate, bool completed, const Vcalendar &cal, const Date &oldComplete, std::string const &uid) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/calendar; charset=utf-8");
    Date now;
    now.SetToNow();
    body = "BEGIN:VCALENDAR\r\n"
           "VERSION:" + cal.getVersion() + "\r\n"
           "PRODID:" + cal.getProdid() + "\r\n"
           "BEGIN:VTODO\r\n"
           "UID:" + uid+ "\r\n"
           "SUMMARY:" + summary + "\r\n"
           "DUE:" + static_cast<std::string>(dueDate) + "\r\n"
           "DTSTAMP:" + static_cast<std::string>(now) + "\r\n";
    if(static_cast<std::string>(oldComplete) == "00000000" && completed)
        body += "COMPLETED:" + static_cast<std::string>(now) + "\r\n";
    else if(completed)
        body += "COMPLETED:" + static_cast<std::string>(oldComplete) + "\r\n";
    body += "END:VTODO\r\n"
            "END:VCALENDAR\r\n";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + cal.getName() + "/" + uid + ".ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PUT"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << str.str() << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}
