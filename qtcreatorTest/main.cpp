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
                std::string("http://192.168.1.7/progetto/calendarserver.php/calendars/oscar/home")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("lorenzo:pintaldi"));
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
           "CALSCALE:GREGORIAN\r\n"
           "BEGIN:VEVENT\r\n"
           "UID_TODO:132456-34365\r\n"
           "SUMMARY_TODO:Weekly meeting\r\n"
           "DTSTART:20120101T120000\r\n"
           "DURATION:PT1H\r\n"
           "RRULE:FREQ=WEEKLY\r\n"
           "END:VEVENT\r\n"
           "END:VCALENDAR\r\n";
    try {
        handle.setOpt(curlpp::Options::Url(
                std::string("http://192.168.1.13/progetto/calendarserver.php/calendars/lorenzo/home/cal.ics")));
        handle.setOpt(new curlpp::Options::HttpAuth(CURLAUTH_ANY));
        handle.setOpt(new curlpp::options::UserPwd("lorenzo:pintaldi"));
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

    body = "<?icsText version=\"1.0\" encoding=\"utf-8\" ?>\n"
           "<D:share-resource xmlns:D=\"DAV:\">\n"
           "    <D:sharee>\n"
           "        <D:href>mailto:piccipicc@gmail.com</D:href>\n"
           "        <D:prop>\n"
           "            <D:displayname>oscar</D:displayname>\n"
           "        </D:prop>\n"
           "        <D:comment>Shared workspace</D:comment>\n"
           "        <D:share-access>\n"
           "            <D:read-write />\n"
           "        </D:share-access>\n"
           "    </D:sharee>\n"
           "</D:share-resource>";
    try {
        handle.setOpt(curlpp::Options::Url(std::string("http://192.168.1.8/progetto/calendarserver.php/calendars/lorenzo/home")));
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

int main(int argc, char *argv[]) {
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();*/
    std::string ics = "BEGIN:VCALENDAR\n"
                      "VERSION:2.0\n"
                      "PRODID:-//Sabre//Sabre VObject 4.2.2//EN\n"
                      "BEGIN:VEVENT\n"
                      "UID:9263504FD3AD\n"
                      "SEQUENCE:0\n"
                      "DTSTAMP:20090602T185254Z\n"
                      "DTSTART:20090602T160000Z\n"
                      "DTEND:20090602T170000Z\n"
                      "TRANSP:OPAQUE\n"
                      "SUMMARY:Lunch\n"
                      "END:VEVENT\n"
                      "BEGIN:VTODO\n"
                      "UID:132456762153245\n"
                      "SUMMARY:Do the dishes\n"
                      "DUE:20121028T115600Z\n"
                      "END:VTODO\n"
                      "END:VCALENDAR\n";
    Vcalendar tmp("prova");
    IcsParser parser(ics);
    parser.getVCalendar(std::ref(tmp));
    std::cout << tmp << '\n';
    return 0;
}
