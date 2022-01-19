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
    std::string *shipSquare;

public:

    Ship1();
    ~Ship1() override;

    /**
     * this function initializes ship squares based on the array *shipSquares
     * @param shipSquares array containing squares of the ship
     */
    void initShip(std::string *shipSquares) override;

    /**
     * this function returns the array of ship squares
     * @return array of ship squares
     */
    std::string* getShipSquares() override;

    /**
     * this function return the length of a ship
     * @return length of a ship
     */
    int getLength() override;

    /**
     * this function return the number of alive parts in a ship
     * @return number of alive parts in a ship
     */
    int getNumOfAliveParts() override;

    /**
    * this function sets the number of alive parts in a ship to num
    * @param num new number of alive parts in a ship
    */
    void setNumOfAliveParts(int num) override;
};


#endif //JIPP2_SHIP1_H
