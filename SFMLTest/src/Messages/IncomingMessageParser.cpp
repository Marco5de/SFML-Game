//
// Created by marco on 27.12.19.
//

#include <iostream>
#include "IncomingMessageParser.h"
#include "../Network.h"

#define LOGGING_LEVEL_1

#include "../../Utils/Logging/Include/logger.h"

void parseGameStatus(json msg);

IncomingMessageParser::IncomingMessageParser() {
    enumMap["Welcome"] = MessageType::Welcome;
    enumMap["GetAvailableLobbies"] = MessageType::GetAvailableLobbies;
    enumMap["AvailableLobbies"] = MessageType::AvailableLobbies;
    enumMap["CreateNewLobby"] = MessageType::CreateNewLobby;
    enumMap["LobbyCreated"] = MessageType::LobbyCreated;
    enumMap["LobbyJoined"] = MessageType::LobbyJoined;
    enumMap["LobbyStatus"] = MessageType::LobbyStatus;
    enumMap["LeaveLobby"] = MessageType::LeaveLobby;
    enumMap["StartGame"] = MessageType::StartGame;
    enumMap["GameStarted"] = MessageType::GameStarted;
    enumMap["GameStatus"] = MessageType::GameStatus;
    enumMap["GameMove"] = MessageType::GameMove;
    enumMap["LeaveGame"] = MessageType::LeaveGame;
    enumMap["Strike"] = MessageType::Strike;
}


void IncomingMessageParser::parseMessage(const std::string &message) {
    json jsonMessage = json::parse(message);
    std::string messageTypeString = jsonMessage["messageType"];
    unsigned int type = enumMap[messageTypeString];

    switch (type) {
        case MessageType::Welcome:
            std::cout << "Received Welcome message: " << jsonMessage["userId"] << std::endl;
            NetworkData::networkDataBuffer.UUID = jsonMessage["userId"];
            break;
        case MessageType::AvailableLobbies: {
            //clears vector each time! --> implement check from below!!
            NetworkData::networkDataBuffer.lobbyVec.clear();
            for (auto &lobby : jsonMessage["availableLobbies"]) {
                //todo remove all these copies!
                Lobby newLobby = parseAvailableLobbies(lobby);
                auto it = std::find(NetworkData::networkDataBuffer.lobbyVec.begin(),
                                    NetworkData::networkDataBuffer.lobbyVec.end(), newLobby);
                //todo do not clear vec each time!
                NetworkData::networkDataBuffer.lobbyVec.push_back(newLobby);
            }
            break;
        }
        case MessageType::LobbyCreated:
            NetworkData::networkDataBuffer.LID = jsonMessage["lobbyId"];
            break;
        case MessageType::LobbyJoined:
            std::cout << "success: " << jsonMessage["successfullyJoined"] << std::endl;
            if (jsonMessage["successfullyJoined"] == "true") {
                LOG("Joined successfully");
                NetworkData::networkDataBuffer.insideLobby = true;
                NetworkData::networkDataBuffer.LID = jsonMessage["lobbyId"];
            }
            break;
        case MessageType::LobbyStatus:
            LOG("Lobby Status erhalten!");
            //todo handle updates!

            break;
        case MessageType::GameStarted:
            LOG("Game Started received");
            NetworkData::networkDataBuffer.gameID = jsonMessage["gameId"];
            NetworkData::networkDataBuffer.inGame = true;
            break;
        case MessageType::GameStatus:
            LOG("GameStatus update erhalten");
            parseGameStatus(jsonMessage);
            break;
        case MessageType::Strike:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "StrikeCount: " << jsonMessage["strikeCount"] << std::endl;
            std::cout << "maxStrikeCount: " << jsonMessage["maxStrikeCount"] << std::endl;
            break;
        default:
            std::cout << "unbekannter Pfad --> Nutze default im switch case" << std::endl;
            break;
    }
}

