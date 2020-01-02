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
#include <map>
#include <SFML/Graphics/RenderWindow.hpp>

#define NUMBER_TILES 61
#define NUMBER_START_STONES 6
constexpr std::array<int, NUMBER_START_STONES> redStartingPositions = {21, 22, 29, 31, 38,
                                                                       39};     /**< starting positions of the red player*/
constexpr std::array<int, NUMBER_START_STONES> blueStartingPositions = {0, 4, 26, 34, 56,
                                                                        60};      /**< starting positions of the blue player*/


const std::array<const std::vector<int>, NUMBER_TILES> neighbors = {
        std::vector<int>{1, 5, 6},                    //0
        std::vector<int>{0, 2, 6, 7},                  //1
        std::vector<int>{1, 3, 7, 8},                  //2
        std::vector<int>{2, 4, 8, 9},                  //3
        std::vector<int>{3, 9, 10},                   //4

        std::vector<int>{0, 6, 11, 12},                //5
        std::vector<int>{0, 1, 5, 7, 12, 13},            //6
        std::vector<int>{1, 2, 6, 8, 13, 14},            //7
        std::vector<int>{2, 3, 7, 9, 14, 15},            //8
        std::vector<int>{3, 4, 8, 10, 15, 16},           //9
        std::vector<int>{4, 9, 16, 17},                //10

        std::vector<int>{5, 12, 18, 19},               //11
        std::vector<int>{5, 6, 11, 13, 19, 20},          //12
        std::vector<int>{6, 7, 12, 14, 20, 21},          //13
        std::vector<int>{7, 8, 13, 15, 21, 22},          //14
        std::vector<int>{8, 9, 14, 16, 22, 23},          //15
        std::vector<int>{9, 10, 15, 17, 23, 24},         //16
        std::vector<int>{10, 16, 24, 24},              //17

        std::vector<int>{11, 19, 26, 27},              //18
        std::vector<int>{11, 12, 18, 20, 27, 28},        //19
        std::vector<int>{12, 13, 19, 21, 28, 29},        //20
        std::vector<int>{13, 14, 20, 22, 29, 30},        //21
        std::vector<int>{14, 15, 21, 23, 30, 31},        //22
        std::vector<int>{15, 16, 22, 24, 31, 32},        //23
        std::vector<int>{16, 17, 23, 25, 32, 33},        //24
        std::vector<int>{17, 24, 33, 34},              //25

        std::vector<int>{18, 27, 35},                 //26
        std::vector<int>{18, 19, 26, 28, 35, 36},        //27
        std::vector<int>{19, 20, 27, 29, 36, 37},        //28
        std::vector<int>{20, 21, 28, 30, 37, 38},        //29
        std::vector<int>{21, 22, 29, 31, 38, 39},        //30
        std::vector<int>{22, 23, 30, 32, 39, 40},        //31
        std::vector<int>{23, 24, 31, 33, 40, 41},        //32
        std::vector<int>{24, 25, 32, 34, 41, 42},        //33
        std::vector<int>{25, 33, 42},                 //34

        std::vector<int>{26, 27, 36, 43},              //35
        std::vector<int>{27, 28, 35, 37, 43, 44},        //36
        std::vector<int>{28, 29, 36, 38, 44, 45},        //37
        std::vector<int>{29, 30, 37, 39, 45, 46},        //38
        std::vector<int>{30, 31, 38, 40, 46, 47},        //39
        std::vector<int>{31, 32, 39, 41, 47, 48},        //40
        std::vector<int>{32, 33, 40, 42, 48, 49},        //41
        std::vector<int>{33, 34, 41, 49},              //42

        std::vector<int>{35, 36, 44, 50},              //43
        std::vector<int>{36, 37, 43, 45, 50, 51},        //44
        std::vector<int>{37, 38, 44, 46, 51, 52},        //45
        std::vector<int>{38, 39, 45, 47, 52, 53},        //46
        std::vector<int>{39, 40, 46, 48, 53, 54},        //47
        std::vector<int>{40, 41, 47, 49, 54, 55},        //48
        std::vector<int>{41, 42, 48, 55},              //49

        std::vector<int>{43, 44, 51, 56},              //50
        std::vector<int>{44, 45, 50, 52, 56, 57},        //51
        std::vector<int>{45, 46, 51, 53, 57, 58},        //52
        std::vector<int>{46, 47, 52, 54, 58, 59},        //53
        std::vector<int>{47, 48, 53, 55, 59, 60},        //54
        std::vector<int>{48, 49, 54, 60},              //55

        std::vector<int>{50, 51, 57},                 //56
        std::vector<int>{51, 52, 56, 58},              //57
        std::vector<int>{52, 53, 57, 59},              //58
        std::vector<int>{53, 54, 58, 60},              //59
        std::vector<int>{54, 55, 59}                  //60
}; /**< lookup table for the neighbors of a given tile*/

enum class gameState {
    MAINMENU,
    LOBBY,
    INGAME,
    CHANGENAME
}; /**< enum containing the possible gamestate, each corresponding to a @GUIView*/

std::string
getStringFromFile(std::string filepath); /**< read String from File to a String. Can be used for text Ressources */
void writeStringToFile(std::string filepath, std::string name);  /**< write String into a file */


class GameProperties {
public:
    GameProperties(const unsigned int windowWidth, const unsigned int windowHeight, const unsigned int level,
                   sf::RenderWindow &window);

    sf::RenderWindow &window;               /**< render window used by all @GUIView*/
    const unsigned int WINDOW_WIDTH;        /**< window width, does not change*/
    const unsigned int WINDOW_HEIGHT;       /**< window height, does not change*/
    sf::ContextSettings settings;           /**< render window settings*/
    gameState currentGameState;             /**< enum gameState referring to currently display @GUIView*/
    std::string playerName;                 /**< currently selected username*/
private:

};


#endif //SFMLTEST_GAME_H
