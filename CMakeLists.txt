cmake_minimum_required(VERSION 3.10)
project(Grand_Strategy CXX)

set(CMAKE_CXX_STANDARD 20)

# Platform specific configurations
if ( APPLE )
	message(">>> GENERATRING BUILD FILES FOR MACOS <<<")
	link_directories(/lib /usr/lib /usr/local/lib)
elseif ( LINUX )
	message(">>> GENERATRING BUILD FILES FOR LINUX <<<")
elseif ( WINDOWS )
	message(">>> GENERATRING BUILD FILES FOR WINDOWS <<<")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (COORD_SYSTEMS_SRCS
	src/GameCore/CoordinateSystems/AxialCoords.cpp
	src/GameCore/CoordinateSystems/CubeCoords.cpp
	src/GameCore/CoordinateSystems/PixelCoords.cpp
	src/GameCore/CoordinateSystems/CoordinateSystems.cpp
	)

set (SRC_TEST
	 src/GameCore/World.cpp
	 src/GameCore/test1.cpp
	 ${COORD_SYSTEMS_SRCS}
	 )

include_directories(./include ./libs)

set(CMAKE_BUILD_TYPE Debug)

#add_executable(client ${CLIENT_SRC})
#add_executable(server ${SERVER_SRC})
add_executable(test1 ${SRC_TEST})

#target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
#target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
target_link_libraries(test1 sfml-graphics sfml-window sfml-network)