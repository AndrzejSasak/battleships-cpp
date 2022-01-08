//
// Created by endriu on 03.01.2022.
//

#include "../include/Ship1.h"

Ship1::Ship1() {
    length = 1;
    numOfAliveParts = length;
    setAlive(true);
}

void Ship1::initShip(std::string *shipSquares) {
    shipSquare[0] = shipSquares[0];
}

int Ship1::getLength() {
    return length;
}

int Ship1::getNumOfAliveParts() {
    return numOfAliveParts;
}

void Ship1::setNumOfAliveParts(int num) {
    numOfAliveParts = num;
}

std::string* Ship1::getShipSquares() {
    return shipSquare;
}

