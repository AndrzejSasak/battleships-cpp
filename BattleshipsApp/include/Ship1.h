//
// Created by endriu on 03.01.2022.
//

#ifndef JIPP2_SHIP1_H
#define JIPP2_SHIP1_H

#include "Ship.h"

class Ship1 : public Ship {
private:
    const int length = 1;
    int numOfAliveParts;
    std::string shipSquare[1];

public:

    Ship1();
    void initShip(std::string *shipSquares) override;
    std::string* getShipSquares() override;

    int getLength() override;

    int getNumOfAliveParts() override;

    void setNumOfAliveParts(int num) override;
};


#endif //JIPP2_SHIP1_H
