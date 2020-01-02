/**
 * @file LobbyOverview.h
 * @defgroup LobbyOverview Lobby overview
 * @ingroup LobbyOverview
 * @author Marco Deuscher
 * @date 23.12.2019
 * @brief defining LobbyOverview
 */

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
    GameProperties &gameProperties; /**< contains all the information about the window and current session*/

    sf::Font menuFont;  /**< Font used for the two text Buttons (Start Game and Leave Game)*/


    sf::Text titleText;         /**< displaying the title*/
    sf::Text returnToMain;      /**< button to return to main menu*/
    sf::Text startGame;         /**< button used to start game*/
    sf::Text createLobby;       /**< button used to create lobby*/
    sf::Text joinLobby;         /**< button used to joinLobby*/
    sf::Text lobby;             /**< displaying lobby information*/
    sf::Text leaveLobby;        /**< button used to leaveLobby*/

    sf::Texture reloadTexture;  /**< texture containing reload image*/
    sf::Sprite reloadSprite;    /**< displaying reload button*/
    sf::Texture nextTexture;    /**< texture containing arrow image*/
    sf::Sprite nextSprite;      /**< displaying next button*/



    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */

    sf::Event event;                    /**< sf::Event used to check if window is still open (can also be used for button presses!)*/

    sf::RenderWindow &lobbyWindow;   /**< RenderWindow in which the mainMenu is drawn */

    void handleEvent() override;
    void handleMouseCursor() override;
    void updateLobbyDisplay();

};


#endif //SFMLTEST_LOBBYOVERVIEW_H
