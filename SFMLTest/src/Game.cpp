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
#include <iostream>
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
/**
 * @brief               writes a given String, into a file and overrides all the previous content!
 * @param filepath      selected file
 * @param name          string to be written
 */
void writeStringToFile(std::string filepath,std::string name){
    std::ofstream file;
    file.open(filepath);
    file << name;
    file.close();
}

/**
 * @brief                   Constructor for @Gameproperties
 *
 * @param windowWidth       windowWidth, does not change
 * @param windowHeight      windowHeight, does not change
 * @param level             selected level of aliasing
 * @param window            already created renderWindow
 */
GameProperties::GameProperties(const unsigned int windowWidth, const unsigned int windowHeight,
                               const unsigned int level, sf::RenderWindow &window) : WINDOW_WIDTH(windowWidth),
                                                                                     WINDOW_HEIGHT(windowHeight),
                                                                                     window(window){
    currentGameState = gameState::MAINMENU;
}


/**
 * @brief sanitizes string to a format expected by server
 * @param str
 */
void sanitizeString(std::string & str){
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}