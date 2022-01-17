//
// Created by endriu on 15.12.2021.
//

#ifndef JIPP2_SHIP2_H
#define JIPP2_SHIP2_H

#include "Ship.h"

class Ship2 : public Ship {
private:
    const int length = 2;
    int numOfAliveParts;
   // std::string shipSquare[2];
   //new allocation
   std::string *shipSquare;

public:
    Ship2();
    ~Ship2() override;

    void initShip(std::string *shipSquares) override;
    std::string* getShipSquares() override;

    int getLength() override;

    int getNumOfAliveParts() override;

    void setNumOfAliveParts(int num) override;


};



#endif //JIPP2_SHIP2_H
