//
// Created by marco on 10.11.19.
//

#include <iostream>
#include "ChangeNameMenu.h"

#define FONT ("Fonts/arial.ttf")
#define BACKGROUND_IMAGE ("images/MainMenu/background.jpg")


ChangeNameMenu::ChangeNameMenu(sf::RenderWindow &window, const int windowWidth, const int windowHeight,
                               gameState *gs) : windowHeight(windowHeight), windowWidth(windowWidth),
                                                changeNameWindow(window) {
    currentGameState = gs;
}


int ChangeNameMenu::initChangeNameMenu() {
    if (!menuFont.loadFromFile(FONT))
        return NAME_MENU_FONTLOADING_ERROR;
    if (!backgroundImage.loadFromFile(BACKGROUND_IMAGE))
        return NAME_MENU_IMAGELOADING_ERROR;

    backgroundSprite.setTexture(backgroundImage);


    backgroundText.setPosition(.125 * windowWidth, .25 * windowHeight);
    backgroundText.setSize(sf::Vector2f(.75 * windowWidth, .15 * windowHeight));
    backgroundText.setFillColor(sf::Color::Black);
    backgroundText.setOutlineColor(sf::Color::Magenta);
    backgroundText.setOutlineThickness(5);

    //todo center, looks terrible
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


    return NAME_MENU_SUCCESS;
}


void ChangeNameMenu::handleChangeNameMenu() {
    handleMouseCursour();
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

}

void ChangeNameMenu::handleMouseCursour() {
    currMousePos = sf::Mouse::getPosition(changeNameWindow);
    currWorldMousePos = changeNameWindow.mapPixelToCoords(currMousePos);
}

void ChangeNameMenu::handleEvent() {
    switch (event.type) {
        case sf::Event::Closed:
            changeNameWindow.close();
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == '\b') {
                if (enteredString.getSize() != 0)
                    enteredString.erase(enteredString.getSize() - 1, 1);
            } else {
                if (enteredString.getSize() < 18)
                    enteredString += event.text.unicode;
            }
            enteredText.setString(enteredString);
            break;
        case sf::Event::KeyPressed: //todo enter funktioniert noch nicht todo
            if (event.KeyPressed == sf::Keyboard::Enter)
                std::cout << "Write to file" << std::endl;
            break;
        case sf::Event::MouseButtonPressed:
            if (returnToMainMenu.getGlobalBounds().contains(currWorldMousePos.x, currWorldMousePos.y)) {
                *currentGameState = gameState::MAINMENU;
                changeNameWindow.setKeyRepeatEnabled(false);
            }
            break;
    }
}