//todo remove copies!
Lobby IncomingMessageParser::parseAvailableLobbies(json lobby) {
    std::string player1UUID;
    std::string playser2UUID;
    std::string lobbyId;
    std::string lobbyName;
    std::string player1Username;
    std::string player2Username;
    std::string date;
    bool closed = ("true" == lobby["isClosed"]);

    lobby["playerOne"].is_null() ? player1UUID = "" : player1UUID = lobby["playerOne"];
    lobby["playerTwo"].is_null() ? playser2UUID = "" : playser2UUID = lobby["playerTwo"];
    lobby["lobbyId"].is_null() ? lobbyId = "" : lobbyId = lobby["lobbyId"];
    lobby["lobbyName"].is_null() ? lobbyName = "" : lobbyName = lobby["lobbyName"];
    lobby["playerOneUserName"].is_null() ? player1Username = "" : player1Username = lobby["playerOneUserName"];
    lobby["playerTwoUserName"].is_null() ? player2Username = "" : player2Username = lobby["playerTwoUserName"];
    lobby["creationDate"].is_null() ? date = "" : date = lobby["creationDate"];

    Lobby newLobby(player1UUID, playser2UUID, lobbyId, lobbyName, player1Username, player2Username, date, closed);
    return newLobby;
}


void parseGameStatus(json jsonMessage) {
    NetworkData::networkDataBuffer.gameStatus.player1Username = jsonMessage["playerOneUserName"];
    NetworkData::networkDataBuffer.gameStatus.player2Username = jsonMessage["playerTwoUserName"];
    NetworkData::networkDataBuffer.gameStatus.player1Left = (jsonMessage["playerOneLeft"] ==
                                                             "true"); //todo check if functinal
    NetworkData::networkDataBuffer.gameStatus.player2left = (jsonMessage["playerTwoLeft"] == "true");
    NetworkData::networkDataBuffer.gameStatus.player1Points = jsonMessage["playerOnePoints"];
    NetworkData::networkDataBuffer.gameStatus.player2Points = jsonMessage["playerTwoPoints"];
    NetworkData::networkDataBuffer.gameStatus.turn = jsonMessage["turn"];
    jsonMessage["lastMoveFrom"].is_null() ? NetworkData::networkDataBuffer.gameStatus.lastMoveFrom = ""
                                          : NetworkData::networkDataBuffer.gameStatus.lastMoveFrom = jsonMessage["lastMoveFrom"];
    jsonMessage["lastMoveTo"].is_null() ? NetworkData::networkDataBuffer.gameStatus.lastMoveTo = ""
                                        : NetworkData::networkDataBuffer.gameStatus.lastMoveTo = jsonMessage["lastMoveTo"];
    NetworkData::networkDataBuffer.gameStatus.creationDate = jsonMessage["creationDate"];
    jsonMessage["actionDate"].is_null() ? NetworkData::networkDataBuffer.gameStatus.actionDate = ""
                                        : NetworkData::networkDataBuffer.gameStatus.actionDate = jsonMessage["actionDate"];
    NetworkData::networkDataBuffer.gameStatus.activePlayer = jsonMessage["activePlayer"];
    NetworkData::networkDataBuffer.gameStatus.tie = (jsonMessage["tie"] == "true");
    //todo for some reason, this string is always null even if a player has won --> moved check for winner into gameView/MoveChecker
    jsonMessage["winner"].is_null() ? NetworkData::networkDataBuffer.gameStatus.winner = "inGame"
                                    : NetworkData::networkDataBuffer.gameStatus.winner = jsonMessage["winner"];
    NetworkData::networkDataBuffer.gameStatus.isClosed = (jsonMessage["isClosed"] == "true");

    NetworkData::networkDataBuffer.gameID = jsonMessage["gameId"];

    //parse board
    NetworkData::networkDataBuffer.gameStatus.board.clear();
    for (int i = 0; i < 61; i++) {
        std::string index = "TILE_" + std::to_string(i + 1);
        if (jsonMessage["board"]["tiles"][index] == "FREE")
            NetworkData::networkDataBuffer.gameStatus.board.push_back(FIELD_STATE::EMPTY);
        else if(jsonMessage["board"]["tiles"][index] == "BLOCKED")
            NetworkData::networkDataBuffer.gameStatus.board.push_back(FIELD_STATE::BLOCKED);
        else if(jsonMessage["board"]["tiles"][index] == "PLAYERONE")
            NetworkData::networkDataBuffer.gameStatus.board.push_back(FIELD_STATE::RED);
        else if(jsonMessage["board"]["tiles"][index] == "PLAYERTWO")
            NetworkData::networkDataBuffer.gameStatus.board.push_back(FIELD_STATE::BLUE);
    }


    //set update flag
    NetworkData::networkDataBuffer.gameStatus.updatet = true;
}

