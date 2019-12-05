//
// Created by marco on 05.12.19.
//

#include "Stone.h"

Stone::Stone(bool red,sf::CircleShape shape) : red(red), shape(shape){}


void Stone::moveToField(sf::CircleShape &kachel) {
    float x = kachel.getGlobalBounds().left + .35 * kachel.getGlobalBounds().width;
    float y = kachel.getGlobalBounds().top + .35 * kachel.getGlobalBounds().height;
    shape.setPosition(x,y);
}


void Stone::setField(int index) {
    this->fieldIndex = index;
}