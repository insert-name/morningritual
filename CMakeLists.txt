#Specify the cmake version being used
cmake_minimum_required(VERSION 2.6)

#Require pkg-config to continue
find_package(PkgConfig REQUIRED)

#Name of the project
set(PROJECT_NAME morningritual)
project(${PROJECT_NAME})

#Set CMake modules path
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules" ${CMAKE_MODULE_PATH})

#Tell the compiler to include -std=c++11
add_definitions(-std=c++11 -Wall)

#Libraries that can be imported with pkg-config
find_package(SFML 2 REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

#All the directories containing header files
include_directories(
"${PROJECT_SOURCE_DIR}/src/core/"
)

set(SOURCE_FILES
src/main.cpp
src/game.cpp
src/world.cpp
src/layer.cpp
src/common.cpp
src/gui.cpp
src/entity.cpp
src/soundmanager.cpp
src/widget.cpp
)

#Take the code and turn it into the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

#Link the final executable to the needed libraries
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
