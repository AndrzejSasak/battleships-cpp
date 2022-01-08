//
// Created by endriu on 15.12.2021.
//

#ifndef JIPP2_SHIP_H
#define JIPP2_SHIP_H
#include <iostream>

class Ship {
private:
    int length;
    int numOfAliveParts;
    bool isAlive;
    bool isFriendly;
public:
    //napisac destruktor
    //~Ship();

    void setAlive(bool newAlive);
    bool getIsAlive() const;

    void setFriendly(bool newIsFriendly);
    bool getFriendly() const;

    virtual int getLength() = 0;
    virtual int getNumOfAliveParts() = 0;
    virtual void setNumOfAliveParts(int num) = 0;
    virtual void initShip(std::string *shipSquares) = 0;
    virtual std::string* getShipSquares() = 0;
    //virtual void setAlive(bool newAlive);

};

#endif //JIPP2_SHIP_H
