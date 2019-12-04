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
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


add_executable(app ${SOURCE} )

target_link_libraries(app ${PROJECT_LINK_LIBS}
        logger
        )