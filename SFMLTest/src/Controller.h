/**
 * @file Controller.h
 * @defgroup Controller Controller
 * @ingroup Controller
 * @author Marco Deuscher
 * @date 27.11.2019
 * @brief defining Controller
 * @notes   should in theory act as a middleman betwenn View and model. In this implementation there is no model so Controller
 *          also handels that part
 */
#ifndef SFMLTEST_CONTROLLER_H
#define SFMLTEST_CONTROLLER_H


#include "MainMenu.h"
#include "GameView.h"
#include "ChangeNameMenu.h"
#include "LobbyOverview.h"
#include "easywsclient.h"
#include <thread>

#include "Headers/IncomingMessageParser.h"
#include "Network.h"

using easywsclient::WebSocket;

class Controller {
public:
    Controller(const unsigned int windowHeight, const unsigned int windowWidth,const unsigned int aliasingLevel,sf::RenderWindow &window);
    void initController();
    void loop();

private:
    GameProperties gameProperties;   /**< contains all the information about the window and current session*/
    MainMenu mainMenu;  /** object implementing the mainMenu*/
    GameView gameView;  /** object implementing the gameView*/
    ChangeNameMenu changeNameMenu;  /** object implementing the change name menu*/
    LobbyOverview lobbyOverview;    /** object implementing the lobby overview*/

    Network network;    /** object handling everything network related*/


    void handleGUI();
    void handleNetwork();

};



#endif //SFMLTEST_CONTROLLER_H
