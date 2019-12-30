//
// Created by marco on 23.12.19.
//

#ifndef SFMLTEST_NETWORK_H
#define SFMLTEST_NETWORK_H


#include <nlohmann/json.hpp>
#include "../Utils/Network/Include/easywsclient.h"

#include "Game.h"
#include "Network.h"
#include "Lobby.h"
#include "Messages/GetAvailableLobbies.h"
#include "Messages/CreateNewLobby.h"
#include "Messages/JoinLobby.h"
#include "Messages/LeaveLobby.h"
#include "Messages/StartGame.h"
#include "Messages/GameMove.h"
#include "Messages/LeaveGame.h"
#include "Messages/IncomingMessageParser.h"

using easywsclient::WebSocket;

enum MessageType {
    Welcome,
    GetAvailableLobbies,
    AvailableLobbies,
    CreateNewLobby,
    LobbyCreated,
    JoinLobby,
    LobbyJoined,
    LobbyStatus,
    LeaveLobby,
    StartGame,
    GameStarted,
    GameStatus,
    GameMove,
    LeaveGame,
    Strike
};

enum networkState{
    welcome,
    createLobby,
    getAvailableLobbies,
    joinLobby,
    leaveLobby,
    startGame,
    gameMove,
    idle
};

class Network {
public:
    void handleNetwork();

    int initNetwork();

private:
    WebSocket::pointer ws;
    IncomingMessageParser messageParser;
    std::string playerUUID;
};

namespace NetworkData {
    struct NetworkDataBuffer {
        networkState state{networkState::welcome};
        bool updated{false};
        std::string globalStringData;
        std::string UUID;
        std::string LID;
        bool lobby{false};
        bool createLobby{false};
        std::string lobbyname;
        std::vector<Lobby> lobbyVec;
        unsigned int lobbyIndex{0};
        bool insideLobby{false}; //nach beenden des client ohne beenden des servers ungültig!
        bool inGame{false};
    };
    extern NetworkDataBuffer networkDataBuffer;
};

//extern NetworkData::NetworkDataBuffer networkDataBuffer;


#endif //SFMLTEST_NETWORK_H
