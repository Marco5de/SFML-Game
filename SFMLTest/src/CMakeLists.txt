cmake_minimum_required(VERSION 3.2)
project(app)


## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE

file(GLOB SOURCE
        "*.h"
        "*.cpp"
        "*.hpp"
        )



set ( PROJECT_LINK_LIBS sfml-graphics sfml-audio)
find_package(nlohmann_json 3.7.0 REQUIRED)
#find_package(websocketpp REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

#fuege lib hinzu, damit ich in anderen directories dagegen linken kann, siehe test!
add_library(Game ${SOURCE})

#fuer das ausführen des eigentlichen spiels
add_executable(app ${SOURCE} Stone.cpp Stone.h Tile.cpp Tile.h GameMoveChecker.cpp GameMoveChecker.h ../Utils/GUI/Include/Centering.h GUIView.h ../Utils/Network/easywsclient.cpp ../Utils/Network/Include/easywsclient.h Network.cpp Network.h LobbyOverview.cpp LobbyOverview.h)

target_link_libraries(app ${PROJECT_LINK_LIBS}
        logger
        centering
        wsclient
        nlohmann_json::nlohmann_json
        )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")