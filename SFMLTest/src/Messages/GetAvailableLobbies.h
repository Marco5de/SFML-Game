//
// Created by marco on 27.12.19.
//

#ifndef SFMLTEST_GETAVAILABLELOBBIES_H
#define SFMLTEST_GETAVAILABLELOBBIES_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;


class GetAvailableLobbies {
public:
    GetAvailableLobbies(unsigned int UUID);
    json getMessage();
    std::string getMessageString();

private:
    json message;

};


#endif //SFMLTEST_GETAVAILABLELOBBIES_H
