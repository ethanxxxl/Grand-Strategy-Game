cmake_minimum_required(VERSION 3.10)

project(Grand_Strategy CXX)

set(SRC
	src/main.cpp
	)

include_directories(./include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

add_executable(run ${SRC})

target_link_libraries(run sfml-graphics sfml-window sfml-system sfml-audio sfml-network)
