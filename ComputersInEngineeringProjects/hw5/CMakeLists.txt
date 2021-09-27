cmake_minimum_required(VERSION 3.10)
project(hw5)

set(CMAKE_CXX_STANDARD 11)

configure_file(images/enemy.png images/enemy.png COPYONLY)
configure_file(images/gameover.png images/gameover.png COPYONLY)
configure_file(images/tiles.png images/tiles.png COPYONLY)
configure_file(sounds/gameOverSound.ogg sounds/gameOverSound.ogg COPYONLY)
configure_file(sounds/blockBuilt.ogg sounds/blockBuilt.ogg COPYONLY)
configure_file(sounds/gameMusic.ogg sounds/gameMusic.ogg COPYONLY)
configure_file(fonts/AIRBORNEGP.ttf fonts/AIRBORNEGP.ttf COPYONLY)
configure_file(fonts/junegull.ttf fonts/junegull.ttf COPYONLY)

# Define sources and executable
set(EXECUTABLE_NAME "hw5")

add_executable(${EXECUTABLE_NAME} main.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()