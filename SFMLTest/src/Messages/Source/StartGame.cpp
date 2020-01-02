//
// Created by marco on 27.12.19.
//

#include "Headers/StartGame.h"
#include "../../Network.h"

StartGame::StartGame(const std::string& userId, const std::string& lobbyId){
    message["messageType"] = "StartGame";
    message["userId"] = userId;
    message["lobbyId"] = lobbyId;
}

json StartGame::getMessage() {
    return message;
}

std::string StartGame::getMessageString() {
    return message.dump();
}