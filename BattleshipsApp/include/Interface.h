//
// Created by endriu on 15.12.2021.
//

#ifndef JIPP2_INTERFACE_H
#define JIPP2_INTERFACE_H

#include <lib.h>
#include <iostream>

class Interface {
private:
    std::string userArea[100];
    std::string enemyArea[100];

public:
    Interface();
    //~Interface();

    //prints the interface
    void printInterface();

    friend void setTakenByUserShip(std::string newSquare, Interface* interface);
    friend void setTakenByEnemyShip(std::string newSquare, Interface* interface);
    friend void setDestroyedUserShipPart(std::string newSquare, Interface* interface);
    friend void setDestroyedEnemyShipPart(std::string newSquare, Interface* interface);
    friend bool isTakenByShip(std::string newSquare, Interface* interface);
    friend void setAlreadyShotUserSquare(std::string newSquare, Interface *interface);
    friend void setAlreadyShotEnemySquare(std::string newSquare, Interface *interface);
    friend void setDestroyedUserShipWhole(std::string newSquare, Interface* interface);
    friend void setDestroyedEnemyShipWhole(std::string newSquare, Interface* interface);


};

#endif //JIPP2_INTERFACE_H
