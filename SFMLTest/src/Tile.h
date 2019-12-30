//
// Created by marco on 05.12.19.
//

#ifndef SFMLTEST_TILE_H
#define SFMLTEST_TILE_H

enum FIELD_STATE{
    RED,
    BLUE,
    EMPTY,
    BLOCKED
};

#include <SFML/Graphics/CircleShape.hpp>
#include "Stone.h"

class Tile {
public:
    Tile(sf::CircleShape shape,int id);
    sf::CircleShape shape;

    int stoneID;
    int getID();
    FIELD_STATE fieldstate{FIELD_STATE::EMPTY};

private:
    const int id;
};


#endif //SFMLTEST_TILE_H
