//
// Created by marco on 05.12.19.
//

#ifndef SFMLTEST_STONE_H
#define SFMLTEST_STONE_H


#include <SFML/Graphics/CircleShape.hpp>

class Stone {
public:
    bool red;
    Stone(bool red,sf::CircleShape shape);
    void moveToField(sf::CircleShape &kachel);
    void setField(int index);
    sf::CircleShape shape;

private:
    int fieldIndex;


};


#endif //SFMLTEST_STONE_H
