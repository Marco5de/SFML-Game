/**
 * @file ChangeNameMenu.h
 * @ingroup ChangeNameMenu
 * @author Marco Deuscher
 * @date 10.11.2019
 * @brief implementing ChangeNameMenu
 */

#include <iostream>
#include <cassert>
#include "ChangeNameMenu.h"

#define LOGGING_LEVEL_1

#include "logger.h"

#define FONT ("Fonts/arial.ttf")
#define BACKGROUND_IMAGE ("images/MainMenu/background.jpg")

/**
 * @brief Constructor with common arguments for GUIView
 * @notes initializes windowWidth and windowHeight, which is not updated afterwards anymore!
 *
 * @param window
 * @param gameProperties
 */
ChangeNameMenu::ChangeNameMenu(sf::RenderWindow &window,
                               GameProperties &gameProperties) :
        changeNameWindow(window), gameProperties(gameProperties), windowHeight(gameProperties.WINDOW_HEIGHT),
        windowWidth(gameProperties.WINDOW_WIDTH) {
}

/**
 * @brief implements init of ChangeNameMenu inherited by @GUIView
 * @notes all Ressources are loaded, if not successfully assertin fails inside here!
 *
 * @return NAME_MENU_SUCCESS if successfull
 */
int ChangeNameMenu::init() {
    assert(menuFont.loadFromFile(FONT));
    assert(backgroundImage.loadFromFile(BACKGROUND_IMAGE));

    backgroundSprite.setTexture(backgroundImage);


    backgroundText.setPosition(.125 * windowWidth, .25 * windowHeight);
    backgroundText.setSize(sf::Vector2f(.75 * windowWidth, .15 * windowHeight));
    backgroundText.setFillColor(sf::Color::Black);
    backgroundText.setOutlineColor(sf::Color::Magenta);
    backgroundText.setOutlineThickness(5);


    enterText.setPosition(.25 * windowWidth, .3 * windowHeight);
    enterText.setCharacterSize(30);
    enterText.setFont(menuFont);
    enterText.setString("Enter your new Name (Maximum of 18 Characters)");
    enterText.setColor(sf::Color::Magenta);

    enteredTextBackground.setPosition(.125 * windowWidth, .65 * windowHeight);
    enteredTextBackground.setSize(sf::Vector2f(.75 * windowWidth, .15 * windowHeight));
    enteredTextBackground.setFillColor(sf::Color::Black);
    enteredTextBackground.setOutlineColor(sf::Color::Magenta);
    enteredTextBackground.setOutlineThickness(5);

    enteredText.setPosition(.15 * windowWidth, .65 * windowHeight);
    enteredText.setCharacterSize(30);
    enteredText.setFont(menuFont);
    enteredText.setString(enteredString);
    enteredText.setColor(sf::Color::Magenta);

    returnToMainMenu.setPosition(.7 * windowWidth, .9 * windowHeight);
    returnToMainMenu.setCharacterSize(30);
    returnToMainMenu.setFont(menuFont);
    returnToMainMenu.setString("Return to main menu");
    returnToMainMenu.setColor(sf::Color::Magenta);
    returnToMainMenu.setOutlineColor(sf::Color::Black);
    returnToMainMenu.setOutlineThickness(50);


    LOG("Init changeNameMenu done");
    return NAME_MENU_SUCCESS;
}

/**
 * @brief implements handleWindow inherited by @GUIView
 * @notes draws all text and objects in the scene
 * @return NAME_MENU_SUCCESS if successfull
 */
int ChangeNameMenu::handleWindow() {
    handleMouseCursor();
    while (changeNameWindow.pollEvent(event)) {
        handleEvent();
    }

    changeNameWindow.clear();
    changeNameWindow.draw(backgroundSprite);
    changeNameWindow.draw(backgroundText);
    changeNameWindow.draw(enterText);
    changeNameWindow.draw(enteredTextBackground);
    changeNameWindow.draw(enteredText);
    changeNameWindow.draw(returnToMainMenu);

    changeNameWindow.display();
    return NAME_MENU_SUCCESS;
}

/**
 * @brief implements handleMouseCursor inherited by @GUIView, is called from inside the loop
 * @notes simply transforms image to world coords
 */
void ChangeNameMenu::handleMouseCursor() {
    currMousePos = sf::Mouse::getPosition(changeNameWindow);
    currWorldMousePos = changeNameWindow.mapPixelToCoords(currMousePos);
}

/**
 * @brief implements handleEvent inherited by @GUIView, is called from inside the loop
 * @notes checks if button was clicked, if menu was open and what to do on button press
 */
void ChangeNameMenu::handleEvent() {
    switch (event.type) {
        case sf::Event::Closed:
            changeNameWindow.close();
            break;
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                gameProperties.currentGameState = gameState::MAINMENU;
                //enteredString.erase(enteredString.getSize()-1,1);
                sanitizeString(enteredString);
                writeStringToFile("nameConfig.txt", enteredString);
                gameProperties.playerName = enteredString;
                changeNameWindow.setKeyRepeatEnabled(false);
            }
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == '\b') {
                if (!enteredString.empty())
                    enteredString.erase(enteredString.size() - 1, 1);
            } else {
                if (enteredString.size() < 25)
                    enteredString += event.text.unicode;
            }
            enteredText.setString(enteredString);
            break;
        case sf::Event::MouseButtonPressed:
            if (returnToMainMenu.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                gameProperties.currentGameState = gameState::MAINMENU;
                writeStringToFile("nameConfig.txt", enteredString);
                gameProperties.playerName = enteredString;
                changeNameWindow.setKeyRepeatEnabled(false);
            }
            break;
    }
}