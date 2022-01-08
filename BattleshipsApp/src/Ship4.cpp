//
// Created by endriu on 03.01.2022.
//

#include "../include/Ship4.h"

Ship4::Ship4() {
    length = 4;
    numOfAliveParts = length;
    setAlive(true);
}


void Ship4::initShip(std::string *shipSquares) {
    shipSquare[0] = shipSquares[0];
    shipSquare[1] = shipSquares[1];
    shipSquare[2] = shipSquares[2];
    shipSquare[3] = shipSquares[3];
}

std::string* Ship4::getShipSquares() {
    return shipSquare;
}

int Ship4::getLength() {
    return length;
}

int Ship4::getNumOfAliveParts() {
    return numOfAliveParts;
}

void Ship4::setNumOfAliveParts(int num) {
    numOfAliveParts = num;
}