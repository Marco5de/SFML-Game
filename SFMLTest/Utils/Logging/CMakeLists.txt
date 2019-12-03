cmake_minimum_required(VERSION 3.1)

PROJECT(Logger)

file(GLOB SOURCES
        "Include/*.h"
         )
add_library(logger SHARED ${SOURCES} )

target_include_directories(logger PUBLIC Include)

#add_executable(Logger Source/log.cpp Include/log.h Include/logger.h)
set_target_properties(logger PROPERTIES LINKER_LANGUAGE CXX)

