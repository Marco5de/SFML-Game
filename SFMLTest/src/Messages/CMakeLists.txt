cmake_minimum_required(VERSION 3.1)
project(Messages)

file(GLOB SOURCE_MESSAGES
        "Headers/*.h"
        "Source/*.cpp"
        "Headers/*.hpp"
        )

add_library(messagesLib ${SOURCE_MESSAGES})

target_include_directories (messagesLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})