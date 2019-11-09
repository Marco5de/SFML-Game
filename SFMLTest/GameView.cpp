/**
 * @file MainMenu.h
 * @defgroup gameView Game View
 * @ingroup gameView
 * @author Marco Deuscher
 * @date 07.11.2019
 * @brief All the game logic and display are inside this class
 */
#include <SFML/Graphics/CircleShape.hpp>
#include "GameView.h"


#define IMAGE_PLAYER_PATH ("images/GameView/player.png")
#define IMAGE_PLAYINGFIELD_PATH ("images/GameView/lavafull.jpg")



/**
 *
 * @param gameWindow
 * @param windowWidth
 * @param windowHeight
 * @param gs
 */
GameView::GameView(sf::RenderWindow *gw,const int windowWidth, const int windowHeight, gameState *gs) : windowHeight(windowHeight),windowWidth(windowWidth){
    gameWindow = gw;
    currentGameState = gs;
}

/**
 *
 * @return
 */
int GameView::initGameView() {
    if(!playingFieldTexture.loadFromFile(IMAGE_PLAYINGFIELD_PATH))
        return GAMEVIEW_IMAGELOADING_ERROR;



    playingField.reserve(61);

    for(int i=0; i<61; i++){
        playingField.push_back(sf::CircleShape(20.0f,6));
        playingField[i].setTexture(&playingFieldTexture);
        //rotate so that long edge is horizontally
        playingField[i].rotate(30);
    }

    createPlayingField();

    return GAMEVIEW_SUCCESS;
}

void GameView::createPlayingField() {
    //offset below are .075
    for(int i=0; i<5; i++){
        playingField[i].setPosition(.1 * windowWidth, (.25 + i*.075) * windowHeight);
    }
    for(int i=0; i<6; i++){
        playingField[6+i].setPosition(.15 * windowWidth, (.21 + i*.075) * windowHeight);
    }
}

int GameView::handleGameView() {
    while (gameWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            gameWindow->close();
    }

    gameWindow->clear();

    for(sf::CircleShape cs : playingField){
        gameWindow->draw(cs);
    }
    gameWindow->display();


    return GAMEVIEW_SUCCESS;


}



























