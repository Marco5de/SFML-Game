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
#include "Game.h"


#define GAMEVIEW_IMAGELOADING_ERROR ((-1))
#define GAMEVIEW_FONTLOADING_ERROR ((-2))
#define GAMEVIEW_SUCCESS (0)


//Todo das ganze acceleration zeugs in eine eigene player klasse packen, nur temp für test hier drin
//todo als nächstes muss dann keypress implementiert werden
//todo danach implementieren der hindernisse

class GameView{
public:
    GameView(sf::RenderWindow *gameWindow, const int windoowWidth, const int windowHeight, gameState *gs);
    int initGameView();
    int handleGameView();


private:
    const int windowWidth;
    const int windowHeight;

    sf::Event event;

    sf::RenderWindow *gameWindow;

    sf::Texture playingFieldTexture;
    sf::Texture playingFieldVoidTexture;
    std::vector<int> forbiddenFields{3,14,16,29,31,33,46,48,59};

    sf::Font textFont;
    sf::Font titleFont;
    sf::Font menuFont;

    sf::Text helpText;
    sf::Text titleText;
    sf::Text menuText;
    std::string helpString;

    std::vector<sf::CircleShape> playingField;

    gameState *currentGameState;

    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */

    void createPlayingField();
    void handleMouseCursour();

};


#endif //SFMLTEST_GAMEVIEW_H
