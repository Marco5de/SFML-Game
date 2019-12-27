//
// Created by marco on 27.12.19.
//

#include "CreateNewLobby.h"
#include "../Network.h"

CreateNewLobby::CreateNewLobby(unsigned int UUID, std::string lobbyName){
    message["messageType"] = MessageType::CreateNewLobby;
    message["userId"] = UUID;
    message["lobbyName"] = lobbyName;
}

json CreateNewLobby::getMessage() {
    return message;
}

std::string CreateNewLobby::getMessageString() {
    return message.dump();
}