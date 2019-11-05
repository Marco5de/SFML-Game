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

#define FONTS_MAINMENU_PATH ("/home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/Fonts/arial.ttf")

#define MAINMENU_FONTLOADING_ERROR ((-1))
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
    sf::Text textStartGame;
    sf::Text textLeaveGame;

    sf::Event event;
    sf::RenderWindow *mainMenuWindow;

};


#endif //SFMLTEST_MAINMENU_H
