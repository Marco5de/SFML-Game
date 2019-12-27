cmake_minimum_required(VERSION 3.1)
project(Messages)

file(GLOB SOURCE
        "*.h"
        "*.cpp"
        "*.hpp"
        )

add_executable(messages ${SOURCE} StartGame.cpp StartGame.h LeaveGame.cpp LeaveGame.h IncomingMessageParser.cpp IncomingMessageParser.h)