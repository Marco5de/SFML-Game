# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build

# Include any dependencies generated for this target.
include Utils/Logging/CMakeFiles/logger.dir/depend.make

# Include the progress variables for this target.
include Utils/Logging/CMakeFiles/logger.dir/progress.make

# Include the compile flags for this target's objects.
include Utils/Logging/CMakeFiles/logger.dir/flags.make

# Object files for target logger
logger_OBJECTS =

# External object files for target logger
logger_EXTERNAL_OBJECTS =

Utils/Logging/liblogger.so: Utils/Logging/CMakeFiles/logger.dir/build.make
Utils/Logging/liblogger.so: Utils/Logging/CMakeFiles/logger.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library liblogger.so"
	cd /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build/Utils/Logging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/logger.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Utils/Logging/CMakeFiles/logger.dir/build: Utils/Logging/liblogger.so

.PHONY : Utils/Logging/CMakeFiles/logger.dir/build

Utils/Logging/CMakeFiles/logger.dir/clean:
	cd /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build/Utils/Logging && $(CMAKE_COMMAND) -P CMakeFiles/logger.dir/cmake_clean.cmake
.PHONY : Utils/Logging/CMakeFiles/logger.dir/clean

Utils/Logging/CMakeFiles/logger.dir/depend:
	cd /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/Utils/Logging /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build/Utils/Logging /home/marco/CLionProjects/CppProj/SFML-Game/SFMLTest/build/Utils/Logging/CMakeFiles/logger.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Utils/Logging/CMakeFiles/logger.dir/depend

