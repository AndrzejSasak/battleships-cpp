cmake_minimum_required(VERSION 3.16)

project(Battleships)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_subdirectory(BattleshipsApp)

add_subdirectory(BattleshipsLib)
