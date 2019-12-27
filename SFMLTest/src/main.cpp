#include <SFML/Graphics.hpp>

#include "Controller.h"

#include "Game.h"
#include "Messages/GetAvailableLobbies.h"
#include "Messages/CreateNewLobby.h"
#include "Messages/JoinLobby.h"
#include "Messages/LeaveLobby.h"
#include "Messages/StartGame.h"
#include "Messages/GameMove.h"
#include "Messages/LeaveGame.h"


#define LOGGING_LEVEL_1
//#define LOGGING_FILE
#include "logger.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void test(){
    class GetAvailableLobbies gal(1337);
    class CreateNewLobby cnl(1337,"IBimsLobby");
    class JoinLobby jl(1337,6969,"UsernamexD");
    class LeaveLobby ll(1337,6969);
    class StartGame sg(1337,6969);
    class GameMove gm(1337,6969,TileEnum::TILE_1,TileEnum::TILE_42);
    class LeaveGame lg(1337,6969);

    std::cout << "GetAvailableLobbies: " << gal.getMessageString() << std::endl;
    std::cout << "CreateNewLobby: " << cnl.getMessageString() << std::endl;
    std::cout << "JoinLobby: " << jl.getMessageString() << std::endl;
    std::cout << "LeaveLobby: " << ll.getMessageString() << std::endl;
    std::cout << "StartGame: " << sg.getMessageString() << std::endl;
    std::cout << "GameMove: " << gm.getMessageString() << std::endl;
    std::cout << "LeaveGame: " << lg.getMessageString() << std::endl;

}

int main() {
    test();
    //enable antialiasing
    //Todo fenster sollte eigentlich auch im Controller erstellt werden, will aber irgendwie noch nicht so ganz
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;


    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Hexxagon", sf::Style::Titlebar | sf::Style::Close,settings);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    GameProperties gameProperties(WINDOW_WIDTH,WINDOW_HEIGHT,8,window);

    Controller controller(WINDOW_HEIGHT,WINDOW_WIDTH,8,window);
    controller.initController();
    LOG("Init erolgreich: starte Loop");
    controller.loop();


    return 0;
}
