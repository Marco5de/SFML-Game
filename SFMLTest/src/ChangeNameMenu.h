/**
 * @file ChangeNameMenu.h
 * @defgroup ChangeNameMenu Change name menu
 * @ingroup ChangeNameMenu
 * @author Marco Deuscher
 * @date 10.11.2019
 * @brief defining ChangeNameMenu
 */

#ifndef SFMLTEST_CHANGENAMEMENU_H
#define SFMLTEST_CHANGENAMEMENU_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Game.h"
#include "GUIView.h"


#define NAME_MENU_SUCCESS ((0))
#define NAME_MENU_FONTLOADING_ERROR ((-1))
#define NAME_MENU_IMAGELOADING_ERROR ((-2))

class ChangeNameMenu : public GUIView{
public:
    ChangeNameMenu(sf::RenderWindow &window, GameProperties &gameProperties);
    int init() override;
    int handleWindow() override;

private:
    const int windowWidth;     /**< Width of the window (not resizeable) */
    const int windowHeight;   /**< Height of the window (note resizeable)*/
    GameProperties &gameProperties; /**< contains all the information about the window and current session*/

    sf::Font menuFont;  /**< Font used for the two text Buttons (Start Game and Leave Game)*/
    sf::Texture backgroundImage;    /**< Texture containing the background image of the main menu */
    sf::Sprite backgroundSprite;    /**< Sprite used for displaying the background image in the main menu*/

    sf::RectangleShape backgroundText;  /**< acts as a background for the displayed Text*/
    sf::Text enterText;     /**< displays the entered text*/
    sf::RectangleShape enteredTextBackground;   /**< acts as a background for the entered Text*/
    sf::Text enteredText;      /**< displays the entered Text*/
    sf::Text returnToMainMenu;  /**< button to return to MainMenu*/

    std::string enteredString="";    /**< contains the entered string*/

    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */

    sf::Event event;                    /**< sf::Event used to check if window is still open (can also be used for button presses!)*/

    sf::RenderWindow &changeNameWindow;   /**< RenderWindow in which the mainMenu is drawn */

    void handleEvent() override;
    void handleMouseCursor() override;

};


#endif //SFMLTEST_CHANGENAMEMENU_H
