//
// Created by endriu on 08.01.2022.
//

#include "../include/User.h"

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

void User::setShotSquare(int index, std::string value) {
    shotSquares[index] = value;
}

std::string User::getShotSquare(int index) {
    return shotSquares[index];
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

