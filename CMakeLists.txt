cmake_minimum_required(VERSION 3.15)
project( oop_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable( oop_project
	src/Archer.cpp
	src/Archer.h
	src/Base.cpp
	src/Base.h
	src/Debug.cpp
	src/Debug.h
	src/Economy.cpp
	src/Economy.h
	src/Entity.cpp
	src/Entity.h
	src/Faction.cpp
	src/Faction.h
	src/FactionModifiers.cpp
	src/FactionModifiers.h
	src/Game.cpp
	src/Game.h
	src/Knight.cpp
	src/Knight.h
	src/Main.cpp
	src/MenuController.cpp
	src/MenuController.h
	src/Peasant.cpp
	src/Peasant.h
	src/Projectile.cpp
	src/Projectile.h
	src/Renderer.cpp
	src/Renderer.h
	src/Unit.cpp
	src/Unit.h
)

#Enables warnings and adds optimisation
add_compile_options(-Wall -Wextra -Wpedantic -O2)
