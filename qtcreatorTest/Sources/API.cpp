//
// Created by oscar on 30/10/21.
//

#include "Headers/API.h"

API::API(std::string IPADDRESS): IPADDRESS(IPADDRESS) {}

std::string API::login(std::string const &username, std::string const &password) {
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
        handle.setOpt(curlpp::Options::Url(std::string("http://" + IPADDRESS + "/progetto/calendarserver.php/calendars/" + username + "/home/")));
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
    return str.str();
}