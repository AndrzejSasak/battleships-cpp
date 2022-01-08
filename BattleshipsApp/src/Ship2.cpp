//
// Created by endriu on 15.12.2021.
//

#include "../include/Ship2.h"

Ship2::Ship2() {
    //length = 2;
    numOfAliveParts = length;
    setAlive(true);
}

void Ship2::initShip(std::string *shipSquares) {
    shipSquare[0] = shipSquares[0];
    shipSquare[1] = shipSquares[1];
}

std::string* Ship2::getShipSquares() {
    return shipSquare;
}

int Ship2::getNumOfAliveParts() {
    return numOfAliveParts;
}

void Ship2::setNumOfAliveParts(int num) {
    numOfAliveParts = num;
}

int Ship2::getLength() {
    return length;
}



