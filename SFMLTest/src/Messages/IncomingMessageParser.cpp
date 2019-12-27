//
// Created by marco on 27.12.19.
//

#include <iostream>
#include "IncomingMessageParser.h"
#include "../Network.h"


void IncomingMessageParser::parseMessage(std::string message) {
    json jsonMessage = json::parse(message);

    switch ((unsigned int) jsonMessage["messageType"]) {
        case MessageType::Welcome:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "WMes: " << jsonMessage["welcomeMessage"] << std::endl;
            break;
        case MessageType::AvailableLobbies:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "lobbies: " << jsonMessage["availableLobbies"] << std::endl;
            break;
        case MessageType::LobbyCreated:
            std::cout << "UID: " << jsonMessage["userId"] << std::endl;
            std::cout << "LID: " << jsonMessage["lobbyId"] << std::endl;
            std::cout << "Success: " << jsonMessage["successfullyCreated"] << std::endl;
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
    }
}