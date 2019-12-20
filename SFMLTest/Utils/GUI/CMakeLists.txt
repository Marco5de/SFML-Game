cmake_minimum_required(VERSION 3.1)

PROJECT(Centering)


set ( PROJECT_LINK_LIBS sfml-graphics sfml-audio)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB SOURCES
        "Include/*.h"
        )
add_library(centering SHARED ${SOURCES} )

target_include_directories(centering PUBLIC Include)

target_link_libraries(centering ${PROJECT_LINK_LIBS}
        )
#add_executable(Logger Source/log.cpp Include/log.h Include/logger.h)
set_target_properties(centering PROPERTIES LINKER_LANGUAGE CXX)

