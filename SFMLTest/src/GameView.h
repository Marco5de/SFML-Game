/**
 * @file MainMenu.h
 * @defgroup gameView Game View
 * @ingroup gameView
 * @author Marco Deuscher
 * @date 07.11.2019
 * @brief All the game logic and display are inside this class
 */

#ifndef SFMLTEST_GAMEVIEW_H
#define SFMLTEST_GAMEVIEW_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Game.h"
#include "Stone.h"
#include "Tile.h"
#include "GameMoveChecker.h"
#include "GUIView.h"
#include "Network.h"



#define GAMEVIEW_SUCCESS (0)


enum class State{
    SELECTION,      /**< player has to select source field*/
    FIELD_SELECTED  /**< player has to select target field*/
}; /**< enum representing the two states inside GameView*/

class GameView : GUIView{
public:
    GameView(sf::RenderWindow &gameWindow,  GameProperties &gameProperties);
    int init() override;
    int handleWindow() override;
    void setScore(int scoreRed, int scoreBlue);
    void setMoveTracker(bool red);

private:
    const int windowWidth;      /**< windowWidth, does not change*/
    const int windowHeight;     /**< windowHeight, does not change*/

    GameProperties &gameProperties;      /**< contains all the information about the window and current session*/

    bool menuOpen = false;      /**< representing state*/
    bool winnerView = false;    /**< representing state*/

    sf::Event event;    /**< sf::Event used to check if window is still open (can also be used for button presses!)*/

    sf::RenderWindow &gameWindow;   /** renderWindow in which game is drawn*/

    sf::Texture playingFieldTexture;        /** texture containing image used for tiles*/
    sf::Texture playingFieldVoidTexture;    /** texture containing image used for void tiles*/
    std::vector<int> forbiddenFields{3,14,16,29,31,33,46,48,59};    /** const vector containing forbidden fields*/

    sf::Text scoreRed;      /**< Text field displaying the score of the red player*/
    sf::Text scoreBlue;     /**< Text field displaying the score of the blue player*/

    sf::Font textFont;      /**< Font used to display text*/
    sf::Font titleFont;     /**< Font used to display title*/
    sf::Font menuFont;      /**< Font used to display menuItems*/

    sf::Text helpText;      /**< Text field containing help texts*/
    sf::Text titleText;     /**< Text field containing title*/
    sf::Text menuText;      /**< Text field containing menu Bbtton*/
    std::string helpString; /**< Text field containing helpString*/

    sf::RectangleShape menuBackground;  /**< acts as a background for the submenu*/
    sf::Text menuMainMenu;              /**< acts as a button inside the submenu*/
    sf::Text menuClose;                 /**< acts as a button inside the submenu*/

    sf::Text winnerText;                /**< displaying text, on who won the game*/
    sf::Text winnerButton;              /**< acts as a button, to return to main menu after game has ended*/

    sf::CircleShape moveTracker;        /**< CircleShape indicating whos turn it is*/

    std::vector<Tile> playingField;     /**< Vector of tiles representing the playing field*/
    std::vector<Stone> redStones;       /**< Vector of Stones, representing the stones of the red player*/
    std::vector<Stone> blueStones;      /**< Vector of Stones, representing the stones of the blue player*/
    GameMoveChecker moveChecker;        /**< object used to check the gameLogic*/


    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */

    bool redTurn;

    State state;                        /**< enum containing state information*/
    int selectedField;                  /**< index of selected field*/

    void createPlayingField();
    void handleMouseCursor() override;
    void handleEvent() override;
    bool isInside(sf::CircleShape &shape );
    void moveStone(int target);
    void highlightValidMoves(Tile &tile);
    void handleNetworkUpdate();
};


#endif //SFMLTEST_GAMEVIEW_H
