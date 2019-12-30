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

std::string getExJson(MessageType type) {
    json j;
    switch (type) {
        case MessageType::Welcome:
            j["messageType"] = MessageType::Welcome;
            j["userId"] = 1337;
            j["welcomeMessage"] = "Hallo du bist hier drinne";
            break;
        case MessageType::AvailableLobbies:
            j["messageType"] = MessageType::AvailableLobbies;
            j["userId"] = 1337;
            j["availableLobbies"] =
                    {"objects", {
                            {"object", {
                                    {"address", "adr1"},
                            },},
                            {"object", {
                                    {"address", "adr2"},
                            },},
                            {"object", {
                                    {"address", "adr3"},
                            },},
                    },
                    };
            break;
        case MessageType::LobbyCreated:
            j["messageType"] = MessageType::LobbyCreated;
            j["userId"] = 1337;
            j["lobbyId"] = 6969;
            j["successfullyCreated"] = true;
            break;
        case MessageType::LobbyJoined:
            j["messageType"] = MessageType::LobbyJoined;
            j["userId"] = 1337;
            j["lobbyId"] = 6969;
            j["successfullyJoined"] = false;
            break;
        case MessageType::LobbyStatus:
            j["messageType"] = MessageType::LobbyStatus;
            j["userId"] = 1337;
            j["lobbyId"] = 6969;
            j["lobby"] = "Todo lobby einfügen!";
            break;

        case MessageType::GameStarted:
            j["messageType"] = MessageType::GameStarted;
            j["userId"] = 1337;
            j["gameId"] = 6969;
            j["creationDate"] = "20:02:53_02-01-2020";
            break;
        case MessageType::GameStatus:
            j["messageType"] = MessageType::GameStatus;
            j["userId"] = 1337;
            j["gameId"] = 6969;
            j["playerOne"] = "Hier muss UUID hin";
            j["playerTwo"] = "Hier muss UUID hin 2";
            j["playerOneUserName"] = "UsernameP1";
            j["playerTwoUserName"] = "UsernameP2";
            j["playerOneLeft"] = false;
            j["playerTwoLeft"] = false;
            j["playerOnePoints"] = 17;
            j["playerTwoPoints"] = 9;
            j["board"] = "Hier muss das aktuelle board rein!";
            j["turn"] = 1;
            j["lastMoveFrom"] = TileEnum::TILE_4;
            j["lastMoveTo"] = TileEnum::TILE_42;
            j["creationDate"] = "20:02:53_02-01-2020";
            j["actionDate"] = "20:05:32_02-01-2020";
            j["activePlayer"] = "Hier muss UUID rein";
            j["tie"] = false;
            j["winner"] = "hier muss UUID des winners rein";
            j["isClosed"] = false;
            break;

        case MessageType::Strike:
            j["messageType"] = MessageType::Strike;
            j["userId"] = 1337;
            j["strikeCount"] = 7;
            j["maxStrikeCount"] = 14;
            break;
    }

    return j.dump();

}

void test() {
    class GetAvailableLobbies gal("str");
    class CreateNewLobby cnl("UUID", "IBimsLobby");
    class JoinLobby jl("UUID", "UUID", "UsernamexD");
    class LeaveLobby ll("UUID", "UUID");
    class StartGame sg("UUID", "UUID");
    class GameMove gm("UUID", "UUUID", "TILE_42","TILE51");
    class LeaveGame lg("UUID", "UUID");

    std::cout << "GetAvailableLobbies: " << gal.getMessageString() << std::endl;
    std::cout << "CreateNewLobby: " << cnl.getMessageString() << std::endl;
    std::cout << "JoinLobby: " << jl.getMessageString() << std::endl;
    std::cout << "LeaveLobby: " << ll.getMessageString() << std::endl;
    std::cout << "StartGame: " << sg.getMessageString() << std::endl;
    std::cout << "GameMove: " << gm.getMessageString() << std::endl;
    std::cout << "LeaveGame: " << lg.getMessageString() << std::endl;

    std::cout << "\n" << std::endl;

    IncomingMessageParser imp;
    imp.parseMessage(getExJson(Strike));

    std::cout << "\n" << std::endl;
}

int main() {
    //test();
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
