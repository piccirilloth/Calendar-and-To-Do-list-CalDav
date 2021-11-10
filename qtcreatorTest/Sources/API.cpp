//
// Created by oscar on 30/10/21.
//

#include "Headers/API.h"

std::string API::IPADDRESS = "192.168.1.7";
std::string API::username = "";
std::string API::password = "";
bool API::loggedIn = false;
std::list<Vcalendar> API::calendars;

API::API() {}

std::string API::login(std::string const &username, std::string const &password) {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Depth: 1");
    headers.push_back("Prefer: return-minimal");
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    body = "<d:propfind xmlns:d=\"DAV:\" xmlns:cs=\"http://calendarserver.org/ns/\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\">\n"
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

std::list<std::string> API::retrieveAllCalendars() {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    std::list<std::string> calendarNames;
    std::string link = "calendarserver.php/calendars/" + username + "/";
    headers.push_back("Depth: 1");
    headers.push_back("Prefer: return-minimal");
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    body = "<d:propfind xmlns:d=\"DAV:\" xmlns:cs=\"http://calendarserver.org/ns/\" xmlns:c=\"urn:ietf:params:xml:ns:caldav\">\n"
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
        int pos = -1;
        std::string res = str.str();
        char *response = res.data();
        int len = link.length();
        while((pos = res.find(link, pos+1)) != std::string::npos) {
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
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return calendarNames;
}

void API::createCalendar(std::string const &calendarName) {
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

std::list<std::string> API::deleteCalendar(const std::string &name) {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::ostringstream str;
    handle.setOpt(curlpp::Options::Url(
            std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/" + name + "/")));
    handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
    handle.setOpt(new curlpp::options::UserPwd(username + ":" + password));
    handle.setOpt(new curlpp::Options::CustomRequest("DELETE"));
    handle.setOpt(curlpp::Options::WriteStream(&str));
    handle.perform();
    return retrieveAllCalendars();
}
