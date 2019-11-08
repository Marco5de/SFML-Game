cmake_minimum_required(VERSION 3.1)

project(SFMLTest)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)



find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


add_executable(SFMLTest main.cpp MainMenu.cpp MainMenu.h Game.h GameView.cpp GameView.h)
target_link_libraries(SFMLTest sfml-graphics sfml-audio)