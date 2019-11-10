/**
 * @file MainMenu.cpp
 * @defgroup MainMenu Main Menu
 * @ingroup MainMenu
 * @author Marco Deuscher
 * @date 05.11.2019
 * @brief Implementing Main Menu
 */


#include <iostream>
#include "MainMenu.h"


#define FONTS_MAINMENU_PATH ("Fonts/arial.ttf")
#define FONTS_TITLE_PATH ("Fonts/orange juice 2.0.ttf")
#define BACKGROUNDIMAGE_MAINMENU_PATH ("images/MainMenu/background.jpg")


//Todo alle drawables in einen std::vector<drawable> packen (Problem ist das iterieren darüber!
//todo alles unabhängig von der Fenstergröße machen


/**
 * @brief Constructor
 *
 * @param window                Window in which the main menu is drawn
 * @param windowWidth           width of the given window
 * @param windowHeight          height of the given window
 */
MainMenu::MainMenu(sf::RenderWindow *window, const int windowWidth, const int windowHeight, gameState *gs) : windowWidth(windowWidth),
                                                                                  windowHeight(windowHeight) {
    mainMenuWindow = window;
    currentGameState = gs;
}

/**
 * @brief       initializing MainMenu
 * @note        in this init function the font is loaded, the text initialized
 *
 * @return      MAINMENU_FONTLOADING_ERROR if loading the font failed, MAINMENU_SUCCESS if successfull
 */
int MainMenu::initMainMenu() {
    if (!mainMenuFont.loadFromFile(FONTS_MAINMENU_PATH))
        return MAINMENU_FONTLOADING_ERROR;
    if(!titleFont.loadFromFile(FONTS_TITLE_PATH))
        return MAINMENU_FONTLOADING_ERROR;
    if(!backgroundImage.loadFromFile(BACKGROUNDIMAGE_MAINMENU_PATH))
        return MAINMENU_IMAGELOADING_ERROR;


    backgroundSprite.setTexture(backgroundImage);

    backgroundRect.setPosition(.1 * windowWidth, .2 * windowHeight);
    backgroundRect.setFillColor(sf::Color::Black);
    backgroundRect.setOutlineColor(sf::Color::Magenta);
    backgroundRect.setOutlineThickness(10);
    sf::Vector2f size(.75 * windowWidth,.325 * windowHeight);
    backgroundRect.setSize(size);

    textStartGame.setFont(mainMenuFont);
    textStartGame.setString("Start Game");
    textStartGame.setCharacterSize(60);
    textStartGame.setPosition(.05 * windowWidth, .9 * windowHeight);

    textLeaveGame.setFont(mainMenuFont);
    textLeaveGame.setString("Leave Game");
    textLeaveGame.setCharacterSize(60);
    textLeaveGame.setPosition(.65 * windowWidth, .9 * windowHeight);

    textTitle.setFont(titleFont);
    textTitle.setString("Hexxagon");
    textTitle.setCharacterSize(200);
    textTitle.setPosition(.15 * windowWidth, .15 * windowHeight);
    textTitle.setFillColor(sf::Color::Magenta);
    textTitle.setOutlineColor(sf::Color::Black);


    return MAINMENU_SUCCESS;
}

/**
 * @brief       this function is called from the main game loop
 *
 * @return      MAINMENU_SUCCESS if successfull
 */
int MainMenu::handleMainMenu() {
    handleMouseCursor();
    //sf::Event event;
    while (mainMenuWindow->pollEvent(event)) {
        handleEvent();
    }

    mainMenuWindow->clear();
    mainMenuWindow->draw(backgroundSprite);
    mainMenuWindow->draw(textStartGame);
    mainMenuWindow->draw(textLeaveGame);
    mainMenuWindow->draw(backgroundRect);
    mainMenuWindow->draw(textTitle);

    mainMenuWindow->display();


    return MAINMENU_SUCCESS;
}

/**
 * @brief   handle everything MouseCursor related inside this function. Color of text is changed is hovering above
 *          Also checking for Mouse Button presses on the textfield, so they act es buttons!
 * @note Take care, that imageCoords have to be transformed to global coords
 */
void MainMenu::handleMouseCursor() {
    //get current mouse position relative to the window and convert from images coords to global coords
    currMousePos = sf::Mouse::getPosition(*mainMenuWindow);
    currWorldMousePos = mainMenuWindow->mapPixelToCoords(currMousePos);
    if (textStartGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        textStartGame.setColor(sf::Color::Cyan);
    } else {
        textStartGame.setColor(sf::Color::White);
    }

    if (textLeaveGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
        textLeaveGame.setColor(sf::Color::Red);
    } else {
        textLeaveGame.setColor(sf::Color::White);
    }
}


void MainMenu::handleEvent() {
    if (event.type == sf::Event::Closed)
        mainMenuWindow->close();
    else if(event.type == sf::Event::MouseButtonPressed && textStartGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
        *currentGameState = gameState::INGAME;
    else if(event.type == sf::Event::MouseButtonPressed && textLeaveGame.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y))
        mainMenuWindow->close();
}