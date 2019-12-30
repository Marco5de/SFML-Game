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


#define GAMEVIEW_IMAGELOADING_ERROR ((-1))
#define GAMEVIEW_FONTLOADING_ERROR ((-2))
#define GAMEVIEW_SUCCESS (0)


//Todo das ganze acceleration zeugs in eine eigene player klasse packen, nur temp für test hier drin
//todo als nächstes muss dann keypress implementiert werden
//todo danach implementieren der hindernisse

enum class State{
    SELECTION,
    FIELD_SELECTED
};



class GameView : GUIView{
public:
    GameView(sf::RenderWindow &gameWindow,  GameProperties &gameProperties);
    int init() override;
    int handleWindow() override;
    void setScore(int scoreRed, int scoreBlue);
    void setMoveTracker(bool red);

private:
    const int windowWidth;
    const int windowHeight;

    GameProperties &gameProperties;

    bool menuOpen = false;

    sf::Event event;

    sf::RenderWindow &gameWindow;

    sf::Texture playingFieldTexture;
    sf::Texture playingFieldVoidTexture;
    std::vector<int> forbiddenFields{3,14,16,29,31,33,46,48,59};

    sf::Text scoreRed;
    sf::Text scoreBlue;

    sf::Font textFont;
    sf::Font titleFont;
    sf::Font menuFont;

    sf::Text helpText;
    sf::Text titleText;
    sf::Text menuText;
    std::string helpString;

    sf::RectangleShape menuBackground;
    sf::Text menuMainMenu;
    sf::Text menuClose;

    sf::CircleShape moveTracker;

    //std::vector<sf::CircleShape> playingField;
    std::vector<Tile> playingField;
    std::vector<Stone> redStones;
    std::vector<Stone> blueStones;
    GameMoveChecker moveChecker;


    sf::Vector2i currMousePos;          /**< Mouse position during the last frame in IMAGE COORDS! */
    sf::Vector2f currWorldMousePos;     /**< Mouse position during last frame in GLOBAL COORDS! */

    void createPlayingField();
    void handleMouseCursor() override;
    void handleEvent() override;
    bool isInside(sf::CircleShape &shape );
    void moveStone(int target);
    void highlightValidMoves(Tile &tile);
    void handleNetworkUpdate();

    //todo logik auslagern
    void checkPlayingField(bool movedStoneRed,int target);

    State state;
    int selectedField;
};


#endif //SFMLTEST_GAMEVIEW_H
