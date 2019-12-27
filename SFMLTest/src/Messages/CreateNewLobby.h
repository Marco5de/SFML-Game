//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_CREATENEWLOBBY_H
#define SFMLTEST_CREATENEWLOBBY_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CreateNewLobby {
public:
    CreateNewLobby(unsigned int UUID, std::string lobbyName);
    json getMessage();
    std::string getMessageString();
private:
    json message;
};


#endif //SFMLTEST_CREATENEWLOBBY_H
