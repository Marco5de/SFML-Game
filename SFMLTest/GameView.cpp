/**
 * @file MainMenu.h
 * @defgroup gameView Game View
 * @ingroup gameView
 * @author Marco Deuscher
 * @date 07.11.2019
 * @brief All the game logic and display are inside this class
 */
#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include "GameView.h"
#include "Game.h"


#define IMAGE_PLAYER_PATH ("images/GameView/player.png")
#define IMAGE_PLAYINGFIELD_PATH ("images/GameView/lavafull.jpg")
#define IMAGE_PLAYINGFIELDVOID_PATH ("images/GameView/sky_tryker_dusk_fair.png")
#define FONT_GAMEVIEW_HELP ("Fonts/arial.ttf")
#define FONT_GAMEVIEW_TITLE ("Fonts/orange juice 2.0.ttf")
#define FONT_GAMEVIEW_MENU ("Fonts/BebasNeue-Regular.ttf")
#define TEXTRESSOURCES_HELPTEXT ("TextRessources/help.txt")


/**
 *
 * @param gameWindow
 * @param windowWidth
 * @param windowHeight
 * @param gs
 */

GameView::GameView(sf::RenderWindow &gw, const int windowWidth, const int windowHeight, GameProperties &gameProperties)
        : gameWindow(gw), gameProperties(gameProperties),
          windowWidth(gameProperties.WINDOW_WIDTH), windowHeight(gameProperties.WINDOW_HEIGHT) {
}

/**
 *
 * @return
 */
int GameView::initGameView() {
    if (!playingFieldTexture.loadFromFile(IMAGE_PLAYINGFIELD_PATH))
        return GAMEVIEW_IMAGELOADING_ERROR;
    if (!playingFieldVoidTexture.loadFromFile(IMAGE_PLAYINGFIELDVOID_PATH))
        return GAMEVIEW_IMAGELOADING_ERROR;
    if (!titleFont.loadFromFile(FONT_GAMEVIEW_TITLE))
        return GAMEVIEW_FONTLOADING_ERROR;
    if (!textFont.loadFromFile(FONT_GAMEVIEW_HELP))
        return GAMEVIEW_FONTLOADING_ERROR;
    if (!menuFont.loadFromFile(FONT_GAMEVIEW_MENU))
        return GAMEVIEW_FONTLOADING_ERROR;


    //reserve storage in vector for playing field
    playingField.reserve(61);

    //load text ressources from files
    helpString = getStringFromFile(TEXTRESSOURCES_HELPTEXT);

    titleText.setFont(titleFont);
    titleText.setColor(sf::Color::Magenta);
    titleText.setOutlineColor(sf::Color::White);
    titleText.setString("Hexxagon");
    titleText.setPosition(.5 * windowWidth, 0 * windowHeight);
    titleText.setCharacterSize(150);

    helpText.setFont(textFont);
    helpText.setColor(sf::Color::Cyan);
    helpText.setString(helpString);
    helpText.setPosition(.575 * windowWidth, .275 * windowHeight);
    helpText.setCharacterSize(15);

    menuText.setFont(menuFont);
    menuText.setColor(sf::Color::Yellow);
    menuText.setString("Menu");
    menuText.setPosition(.015 * windowWidth, .9 * windowHeight);
    menuText.setCharacterSize(50);

    scoreBlue.setFont(menuFont);
    scoreBlue.setColor(sf::Color::Blue);
    scoreBlue.setOutlineThickness(1);
    scoreBlue.setOutlineColor(sf::Color::Yellow);
    //todo remove hardcoded value, put players score in here
    scoreBlue.setString("0");
    scoreBlue.setPosition(.015 * windowWidth, .01 * windowHeight);
    scoreBlue.setCharacterSize(50);

    scoreRed.setFont(menuFont);
    scoreRed.setColor(sf::Color::Red);
    scoreRed.setOutlineColor(sf::Color::Yellow);
    scoreRed.setOutlineThickness(1);
    scoreRed.setString("0");
    scoreRed.setPosition(.015 * windowWidth, 0.07 * windowHeight);
    scoreRed.setCharacterSize(50);

    moveTracker.setRadius(10);
    moveTracker.setPointCount(3);
    moveTracker.setFillColor(sf::Color::Yellow);
    moveTracker.setOutlineColor(sf::Color::Blue);
    moveTracker.setOutlineThickness(1.5);
    moveTracker.setPosition(.055 * windowWidth, .075 * windowHeight);
    moveTracker.rotate(-90);
    moveTracker.setScale(2, 2);


    menuBackground.setPosition(.075 * windowWidth, .25 * windowHeight);
    menuBackground.setSize(sf::Vector2f(.25 * windowWidth, .5 * windowHeight));
    menuBackground.setFillColor(sf::Color::Black);
    menuBackground.setOutlineColor(sf::Color::Yellow);
    menuBackground.setOutlineThickness(5);

    menuMainMenu.setPosition(.08 * windowWidth, .275 * windowHeight);
    menuMainMenu.setCharacterSize(30);
    menuMainMenu.setFont(menuFont);
    menuMainMenu.setColor(sf::Color::Yellow);
    menuMainMenu.setOutlineThickness(5);
    menuMainMenu.setOutlineColor(sf::Color::Blue);
    menuMainMenu.setString("Return to Main Menu");

    menuClose.setPosition(.08 * windowWidth, .375 * windowHeight);
    menuClose.setCharacterSize(30);
    menuClose.setFont(menuFont);
    menuClose.setColor(sf::Color::Yellow);
    menuClose.setOutlineThickness(5);
    menuClose.setOutlineColor(sf::Color::Blue);
    menuClose.setString("Close Menu");

    for (int i = 0; i < 61; i++) {
        playingField.push_back(sf::CircleShape(40.0f, 6));
        if (std::find(forbiddenFields.begin(), forbiddenFields.end(), i + 1) != forbiddenFields.end()) {
            playingField[i].setTexture(&playingFieldVoidTexture);
        } else
            playingField[i].setTexture(&playingFieldTexture);
        //rotate so that long edge is horizontally
        playingField[i].rotate(30);
        playingField[i].setOutlineThickness(2.5);
        playingField[i].setOutlineColor(sf::Color::White);
    }

    createPlayingField();

    return GAMEVIEW_SUCCESS;
}

