//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_LOBBY_H
#define SFMLTEST_LOBBY_H

#include <string>

using UUID = unsigned int;

class Lobby {
public:
    UUID player1;
    UUID player2;
    UUID lobbyID;
    std::string player1Username;
    std::string playser2Username;

    //todo add date class!
    std::string date;
    bool closed;
};


#endif //SFMLTEST_LOBBY_H
