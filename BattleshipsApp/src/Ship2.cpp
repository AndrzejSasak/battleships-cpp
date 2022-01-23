#include "../include/Ship2.h"

Ship2::Ship2() {
    numOfAliveParts = length;
    setAlive(true);
    shipSquare = new std::string[numOfAliveParts];
}

Ship2::~Ship2() {
    delete shipSquare;
}

void Ship2::initShip(std::string *shipSquares) {
    for(int i = 0; i < length; i++) {
        shipSquare[i] = shipSquares[i];
    }
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


