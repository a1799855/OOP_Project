cmake_minimum_required(VERSION 3.15)
project( oop_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable( oop_project
	src/Base.h
	src/Base.cpp
	src/Debug.h
	src/Debug.cpp
	src/Entity.h
	src/Entity.cpp
	src/Unit.h
	src/Unit.cpp
	src/Knight.h
	src/Knight.cpp
	src/Peasant.h
	src/Peasant.cpp
	src/Game.h
	src/Game.cpp
	src/Main.cpp
	src/Projectile.h
	src/Projectile.cpp
	src/Archer.h
	src/Archer.cpp
	src/Economy.h
	src/Economy.cpp
	# src/FactionModifiers.h
	# src/FactionModifiers.h
	# src/Faction.h
	# src/Faction.h
)

#Enables warnings and adds optimisation
add_compile_options(-Wall -Wextra -Wpedantic -O2)
