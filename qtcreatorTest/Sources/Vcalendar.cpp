//
// Created by picci on 27/10/2021.
//

#include "Headers/Vcalendar.h"

Vcalendar::Vcalendar(std::string const &obj) {
    name = obj; //TODO: change name with icsText
}

std::string Vcalendar::getName() {
    return name;
}