//todo das spielfeld darf auf gar keinen Fall hardcoded sein! finde abhängigkeit zwischen abstand, bildgröße und spritegröße!
void GameView::createPlayingField() {
    //offset below are .075
    for (int i = 0; i < 5; i++) {
        playingField[i].setPosition(.1 * windowWidth, (.25 + i * .1) * windowHeight);
        playingField[56 + i].setPosition(.5 * windowWidth, (.25 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 6; i++) {
        playingField[5 + i].setPosition(.15 * windowWidth, (.2 + i * .1) * windowHeight);
        playingField[50 + i].setPosition(.45 * windowWidth, (.2 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 7; i++) {
        playingField[11 + i].setPosition(.2 * windowWidth, (.15 + i * .1) * windowHeight);
        playingField[43 + i].setPosition(.4 * windowWidth, (.15 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 8; i++) {
        playingField[18 + i].setPosition(.25 * windowWidth, (.1 + i * .1) * windowHeight);
        playingField[35 + i].setPosition(.35 * windowWidth, (.1 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 9; i++) {
        playingField[26 + i].setPosition(.3 * windowWidth, (.05 + i * .1) * windowHeight);
    }
}

int GameView::handleGameView() {
    handleMouseCursour();

    while (gameWindow.pollEvent(event)) {
        handleEvent();
    }

    gameWindow.clear();


    for (sf::CircleShape cs : playingField) {
        gameWindow.draw(cs);
    }
    gameWindow.draw(titleText);
    gameWindow.draw(helpText);
    gameWindow.draw(menuText);
    gameWindow.draw(scoreRed);
    gameWindow.draw(scoreBlue);
    gameWindow.draw(moveTracker);


    if (menuOpen) {
        gameWindow.draw(menuBackground);
        gameWindow.draw(menuMainMenu);
        gameWindow.draw(menuClose);
    }

    gameWindow.display();


    return GAMEVIEW_SUCCESS;
}

void GameView::handleEvent() {
    if (event.type == sf::Event::Closed)
        gameWindow.close();
    if (event.type == sf::Event::MouseButtonPressed &&
        menuText.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        //*currentGameState = gameState::MAINMENU;
        menuOpen ? menuOpen = false : menuOpen = true;
    }
    //Todo fix, that field are double detected by checking if in close proximity of oriign
    //todo --> fit circle shape in hexagon, that is fully contained!
    if (!menuOpen) {
        for (int i = 0; i < playingField.size(); i++) {
            if (event.type == sf::Event::MouseButtonPressed &&
                playingField[i].getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                std::cout << "Clicked Field #" << i << std::endl;
            }
        }
    }

    if (menuOpen) {
        if (event.type == sf::Event::MouseButtonPressed &&
            menuMainMenu.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
            gameProperties.currentGameState = gameState::MAINMENU;
        else if (event.type == sf::Event::MouseButtonPressed &&
                 menuClose.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
            menuOpen = false;
    }
}


void GameView::handleMouseCursour() {
    //get current mouse position relative to the window and convert from images coords to global coords
    currMousePos = sf::Mouse::getPosition(gameWindow);
    currWorldMousePos = gameWindow.mapPixelToCoords(currMousePos);
    if (menuText.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        menuText.setColor(sf::Color::Red);
    } else {
        menuText.setColor(sf::Color::Yellow);
    }

    //Todo fix, that field are double detected by checking if in close proximity of oriign
    //todo --> fit circle shape in hexagon, that is fully contained!
    //todo remove code douplitcation! --> combine handle cursor and handleEvent
    if (!menuOpen) {
        for (auto &shape : playingField) {
            if (shape.getGlobalBounds().contains(currWorldMousePos.x, currMousePos.y)) {
                shape.setOutlineColor(sf::Color::Yellow);
            } else
                shape.setOutlineColor(sf::Color::White);
        }
    }

}


void GameView::setScore(int scoreRed, int scoreBlue) {
    this->scoreBlue.setString(std::to_string(scoreBlue));
    this->scoreRed.setString(std::to_string(scoreRed));
}

void GameView::setMoveTracker(bool red) {
    if (red) {
        moveTracker.setOutlineColor(sf::Color::Red);
        moveTracker.setPosition(.055 * windowWidth, .14 * windowHeight);
        return;
    }
    moveTracker.setOutlineColor(sf::Color::Blue);
    moveTracker.setPosition(.055 * windowWidth, .075 * windowHeight);
    return;
}


























