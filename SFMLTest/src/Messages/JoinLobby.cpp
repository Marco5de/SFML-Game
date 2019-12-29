//
// Created by marco on 27.12.19.
//

#include "JoinLobby.h"
#include "../Network.h"

JoinLobby::JoinLobby(const std::string& userID, const std::string& lobbyID,const std::string& userName){
    message["messageType"] = "JoinLobby";
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
