//
// Created by marco on 27.12.19.
//

#include "GameMove.h"

GameMove::GameMove(unsigned int userId, unsigned int gameId,
        TileEnum tile1, TileEnum tile2){
    message["messageType"] = MessageType::GameMove;
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
