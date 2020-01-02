//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_LEAVEGAME_H
#define SFMLTEST_LEAVEGAME_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class LeaveGame {
public:
    LeaveGame(const std::string& userId, const std::string& gameId);
    json getMessage();
    std::string getMessageString();

private:
    json message;
};


#endif //SFMLTEST_LEAVEGAME_H
