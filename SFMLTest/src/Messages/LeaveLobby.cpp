//
// Created by marco on 27.12.19.
//

#include "LeaveLobby.h"
#include "../Network.h"


LeaveLobby::LeaveLobby(unsigned int userId, unsigned int lobbyId){
    message["messageType"] = MessageType::LeaveLobby;
    message["userId"] = userId;
    message["lobbyId"] = lobbyId;
}


json LeaveLobby::getMessage() {
    return message;
}

std::string LeaveLobby::getMessageString() {
    return message.dump();
}
