#include "../include/Ship4.h"

Ship4::Ship4() {
    numOfAliveParts = length;
    setAlive(true);
    shipSquare = new std::string[numOfAliveParts];
}

Ship4::~Ship4() {
    delete shipSquare;
}

void Ship4::initShip(std::string *shipSquares) {
    for(int i = 0; i < length; i++) {
        shipSquare[i] = shipSquares[i];
    }
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
