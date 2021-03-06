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
#include <cassert>
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
 * @brief                   Constructor for @GameView
 * @param gameWindow        render window used to display game in
 * @param windowWidth       window width, does not change
 * @param windowHeight      window height, does not change
 * @param gs                gamePropterties
 */

GameView::GameView(sf::RenderWindow &gw, GameProperties &gameProperties)
        : gameWindow(gw), gameProperties(gameProperties),
          windowWidth(gameProperties.WINDOW_WIDTH), windowHeight(gameProperties.WINDOW_HEIGHT) {
}

/**
 * @brief   implementing init inherited by @GUIView, called once
 * @notes   all required ressoures are loaded in here, if not successfull assertion fails
 *          playingFieldLayout and Stones are also created in here!
 * @return  GAMEVIEW_SUCCESS if successfull
 */
int GameView::init() {
    assert(playingFieldTexture.loadFromFile(IMAGE_PLAYINGFIELD_PATH));
    assert(playingFieldVoidTexture.loadFromFile(IMAGE_PLAYINGFIELDVOID_PATH));
    assert(titleFont.loadFromFile(FONT_GAMEVIEW_TITLE));
    assert(textFont.loadFromFile(FONT_GAMEVIEW_HELP));
    assert(menuFont.loadFromFile(FONT_GAMEVIEW_MENU));

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

    winnerText.setPosition(.15 * windowWidth, .25 * windowHeight);
    winnerText.setCharacterSize(50);
    winnerText.setFont(menuFont);
    winnerText.setColor(sf::Color::Yellow);
    winnerText.setOutlineThickness(2);
    winnerText.setOutlineColor(sf::Color::Red);
    winnerText.setString("");

    winnerButton.setPosition(.45 * windowWidth, .85 * windowHeight);
    winnerButton.setCharacterSize(30);
    winnerButton.setFont(menuFont);
    winnerButton.setColor(sf::Color::Cyan);
    winnerButton.setString("Return to\nMainMenu");


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
    if (redStartingPositions.size() != blueStartingPositions.size()) {
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

    return GAMEVIEW_SUCCESS;
}


/**
 * @brief sets the Position for the tiles of the playingField
 */
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

/**
 * @brief   implementing handleWindow inherited by @GUIView, called from loop
 * @notes   drawing is done in here. Performs checks which elements of the View have to be drawn at some moment
 * @return  GAMEVIEW_SUCCESS if successfull
 */
int GameView::handleWindow() {
    handleMouseCursor();
    handleNetworkUpdate();

    while (gameWindow.pollEvent(event)) {
        handleEvent();
    }

    gameWindow.clear();

    if (winnerView) {
        if (std::stoi(std::string(scoreRed.getString())) == 0) {
            winnerText.setString("GAME OVER\nBlue player has won. Press Button to return to MainMenu");
        } else if (std::stoi(std::string(scoreRed.getString()))) {
            winnerText.setString("GAME OVER\nRed player has won. Press Button to return to MainMenu");
        }
        gameWindow.draw(winnerText);
        gameWindow.draw(winnerButton);
        gameWindow.display();
        return GAMEVIEW_SUCCESS;
    }


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
/**
 * @brief   implementing handleEvent inherited by @GUIView, called from loop
 * @notes   all events are handled in here. State information is needed to be sure which submenus are open!
 */
void GameView::handleEvent() {
    if (event.type == sf::Event::Closed)
        gameWindow.close();
    if (event.type == sf::Event::MouseButtonPressed &&
        menuText.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        menuOpen ? menuOpen = false : menuOpen = true;
    }

    if(event.type == sf::Event::KeyPressed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            std::cout << "Escape key pressed" << std::endl;
            state = State::SELECTION;
        }
    }
    int localTarget;
    if (!menuOpen && !winnerView) {
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
                    //if (playingField[localTarget].fieldstate != FIELD_STATE::EMPTY) {
                        state = State::FIELD_SELECTED;
                        selectedField = localTarget;
                        LOG("Field selected #" + std::to_string(selectedField));
                    //}
                    break;
                case State::FIELD_SELECTED:
                    //check that selected field is empty and non void
                    if (/*playingField[localTarget].fieldstate == FIELD_STATE::EMPTY &&*/
                        !(std::find(forbiddenFields.begin(), forbiddenFields.end(), localTarget + 1) !=
                          forbiddenFields.end())) {
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

    if (winnerView) {
        if (event.type == sf::Event::MouseButtonPressed &&
            winnerButton.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
            gameProperties.currentGameState = gameState::MAINMENU;
            winnerView = false;
        }
    }
}

/**
 * @brief                   moves a Stone from the playing field to a selected target Field
 * @notes                   sets Network Paramters, so GameMove is sent to server. Move is checked locally beforehand!
 * @param localTarget       index of the selected target field
 */
void GameView::moveStone(int localTarget) {
    //todo implement, that move is ignored when its not your turn
    int status = moveChecker.checkMove(selectedField, localTarget);
    bool red = false;
    if (!status) {
        std::cout << "Not allowed move from: " << selectedField << " to " << localTarget << std::endl;
        state = State::SELECTION;
        return;
    }

    // denn es wird nur der Move von feld x -> y gebraucht und ob der valide ist --> hier schon alles bekannt!
    NetworkData::networkDataBuffer.sourceTile = "TILE_" + std::to_string(selectedField + 1);
    NetworkData::networkDataBuffer.targetTile = "TILE_" + std::to_string(localTarget + 1);
    NetworkData::networkDataBuffer.state = networkState::gameMove;

    if(status == SIMPLE_MOVE){
        playingField[localTarget].fieldstate = FIELD_STATE::BLUE;
        playingField[selectedField].fieldstate = FIELD_STATE::EMPTY;
    }else if(status == DUPLICATE){
        playingField[localTarget].fieldstate = FIELD_STATE::BLUE;
    }
}

/**
 * @brief           checks if a button press was inside a hexagon shape
 * @notes           reference: http://www.playchilla.com/how-to-check-if-a-point-is-inside-a-hexagon
 * @param shape     shape to check
 * @return          true if inside, false if outside
 */
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
/**
 * @brief   implementing handleMouseCursor inherited by @GUIView
 * @notes   handles everything mouse cursor related
 */
void GameView::handleMouseCursor() {
    //get current mouse position relative to the window and convert from images coords to global coords
    currMousePos = sf::Mouse::getPosition(gameWindow);
    currWorldMousePos = gameWindow.mapPixelToCoords(currMousePos);
    if (menuText.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        menuText.setColor(sf::Color::Red);
    } else {
        menuText.setColor(sf::Color::Yellow);
    }


    if (!menuOpen) {
        for (int i = 0; i < 61; i++) {
            playingField[i].shape.setOutlineColor(sf::Color::White);
            playingField[i].shape.setOutlineThickness(1);
        }
        for (auto &tile : playingField) {
            if (isInside(tile.shape))
                highlightValidMoves(tile);

        }
    }

}

/**
 * @brief           highlights all valid moves for a given tile
 * @param tile      selected tile
 */
void GameView::highlightValidMoves(Tile &tile) {
    auto indirectNeighbors = moveChecker.getIndirectNeighbors(tile);
    for (int id : neighbors[tile.getID()]) {
        playingField[id].shape.setOutlineColor(sf::Color::Yellow);
        playingField[id].shape.setOutlineThickness(2.5);
    }
    for (int id : indirectNeighbors) {
        playingField[id].shape.setOutlineColor(sf::Color::Green);
        playingField[id].shape.setOutlineThickness(2.5);
    }
}

/**
 * @brief               sets score for red and blue player
 * @param scoreRed      score for red player
 * @param scoreBlue     score for blue player
 */
void GameView::setScore(int scoreRed, int scoreBlue) {
    this->scoreBlue.setString(std::to_string(scoreBlue));
    this->scoreRed.setString(std::to_string(scoreRed));
}

/**
 * @brief           sets move tracker
 * @param red       true if move tracker is set for the red player
 */
void GameView::setMoveTracker(bool red) {
    if (red) {
        moveTracker.setOutlineColor(sf::Color::Red);
        moveTracker.setPosition(.055 * windowWidth, .14 * windowHeight);
        return;
    }
    moveTracker.setOutlineColor(sf::Color::Blue);
    moveTracker.setPosition(.055 * windowWidth, .075 * windowHeight);
}

/**
 * @brief   processes network updates that may have happend
 * @notes   sets positons of playing stones and checks the flags (winner,tie,closed,etc.)
 */
void GameView::handleNetworkUpdate() {
    if (!NetworkData::networkDataBuffer.gameStatus.updatet)
        return;

    redStones.clear();
    blueStones.clear();

    for (int i = 0; i < 61; i++) {
        if (NetworkData::networkDataBuffer.gameStatus.board[i] == FIELD_STATE::RED) {
            redStones.emplace_back(true, sf::CircleShape(15));
            redStones[redStones.size() - 1].setField(i);
            redStones[redStones.size() - 1].moveToField(playingField[i].shape);
            redStones[redStones.size() - 1].shape.setOutlineColor(sf::Color::Black);
            redStones[redStones.size() - 1].shape.setOutlineThickness(5);
            redStones[redStones.size() - 1].shape.setFillColor(sf::Color::Red);
            playingField[i].fieldstate = FIELD_STATE::RED;
            playingField[i].stoneID = redStones.size() - 1;
        } else if (NetworkData::networkDataBuffer.gameStatus.board[i] == FIELD_STATE::BLUE) {
            blueStones.emplace_back(false, sf::CircleShape(15));
            blueStones[blueStones.size() - 1].setField(i);
            blueStones[blueStones.size() - 1].moveToField(playingField[i].shape);
            blueStones[blueStones.size() - 1].shape.setOutlineColor(sf::Color::Black);
            blueStones[blueStones.size() - 1].shape.setOutlineThickness(5);
            blueStones[blueStones.size() - 1].shape.setFillColor(sf::Color::Blue);
            playingField[i].fieldstate = FIELD_STATE::BLUE;
            playingField[i].stoneID = blueStones.size() - 1;
        }
    }

    //handle flags
    if (NetworkData::networkDataBuffer.gameStatus.isClosed)
        gameProperties.currentGameState = gameState::MAINMENU;
    if (NetworkData::networkDataBuffer.gameStatus.tie) {
        std::cout << "Tie. Leaving to MainMenu" << std::endl;
        gameProperties.currentGameState = gameState::MAINMENU;
    }


    NetworkData::networkDataBuffer.gameStatus.turn % 2 ? setMoveTracker(true) : setMoveTracker(false);
    redTurn = (bool) NetworkData::networkDataBuffer.gameStatus.turn % 2;
    setScore(NetworkData::networkDataBuffer.gameStatus.player1Points,
             NetworkData::networkDataBuffer.gameStatus.player2Points);

    //check for winner
    if (!NetworkData::networkDataBuffer.gameStatus.player1Points ||
        !NetworkData::networkDataBuffer.gameStatus.player2Points) {
        std::cout << "Winner detected" << std::endl;
        NetworkData::networkDataBuffer.inGame = false;
        NetworkData::networkDataBuffer.gameID.erase();
        winnerView = true;
    }

    NetworkData::networkDataBuffer.gameStatus.updatet = false;
}



















