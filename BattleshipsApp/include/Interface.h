//
// Created by endriu on 15.12.2021.
//

#ifndef JIPP2_INTERFACE_H
#define JIPP2_INTERFACE_H

//#include <lib.h>
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

    void setTakenByUserShip(std::string newSquare, Interface* interf);
    void setTakenByEnemyShip(std::string newSquare, Interface* interf);
    void setDestroyedUserShipPart(std::string newSquare, Interface* interf);
    void setDestroyedEnemyShipPart(std::string newSquare, Interface* interf);
    bool isTakenByShip(std::string newSquare, Interface* interf);
    void setAlreadyShotUserSquare(std::string newSquare, Interface *interf);
    void setAlreadyShotEnemySquare(std::string newSquare, Interface *interf);
    void setDestroyedUserShipWhole(std::string newSquare, Interface* interf);
    void setDestroyedEnemyShipWhole(std::string newSquare, Interface* interf);


};

#endif //JIPP2_INTERFACE_H
