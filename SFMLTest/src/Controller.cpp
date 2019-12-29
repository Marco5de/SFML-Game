//
// Created by marco on 27.11.19.
//

#include <iostream>
#include <cassert>
#include "Controller.h"


#define LOGGING_LEVEL_1

#include "logger.h"



Controller::Controller(const unsigned int windowHeight, const unsigned int windowWidth,
                       const unsigned int aliasingLevel, sf::RenderWindow &window) :
        gameProperties(windowWidth, windowHeight, aliasingLevel, window),
        mainMenu(gameProperties.window, gameProperties),
        gameView(gameProperties.window, gameProperties),
        changeNameMenu(gameProperties.window, gameProperties),
        lobbyOverview(gameProperties.window, gameProperties)
        {}

void Controller::initController() {
    gameProperties.window.setFramerateLimit(60);
    gameProperties.window.setKeyRepeatEnabled(false);
    gameProperties.playerName = getStringFromFile("nameConfig.txt");

    assert(mainMenu.init() == MAINMENU_SUCCESS);
    assert(gameView.init() == GAMEVIEW_SUCCESS);
    assert(changeNameMenu.init() == NAME_MENU_SUCCESS);
    assert(lobbyOverview.init() == MAINMENU_SUCCESS);
    assert(network.initNetwork());

    //todo remove, just for testing
    gameView.setScore(17, 12);
    gameView.setMoveTracker(false);
    LOG("Init Controller Done")
}


void Controller::loop() {
    while (gameProperties.window.isOpen()) {
        handleGUI();
        handleNetwork();
    }
}



void Controller::handleNetwork() {
   network.handleNetwork();
}



void Controller::handleGUI() {
    switch (gameProperties.currentGameState) {
        case gameState::MAINMENU:
            mainMenu.handleWindow();
            break;
        case gameState::LOBBY:
            lobbyOverview.handleWindow();
            break;
        case gameState::INGAME:
            gameView.handleWindow();
            break;
        case gameState::CHANGENAME:
            changeNameMenu.handleWindow();
            break;
    }

}

