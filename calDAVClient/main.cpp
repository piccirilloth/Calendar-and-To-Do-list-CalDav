#include "Headers/mainwindow.h"

#include <QApplication>

#include <iostream>
#include <sstream>
#include "curlpp-0.8.1/include/curlpp/cURLpp.hpp"
#include "curlpp-0.8.1/include/curlpp/Easy.hpp"
#include "curlpp-0.8.1/include/curlpp/Options.hpp"
#include "curlpp-0.8.1/include/curlpp/Exception.hpp"
#include "Headers/API.h"
#include "Headers/IcsParser.h"
#include <Headers/Date.h>

std::string downloadCalendars() {
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
                std::string("http://192.168.1.7/progetto/calendarserver.php/calendars/oscar/calendar1")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("oscar:piccirillo"));
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

void updateCalendar() {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: text/calendar; charset=utf-8");
    body = "BEGIN:VCALENDAR\r\n"
           "VERSION:2.0\r\n"
           "PRODID:-//Sabre//Sabre VObject 4.2.2//EN\r\n"
           "BEGIN:VEVENT\r\n"
           "SEQUENCE:0\r\n"
           "UID:0\r\n"
           "DTSTAMP:20090602T185254Z\r\n"
           "DTSTART:20090602T160000Z\r\n"
           "DTEND:dhjfkdhs\r\n"
           "TRANSP:OPAQUE\r\n"
           "SUMMARY:Another event 6\r\n"
           "END:VEVENT\r\n"
           /*"BEGIN:VTODO\r\n"
           "UID:4\r\n"
           "SUMMARY:another VTODO\r\n"
           "DUE:20211030T115600Z\r\n"
           "END:VTODO\r\n"*/
           "END:VCALENDAR\r\n";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://192.168.1.10/progetto/calendarserver.php/calendars/oscar/calendar1/0.ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("oscar:piccirillo"));
        handle.setOpt(new curlpp::Options::CustomRequest("PUT"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << curlpp::infos::ResponseCode::get(handle) << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}

void shareCalendar() {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Content-Type: application/davsharing+xml; charset=\"utf-8\"");
    //headers.push_back("If-None-Match: *");
    /*body = "BEGIN:VCALENDAR\r\n"
           "VERSION:2.0\r\n"
           "PRODID:-//Sabre//Sabre VObject 4.2.2//EN\r\n"
           "BEGIN:VEVENT\r\n"
           "UID_TODO:9263504FD3AD\r\n"
           "SEQUENCE:0\r\n"
           "DTSTAMP_TODO:20090602T185254Z\r\n"
           "DTSTART:20090602T160000Z\r\n"
           "DTEND:20090602T170000Z\r\n"
           "TRANSP:OPAQUE\r\n"
           "SUMMARY_TODO:Lunch\r\n"
           "ORGANIZER;CN=\"lorenzo\":lore.pinta998@gmail.com\r\n"
           "ATTENDEE;CN=\"oscar\";CUTYPE=INDIVIDUAL;PARTSTAT=ACCEPTED:\r\n"
           " piccipicc@gmail.com\r\n"
           "END:VEVENT\r\n"
           "END:VCALENDAR\r\n";*/

    body =
           "<D:share-resource xmlns:D=\"DAV:\">\n"
           "    <D:sharee>\n"
           "        <D:href>mailto:piccipicc@gmail.com</D:href>\n"
           "        <D:prop>\n"
           "            <D:displayname>oscar-sharedcalendar</D:displayname>\n"
           "        </D:prop>\n"
           "        <D:comment>Shared workspace</D:comment>\n"
           "        <D:share-access>\n"
           "            <D:read-write />\n"
           "        </D:share-access>\n"
           "    </D:sharee>\n"
           "</D:share-resource>";
    try {
        handle.setOpt(curlpp::Options::Url(std::string("http://192.168.1.7/progetto/calendarserver.php/calendars/lorenzo/calendarLorenzo/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("lorenzo:pintaldi"));
        handle.setOpt(new curlpp::Options::CustomRequest("POST"));
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
}

void deleteIcs() {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::ostringstream str;
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://192.168.1.10/progetto/calendarserver.php/calendars/oscar/calendar-1/6.ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("oscar:piccirillo"));
        handle.setOpt(new curlpp::Options::CustomRequest("DELETE"));
        handle.setOpt(curlpp::Options::WriteStream(&str));

        handle.perform();
        std::cout << curlpp::infos::ResponseCode::get(handle) << '\n';
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
}

void getEmail() {
    curlpp::Cleanup init;
    curlpp::Easy handle;
    std::list<std::string> headers;
    std::string result;
    std::string body;
    std::ostringstream str;
    headers.push_back("Depth: 0");
    headers.push_back("Prefer: return-minimal");
    headers.push_back("Content-Type: application/xml; charset=utf-8");
    body = "<d:propfind xmlns:d=\"DAV:\">\n"
           "  <d:prop>\n"
           "    <d:current-user-principal />"
           "    <d:principal-URL />"
           "  </d:prop>\n"
           "</d:propfind>";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://192.168.1.7/progetto/calendarserver.php/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("oscar:piccirillo"));
        handle.setOpt(new curlpp::Options::CustomRequest("PROPFIND"));
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

bool isShared() {
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
                std::string("http://192.168.1.10/progetto/calendarserver.php/calendars/lorenzo/9b45f7b1-0bb8-4560-b407-35c9e9f6ba58")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("lorenzo:pintaldi"));
        handle.setOpt(new curlpp::Options::CustomRequest("PROPFIND"));
        handle.setOpt(new curlpp::Options::PostFields(body));
        handle.setOpt(new curlpp::Options::PostFieldSize(body.length()));
        handle.setOpt(new curlpp::Options::HttpHeader(headers));
        handle.setOpt(curlpp::Options::WriteStream(&str));
        handle.perform();
        std::cout << str.str() << '\n';
        if(str.str().find("cs:shared-owner") == std::string::npos)
            shared = true;
        else
            shared = false;
    }
    catch (cURLpp::RuntimeError &e) {
        std::cout << e.what() << std::endl;
    }
    catch (cURLpp::LogicError &e) {
        std::cout << e.what() << std::endl;
    }
    return shared;
}

std::string getOriganizer() {
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
                std::string("http://192.168.1.10/progetto/calendarserver.php/calendars/oscar/5eb04b90-1363-4534-9461-9440a96f31f1/")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("oscar:piccirillo"));
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

int main(int argc, char *argv[]) {
    //updateCalendar();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.synchronizeCalendarList();
    return a.exec();
    //std::cout << getOriganizer() << '\n';
    //isShared();
    //deleteIcs();
    //getEmail();
    //shareCalendar();
    /*Vcalendar tmp("prova");
    IcsParser parser(downloadCalendars());
    parser.getVCalendar(std::ref(tmp));
    std::cout << tmp << '\n';
    //updateCalendar();
    std::cout << parser.getIcsFileVevent(tmp, "sabre-vobject-e7df1a0c-3642-4a41-bb66-08c39330ae89") << '\n';
    std::cout << parser.getIcsFileVtodo(tmp, "132456762153245") << '\n';*/
    return 0;
}