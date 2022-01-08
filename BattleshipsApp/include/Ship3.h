//
// Created by endriu on 03.01.2022.
//

#ifndef JIPP2_SHIP3_H
#define JIPP2_SHIP3_H

#include "Ship.h"

class Ship3 : public Ship {
private:
    int length;
    int numOfAliveParts;
    std::string shipSquare[3];

public:
    Ship3();

    void initShip(std::string *shipSquares) override;
    std::string* getShipSquares() override;

    int getLength() override;

    int getNumOfAliveParts() override;

    void setNumOfAliveParts(int num) override;
};

#endif //JIPP2_SHIP3_H
