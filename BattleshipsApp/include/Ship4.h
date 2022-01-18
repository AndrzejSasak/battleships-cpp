//
// Created by endriu on 03.01.2022.
//

#ifndef JIPP2_SHIP4_H
#define JIPP2_SHIP4_H

#include "Ship.h"

class Ship4 : public Ship {
private:
    const int length = 4;
    int numOfAliveParts;
    std::string *shipSquare;

public:
    Ship4();
    ~Ship4() override;

    void initShip(std::string *shipSquares) override;
    std::string* getShipSquares() override;

    int getLength() override;

    int getNumOfAliveParts() override;

    void setNumOfAliveParts(int num) override;
};

#endif //JIPP2_SHIP4_H
