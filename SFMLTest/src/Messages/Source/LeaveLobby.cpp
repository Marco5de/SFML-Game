//
// Created by marco on 27.12.19.
//

#include "Headers/LeaveLobby.h"
#include "../../Network.h"


LeaveLobby::LeaveLobby(const std::string& userId, const std::string& lobbyId){
    message["messageType"] = "LeaveLobby";
    message["userId"] = userId;
    message["lobbyId"] = lobbyId;
}


json LeaveLobby::getMessage() {
    return message;
}

std::string LeaveLobby::getMessageString() {
    return message.dump();
}
