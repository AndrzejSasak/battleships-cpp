#include "../include/User.h"

User::User(int numOfShips1, int numOfShips2, int numOfShips3, int numOfShips4, int numOfAliveShipPts):
        numOfShips1(numOfShips1),
        numOfShips2(numOfShips2),
        numOfShips3(numOfShips3),
        numOfShips4(numOfShips4),
        numOfAliveShipPts(numOfAliveShipPts)
{}

void User::setNumOfShips1(int num) {
    numOfShips1 = num;
}

void User::setNumOfShips2(int num) {
    numOfShips2 = num;
}

void User::setNumOfShips3(int num) {
    numOfShips3 = num;
}

void User::setNumOfShips4(int num) {
    numOfShips4 = num;
}

int User::getNumOfShips1() {
    return numOfShips1;
}

int User::getNumOfShips2() {
    return numOfShips2;
}

int User::getNumOfShips3() {
    return numOfShips3;
}

int User::getNumOfShips4() {
    return numOfShips4;
}

void User::setNumOfShots(int num) {
    numOfShots = num;
}

int User::getNumOfShots() {
    return numOfShots;
}

void User::setShotSquare(int numberOfShots, std::string newSquare) {
    shotSquares[numberOfShots] = newSquare;
}

std::string User::getShotSquare(int numberOfShots) {
    return shotSquares[numberOfShots];
}

void User::setNumOfAliveShipPts(int num) {
    numOfAliveShipPts = num;
}

int User::getNumOfAliveShipPts() {
    return numOfAliveShipPts;
}

void User::operator--() {
    --numOfAliveShipPts;
}

