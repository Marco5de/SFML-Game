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

#define LOGGING_LEVEL_1

#include "logger.h"


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

GameView::GameView(sf::RenderWindow &gw, GameProperties &gameProperties)
        : gameWindow(gw), gameProperties(gameProperties),
          windowWidth(gameProperties.WINDOW_WIDTH), windowHeight(gameProperties.WINDOW_HEIGHT) {
}

/**
 *
 * @return
 */
int GameView::init() {
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

    state = State::SELECTION;
    selectedField = 0;


    for (int i = 0; i < 61; i++) {
        playingField.emplace_back(sf::CircleShape(40.0f, 6), i);
        if (std::find(forbiddenFields.begin(), forbiddenFields.end(), i + 1) != forbiddenFields.end()) {
            playingField[i].shape.setTexture(&playingFieldVoidTexture);
        } else
            playingField[i].shape.setTexture(&playingFieldTexture);
        //rotate so that long edge is horizontally
        playingField[i].shape.rotate(30);
        //playingField[i].setOutlineThickness(2.5);
        playingField[i].shape.setOutlineThickness(1);
        playingField[i].shape.setOutlineColor(sf::Color::White);
    }

    createPlayingField();

    //initial gibt es 4 Steine pro Spieler
    redStones.reserve(redStartingPositions.size());
    blueStones.reserve(blueStartingPositions.size());
    if(redStartingPositions.size() != blueStartingPositions.size()){
        LOG_ERR("Anzahl der Spielsteine am Start stimmt nicht überein");
        std::exit(1);
    }

    for (int i = 0; i < redStartingPositions.size(); i++) {
        int redIndex = redStartingPositions[i];
        int blueIndex = blueStartingPositions[i];

        redStones.emplace_back(true, sf::CircleShape(15));
        redStones[i].moveToField(playingField[redIndex].shape);
        redStones[i].setField(redIndex);
        redStones[i].shape.setOutlineColor(sf::Color::Black);
        redStones[i].shape.setOutlineThickness(5);
        redStones[i].shape.setFillColor(sf::Color::Red);
        playingField[redIndex].fieldstate = FIELD_STATE::RED;
        playingField[redIndex].stoneID = i;

        blueStones.emplace_back(false, sf::CircleShape(15));
        blueStones[i].moveToField(playingField[blueIndex].shape);
        blueStones[i].setField(blueIndex);
        blueStones[i].shape.setOutlineColor(sf::Color::Black);
        blueStones[i].shape.setOutlineThickness(5);
        blueStones[i].shape.setFillColor(sf::Color::Blue);
        playingField[blueIndex].fieldstate = FIELD_STATE::BLUE;
        playingField[blueIndex].stoneID = i;
    }
    setScore(blueStones.size(), redStones.size());

    LOG("Init Gameview successfull");

    return GAMEVIEW_SUCCESS;
}


