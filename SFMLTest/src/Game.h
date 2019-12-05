/**
 * @file Game.h
 * @defgroup genPurpose General Purpose
 * @ingroup genPurpose
 * @author Marco Deuscher
 * @date 07.11.2019
 * @brief in this header some general purpose things, helper functions and game state are defined
 */

#ifndef SFMLTEST_GAME_H
#define SFMLTEST_GAME_H

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

#define NUMBER_START_STONES 6
constexpr std::array<int,NUMBER_START_STONES> redStartingPositions = {21,22,29,31,38,39};
constexpr std::array<int,NUMBER_START_STONES> blueStartingPositions = {0,4,26,34,56,60};

enum class gameState{
    MAINMENU,
    INGAME,
    CHANGENAME
};

std::string getStringFromFile(std::string filepath); /**< read String from File to a String. Can be used for text Ressources */
void writeStringToFile(std::string filepath,std::string name);


class GameProperties{
public:
    GameProperties(const unsigned int windowWidth, const unsigned int windowHeight,const unsigned int level,sf::RenderWindow &window);
    sf::RenderWindow &window;
    const unsigned int WINDOW_WIDTH;
    const unsigned int WINDOW_HEIGHT;
    sf::ContextSettings settings;
    gameState currentGameState;
    std::string playerName;
private:


};

#endif //SFMLTEST_GAME_H
