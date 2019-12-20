//
// Created by marco on 20.12.19.
//

#ifndef SFMLTEST_GAMEMOVECHECKER_H
#define SFMLTEST_GAMEMOVECHECKER_H

#define INVALID_MOVE 0
#define DUPLICATE 2
#define SIMPLE_MOVE 1

#include "Tile.h"
#include "Game.h"
#include "logger.h"

class GameMoveChecker {


public:
    auto getIndirectNeighbors(Tile &tile) -> std::vector<int>;
    auto getIndirectNeighbors(int tileID) -> std::vector<int>;
    int checkMove(int selectedField,int target);

private:
    std::vector<Tile> playingField;
    std::vector<Stone> redStones;
    std::vector<Stone> blueStones;

};


#endif //SFMLTEST_GAMEMOVECHECKER_H
