//
// Created by marco on 05.12.19.
//

#ifndef SFMLTEST_TILE_H
#define SFMLTEST_TILE_H


#include <SFML/Graphics/CircleShape.hpp>
#include "Stone.h"

class Tile {
public:
    Tile(sf::CircleShape shape,int id);
    sf::CircleShape shape;
    //Stone &stone;
    bool empty{true};
    //todo hacky find better way!
    bool red;
    int stoneID;

private:
    int id;
};


#endif //SFMLTEST_TILE_H
