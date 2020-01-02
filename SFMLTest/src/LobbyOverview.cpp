//
// Created by marco on 23.12.19.
//

#include <cassert>
#include <iostream>
#include "LobbyOverview.h"
#include <iomanip>
#include <ctime>


#include "Network.h"


#define LOBBY_SUCCESS ((0))
#define LOBBY_FONTLOADING_ERROR ((-1))
#define LOBBY_IMAGELOADING_ERROR ((-2))

#define FONT_LOBBY_TITLE ("Fonts/orange juice 2.0.ttf")
#define FONT_LOBBY_MENU ("Fonts/BebasNeue-Regular.ttf")
#define RELOAD_IMAGE_LOBBY ("images/LobbyOverview/reload.png")
#define NEXT_IMAGE_LOBBY ("images/LobbyOverview/arrow.png")


LobbyOverview::LobbyOverview(sf::RenderWindow &window, GameProperties &gameProperties) :
        lobbyWindow(window),
        gameProperties(gameProperties),
        windowHeight(gameProperties.WINDOW_HEIGHT),
        windowWidth(gameProperties.WINDOW_WIDTH) {}

int LobbyOverview::init() {
    assert(menuFont.loadFromFile(FONT_LOBBY_MENU));
    assert(reloadTexture.loadFromFile(RELOAD_IMAGE_LOBBY));
    assert(nextTexture.loadFromFile(NEXT_IMAGE_LOBBY));

    titleText.setFont(menuFont);
    titleText.setColor(sf::Color::Cyan);
    titleText.setPosition(windowWidth * .3, windowHeight * 0.01);
    titleText.setCharacterSize(100);
    titleText.setString("Lobby Overview");

    returnToMain.setFont(menuFont);
    returnToMain.setColor(sf::Color::Yellow);
    returnToMain.setPosition(windowWidth * 0.01, windowHeight * 0.01);
    returnToMain.setCharacterSize(20);
    returnToMain.setString("Return to \nMain Menu");

    startGame.setFont(menuFont);
    startGame.setColor(sf::Color::Yellow);
    startGame.setPosition(windowWidth * .95, windowHeight * .01);
    startGame.setCharacterSize(20);
    startGame.setString("Start\nGame");


    createLobby.setFont(menuFont);
    createLobby.setColor(sf::Color::Yellow);
    createLobby.setPosition(windowWidth * .6, windowHeight * .9);
    createLobby.setCharacterSize(20);
    createLobby.setString("Create new\nLobby");

    joinLobby.setFont(menuFont);
    joinLobby.setColor(sf::Color::Yellow);
    joinLobby.setPosition(windowWidth * .4, windowHeight * .9);
    joinLobby.setCharacterSize(20);
    joinLobby.setString("Join\nLobby");

    lobby.setFont(menuFont);
    lobby.setColor(sf::Color::Magenta);
    lobby.setPosition(windowWidth * .3, windowHeight * .25);
    lobby.setCharacterSize(40);
    lobby.setString("Empty");


    leaveLobby.setFont(menuFont);
    leaveLobby.setColor(sf::Color::Yellow);
    leaveLobby.setPosition(windowWidth * .95, windowHeight * .9);
    leaveLobby.setCharacterSize(20);
    leaveLobby.setString("Leave\nLobby");

    reloadSprite.setTexture(reloadTexture);
    reloadSprite.setPosition(.4 * windowWidth, .65 * windowHeight);
    reloadSprite.setColor(sf::Color::Yellow);
    reloadSprite.scale(.75, .75);

    nextSprite.setTexture(nextTexture);
    nextSprite.setPosition(.6 * windowWidth, .65 * windowHeight);
    nextSprite.setColor(sf::Color::Yellow);
    nextSprite.scale(.75, .75);


    return LOBBY_SUCCESS;
}


int LobbyOverview::handleWindow() {
    //check if ready to go ingame
    if (NetworkData::networkDataBuffer.inGame || !NetworkData::networkDataBuffer.gameID.empty())
        gameProperties.currentGameState = gameState::INGAME;
    updateLobbyDisplay();
    handleMouseCursor();
    while (lobbyWindow.pollEvent(event)) {
        handleEvent();
    }


    lobbyWindow.clear();
    lobbyWindow.draw(titleText);
    lobbyWindow.draw(returnToMain);
    if (NetworkData::networkDataBuffer.insideLobby) {
        lobbyWindow.draw(leaveLobby);
        //check if first player and lobby is full!
        if (NetworkData::networkDataBuffer.lobbyVec[NetworkData::networkDataBuffer.lobbyIndex].player1UUID ==
            NetworkData::networkDataBuffer.UUID
            && !NetworkData::networkDataBuffer.lobbyVec[NetworkData::networkDataBuffer.lobbyIndex].player2UUID.empty())
            lobbyWindow.draw(startGame);
    } else {
        lobbyWindow.draw(createLobby);
        lobbyWindow.draw(joinLobby);
        if (NetworkData::networkDataBuffer.lobbyVec.size() > 1)
            lobbyWindow.draw(nextSprite);
    }
    lobbyWindow.draw(lobby);
    lobbyWindow.draw(reloadSprite);

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
            } else if (startGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                if (NetworkData::networkDataBuffer.insideLobby)
                    NetworkData::networkDataBuffer.state = networkState::startGame;
            } else if (reloadSprite.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                NetworkData::networkDataBuffer.state = networkState::getAvailableLobbies;
            } else if (createLobby.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                //eingeben eines Lobbynamens
                NetworkData::networkDataBuffer.state = networkState::createLobby;
                NetworkData::networkDataBuffer.lobbyname = "Lobbyname";
            } else if (joinLobby.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                if(NetworkData::networkDataBuffer.lobbyVec[NetworkData::networkDataBuffer.lobbyIndex].player2UUID.empty()) {
                    NetworkData::networkDataBuffer.playerName = gameProperties.playerName;
                    NetworkData::networkDataBuffer.state = networkState::joinLobby;
                }
            } else if (nextSprite.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                if (NetworkData::networkDataBuffer.lobbyVec.empty())
                    break;
                NetworkData::networkDataBuffer.lobbyIndex = (NetworkData::networkDataBuffer.lobbyIndex + 1) %
                                                            NetworkData::networkDataBuffer.lobbyVec.size();
            } else if (leaveLobby.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                NetworkData::networkDataBuffer.state = networkState::leaveLobby;
            }
            break;
    }
}

void LobbyOverview::updateLobbyDisplay() {
    unsigned int index = NetworkData::networkDataBuffer.lobbyIndex;
    if (!NetworkData::networkDataBuffer.lobbyVec.empty())
        lobby.setString(NetworkData::networkDataBuffer.lobbyVec[index].to_string());
}