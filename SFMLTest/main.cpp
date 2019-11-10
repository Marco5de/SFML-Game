#include <SFML/Graphics.hpp>
#include <iostream>

#include "MainMenu.h"
#include "GameView.h"


//Todo auslagern der spieleigenschaften in ein eigenes Game Propterties objekt --> fenster größe in den einzelnen modi, spielstatus --> löst auch das ENum problem
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Flappy Birds", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    //Todo handing enum raw pointer to class works but isn't a nice way to do this!
    gameState gameState = gameState::MAINMENU;

    MainMenu mainMenu(&window, WINDOW_WIDTH, WINDOW_HEIGHT, &gameState);
    GameView gameView(&window,WINDOW_WIDTH,WINDOW_HEIGHT,&gameState);


    if (mainMenu.initMainMenu() != MAINMENU_SUCCESS) {
        std::cout << "Error initting Main menu. exiting with error code1" << std::endl;
        std::exit(1);
    }

    if(gameView.initGameView() != GAMEVIEW_SUCCESS){
        std::cout << "Error initting Game View. Exiting with error code 1" << std::endl;
        std::exit(1);
    }

    while (window.isOpen()) {
        switch (gameState) {
            case gameState::MAINMENU:
                mainMenu.handleMainMenu();
                break;
            case gameState::INGAME:
                gameView.handleGameView();
                break;
        }

    }

    return 0;
}