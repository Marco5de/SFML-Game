/**
 * @file MainMenu.h
 * @defgroup gameView Game View
 * @ingroup gameView
 * @author Marco Deuscher
 * @date 07.11.2019
 * @brief All the game logic and display are inside this class
 */
#include "GameView.h"


#define IMAGE_PLAYER_PATH ("images/GameView/player.png")



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
    if(!playerTexture.loadFromFile(IMAGE_PLAYER_PATH))
        return GAMEVIEW_IMAGELOADING_ERROR;


    playerSprite.setTexture(playerTexture);
    playerSprite.setPosition(.1 * windowWidth, .5 * windowHeight);
    playerSprite.setScale(.5,.5);

    accelaration_x = 0;
    acceleration_y = 0;
    velocity_x = 0;
    velocity_y = 0;
    dt = 1.0;

    return GAMEVIEW_SUCCESS;
}



int GameView::handleGameView() {
    while (gameWindow->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            gameWindow->close();
    }
    physics();

    gameWindow->clear();
    gameWindow->draw(playerSprite);
    gameWindow->display();


    return GAMEVIEW_SUCCESS;


}

void GameView::physics() {
    acceleration_y += 0.1;
    velocity_y = acceleration_y * dt;

    playerSprite.move(0,velocity_y * dt);
}


























