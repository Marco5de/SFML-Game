cmake_minimum_required(VERSION 3.1)

project(SFMLTest)



add_subdirectory(Utils/Logging)
add_subdirectory(Utils/GUI)
add_subdirectory(Utils/Network)
add_subdirectory(Google_tests)
add_subdirectory(src)

enable_testing()
