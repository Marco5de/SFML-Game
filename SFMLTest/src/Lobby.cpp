//
// Created by marco on 27.12.19.
//

#include "Lobby.h"

Lobby::Lobby(std::string player1UUID, std::string player2UUID, std::string lobbyId, std::string lobbyName,
             std::string player1Username,
             std::string player2Username, std::string date, bool closed) :
             player1Username(player1Username),
             player1UUID(player1UUID),
             player2Username(player2Username),
             player2UUID(player2UUID),
             lobbyID(lobbyId),
             lobbyName(lobbyName),
             date(date),
             closed(closed)
{}

//todo output!
std::string Lobby::to_string() {
    return lobbyName + "\nPlayer1: " + player1Username + " Player2: " + player2Username + "\nCreationDate: " + date
        + "Closed: " + std::to_string(closed);
}
