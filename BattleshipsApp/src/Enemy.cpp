//
// Created by endriu on 08.01.2022.
//

#include "../include/Enemy.h"

Enemy::Enemy(int numOfShips1, int numOfShips2, int numOfShips3, int numOfShips4, int numOfAliveShipPts):
numOfShips1(numOfShips1),
numOfShips2(numOfShips2),
numOfShips3(numOfShips3),
numOfShips4(numOfShips4),
numOfAliveShipPts(numOfAliveShipPts)
{}

void Enemy::setDifficulty(int diffValue) {
    difficulty = diffValue;
}

int Enemy::getDifficulty() {
    return difficulty;
}

void Enemy::setNumOfShips1(int num) {
    numOfShips1 = num;
}

void Enemy::setNumOfShips2(int num) {
    numOfShips2 = num;
}

void Enemy::setNumOfShips3(int num) {
    numOfShips3 = num;
}

void Enemy::setNumOfShips4(int num) {
    numOfShips4 = num;
}

int Enemy::getNumOfShips1() {
    return numOfShips1;
}

int Enemy::getNumOfShips2() {
    return numOfShips2;
}

int Enemy::getNumOfShips3() {
    return numOfShips3;
}

int Enemy::getNumOfShips4() {
    return numOfShips4;
}

void Enemy::setNumOfShots(int num) {
    numOfShots = num;
}

int Enemy::getNumOfShots() {
    return numOfShots;
}

void Enemy::setShotSquare(int index, std::string value) {
    shotSquares[index] = value;
}

std::string Enemy::getShotSquare(int index) {
    return shotSquares[index];
}

void Enemy::setNumOfAliveShipPts(int num) {
    numOfAliveShipPts = num;
}

int Enemy::getNumOfAliveShipPts() {
    return numOfAliveShipPts;
}

void Enemy::operator--() {
    --numOfAliveShipPts;
}






