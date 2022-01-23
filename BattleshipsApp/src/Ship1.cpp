#include "../include/Ship1.h"

Ship1::Ship1() {
    numOfAliveParts = length;
    setAlive(true);
    shipSquare = new std::string[numOfAliveParts];
}

Ship1::~Ship1() {
    delete shipSquare;
}

void Ship1::initShip(std::string *shipSquares) {
    for(int i = 0; i < length; i++) {
        shipSquare[i] = shipSquares[i];
    }
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


