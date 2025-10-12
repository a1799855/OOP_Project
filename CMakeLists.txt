cmake_minimum_required(VERSION 3.15)
project( oop_project_dummy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable( oop_project_dummy
	src/main.cpp
	src/game.cpp
	src/renderer.cpp
	src/debug.cpp
	src/game.h
	src/renderer.h
	src/debug.h
)

#Enables warnings and adds optimisation
add_compile_options(-Wall -Wextra -Wpedantic -O2)
