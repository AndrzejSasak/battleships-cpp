//
// Created by endriu on 15.12.2021.
//

#ifndef JIPP2_SHIP_H
#define JIPP2_SHIP_H
#include <iostream>

class Ship {
private:
    bool isAlive;
public:
    virtual ~Ship() = default;

    /**
     * this function sets the state of a ship to newAlive
     * @param newAlive new state of the ship
     */
    void setAlive(bool newAlive);
    /**
     * this function returns the alive state of a ship
     * @return true if ship is alive, false if ship is not alive
     */
    bool getIsAlive() const;

    /**
     * this function return the length of a ship
     * @return length of a ship
     */
    virtual int getLength() = 0;

    /**
     * this function return the number of alive parts in a ship
     * @return number of alive parts in a ship
     */
    virtual int getNumOfAliveParts() = 0;

    /**
     * this function sets the number of alive parts in a ship to num
     * @param num new number of alive parts in a ship
     */
    virtual void setNumOfAliveParts(int num) = 0;

    /**
     * this function initializes ship squares based on the array *shipSquares
     * @param shipSquares array containing squares of the ship
     */
    virtual void initShip(std::string *shipSquares) = 0;

    /**
     * this function returns the array of ship squares
     * @return array of ship squares
     */
    virtual std::string* getShipSquares() = 0;


};

#endif //JIPP2_SHIP_H
