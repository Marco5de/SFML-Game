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
    virtual int init() = 0;
    virtual int handleWindow() = 0;
private:
    virtual void handleMouseCursor() = 0;
    virtual void handleEvent() = 0;
};

#endif //SFMLTEST_GUIVIEW_H
