//
// Created by marco on 27.11.19.
//

#ifndef SFMLTEST_CONTROLLER_H
#define SFMLTEST_CONTROLLER_H


#include "MainMenu.h"
#include "GameView.h"
#include "ChangeNameMenu.h"

class Controller {
public:
    Controller(const unsigned int windowHeight, const unsigned int windowWidth,const unsigned int aliasingLevel,sf::RenderWindow &window);
    void initController();
    void loop();
    std::string playerName;

private:
    GameProperties gameProperties;
    MainMenu mainMenu;
    GameView gameView;
    ChangeNameMenu changeNameMenu;


    void handleGUI();

};


#endif //SFMLTEST_CONTROLLER_H
