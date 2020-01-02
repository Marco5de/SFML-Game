#include <SFML/Graphics.hpp>

#include "Controller.h"

#include "Game.h"
#include "Network.h"
#include "Messages/GetAvailableLobbies.h"
#include "Messages/CreateNewLobby.h"
#include "Messages/JoinLobby.h"
#include "Messages/LeaveLobby.h"
#include "Messages/StartGame.h"
#include "Messages/GameMove.h"
#include "Messages/LeaveGame.h"
#include <nlohmann/json.hpp>
#include "Messages/IncomingMessageParser.h"

using json = nlohmann::json;


#define LOGGING_LEVEL_1
//#define LOGGING_FILE
#include "logger.h"



#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main() {

    //enable antialiasing
    //Todo fenster sollte eigentlich auch im Controller erstellt werden, will aber irgendwie noch nicht so ganz
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Hexxagon",
                            sf::Style::Titlebar | sf::Style::Close, settings);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    GameProperties gameProperties(WINDOW_WIDTH, WINDOW_HEIGHT, 8, window);

    Controller controller(WINDOW_HEIGHT, WINDOW_WIDTH, 8, window);
    controller.initController();
    LOG("Init erolgreich: starte Loop");
    controller.loop();


    return 0;
}
