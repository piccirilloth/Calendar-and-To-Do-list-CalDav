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
        while((pos = res.find(link, pos+1)) != std::string::npos) {
            std::string name = "";
            int i=pos;
            if(response[i+link.length()] == '<')
                continue;
            while(response[i+link.length()] != '/') {
                name.push_back(response[i + link.length()]);
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