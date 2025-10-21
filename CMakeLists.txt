cmake_minimum_required(VERSION 3.15)
project( oop_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable( oop_project
	src_alt/Archer.cpp
	src_alt/Archer.h
	src_alt/Base.cpp
	src_alt/Base.h
	src_alt/Debug.cpp
	src_alt/Debug.h
	src_alt/Economy.cpp
	src_alt/Economy.h
	src_alt/Entity.cpp
	src_alt/Entity.h
	src_alt/Faction.cpp
	src_alt/Faction.h
	src_alt/FactionModifiers.cpp
	src_alt/FactionModifiers.h
	src_alt/Game.cpp
	src_alt/Game.h
	src_alt/Knight.cpp
	src_alt/Knight.h
	src_alt/Main.cpp
	src_alt/MenuController.cpp
	src_alt/MenuController.h
	src_alt/Peasant.cpp
	src_alt/Peasant.h
	src_alt/Projectile.cpp
	src_alt/Projectile.h
	src_alt/Renderer.cpp
	src_alt/Renderer.h
	src_alt/Unit.cpp
	src_alt/Unit.h
)

#Enables warnings and adds optimisation
add_compile_options(-Wall -Wextra -Wpedantic -O2)
