//
// Created by marco on 27.12.19.
//

#include "Headers/CreateNewLobby.h"
#include "../../Network.h"

CreateNewLobby::CreateNewLobby(const std::string& UUID, const std::string& lobbyName){
    message["messageType"] = "CreateNewLobby";
    message["userId"] = UUID;
    message["lobbyName"] = lobbyName;
}

json CreateNewLobby::getMessage() {
    return message;
}

std::string CreateNewLobby::getMessageString() {
    return message.dump();
}