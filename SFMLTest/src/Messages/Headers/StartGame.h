//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_STARTGAME_H
#define SFMLTEST_STARTGAME_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class StartGame {
public:
    StartGame(const std::string& userId, const std::string& lobbyId);
    json getMessage();
    std::string getMessageString();
private:
    json message;
};


#endif //SFMLTEST_STARTGAME_H
