cmake_minimum_required(VERSION 3.10)

project(Grand_Strategy CXX)

set(CLIENT_SRC
	src/client.cpp
    src/Company.cpp
    src/Tile.cpp
	src/UITools.cpp
	src/World.cpp
	src/Player.cpp
	src/EventHandler.cpp
	)

set (SERVER_SRC
	src/server.cpp
    src/Company.cpp
    src/Tile.cpp
	src/UITools.cpp
	src/World.cpp
	src/Player.cpp
	src/EventHandler.cpp
	)

include_directories(./include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(client ${CLIENT_SRC})
add_executable(server ${SERVER_SRC})

target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
