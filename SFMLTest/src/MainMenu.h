/**
 * @file MainMenu.h
 * @ingroup MainMenu
 * @author Marco Deuscher
 * @date 05.11.2019
 * @brief defining MainMenu
 */

#ifndef SFMLTEST_MAINMENU_H
#define SFMLTEST_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"
#include "GUIView.h"

#define MAINMENU_FONTLOADING_ERROR ((-1))
#define MAINMENU_IMAGELOADING_ERROR ((-2))
#define MAINMENU_SUCCESS ((0))

/**
 * @class       MainMenu
 * @brief       MainMenu functionality is implemented in here
 */
class MainMenu : public GUIView {

public:
    MainMenu(sf::RenderWindow &window,  GameProperties &gameProperties);

    int init() override; /**< in this function all the objects are created, font loaded etc. */
    int handleWindow() override; /**< in this function the sprites/text etc. are drawn, this function is called from the main thread */


private:
    GameProperties &gameProperties; /**< contains all the information about the window and current session*/

    const int windowWidth;     /**< Width of the window (not resizeable) */
    const int windowHeight;   /**< Height of the window (note resizeable)*/

    sf::Font mainMenuFont;  /**< Font used for the two text Buttons (Start Game and Leave Game)*/
    sf::Font titleFont;     /**< Font used for the Title of the game */

    sf::Texture backgroundImage;    /**< Texture containing the background image of the main menu */
    sf::Sprite backgroundSprite;    /**< Sprite used for displaying the background image in the main menu*/

    sf::Texture menuTexture;    /**< Texture containing the menuButton image*/
    sf::Sprite menuButton;      /**< Sprite used for displaying the menu Button*/
    bool menuOpen = false;      /**< Stores state information*/
    sf::RectangleShape subMenuBackground;   /**< acts as a background for the submenu*/
    sf::Text subMenuChangeName;             /**< Button inside the submenu*/

    sf::RectangleShape nameBackground;  /**< acts as a background on which the playerName is displayed*/
    sf::Text displayName;               /**< Text displaying the players name*/

    sf::RectangleShape backgroundRect;  /**< acts as background for the Title*/

    sf::Text textStartGame;         /**< text acting as a button to start the game, changes color when hovered above*/
    sf::Text textLeaveGame;         /**< text acting as a button to leave the game, changes color when hovered above*/
    sf::Text textTitle;             /**< text displaying the name of the game*/

    sf::Event event;                    /**< sf::Event used to check if window is still open (can also be used for button presses!)*/
    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */
    sf::RenderWindow &renderWindow;   /**< RenderWindow in which the mainMenu is drawn */

    sf::Music music;        /**< object containing the sound-Track of the game*/


    void handleMouseCursor() override;
    void handleEvent() override;
};


#endif //SFMLTEST_MAINMENU_H
