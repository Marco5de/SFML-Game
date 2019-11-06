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



#define MAINMENU_FONTLOADING_ERROR ((-1))
#define MAINMENU_IMAGELOADING_ERROR ((-2))
#define MAINMENU_SUCCESS ((0))

/**
 * @class       MainMenu
 * @brief       MainMenu functionality is implemented in here
 */
class MainMenu {

public:
    MainMenu(sf::RenderWindow *window, int windowWidth, int windowHeight);

    int initMainMenu(); /**< in this function all the objects are created, font loaded etc. */
    int
    handleMainMenu(); /**< in this function the sprites/text etc. are drawn, this function is called from the main thread */


private:
    int windowWidth;
    int windowHeight;

    sf::Font mainMenuFont;
    sf::Font titleFont;

    sf::Texture backgroundImage;
    sf::Sprite backgroundSprite;

    sf::Text textStartGame;
    sf::Text textLeaveGame;
    sf::Text textTitle;

    sf::Event event;
    sf::Vector2i currMousePos;
    sf::Vector2f currWorldMousePos;
    sf::RenderWindow *mainMenuWindow;

    std::vector<sf::Drawable> drawableVector;

    void handleMouseCursor();

};


#endif //SFMLTEST_MAINMENU_H
