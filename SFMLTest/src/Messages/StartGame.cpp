//
// Created by marco on 27.12.19.
//

#include "StartGame.h"
#include "../Network.h"

StartGame::StartGame(unsigned int userId, unsigned int lobbyId){
    message["messageType"] = MessageType::StartGame;
    message["userId"] = userId;
    message["lobbyId"] = lobbyId;
}

json StartGame::getMessage() {
    return message;
}

std::string StartGame::getMessageString() {
    return message.dump();
}