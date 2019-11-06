#include <SFML/Graphics.hpp>
#include <iostream>

#include "MainMenu.h"



int main() {
    sf::RenderWindow window(sf::VideoMode(720, 480), "SFML Flappy Birds",sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);


    MainMenu mainMenu(&window,720,480);
    if (mainMenu.initMainMenu() != MAINMENU_SUCCESS) {
        std::cout << "Error initting Main menu. exiting with error code1" << std::endl;
        std::exit(1);
    }

    while (window.isOpen()) {
        mainMenu.handleMainMenu();
    }

    return 0;
}