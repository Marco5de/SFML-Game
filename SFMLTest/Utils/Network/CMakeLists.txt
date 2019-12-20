cmake_minimum_required(VERSION 3.1)

PROJECT(WSclient)

file(GLOB SOURCES
        "Include/*.h"
        )
add_library(wsclient SHARED ${SOURCES} )

target_include_directories(wsclient PUBLIC Include)

#add_executable(Logger Source/log.cpp Include/log.h Include/logger.h)
set_target_properties(wsclient PROPERTIES LINKER_LANGUAGE CXX)

