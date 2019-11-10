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

enum class gameState{
    MAINMENU,
    INGAME,
    CHANGENAME
};

std::string getStringFromFile(std::string filepath); /**< read String from File to a String. Can be used for text Ressources */


#endif //SFMLTEST_GAME_H
