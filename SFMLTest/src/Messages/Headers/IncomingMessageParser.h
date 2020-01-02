//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_INCOMINGMESSAGEPARSER_H
#define SFMLTEST_INCOMINGMESSAGEPARSER_H

#include <string>
#include "../../Lobby.h"
#include <nlohmann/json.hpp>


using json = nlohmann::json;


class IncomingMessageParser {
public:
    IncomingMessageParser();
    void parseMessage(const std::string &message);

private:
    std::map<std::string, unsigned int> enumMap;

};


#endif //SFMLTEST_INCOMINGMESSAGEPARSER_H
