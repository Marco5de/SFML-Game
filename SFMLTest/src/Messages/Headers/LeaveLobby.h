//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_LEAVELOBBY_H
#define SFMLTEST_LEAVELOBBY_H

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class LeaveLobby {
public:
    LeaveLobby(const std::string& userId, const std::string& lobbyId);
    json getMessage();
    std::string getMessageString();

private:
    json message;
};


#endif //SFMLTEST_LEAVELOBBY_H
