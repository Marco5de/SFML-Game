/**
 * @file Game.cpp
 * @defgroup genPurpose General Purpose
 * @ingroup genPurpose
 * @author Marco Deuscher
 * @date 10.11.2019
 * @brief in this header some general purpose things, helper functions and game state are implemented
 */


#include <fstream>
#include <sstream>
#include "Game.h"


/**
 * @brief           reads a String form the specified file into a buffer and returns a std::string Object,
 *                  can be used to get text ressources for i.e. buttons, textfields etc.
 * @param filepath  specifies path to text file that is supposed to be read
 * @return String   read in String
 */
std::string getStringFromFile(std::string filepath) {
    std::ifstream ifstream(filepath);
    std::stringstream buffer;
    buffer << ifstream.rdbuf();
    return buffer.str();
}


GameProperties::GameProperties(const unsigned int windowWidth, const unsigned int windowHeight,
                               const unsigned int level) : WINDOW_WIDTH(windowWidth), WINDOW_HEIGHT(windowHeight),
                                                           settings(0, 0, level)
                                                           /*,window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                                                                  "SFML Hexxagon",
                                                                  sf::Style::Titlebar | sf::Style::Close, settings) */{
    currentGameState = gameState::MAINMENU;
}