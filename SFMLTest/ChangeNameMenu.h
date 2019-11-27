//
// Created by marco on 10.11.19.
//

#ifndef SFMLTEST_CHANGENAMEMENU_H
#define SFMLTEST_CHANGENAMEMENU_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Game.h"

//todo documentation copied from main menu

#define NAME_MENU_SUCCESS ((0))
#define NAME_MENU_FONTLOADING_ERROR ((-1))
#define NAME_MENU_IMAGELOADING_ERROR ((-2))

class ChangeNameMenu {
public:
    ChangeNameMenu(sf::RenderWindow &window, GameProperties &gameProperties);
    int initChangeNameMenu();
    void handleChangeNameMenu();

private:
    const int windowWidth;     /**< Width of the window (not resizeable) */
    const int windowHeight;   /**< Height of the window (note resizeable)*/
    GameProperties &gameProperties;

    sf::Font menuFont;  /**< Font used for the two text Buttons (Start Game and Leave Game)*/
    sf::Texture backgroundImage;    /**< Texture containing the background image of the main menu */
    sf::Sprite backgroundSprite;    /**< Sprite used for displaying the background image in the main menu*/

    sf::RectangleShape backgroundText;
    sf::Text enterText;
    sf::RectangleShape enteredTextBackground;
    sf::Text enteredText;
    sf::Text returnToMainMenu;

    sf::String enteredString="";

    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */

    sf::Text enteredName;
    sf::Event event;                    /**< sf::Event used to check if window is still open (can also be used for button presses!)*/

    sf::RenderWindow &changeNameWindow;   /**< RenderWindow in which the mainMenu is drawn */
    //gameState *currentGameState;

    void handleEvent();
    void handleMouseCursour();

};


#endif //SFMLTEST_CHANGENAMEMENU_H
