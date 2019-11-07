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
#include "Game.h"


#define GAMEVIEW_IMAGELOADING_ERROR ((-1))
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

    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    std::vector<sf::Drawable> drawableVector;

    float accelaration_x;
    float acceleration_y;
    float velocity_x;
    float velocity_y;
    float dt;           /**< discrete time stamp used for physics */

    gameState *currentGameState;

    void physics();

};


#endif //SFMLTEST_GAMEVIEW_H
