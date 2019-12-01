//
// Created by marco on 27.11.19.
//

#include <iostream>
#include "Controller.h"


Controller::Controller(const unsigned int windowHeight, const unsigned int windowWidth,
                       const unsigned int aliasingLevel, sf::RenderWindow &window) :
        gameProperties(windowWidth, windowHeight, aliasingLevel, window),
        mainMenu(gameProperties.window, gameProperties),
        gameView(gameProperties.window, gameProperties),
        changeNameMenu(gameProperties.window,gameProperties)
        {}

void Controller::initController() {
    gameProperties.window.setFramerateLimit(60);
    gameProperties.window.setKeyRepeatEnabled(false);

    if (mainMenu.initMainMenu() != MAINMENU_SUCCESS) {
        std::cout << "Error initting Main menu. exiting with error code1" << std::endl;
        std::exit(1);
    }

    if (gameView.initGameView() != GAMEVIEW_SUCCESS) {
        std::cout << "Error initting Game View. Exiting with error code 1" << std::endl;
        std::exit(1);
    }

    if (changeNameMenu.initChangeNameMenu() != NAME_MENU_SUCCESS) {
        std::cout << "Error initting name change menu. Exiting with error code 1" << std::endl;
        std::exit(1);
    }

    //todo remove, just for testing
    gameView.setScore(17, 12);
    gameView.setMoveTracker(false);
}

void Controller::loop() {
   handleGUI();
}


void Controller::handleGUI() {
    while (gameProperties.window.isOpen()) {
        switch (gameProperties.currentGameState) {
            case gameState::MAINMENU:
                mainMenu.handleMainMenu();
                break;
            case gameState::INGAME:
                gameView.handleGameView();
                break;
            case gameState::CHANGENAME:
                changeNameMenu.handleChangeNameMenu();
                break;
        }
    }
}