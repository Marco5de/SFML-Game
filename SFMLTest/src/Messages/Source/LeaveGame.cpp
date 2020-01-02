//
// Created by marco on 27.12.19.
//

#include "Headers/LeaveGame.h"
#include "../../Network.h"

LeaveGame::LeaveGame(const std::string& userId, const std::string& gameId){
    message["messageType"] = "LeaveGame";
    message["userId"] = userId;
    message["gameId"] = gameId;
}

json LeaveGame::getMessage() {
    return message;
}

std::string LeaveGame::getMessageString() {
    return message.dump();
}
