//
// Created by marco on 23.12.19.
//

#ifndef SFMLTEST_NETWORK_H
#define SFMLTEST_NETWORK_H

#include <easywsclient.h>
#include <nlohmann/json.hpp>

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
