//
// Created by marco on 20.12.19.
//

#ifndef SFMLTEST_GAMEMOVECHECKER_H
#define SFMLTEST_GAMEMOVECHECKER_H


#include "Tile.h"
#include "Game.h"
#include "logger.h"

class GameMoveChecker {


public:
    auto getIndirectNeighbors(Tile &tile) -> std::vector<int>;
private:

};


#endif //SFMLTEST_GAMEMOVECHECKER_H
