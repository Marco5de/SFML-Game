//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_GAMEMOVE_H
#define SFMLTEST_GAMEMOVE_H

#include <string>
#include <nlohmann/json.hpp>
#include "../../Network.h"
#include "../../Game.h"

using json = nlohmann::json;

class GameMove {
public:
    GameMove(const std::string& userId,
             const std::string& gameId,
             const std::string& tile1,
             const std::string& tile2
             );
    json getMessage();
    std::string getMessageString();

private:
    json message;
};


#endif //SFMLTEST_GAMEMOVE_H
