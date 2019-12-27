//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_INCOMINGMESSAGEPARSER_H
#define SFMLTEST_INCOMINGMESSAGEPARSER_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class IncomingMessageParser {
public:
    void parseMessage(std::string message);

private:
};


#endif //SFMLTEST_INCOMINGMESSAGEPARSER_H
