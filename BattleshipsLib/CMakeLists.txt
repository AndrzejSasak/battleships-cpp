cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(BattleshipsLib)

include_directories(include)

add_library(BattleshipsLib STATIC src/lib.cpp)