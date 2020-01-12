/**
 * @file Controller.cpp
 * @ingroup Controller
 * @author Marco Deuscher
 * @date 27.11.2019
 * @brief implementing Controller
 * @notes   should in theory act as a middleman betwenn View and model. In this implementation there is no model so Controller
 *          also handels that part
 */

#include <cassert>
#include "Controller.h"


#define LOGGING_LEVEL_1

#include "logger.h"


/**
 * @brief                       Constructor for @Controller
 * @param windowHeight          height of the window
 * @param windowWidth           width of the window
 * @param aliasingLevel         selected aliasing level
 * @param window                already created render window
 */
Controller::Controller(const unsigned int windowHeight, const unsigned int windowWidth,
                       const unsigned int aliasingLevel, sf::RenderWindow &window) :
        gameProperties(windowWidth, windowHeight, aliasingLevel, window),
        mainMenu(gameProperties.window, gameProperties),
        gameView(gameProperties.window, gameProperties),
        changeNameMenu(gameProperties.window, gameProperties),
        lobbyOverview(gameProperties.window, gameProperties),
        network(gameProperties) {}

/**
 * @brief   initializes controller and all of its components
 * @notes   widnow properties are set. All @GUIView are initialized. PlayerName is loaded. Score and MoveTracker are set
 *          Assertion for init of View in here!
 */
void Controller::initController() {
    gameProperties.window.setFramerateLimit(60);
    gameProperties.window.setKeyRepeatEnabled(false);
    gameProperties.playerName = getStringFromFile("nameConfig.txt");

    assert(mainMenu.init() == MAINMENU_SUCCESS);
    assert(gameView.init() == GAMEVIEW_SUCCESS);
    assert(changeNameMenu.init() == NAME_MENU_SUCCESS);
    assert(lobbyOverview.init() == MAINMENU_SUCCESS);
    assert(network.initNetwork());

    //set initial score --> has to be some value != 0, otherwise winner detection would be activated
    gameView.setScore(6, 6);
    gameView.setMoveTracker(false); //player 1 is always the starting player
    LOG("Init Controller Done")
}

/**
 * @brief   Main game Loop, handling GUI and network
 */
void Controller::loop() {
    while (gameProperties.window.isOpen()) {
        handleGUI();
        handleNetwork();
    }
}

/**
 * @brief   simply calls network class to perform network related tasks
 */
void Controller::handleNetwork() {
    network.handleNetwork();
}

/**
 * @brief   updates the currently selected view, based on the @GameProperties gameState
 */
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

