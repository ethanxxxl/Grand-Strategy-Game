cmake_minimum_required(VERSION 3.10)
project(Grand_Strategy CXX)

set(CMAKE_CXX_STANDARD 20)

# Platform specific configurations
if ( APPLE )
	message(">>> GENERATRING BUILD FILES FOR MACOS <<<")
	link_directories(/lib /usr/lib /usr/local/lib)
	include_directories(/usr/local/include)
elseif ( LINUX )
	message(">>> GENERATRING BUILD FILES FOR LINUX <<<")
elseif ( WINDOWS )
	message(">>> GENERATRING BUILD FILES FOR WINDOWS <<<")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (COORD_SYSTEMS_SRC
	src/GameCore/CoordinateSystems/AxialCoords.cpp
	src/GameCore/CoordinateSystems/CubeCoords.cpp
	src/GameCore/CoordinateSystems/PixelCoords.cpp
	src/GameCore/CoordinateSystems.cpp
	)

set (GAME_CORE_SRC
	 src/GameCore/World.cpp
	 src/GameCore/Game.cpp
	 src/GameCore/Player.cpp
	 src/GameCore/GameObject.cpp
	 src/GameCore/Grouping.cpp
	 ${COORD_SYSTEMS_SRC}
	 )
	 
set (NETWORKING_SRC
	src/ClientMessage.cpp
	src/ServerMessage.cpp
	)

include_directories(./include ./libs)

add_executable(client ${GAME_CORE_SRC} ${NETWORKING_SRC} src/client.cpp)
add_executable(server ${GAME_CORE_SRC} ${NETWORKING_SRC} src/server.cpp)
add_executable(test1 ${GAME_CORE_SRC} src/GameCore/test1.cpp)

target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
target_link_libraries(test1 sfml-graphics sfml-window sfml-network)