//
// Created by picci on 27/10/2021.
//

#include "Headers/Vcalendar.h"

Vcalendar::Vcalendar(std::string const &obj) {
    xml = obj;
}

std::string Vcalendar::getXml() {
    return xml;
}
