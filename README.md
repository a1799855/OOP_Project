# OOP_Project
Pretty crude rough draft. I spent far too long trying to get the logic for units working. Decided to scrap units for the prototype.

To run this you need to install CMake and have the files in a folder somewhere.
The process should be like so:
sudo apt install cmake
cd prototype (or where and whatever you call the folder that the CMakeLists.txt file and src folder)
cmake -S . -B build
cmake --build build -j
./build/oop_project_dummy (name of the executable)
