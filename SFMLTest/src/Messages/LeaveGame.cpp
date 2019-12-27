//
// Created by marco on 27.12.19.
//

#include "LeaveGame.h"
#include "../Network.h"

LeaveGame::LeaveGame(unsigned int userId, unsigned int gameId){
    message["messageType"] = MessageType::LeaveGame;
    message["userId"] = userId;
    message["gameId"] = gameId;
}

json LeaveGame::getMessage() {
    return message;
}

std::string LeaveGame::getMessageString() {
    return message.dump();
}
