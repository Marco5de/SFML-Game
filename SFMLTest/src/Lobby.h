/**
 * @file Lobby.h
 * @defgroup Lobby Lobby
 * @ingroup Lobby
 * @author Marco Deuscher
 * @date 27.12.2019
 * @brief defining Lobby
 */


#ifndef SFMLTEST_LOBBY_H
#define SFMLTEST_LOBBY_H

#include <string>


class Lobby {
public:
    Lobby(std::string player1UUID,
            std::string player2UUID,
            std::string lobbyId,
            std::string lobbyName,
            std::string player1Username,
            std::string player2Username,
            std::string date,
            bool closed);

    std::string player1UUID;        /**< UUID of player one, saved inside a string*/
    std::string player2UUID;        /**< UUID of player two, saved inside a string*/
    std::string lobbyID;            /**< UUID of lobby, saved inside a string*/
    std::string lobbyName;          /**< lobby name*/
    std::string player1Username;    /**< username of first player*/
    std::string player2Username;    /**< username of second player*/


    std::string date;               /**< creation date of the lobby*/
    bool closed;                    /** state information about lobby*/

    /**
     * @brief           overloading equals operator for lobbies
     * @notes           two lobbies are equal if they have the same UUID
     * @param lhs       lefthandside
     * @param rhs       righthandside
     * @return          true if UUID equal, false if UUID not equal
     */
    friend bool operator==(const Lobby &lhs,const Lobby &rhs){
        return !lhs.lobbyID.compare(rhs.lobbyID);
    }
    std::string to_string();
};


#endif //SFMLTEST_LOBBY_H
