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
        lobbyOverview(gameProperties.window, gameProperties),
        messageParser()
        {}

void Controller::initController() {
    gameProperties.window.setFramerateLimit(60);
    gameProperties.window.setKeyRepeatEnabled(false);

    if (mainMenu.init() != MAINMENU_SUCCESS) {
        std::cout << "Error initting Main menu. exiting with error code1" << std::endl;
        std::exit(1);
    }

    if (gameView.init() != GAMEVIEW_SUCCESS) {
        std::cout << "Error initting Game View. Exiting with error code 1" << std::endl;
        std::exit(1);
    }

    if (changeNameMenu.init() != NAME_MENU_SUCCESS) {
        std::cout << "Error initting name change menu. Exiting with error code 1" << std::endl;
        std::exit(1);
    }

    if (lobbyOverview.init() != MAINMENU_SUCCESS) {
        std::cout << "Error initting lobby view. Exiting with error code 1" << std::endl;
        std::exit(1);
    }


    //todo remove, just for testing
    gameView.setScore(17, 12);
    gameView.setMoveTracker(false);
    LOG("Init Controller Done")

    //todo minimal example --> Todo work on this!
    ws = WebSocket::from_url("ws://localhost:4444");
    assert(ws);
    //networkThread = std::thread(&Controller::networkTest, this);
    //networkThread.detach();

}


void Controller::loop() {
    while (gameProperties.window.isOpen()) {
        handleGUI();
        handleNetwork();
    }
}

void Controller::handleNetwork() {
    if (ws->getReadyState() != WebSocket::CLOSED) {
        WebSocket::pointer wsp = &*ws; // <-- because a unique_ptr cannot be copied into a lambda
        ws->poll(); //does not block by default!
        ws->dispatch([wsp](const std::string &message) {
            printf(">>> %s\n", message.c_str());
        });
    }

    class GetAvailableLobbies gal(1337);
    ws->send(gal.getMessageString());

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

