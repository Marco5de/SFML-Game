//
// Created by marco on 23.12.19.
//

#ifndef SFMLTEST_LOBBYOVERVIEW_H
#define SFMLTEST_LOBBYOVERVIEW_H


#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "GUIView.h"

class LobbyOverview : public GUIView{
public:
    LobbyOverview(sf::RenderWindow &window, GameProperties &gameProperties);
    int init() override;
    int handleWindow() override;

private:
    const int windowWidth;     /**< Width of the window (not resizeable) */
    const int windowHeight;   /**< Height of the window (note resizeable)*/
    GameProperties &gameProperties;

    sf::Font menuFont;  /**< Font used for the two text Buttons (Start Game and Leave Game)*/


    sf::Text titleText;
    sf::Text returnToMain;
    sf::Text startGame;

    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */

    sf::Event event;                    /**< sf::Event used to check if window is still open (can also be used for button presses!)*/

    sf::RenderWindow &lobbyWindow;   /**< RenderWindow in which the mainMenu is drawn */
    //gameState *currentGameState;

    void handleEvent() override;
    void handleMouseCursor() override;

};


#endif //SFMLTEST_LOBBYOVERVIEW_H
