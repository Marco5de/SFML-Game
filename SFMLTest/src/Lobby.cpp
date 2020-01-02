/**
 * @file Lobby.cpp
 * @ingroup Lobby
 * @author Marco Deuscher
 * @date 27.12.2019
 * @brief implementing Lobby
 */

#include "Lobby.h"

#include <utility>

/**
 * @brief                       Constructor for @Lobby
 * @param player1UUID           UUID of player one
 * @param player2UUID           UUID of player two
 * @param lobbyId               UUID for the lobby
 * @param lobbyName             lobbyName
 * @param player1Username       username of player one
 * @param player2Username       username of player two
 * @param date                  creation date of the lobby
 * @param closed                state information, if lobby is closed
 */
Lobby::Lobby(std::string player1UUID, std::string player2UUID, std::string lobbyId, std::string lobbyName,
             std::string player1Username,
             std::string player2Username, std::string date, bool closed) :
             player1Username(std::move(player1Username)),
             player1UUID(std::move(player1UUID)),
             player2Username(std::move(player2Username)),
             player2UUID(std::move(player2UUID)),
             lobbyID(std::move(lobbyId)),
             lobbyName(std::move(lobbyName)),
             date(std::move(date)),
             closed(closed)
{}

/**
 * @brief       returns formatted string used to display the relevant information about the lobby
 * @return      String containg username player1/2, lobbyName, creationDate, isClosed
 */
std::string Lobby::to_string() {
    return lobbyName + "\nPlayer1: " + player1Username + " Player2: " + player2Username + "\nCreationDate: " + date
        + "Closed: " + std::to_string(closed);
}
