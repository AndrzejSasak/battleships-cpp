//
// Created by endriu on 15.12.2021.
//

#include "../include/Ship.h"

void Ship::setAlive(bool newIsAlive) {
    isAlive = newIsAlive;
}

bool Ship::getIsAlive() const {
    return isAlive;
}