//todo das spielfeld darf auf gar keinen Fall hardcoded sein! finde abhängigkeit zwischen abstand, bildgröße und spritegröße!
void GameView::createPlayingField() {
    //offset below are .075
    for (int i = 0; i < 5; i++) {
        playingField[i].shape.setPosition(.1 * windowWidth, (.25 + i * .1) * windowHeight);
        playingField[56 + i].shape.setPosition(.5 * windowWidth, (.25 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 6; i++) {
        playingField[5 + i].shape.setPosition(.15 * windowWidth, (.2 + i * .1) * windowHeight);
        playingField[50 + i].shape.setPosition(.45 * windowWidth, (.2 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 7; i++) {
        playingField[11 + i].shape.setPosition(.2 * windowWidth, (.15 + i * .1) * windowHeight);
        playingField[43 + i].shape.setPosition(.4 * windowWidth, (.15 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 8; i++) {
        playingField[18 + i].shape.setPosition(.25 * windowWidth, (.1 + i * .1) * windowHeight);
        playingField[35 + i].shape.setPosition(.35 * windowWidth, (.1 + i * .1) * windowHeight);
    }
    for (int i = 0; i < 9; i++) {
        playingField[26 + i].shape.setPosition(.3 * windowWidth, (.05 + i * .1) * windowHeight);
    }
}

int GameView::handleWindow() {
    handleMouseCursor();

    while (gameWindow.pollEvent(event)) {
        handleEvent();
    }

    gameWindow.clear();

    //Todo mal checken ob man das so lassen kann
    setScore(redStones.size(), blueStones.size());

    for (Tile tile : playingField) {
        gameWindow.draw(tile.shape);
    }
    for (Stone stone : redStones) {
        gameWindow.draw(stone.shape);
    }
    for (Stone stone : blueStones) {
        gameWindow.draw(stone.shape);
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
        menuOpen ? menuOpen = false : menuOpen = true;
    }
    //Todo fix, that field are double detected by checking if in close proximity of oriign
    //todo --> fit circle shape in hexagon, that is fully contained
    int localTarget;
    if (!menuOpen) {
        int count = 0;
        for (int i = 0; i < playingField.size(); i++) {
            if (event.type == sf::Event::MouseButtonPressed && isInside(playingField[i].shape)) {
                localTarget = i;
                count++;
            }
        }

        if (count == 1) {
            switch (state) {
                case State::SELECTION:
                    if (playingField[localTarget].fieldstate != FIELD_STATE::EMPTY) {
                        state = State::FIELD_SELECTED;
                        selectedField = localTarget;
                        LOG("Field selected #" + std::to_string(selectedField));
                    }
                    break;
                case State::FIELD_SELECTED:
                    //check that selected field is empty and non void
                    if (playingField[localTarget].fieldstate == FIELD_STATE::EMPTY &&
                        !(std::find(forbiddenFields.begin(), forbiddenFields.end(), localTarget + 1) != forbiddenFields.end())) {
                        moveStone(localTarget);
                        state = State::SELECTION;
                    }
                    break;
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


void GameView::moveStone(int localTarget) {
    int status = moveChecker.checkMove(selectedField,localTarget);
    bool red = false;
    if(!status)
        return;

    if(status == SIMPLE_MOVE) {
        if (playingField[selectedField].fieldstate == FIELD_STATE::RED) {
            redStones[playingField[selectedField].stoneID].moveToField(playingField[localTarget].shape);
            redStones[playingField[selectedField].stoneID].setField(localTarget);
            playingField[localTarget].fieldstate = FIELD_STATE::RED;
            red = true;
        } else {
            blueStones[playingField[selectedField].stoneID].moveToField(playingField[localTarget].shape);
            blueStones[playingField[selectedField].stoneID].setField(localTarget);
            //playingField[localTarget].red = false;
            playingField[localTarget].fieldstate = FIELD_STATE::BLUE;
        }
        //todo später hier züge erkennen gegenfalls anders machen
        //playingField[selectedField].empty = true;
        playingField[selectedField].fieldstate = FIELD_STATE::EMPTY;
        playingField[localTarget].stoneID = playingField[selectedField].stoneID;
        playingField[selectedField].stoneID = -1; //todo mögliche Fehlerquelle!
    } else if (status == DUPLICATE){
        //Todo Duplicate Stone
        if(playingField[selectedField].fieldstate == FIELD_STATE::RED){
            redStones.emplace_back(true,sf::CircleShape(15));
            redStones[redStones.size()-1].setField(localTarget);
            redStones[redStones.size()-1].moveToField(playingField[localTarget].shape);
            redStones[redStones.size()-1].shape.setOutlineColor(sf::Color::Black);
            redStones[redStones.size()-1].shape.setOutlineThickness(5);
            redStones[redStones.size()-1].shape.setFillColor(sf::Color::Red);
            playingField[localTarget].fieldstate = FIELD_STATE::RED;
            playingField[localTarget].stoneID = redStones.size()-1;
            red = true;
        }else{
            blueStones.emplace_back(false,sf::CircleShape(15));
            blueStones[blueStones.size()-1].setField(localTarget);
            blueStones[blueStones.size()-1].moveToField(playingField[localTarget].shape);
            blueStones[blueStones.size()-1].shape.setOutlineColor(sf::Color::Black);
            blueStones[blueStones.size()-1].shape.setOutlineThickness(5);
            blueStones[blueStones.size()-1].shape.setFillColor(sf::Color::Blue);
            playingField[localTarget].fieldstate = FIELD_STATE::BLUE;
            playingField[localTarget].stoneID = blueStones.size()-1;
        }
    }

    //todo zusammenfassen von nebeneinanderliegenden!
    checkPlayingField(red,localTarget);
}
//todo remove logik from view!, remove duplicate code,
void GameView::checkPlayingField(bool movedStoneRed,int target) {
    //ich brauch statt dem boolean ein ENUM! Field RED,BLUE,EMPTY --> damit eindeutig zugeordnet werden kann!
    std::vector<int> directNeighbors = neighbors[target];
    for(int id : directNeighbors){
        if(playingField[id].fieldstate == FIELD_STATE::EMPTY)
            continue;
        if(!(playingField[id].fieldstate == FIELD_STATE::RED) && movedStoneRed){
            auto it = blueStones.begin() + playingField[id].stoneID;
            blueStones.erase(it);

            redStones.emplace_back(true,sf::CircleShape(15));
            redStones[redStones.size()-1].setField(id);
            redStones[redStones.size()-1].moveToField(playingField[id].shape);
            redStones[redStones.size()-1].shape.setOutlineColor(sf::Color::Black);
            redStones[redStones.size()-1].shape.setOutlineThickness(5);
            redStones[redStones.size()-1].shape.setFillColor(sf::Color::Red);
            playingField[id].fieldstate = FIELD_STATE::RED;
            playingField[id].stoneID = redStones.size()-1;
        }else if(playingField[id].fieldstate == FIELD_STATE::RED && !movedStoneRed){
            auto it = redStones.begin() + playingField[id].stoneID;
            redStones.erase(it);

            blueStones.emplace_back(true,sf::CircleShape(15));
            blueStones[blueStones.size()-1].setField(id);
            blueStones[blueStones.size()-1].moveToField(playingField[id].shape);
            blueStones[blueStones.size()-1].shape.setOutlineColor(sf::Color::Black);
            blueStones[blueStones.size()-1].shape.setOutlineThickness(5);
            blueStones[blueStones.size()-1].shape.setFillColor(sf::Color::Blue);
            playingField[id].fieldstate = FIELD_STATE::BLUE;
            playingField[id].stoneID = blueStones.size()-1;
        }
    }
}

bool GameView::isInside(sf::CircleShape &shape) {
    sf::Vector2f middle;
    sf::Vector2f transformed;
    float v = shape.getGlobalBounds().width;
    float h = shape.getGlobalBounds().height;

    middle.x = shape.getGlobalBounds().left + .5 * v;
    middle.y = shape.getGlobalBounds().top + .5 * h;
    transformed.x = std::abs(currWorldMousePos.x - middle.x);
    transformed.y = std::abs(currWorldMousePos.y - middle.y);

    if (transformed.x > shape.getGlobalBounds().width / 2 || transformed.y > shape.getGlobalBounds().height / 2)
        return false;

    return v / 2 * h / 2 - v / 4 * transformed.x - h / 2 * transformed.y >= 0;
}

void GameView::handleMouseCursor() {
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
        for(int i=0; i<61;i++){
            playingField[i].shape.setOutlineColor(sf::Color::White);
            playingField[i].shape.setOutlineThickness(1);
        }
        for (auto &tile : playingField) {
            if (isInside(tile.shape))
                highlightValidMoves(tile);

        }
    }

}

void GameView::highlightValidMoves(Tile &tile) {
    auto indirectNeighbors = moveChecker.getIndirectNeighbors(tile);
    for(int id : neighbors[tile.getID()]){
        playingField[id].shape.setOutlineColor(sf::Color::Yellow);
        playingField[id].shape.setOutlineThickness(2.5);
    }
    for(int id : indirectNeighbors){
        playingField[id].shape.setOutlineColor(sf::Color::Green);
        playingField[id].shape.setOutlineThickness(2.5);
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


























