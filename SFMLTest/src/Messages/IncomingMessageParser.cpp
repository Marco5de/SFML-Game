//
// Created by marco on 27.12.19.
//

#include <iostream>
#include "IncomingMessageParser.h"
#include "../Network.h"

#define LOGGING_LEVEL_1
#include "../../Utils/Logging/Include/logger.h"


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
                //insert only if lobby is not yet inside the vec!
                //todo der check funktioniert nicht!
                /*
                if (it == NetworkData::networkDataBuffer.lobbyVec.end()) {
                    LOG("Inserted new Lobby");

                }*/
                NetworkData::networkDataBuffer.lobbyVec.push_back(newLobby);
            }
            break;
        }
        case MessageType::LobbyCreated:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "LID: " << jsonMessage["lobbyId"] << std::endl;
            std::cout << "Success: " << jsonMessage["successfullyCreated"] << std::endl;
            NetworkData::networkDataBuffer.LID = jsonMessage["lobbyId"];
            break;
        case MessageType::LobbyJoined:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "LID: " << jsonMessage["lobbyId"] << std::endl;
            std::cout << "success: " << jsonMessage["successfullyJoined"] << std::endl;
            break;
        case MessageType::LobbyStatus:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "LID: " << jsonMessage["lobbyId"] << std::endl;
            std::cout << "Lobby: " << jsonMessage["lobby"] << std::endl;
            break;
        case MessageType::GameStarted:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "GID: " << jsonMessage["gameId"] << std::endl;
            std::cout << "CreationDate: " << jsonMessage["creationDate"] << std::endl;
            break;
        case MessageType::GameStatus:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "GID: " << jsonMessage["gameId"] << std::endl;
            std::cout << "playerOne: " << jsonMessage["playerOne"] << std::endl;
            std::cout << "playerTwo: " << jsonMessage["playerTwo"] << std::endl;
            std::cout << "playerOneUserName: " << jsonMessage["playerOneUserName"] << std::endl;
            std::cout << "playerTwoUserName: " << jsonMessage["playerTwoUserName"] << std::endl;
            std::cout << "playerOneLeft: " << jsonMessage["playerOneLeft"] << std::endl;
            std::cout << "playerTwoLeft: " << jsonMessage["playerTwoLeft"] << std::endl;
            std::cout << "playerOnePoints: " << jsonMessage["playerOnePoints"] << std::endl;
            std::cout << "playerTwoPoints: " << jsonMessage["playerTwoPoints"] << std::endl;
            std::cout << "Board: " << jsonMessage["board"] << std::endl;
            std::cout << "Turn: " << jsonMessage["turn"] << std::endl;
            std::cout << "LastMoveFrom: " << jsonMessage["lastMoveFrom"] << std::endl;
            std::cout << "LastMoveTo: " << jsonMessage["lastMoveTo"] << std::endl;
            std::cout << "creation Date: " << jsonMessage["creationDate"] << std::endl;
            std::cout << "actionDate: " << jsonMessage["actionDate"] << std::endl;
            std::cout << "Active Player: " << jsonMessage["activePlayer"] << std::endl;
            std::cout << "Tie: " << jsonMessage["tie"] << std::endl;
            std::cout << "Winner: " << jsonMessage["winner"] << std::endl;
            std::cout << "IsClosed: " << jsonMessage["isClosed"] << std::endl;
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
    lobby["lobbyName"].is_null() ? lobbyName = "" : lobbyId = lobby["lobbyName"];
    lobby["playerOneUserName"].is_null() ? player1Username = "" : player1Username = lobby["playerOneUserName"];
    lobby["playerTwoUserName"].is_null() ? player2Username = "" : player2Username = lobby["playerTwoUserName"];
    lobby["creationDate"].is_null() ? date = "" : date = lobby["creationDate"];


    Lobby newLobby(player1UUID, playser2UUID, lobbyId, lobbyName, player1Username, player2Username, date, closed);
    return newLobby;
}