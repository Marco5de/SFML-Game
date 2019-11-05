//
// Created by marco on 05.11.19.
//

#include "MainMenu.h"


MainMenu::MainMenu(sf::RenderWindow *window, int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight){
    mainMenuWindow = window;
}

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
