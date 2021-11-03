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

class API {
private:
    std::string IPADDRESS;
public:
    API(std::string IPADDRESS);

    std::string login(std::string const &username, std::string const &password);
};


#endif //QTCREATORTEST_API_H