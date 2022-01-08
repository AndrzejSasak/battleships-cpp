cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)

project(BattleshipsApp)

include_directories(../BattleshipsLib/include)

add_executable(BattleshipsApp include/Interface.h include/Ship.h include/Ship1.h include/Ship2.h include/Ship3.h include/Ship4.h src/mainApp.cpp src/Interface.cpp src/Ship.cpp src/Ship1.cpp src/Ship2.cpp src/Ship3.cpp src/Ship4.cpp)

target_link_libraries(BattleshipsApp BattleshipsLib)