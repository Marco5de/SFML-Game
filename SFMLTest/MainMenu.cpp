/**
 * @file MainMenu.cpp
 * @defgroup MainMenu Main Menu
 * @ingroup MainMenu
 * @author Marco Deuscher
 * @date 05.11.2019
 * @brief Implementing Main Menu
 */

#include "MainMenu.h"

/**
 * @brief Constructor
 *
 * @param window                Window in which the main menu is drawn
 * @param windowWidth           width of the given window
 * @param windowHeight          height of the given window
 */
MainMenu::MainMenu(sf::RenderWindow *window, int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight){
    mainMenuWindow = window;
}

/**
 * @brief       initializing MainMenu
 * @note        in this init function the font is loaded, the text initialized
 *
 * @return      MAINMENU_FONTLOADING_ERROR if loading the font failed, MAINMENU_SUCCESS if successfull
 */
int MainMenu::initMainMenu() {
    if (!mainMenuFont.loadFromFile(FONTS_MAINMENU_PATH)) {
        return MAINMENU_FONTLOADING_ERROR;
    }

    textStartGame.setFont(mainMenuFont);
    textStartGame.setString("Start Game");
    textStartGame.setCharacterSize(20);
    textStartGame.setPosition(0 * windowWidth, .9 * windowHeight);

    textLeaveGame.setFont(mainMenuFont);
    textLeaveGame.setString("Leave Game");
    textLeaveGame.setCharacterSize(20);
    textLeaveGame.setPosition(.75 * windowWidth, .9 * windowHeight);

    return MAINMENU_SUCCESS;
}

/**
 * @brief       this function is called from the main game loop
 *
 * @return      MAINMENU_SUCCESS if successfull
 */
int MainMenu::handleMainMenu() {
    //sf::Event event;
    while (mainMenuWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            mainMenuWindow->close();
    }

    mainMenuWindow->clear();
    mainMenuWindow->draw(textStartGame);
    mainMenuWindow->draw(textLeaveGame);
    mainMenuWindow->display();

    return MAINMENU_SUCCESS;
}
