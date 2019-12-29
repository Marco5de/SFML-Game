//
// Created by marco on 27.12.19.
//

#include "GetAvailableLobbies.h"
#include "../Network.h"

GetAvailableLobbies::GetAvailableLobbies(const std::string& UUID){
    //stimmt so evtl nicht mit der Spezifikatio überein! --> in java sollte enum aber eigentlich auch einfach nur int von 0 an sein
    message["messageType"] = "GetAvailableLobbies";
    message["userId"] = UUID;
}


json GetAvailableLobbies::getMessage() {
    return message;
}

std::string GetAvailableLobbies::getMessageString() {
    return message.dump();
}