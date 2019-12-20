//
// Created by marco on 20.12.19.
//

#ifndef SFMLTEST_GUIVIEW_H
#define SFMLTEST_GUIVIEW_H

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.h"

class GUIView{
public:
    GUIView(sf::RenderWindow &window,GameProperties &gameProperties) : window(window), gameProperties(gameProperties){}
    virtual int init() = 0;
    virtual int handleWindow() = 0;
private:
    sf::Event event;
    sf::RenderWindow &window;
    sf::Vector2i currRelMousePos;
    sf::Vector2f currWorldMousePos;
    GameProperties &gameProperties;

    virtual void handleMouseCursor() = 0;
    virtual void handleEvnet() = 0;
};

#endif //SFMLTEST_GUIVIEW_H
