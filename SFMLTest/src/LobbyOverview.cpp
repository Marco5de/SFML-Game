/**
 * @file LobbyOverview.cpp
 * @ingroup LobbyOverview
 * @author Marco Deuscher
 * @date 23.12.2019
 * @brief implementing LobbyOverview
 */

#include <cassert>
#include <iostream>
#include "LobbyOverview.h"
#include <string>
#include "Game.h"


#include "Network.h"


#define LOBBY_SUCCESS ((0))
#define LOBBY_FONTLOADING_ERROR ((-1))
#define LOBBY_IMAGELOADING_ERROR ((-2))

#define FONT_LOBBY_TITLE ("Fonts/orange juice 2.0.ttf")
#define FONT_LOBBY_MENU ("Fonts/BebasNeue-Regular.ttf")
#define RELOAD_IMAGE_LOBBY ("images/LobbyOverview/reload.png")
#define NEXT_IMAGE_LOBBY ("images/LobbyOverview/arrow.png")

/**
 * @brief                       Constructor for @LobbyOverview
 *
 * @param window                render window
 * @param gameProperties        game Properties
 */
LobbyOverview::LobbyOverview(sf::RenderWindow &window, GameProperties &gameProperties) :
        lobbyWindow(window),
        gameProperties(gameProperties),
        windowHeight(gameProperties.WINDOW_HEIGHT),
        windowWidth(gameProperties.WINDOW_WIDTH) {}

/**
 * @brief   implementing init inherited by @GUIView, called once
 * @notes   loads all ressources from files and places the GUI elements, assertion for ressources can fail!
 * @return  LOBBY_SUCCESS if successfull
 */
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

    backgroundTextField.setPosition(.25 * windowWidth, .25 * windowHeight);
    backgroundTextField.setSize(sf::Vector2f(windowWidth, windowHeight));
    backgroundTextField.setScale(2, 2);
    backgroundTextField.setFillColor(sf::Color::Black);
    backgroundTextField.setOutlineColor(sf::Color::Magenta);

    enteredText.setPosition(.25 * windowWidth, .25 * windowHeight);
    enteredText.setFont(menuFont);
    enteredText.setColor(sf::Color::Yellow);
    enteredText.setCharacterSize(40);
    enteredText.setString((""));

    menuText.setPosition(.01 * windowWidth, .01 * windowHeight);
    menuText.setFont(menuFont);
    menuText.setColor(sf::Color::Magenta);
    menuText.setCharacterSize(30);
    menuText.setString("Enter a lobby name and confirm with enter:");


    return LOBBY_SUCCESS;
}

/**
 * @brief   implementing handleWindow inherited by @GUIView, called from loop
 * @notes   draws the text and scene objects, performs checks based on state infor which objects to draw
 * @return  LOBBY_SUCESS if successfull
 */
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

    if (enterLobbyName) {
        lobbyWindow.draw(backgroundTextField);
        lobbyWindow.draw(menuText);
        lobbyWindow.draw(enteredText);
        lobbyWindow.display();
        return LOBBY_SUCCESS;
    }

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

/**
 * @brief implements handleMouseCursor inherited by @GUIView
 * @notes simply transforms image to world coords
 */
void LobbyOverview::handleMouseCursor() {
    currMousePos = sf::Mouse::getPosition(lobbyWindow);
    currWorldMousePos = lobbyWindow.mapPixelToCoords(currMousePos);
}

/**
 * @brief   implements handleEvent inherited by @GUIView
 * @notes   all events are handled in here(button presses)
 *          sets Network data needed to set network messages
 */
void LobbyOverview::handleEvent() {
    switch (event.type) {
        case sf::Event::Closed:
            lobbyWindow.close();
            break;
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                enterLobbyName = false;
                lobbyWindow.setKeyRepeatEnabled(false);
                sanitizeString(enteredString);
                NetworkData::networkDataBuffer.lobbyname = enteredString;
                NetworkData::networkDataBuffer.state = networkState::createLobby;
            }
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == '\b') {
                if (!enteredString.empty())
                    enteredString.erase(enteredString.size() - 1, 1);
            } else {
                if (enteredString.size() < 35)
                    enteredString += event.text.unicode;
            }
            enteredText.setString(enteredString);
            break;
            //siehe hier bewusst kein BREAK!
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
                enterLobbyName = true;
                lobbyWindow.setKeyRepeatEnabled(true);
            } else if (joinLobby.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                if (NetworkData::networkDataBuffer.lobbyVec[NetworkData::networkDataBuffer.lobbyIndex].player2UUID.empty()) {
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

/**
 * @brief   displays lobby information on screen
 */
void LobbyOverview::updateLobbyDisplay() {
    unsigned int index = NetworkData::networkDataBuffer.lobbyIndex;
    if (!NetworkData::networkDataBuffer.lobbyVec.empty())
        lobby.setString(NetworkData::networkDataBuffer.lobbyVec[index].to_string());
}
