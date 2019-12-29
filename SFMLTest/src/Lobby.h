//
// Created by marco on 27.12.19.
//

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

    std::string player1UUID;
    std::string player2UUID;
    std::string lobbyID;
    std::string lobbyName;
    std::string player1Username;
    std::string player2Username;

    //todo add date class!
    std::string date;
    bool closed;

    friend bool operator==(const Lobby &lhs,const Lobby &rhs){
        return !lhs.lobbyID.compare(rhs.lobbyID);
    }
    std::string to_string();
};


#endif //SFMLTEST_LOBBY_H
