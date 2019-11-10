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

#include "Game.h"

#define MAINMENU_FONTLOADING_ERROR ((-1))
#define MAINMENU_IMAGELOADING_ERROR ((-2))
#define MAINMENU_SUCCESS ((0))

/**
 * @class       MainMenu
 * @brief       MainMenu functionality is implemented in here
 */
class MainMenu {

public:
    MainMenu(sf::RenderWindow *window, const int windowWidth, const int windowHeight, gameState *gs);

    int initMainMenu(); /**< in this function all the objects are created, font loaded etc. */
    int handleMainMenu(); /**< in this function the sprites/text etc. are drawn, this function is called from the main thread */


private:
    const int windowWidth;     /**< Width of the window (not resizeable) */
    const int windowHeight;   /**< Height of the window (note resizeable)*/

    sf::Font mainMenuFont;  /**< Font used for the two text Buttons (Start Game and Leave Game)*/
    sf::Font titleFont;     /**< Font used for the Title of the game */

    sf::Texture backgroundImage;    /**< Texture containing the background image of the main menu */
    sf::Sprite backgroundSprite;    /**< Sprite used for displaying the background image in the main menu*/

    sf::RectangleShape backgroundRect;

    sf::Text textStartGame;         /**< text acting as a button to start the game, changes color when hovered above*/
    sf::Text textLeaveGame;         /**< text acting as a button to leave the game, changes color when hovered above*/
    sf::Text textTitle;             /**< text displaying the name of the game*/

    sf::Event event;                    /**< sf::Event used to check if window is still open (can also be used for button presses!)*/
    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */
    sf::RenderWindow *mainMenuWindow;   /**< RenderWindow in which the mainMenu is drawn */

    /* todo implement */
    std::vector<sf::Drawable> drawableVector; /**< vector containing all the drawables to simplify the drawing porcess, currently NOT used */

    void handleMouseCursor();
    void handleEvent();

    gameState *currentGameState; /**< enum class which holds the current game state */

};


#endif //SFMLTEST_MAINMENU_H
