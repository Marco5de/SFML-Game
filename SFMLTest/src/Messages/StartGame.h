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
    StartGame(unsigned int userId, unsigned int lobbyId);
    json getMessage();
    std::string getMessageString();
private:
    json message;
};


#endif //SFMLTEST_STARTGAME_H
