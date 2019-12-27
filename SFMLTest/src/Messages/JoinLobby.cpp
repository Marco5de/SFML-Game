//
// Created by marco on 27.12.19.
//

#include "JoinLobby.h"
#include "../Network.h"

JoinLobby::JoinLobby(unsigned int userID, unsigned int lobbyID,std::string userName){
    message["messageType"] = MessageType::JoinLobby;
    message["userId"] = userID;
    message["lobbyId"] = lobbyID;
    message["userName"] = userName;
}

json JoinLobby::getMessage() {
    return message;
}

std::string JoinLobby::getMessageString() {
    return message.dump();
}
