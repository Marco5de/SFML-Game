//
// Created by marco on 23.12.19.
//

#include <cassert>
#include "LobbyOverview.h"

#include "Network.h"


#define LOBBY_SUCCESS ((0))
#define LOBBY_FONTLOADING_ERROR ((-1))
#define LOBBY_IMAGELOADING_ERROR ((-2))

#define FONT_LOBBY_TITLE ("Fonts/orange juice 2.0.ttf")
#define FONT_LOBBY_MENU ("Fonts/BebasNeue-Regular.ttf")


LobbyOverview::LobbyOverview(sf::RenderWindow &window, GameProperties &gameProperties) :
        lobbyWindow(window),
        gameProperties(gameProperties),
        windowHeight(gameProperties.WINDOW_HEIGHT),
        windowWidth(gameProperties.WINDOW_WIDTH) {}

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
    startGame.setPosition(windowWidth * .95, windowHeight * .9);
    startGame.setCharacterSize(20);
    startGame.setString("Start\nGame");

    refreshLobbies.setFont(menuFont);
    refreshLobbies.setColor(sf::Color::Yellow);
    refreshLobbies.setPosition(windowWidth * .25, windowHeight * .9);
    refreshLobbies.setCharacterSize(20);
    refreshLobbies.setString("Refresh \nLobbies");

    createLobby.setFont(menuFont);
    createLobby.setColor(sf::Color::Yellow);
    createLobby.setPosition(windowWidth * .75, windowHeight * .9);
    createLobby.setCharacterSize(20);
    createLobby.setString("Create new\nLobby");

    joinLobby.setFont(menuFont);
    joinLobby.setColor(sf::Color::Yellow);
    joinLobby.setPosition(windowWidth * .45, windowHeight * .9);
    joinLobby.setCharacterSize(20);
    joinLobby.setString("Join\nLobby");

    lobby.setFont(menuFont);
    lobby.setColor(sf::Color::Magenta);
    lobby.setPosition(windowWidth * .4, windowHeight * .25);
    lobby.setCharacterSize(40);
    lobby.setString("Empty"); //todo fix!

    left.setFont(menuFont);
    left.setColor(sf::Color::Green);
    left.setPosition(windowWidth * .4,windowHeight * .65);
    left.setCharacterSize(30);
    left.setString("Next");

    return LOBBY_SUCCESS;
}


int LobbyOverview::handleWindow() {
    updateLobbyDisplay();
    handleMouseCursor();
    while (lobbyWindow.pollEvent(event)) {
        handleEvent();
    }

    lobbyWindow.clear();
    lobbyWindow.draw(titleText);
    lobbyWindow.draw(returnToMain);
    lobbyWindow.draw(startGame);
    lobbyWindow.draw(refreshLobbies);
    lobbyWindow.draw(createLobby);
    lobbyWindow.draw(joinLobby);
    lobbyWindow.draw(lobby);

    lobbyWindow.draw(left);

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
            if (returnToMain.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                gameProperties.currentGameState = gameState::MAINMENU;
            } else if (startGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
                gameProperties.currentGameState = gameState::INGAME;
            else if (refreshLobbies.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                NetworkData::networkDataBuffer.state = networkState::getAvailableLobbies;
            } else if (createLobby.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                //eingeben eines Lobbynamens
                NetworkData::networkDataBuffer.state = networkState::createLobby;
                NetworkData::networkDataBuffer.lobbyname = "hardcoded";
            } else if (joinLobby.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                NetworkData::networkDataBuffer.state = networkState::joinLobby;
            } else if(left.getGlobalBounds().contains(currWorldMousePos.x,currWorldMousePos.y)){
                index = (index+1) % NetworkData::networkDataBuffer.lobbyVec.size();
            }
            break;
    }
}

void LobbyOverview::updateLobbyDisplay() {
    if (!NetworkData::networkDataBuffer.lobbyVec.empty())
        lobby.setString(NetworkData::networkDataBuffer.lobbyVec[index].to_string());
}