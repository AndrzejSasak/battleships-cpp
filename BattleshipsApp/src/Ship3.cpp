//
// Created by endriu on 03.01.2022.
//

#include "../include/Ship3.h"

Ship3::Ship3() {
    numOfAliveParts = length;
    setAlive(true);
    shipSquare = new std::string[numOfAliveParts];
}

Ship3::~Ship3() {
    delete shipSquare;
}

void Ship3::initShip(std::string *shipSquares) {
    shipSquare[0] = shipSquares[0];
    shipSquare[1] = shipSquares[1];
    shipSquare[2] = shipSquares[2];
}

std::string* Ship3::getShipSquares() {
    return shipSquare;
}

int Ship3::getLength() {
    return length;
}
int Ship3::getNumOfAliveParts() {
    return numOfAliveParts;
}

void Ship3::setNumOfAliveParts(int num) {
    numOfAliveParts = num;
}

