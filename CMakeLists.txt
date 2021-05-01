cmake_minimum_required(VERSION 3.10)

project(Grand_Strategy CXX)

set (SRC_TEST
	 src/GameCore/World.cpp
	 src/GameCore/test1.cpp
	 )

include_directories(./include ./libs)
add_subdirectory(libs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

#add_executable(client ${CLIENT_SRC})
#add_executable(server ${SERVER_SRC})
add_executable(test1 ${SRC_TEST})

#target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
#target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-audio sfml-network noise)
target_link_libraries(test1 sfml-graphics sfml-window sfml-network noise)