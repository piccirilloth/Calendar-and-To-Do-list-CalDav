//
// Created by oscar on 30/10/21.
//

#include "Headers/API.h"

std::string API::IPADDRESS = "192.168.1.10";
std::string API::username = "";
std::string API::password = "";
bool API::loggedIn = false;
std::list<std::string> API::calendarNames;

API::API() {}

std::string API::lockResource(const std::string &calendarName, const std::string &icsName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/xml; charset=\"utf-8\"");

    body = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
           "<d:lockinfo xmlns:d=\"DAV:\">"
           "<d:lockscope><d:exclusive/></d:lockscope>"
           "<d:locktype><d:write/></d:locktype>"
           "<d:owner>"
           "<d:href>http://" + IPADDRESS + "/progetto/calendarserver.php/principals/" + username + "/</d:href>"
           "</d:owner>"
           "</d:lockinfo>";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName + "/" + icsName)));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("LOCK"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << str.str() << '\n';
        //searching token
        std::string src = str.str();
        int pos = str.str().find("opaquelocktoken");
        pos += 16;
        std::string tmp("");
        bool end = false;
        while (!end) {
            tmp += src[pos++];
            if (src[pos] == '<')
                end = true;
        }
        std::cout << tmp << '\n';
        return tmp;
    }

    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
        return "";
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
        return "";
    }
}

void API::unlockResource(const std::string &calendarName, const std::string &token, const std::string &icsName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/xml; charset=\"utf-8\"");
    headers.push_back("Lock-Token: <opaquelocktoken:" + token + ">");

    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName + "/" + icsName)));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("UNLOCK"));
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
    std::lock_guard<std::mutex> lg(m);
    for(std::string const &value : names) {
        calendarNames.push_back(value);
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

long API::createEmptyCalendar(std::string const &calendarName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n"
                       "   <C:mkcalendar xmlns:D=\"DAV:\"\n"
                       "                 xmlns:C=\"urn:ietf:params:xml:ns:caldav\">\n"
                       "     <D:set>\n"
                       "       <D:prop>\n"
                       "         <D:displayname>" + calendarName + "</D:displayname>\n"
                       "       </D:prop>\n"
                       "     </D:set>\n"
                       "   </C:mkcalendar>";
    std::ostringstream str;
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    long http_code = 0;
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
        http_code = curlpp::infos::ResponseCode::get(handle);
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return http_code;
}

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
    std::string organizer = getOrganizer(calendarName);
    ret.setName(calendarName);
    ret.setOrganizer(organizer);
    return ret;
}

long API::deleteIcs(const std::string &uid, std::string const &calName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::ostringstream str;
    long http_code = 0;
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calName + "/" + uid + ".ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("DELETE"));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        http_code = curlpp::infos::ResponseCode::get(handle);
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return http_code;
}

long API::createEvent(const std::string &summary, const Date &startDate, const Date &endDate, Vcalendar const &cal) {
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
    long http_code = 0;
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
        std::cout << http_code << '\n';
        http_code = curlpp::infos::ResponseCode::get(handle);
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return http_code;
}

long API::updateEvent(std::string const &summary, Date const &startDate, Date const &endDate, std::string const &uid, Vcalendar const &cal) {
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
    long http_code = 0;
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
        http_code = curlpp::infos::ResponseCode::get(handle);
        std::cout << http_code << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return http_code;
}

long API::createTodo(const std::string &summary, const std::string &dueDate, const Vcalendar &cal) {
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
    long http_code = 0;
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
        http_code = curlpp::infos::ResponseCode::get(handle);
        std::cout << http_code << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return http_code;
}

long API::updateTodo(const std::string &summary, const Date &dueDate, bool completed, const Vcalendar &cal, const Date &oldComplete, std::string const &uid) {
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
    long http_code = 0;
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
        std::cout << http_code << '\n';
        http_code = curlpp::infos::ResponseCode::get(handle);
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return http_code;
}

long API::shareCalendar(const std::string &mail, const std::string &comment, const std::string &accessPolicy, const std::string &calendarName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: application/davsharing+xml; charset=\"utf-8\"");
    long http_code = 0;
    body =  "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
            "<D:share-resource xmlns:D=\"DAV:\">\n"
            "    <D:sharee>\n"
            "        <D:href>mailto:" + mail + "</D:href>\n"
            "        <D:prop>\n"
            "            <D:displayname>" + "shared by " + username + "</D:displayname>\n"
            "        </D:prop>\n"
            "        <D:comment>" + comment + "</D:comment>\n"
            "        <D:share-access>\n"
            "            <D:" + accessPolicy + " />\n"
            "        </D:share-access>\n"
            "    </D:sharee>\n"
            "    <D:prop>"
            "        <D:displayname />"
            "    </D:prop>"
            "</D:share-resource>";
    try {
        handle.setOpt(curlpp::Options::Url(std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName + "/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("POST"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        http_code = curlpp::Infos::ResponseCode::get(handle);
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return http_code;
}

bool API::isShared(const std::string &calendarName, std::string &displayName) {
    std::lock_guard<std::mutex> lg(m);
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    bool shared;
    headers.push_back("Depth: 0");
    headers.push_back("Prefer: return-minimal");
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    body = "<d:propfind xmlns:d=\"DAV:\">\n"
           "  <d:prop>\n"
           "    <d:resourcetype />"
           "    <d:displayname />"
           "  </d:prop>\n"
           "</d:propfind>";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName + "/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PROPFIND"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::string res = str.str();
        if(res.find("cs:shared-owner") == std::string::npos)
            shared = true;
        else
            shared = false;
        if(shared == true) {
            std::string disName = "<d:displayname>";
            int pos = res.find(disName);
            pos += disName.length(); //+1 for the space
            std::string result = "";
            char c;
            while((c = res[pos]) != '<') {
                result.push_back(c);
                pos++;
            }
            displayName = result;
        } else
            displayName = "";
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return shared;
}

std::string API::getOrganizer(const std::string &calendarName) {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    bool shared;
    headers.push_back("Depth: 0");
    headers.push_back("Prefer: return-minimal");
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    body = "<d:propfind xmlns:d=\"DAV:\" xmlns:cs=\"http://calendarserver.org/ns/\">\n"
           "<d:prop>"
           "    <cs:invite><cs:organizer /></cs:invite>"
           "</d:prop>"
           "</d:propfind>";
    std::string organizer = "";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + calendarName + "/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
        handle.setOpt(new curlpp::Options::CustomRequest("PROPFIND"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::string stringToSearch = "<cs:organizer><d:href>/progetto/calendarserver.php/principals/";
        std::string res = str.str();
        int pos = 0;
        if((pos = res.find(stringToSearch)) != std::string::npos) {
            pos += stringToSearch.length();
            while(res[pos] != '<') {
                organizer.push_back(res[pos]);
                pos++;
            }
        }
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return organizer;
}
