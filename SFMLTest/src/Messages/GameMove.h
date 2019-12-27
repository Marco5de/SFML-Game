//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_GAMEMOVE_H
#define SFMLTEST_GAMEMOVE_H

#include <string>
#include <nlohmann/json.hpp>
#include "../Network.h"
#include "../Game.h"

using json = nlohmann::json;

class GameMove {
public:
    GameMove(unsigned int userId,
             unsigned int gameId,
             TileEnum tile1,
             TileEnum tile2
             );
    json getMessage();
    std::string getMessageString();

private:
    json message;
};


#endif //SFMLTEST_GAMEMOVE_H
