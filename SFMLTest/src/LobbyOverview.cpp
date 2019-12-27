//
// Created by marco on 23.12.19.
//

#include <cassert>
#include "LobbyOverview.h"


#define LOBBY_SUCCESS ((0))
#define LOBBY_FONTLOADING_ERROR ((-1))
#define LOBBY_IMAGELOADING_ERROR ((-2))

#define FONT_LOBBY_TITLE ("Fonts/orange juice 2.0.ttf")
#define FONT_LOBBY_MENU ("Fonts/BebasNeue-Regular.ttf")


LobbyOverview::LobbyOverview(sf::RenderWindow &window, GameProperties &gameProperties) :
        lobbyWindow(window),
        gameProperties(gameProperties),
        windowHeight(gameProperties.WINDOW_HEIGHT),
        windowWidth(gameProperties.WINDOW_WIDTH)
{}

int LobbyOverview::init() {
    assert(menuFont.loadFromFile(FONT_LOBBY_MENU));

    titleText.setFont(menuFont);
    titleText.setColor(sf::Color::Yellow);
    titleText.setPosition(windowWidth * .45, windowHeight * 0.01);
    titleText.setCharacterSize(30);
    titleText.setString("Lobby Overview");

    returnToMain.setFont(menuFont);
    returnToMain.setColor(sf::Color::Yellow);
    returnToMain.setPosition(windowWidth * 0.01, windowHeight * 0.9);
    returnToMain.setCharacterSize(20);
    returnToMain.setString("Return to \nMain Menu");

    startGame.setFont(menuFont);
    startGame.setColor(sf::Color::Yellow);
    startGame.setPosition(windowWidth * .95,windowHeight * .9);
    startGame.setCharacterSize(20);
    startGame.setString("Start\nGame");

    return LOBBY_SUCCESS;
}




int LobbyOverview::handleWindow() {
    handleMouseCursor();
    while (lobbyWindow.pollEvent(event)) {
        handleEvent();
    }

    lobbyWindow.clear();
    lobbyWindow.draw(titleText);
    lobbyWindow.draw(returnToMain);
    lobbyWindow.draw(startGame);

    lobbyWindow.display();
    return LOBBY_SUCCESS;
}

void LobbyOverview::handleMouseCursor() {
    currMousePos = sf::Mouse::getPosition(lobbyWindow);
    currWorldMousePos = lobbyWindow.mapPixelToCoords(currMousePos);
}

void LobbyOverview::handleEvent() {
    switch (event.type) {
        case sf::Event::Closed:
            lobbyWindow.close();
            break;

        case sf::Event::MouseButtonPressed:
            if(returnToMain.getGlobalBounds().contains(currWorldMousePos.x,currWorldMousePos.y)){
                gameProperties.currentGameState = gameState::MAINMENU;
            } else if (startGame.getGlobalBounds().contains(currWorldMousePos.x,currWorldMousePos.y))
                gameProperties.currentGameState = gameState::INGAME;
            break;
    }
}