//
// Created by marco on 23.12.19.
//

#ifndef SFMLTEST_NETWORK_H
#define SFMLTEST_NETWORK_H


#include <nlohmann/json.hpp>
#include <thread>
#include "../Utils/Network/Include/easywsclient.h"

#include "Game.h"
#include "Network.h"
#include "Lobby.h"
#include "Tile.h"
#include "Headers/GetAvailableLobbies.h"
#include "Headers/CreateNewLobby.h"
#include "Headers/JoinLobby.h"
#include "Headers/LeaveLobby.h"
#include "Headers/StartGame.h"
#include "Headers/GameMove.h"
#include "Headers/LeaveGame.h"
#include "Headers/IncomingMessageParser.h"

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
    Network(GameProperties &gameProperties);
    void handleNetwork();

    int initNetwork();

private:
    WebSocket::pointer ws;
    IncomingMessageParser messageParser;
    std::string playerUUID;
    GameProperties gameProperties;

    std::thread networkThread;
};

namespace NetworkData {
    struct GameStatus{
        std::string player1Username;
        std::string player2Username;
        bool player1Left{false};
        bool player2left{false};
        int player1Points;
        int player2Points;
        std::vector<FIELD_STATE> board{0};
        int turn;
        std::string lastMoveFrom;
        std::string lastMoveTo;
        std::string creationDate;
        std::string actionDate;
        std::string activePlayer;
        bool tie;
        std::string winner;
        bool isClosed;
        bool updatet;
    };
    struct NetworkDataBuffer {
        networkState state{networkState::welcome};
        bool updated{false};
        std::string globalStringData;
        std::string UUID;
        std::string LID;
        bool lobby{false};
        bool createLobby{false};
        std::string lobbyname;
        std::string playerName;
        std::vector<Lobby> lobbyVec;
        unsigned int lobbyIndex{0};
        bool insideLobby{false}; //nach beenden des client ohne beenden des servers ungültig!
        bool inGame{false};
        std::string sourceTile;
        std::string targetTile;
        std::string gameID;
        GameStatus gameStatus;
    };
    extern NetworkDataBuffer networkDataBuffer;
};



#endif //SFMLTEST_NETWORK_H
