//
// Created by marco on 27.11.19.
//

#ifndef SFMLTEST_CONTROLLER_H
#define SFMLTEST_CONTROLLER_H


#include "MainMenu.h"
#include "GameView.h"
#include "ChangeNameMenu.h"
#include "LobbyOverview.h"
#include "easywsclient.h"
#include <thread>

#include "Messages/IncomingMessageParser.h"
#include "Network.h"

using easywsclient::WebSocket;

class Controller {
public:
    Controller(const unsigned int windowHeight, const unsigned int windowWidth,const unsigned int aliasingLevel,sf::RenderWindow &window);
    void initController();
    void loop();

private:
    GameProperties gameProperties;
    MainMenu mainMenu;
    GameView gameView;
    ChangeNameMenu changeNameMenu;
    LobbyOverview lobbyOverview;

    Network network;


    void handleGUI();
    void handleNetwork();

};



#endif //SFMLTEST_CONTROLLER_H
