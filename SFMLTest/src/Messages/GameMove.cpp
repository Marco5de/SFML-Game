//
// Created by marco on 27.12.19.
//

#include "GameMove.h"

GameMove::GameMove(const std::string& userId, const std::string& gameId,
        const std::string& tile1, const std::string& tile2){
    message["messageType"] = "GameMove";
    message["userId"] = userId;
    message["gameId"] = gameId;
    message["moveFrom"] = tile1;
    message["moveTo"] = tile2;
}

json GameMove::getMessage() {
    return message;
}

std::string GameMove::getMessageString() {
    return message.dump();
}
