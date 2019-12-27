//
// Created by marco on 23.12.19.
//

#ifndef SFMLTEST_NETWORK_H
#define SFMLTEST_NETWORK_H


#include <nlohmann/json.hpp>
#include "../Utils/Network/Include/easywsclient.h"

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




class Network {
public:

private:
    WebSocket::pointer ws;

};


#endif //SFMLTEST_NETWORK_H
