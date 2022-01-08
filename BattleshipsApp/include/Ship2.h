//
// Created by endriu on 15.12.2021.
//

#ifndef JIPP2_SHIP2_H
#define JIPP2_SHIP2_H

#include "Ship.h"

class Ship2 : public Ship {
private:
    int length;
    int numOfAliveParts;
    std::string shipSquare[2];

public:
    Ship2();

    void initShip(std::string *shipSquares) override;
    std::string* getShipSquares() override;

    int getLength() override;

    int getNumOfAliveParts() override;

    void setNumOfAliveParts(int num) override;
};



#endif //JIPP2_SHIP2_H
