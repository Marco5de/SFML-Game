//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_JOINLOBBY_H
#define SFMLTEST_JOINLOBBY_H

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class JoinLobby {
public:
    JoinLobby(const std::string& UUID, const std::string& lobbyID,const std::string& userName);
    json getMessage();
    std::string getMessageString();
private:
    json message;
};


#endif //SFMLTEST_JOINLOBBY_H
