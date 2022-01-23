#include "../include/Ship.h"

void Ship::setAlive(bool newIsAlive) {
    isAlive = newIsAlive;
}

bool Ship::getIsAlive() const {
    return isAlive;
}
