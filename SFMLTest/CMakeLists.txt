cmake_minimum_required(VERSION 3.1)

project(SFMLTest)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)
set ( PROJECT_LINK_LIBS sfml-graphics sfml-audio)
file(GLOB local_SOURCE
        "*.h"
        "*.cpp"
        "*.hpp"
        )

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_subdirectory(Utils/Logging)

add_executable(SFMLTest ${local_SOURCE} log.h logger.h)
target_link_libraries(SFMLTest ${PROJECT_LINK_LIBS}
        logger
        )