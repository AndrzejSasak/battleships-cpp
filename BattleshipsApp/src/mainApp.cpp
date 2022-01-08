//
// Created by endriu on 15.12.2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Interface.h"
#include "../include/Ship4.h"
#include "../include/Ship3.h"
#include "../include/Ship2.h"
#include "../include/Ship1.h"
#include <ctime>
#include <windows.h>
//#include "../include/Ship.h"

void printWelcomeScreen() {
    std::cout << "Welcome to the Battleships game!" << std::endl;
}

int pickUserShip(Interface *interf, Ship *userShip) {
    int length = userShip->getLength();

    std::string shipSquares[length];

    std::cout << "Please pick the squares for your ship of length " << length << ":" << std::endl;
    int squareIndex[length];
    for(int i = 0; i < length; i++) {
        std::cin >> shipSquares[i];

        //checking if the ship squares are next to each other
        squareIndex[i] = parseSquareInputToIndex(shipSquares[i]);
        if((squareIndex[i] != (squareIndex[i-1] - 10) && squareIndex[i] != (squareIndex[i-1]  + 10) && squareIndex[i] != (squareIndex[i-1] - 1) && squareIndex[i] != (squareIndex[i-1]+ 1)) && i > 0) {
            std::cout << "The chosen square is not next to a previous square. Please pick other squares." << std::endl;
            return -1;
        }
    }

    //checking if one of the squares on input is already  taken by a ship or surrounding a ship
    for(int i = 0; i < length; i++) {
        if (isTakenByShip(shipSquares[i], interf) == 1) {
            std::cout << "One of the squares is already taken by a ship or its surroundings." << std::endl;
            return -1;
        }
    }
    //checking if there are duplicate squares on input
    if(length > 1) {
        std::string *end = shipSquares + length;
        std::sort(shipSquares, end);
        bool containsDuplicates = (std::unique(shipSquares, end) != end);
        if (containsDuplicates == 1) {
            std::cout << "Entered input cannot contain duplicates." << std::endl;
            return -1;
        }
    }

    for (int i = 0; i < length; i++) {
        setTakenByUserShip(shipSquares[i], interf);
    }
    userShip->initShip(shipSquares);

    return 0;
}

void pickEnemyShip(Interface *interf, Ship *enemyShip) {

    int length = enemyShip->getLength();
    if(length == 1) {
        int randomNumber = rand() % 10;
        int randomLetter = (rand() % 10) + 65;

        std::string randomLetterStr(1, char(randomLetter));
        std::string randomNumberStr = std::to_string(randomNumber);
        std::string squares[1];
        squares[0] = randomLetterStr + randomNumberStr;

        enemyShip->initShip(squares);
        setTakenByEnemyShip(squares[0], interf);
    }

}

//temporary fixed enemy area
/*
void pickEnemyShips(Interface *interf, Ship *enemyShips[]) {
    int length = enemyShips[0]->getLength();
    std::string shipSquares[4];
    if(length == 1) {
        shipSquares[0] = "A1";
        shipSquares[1] = "C1";
        shipSquares[2] = "E1";
        shipSquares[3] = "G1";
        setTakenByEnemyShip(shipSquares[0], interf);
        setTakenByEnemyShip(shipSquares[1], interf);
        setTakenByEnemyShip(shipSquares[2], interf);
        setTakenByEnemyShip(shipSquares[3], interf);
        enemyShips[0]->initShip(shipSquares);
    } else if (length == 2) {

    }
}
*/

int userShoot(Ship *enemyShips1[], Interface *interf) {
    std::string guessSquare;
    std::cout << "Shoot at a square: " << std::endl;
    std::cin >> guessSquare;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 1; j++) {
            std::cout << enemyShips1[i]->getShipSquares()[j] << std::endl;
            if(enemyShips1[i]->getShipSquares()[j] == guessSquare) {
                if(enemyShips1[i]->getIsAlive()) {
                    std::cout << "You guessed correctly! You destroyed this part of the enemy ship!" << std::endl;
                    enemyShips1[i]->setAlive(false);
                } else {
                    std::cout << "You have already destroyed this part of the ship!" << std::endl;
                    return 0;
                }
                setDestroyedEnemyShipPart(guessSquare, interf);
                return 1;
            }
        }
    }
    //these below need to be modified
    /*
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 2; j++) {
            if(enemyShips2[i]->getShipSquares()[j] == guessSquare) {
                std::cout << "You guessed correctly! You destroyed this part of the enemy ship!" << std::endl;
                setDestroyedEnemyShip(guessSquare, interf);
                return 1;
            }
        }
    }
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            if(enemyShips3[i]->getShipSquares()[j] == guessSquare) {
                std::cout << "You guessed correctly! You destroyed this part of the enemy ship!" << std::endl;
                setDestroyedEnemyShip(guessSquare, interf);
                return 1;
            }
        }
    }
    for(int i = 0; i < 1; i++) {
        for(int j = 0; j < 4; j++) {
            if(enemyShips4[i]->getShipSquares()[j] == guessSquare) {
                std::cout << "You guessed correctly! You destroyed this part of the enemy ship!" << std::endl;
                setDestroyedEnemyShip(guessSquare, interf);
                return 1;
            }
        }
    }
    */
    std::cout << "You missed!" << std::endl;
    setAlreadyShotEnemySquare(guessSquare, interf);

    return 0;
}
/*
int enemyShootShip1(Ship *userShips1[], Interface *interf) {

}
*/
void chooseSquare(bool *hasTarget, std::string &guessSquare, std::string previouslyShotSquare) {
    if(!*hasTarget) {
        int randomNumber = rand() % 10;
        int randomLetter = (rand() % 10) + 65;
        std::string randomLetterStr(1, char(randomLetter));
        std::string randomNumberStr = std::to_string(randomNumber);
        guessSquare = randomLetterStr + randomNumberStr;
    } else if(*hasTarget) {
        int random = (rand() % 4) + 1;
        std::cout << "RANDOM = " << random << std::endl;
        switch(random) {
            case 1: {
                //up square
                unsigned char newLetter = (previouslyShotSquare[0] - 1);
                std::string newLetterStr(1, char(newLetter));
                guessSquare = newLetterStr + previouslyShotSquare[1];
            }
                break;
            case 2: {
                //down square
                unsigned char newLetter = (previouslyShotSquare[0] + 1);
                std::string newLetterStr(1, char(newLetter));
                guessSquare = newLetterStr + previouslyShotSquare[1];
            }
                break;
            case 3: {
                //left square
                unsigned char newNumber = (previouslyShotSquare[1] - 1);
                std::string newNumberStr(1, char(newNumber));
                guessSquare = previouslyShotSquare[0] + newNumberStr;
            }
                break;
            case 4: {
                //right square
                unsigned char newNumber = (previouslyShotSquare[1] + 1);
                std::string newNumberStr(1, char(newNumber));
                guessSquare = previouslyShotSquare[0] + newNumberStr;
            }
            default:
                break;
        }
    }
}

void checkIfSquareWasAlreadyShot(bool *hasTarget, int &numOfEnemyShots,std::string enemyShots[], std::string &guessSquare, std::string previouslyShotSquare) {
    for(int i = 0; i < numOfEnemyShots; i++) {
        if(enemyShots[i] == guessSquare) {
            chooseSquare(hasTarget, guessSquare, previouslyShotSquare);
            i = 0;
        }
    }
}

int enemyShoot(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], Interface *interf, std::string &previouslyShotSquare, std::string enemyShots[], int &numOfEnemyShots, bool *hasTarget) {

    int length1 = userShips1[0]->getLength();
    int length2 = userShips2[0]->getLength();
    int length3 = userShips3[0]->getLength();
    int length4 = userShips4[0]->getLength();
    int numOfShips1 = 4;
    int numOfShips2 = 3;
    int numOfShips3 = 2;
    int numOfShips4 = 1;

    std::string guessSquare;
    /*
    if(!*hasTarget) {
        int randomNumber = rand() % 10;
        int randomLetter = (rand() % 10) + 65;
        std::string randomLetterStr(1, char(randomLetter));
        std::string randomNumberStr = std::to_string(randomNumber);
        guessSquare = randomLetterStr + randomNumberStr;
    } else if(*hasTarget) {
        int random = (rand() % 4) + 1;
        std::cout << "RANDOM = " << random << std::endl;
        //two ifs to be deleted
        if(random == 1) random += 2;
        if(random == 2) random +=2;
        switch(random) {
            case 1: {
                //up square
                char newLetter = (previouslyShotSquare[0] - 1);
                guessSquare = newLetter + previouslyShotSquare[1];
            }
                break;
            case 2: {
                //down square
                char newLetter = (previouslyShotSquare[0] + 1);
                guessSquare = newLetter + previouslyShotSquare[1];
            }
                break;
            case 3: {
                //left square
                char newNumber = (previouslyShotSquare[1] - 1);
                std::string newNumberStr(1, char(newNumber));
                guessSquare = previouslyShotSquare[0] + newNumberStr;
            }
                break;
            case 4: {
                //right square
                char newNumber = (previouslyShotSquare[1] + 1);
                std::string newNumberStr(1, char(newNumber));
                guessSquare = previouslyShotSquare[0] + newNumberStr;
            }
            default:
                break;
        }
    }
    */

    chooseSquare(hasTarget, guessSquare, previouslyShotSquare);
    checkIfSquareWasAlreadyShot(hasTarget, numOfEnemyShots, enemyShots, guessSquare, previouslyShotSquare);

    enemyShots[numOfEnemyShots] = guessSquare;
    numOfEnemyShots++;

    std::cout << "Enemy is shooting at square " << guessSquare << "..." << std::endl;
    std::cout << "Enemy has target: " << *hasTarget << std::endl;
    Sleep(1000);
    std::cout << "PREVIOUS: " << previouslyShotSquare << std::endl;
    //previouslyShotSquare = guessSquare;

    for(int i = 0; i < numOfShips1; i++) {
        for(int j = 0; j < length1; j++) {
            if(userShips1[i]->getShipSquares()[j] == guessSquare) {
                if(userShips1[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " <<  guessSquare << ", and destroyed your whole ship!" << std::endl;
                    userShips1[i]->setAlive(false);
                }
                setDestroyedUserShipWhole(guessSquare, interf);
                return 1;
            }
        }
    }
    //wzorzec
    for(int i = 0; i < numOfShips2; i++) {
        for (int j = 0; j < length2; j++) {
            if (userShips2[i]->getShipSquares()[j] == guessSquare) {
                if (userShips2[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips2[i]->getNumOfAliveParts();
                    if(numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips2[i]->setNumOfAliveParts(numOfAliveParts);
                        if(numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                            for(int k = 0; k < length2; k++) {
                                setDestroyedUserShipWhole(userShips2[i]->getShipSquares()[k], interf);
                            }
                            userShips2[i]->setAlive(false);
                            *hasTarget = false;



                            return 1;
                        }
                    }
                    previouslyShotSquare = guessSquare;
                    // previouslyShotSquare[1] = previouslyShotSquare[0];
                    *hasTarget = true;
                }
                setDestroyedUserShipPart(guessSquare, interf);
                return 1;
            }

        }
    }
    for(int i = 0; i < numOfShips3; i++) {
        for (int j = 0; j < length3; j++) {
            if (userShips3[i]->getShipSquares()[j] == guessSquare) {
                if (userShips3[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips3[i]->getNumOfAliveParts();
                    if(numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips3[i]->setNumOfAliveParts(numOfAliveParts);
                        if(numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                            for(int k = 0; k < length3; k++) {
                                setDestroyedUserShipWhole(userShips3[i]->getShipSquares()[k], interf);
                            }
                            userShips3[i]->setAlive(false);
                            *hasTarget = false;
                            return 1;
                        }
                    } else if(numOfAliveParts == 0) {
                        userShips3[i]->setAlive(false);
                    }

                    previouslyShotSquare = guessSquare;
                    *hasTarget = true;

                }
                setDestroyedUserShipPart(guessSquare, interf);
                return 1;
            }
        }
    }
    for(int i = 0; i < numOfShips4; i++) {
        for(int j = 0; j < length4; j++) {
            if(userShips4[i]->getShipSquares()[j] == guessSquare) {
                if (userShips4[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips4[i]->getNumOfAliveParts();
                    if(numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips4[i]->setNumOfAliveParts(numOfAliveParts);
                        if(numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                            for(int k = 0; k < length4; k++) {
                                setDestroyedUserShipWhole(userShips4[i]->getShipSquares()[k], interf);
                            }
                            userShips4[i]->setAlive(false);
                            *hasTarget = false;
                            return 1;
                        }
                    } else if(numOfAliveParts == 0) {
                        userShips4[i]->setAlive(false);
                    }
                    previouslyShotSquare[0] = guessSquare[0];
                    *hasTarget = true;
                }
                setDestroyedUserShipPart(guessSquare, interf);
                return 1;
            }
        }
    }
    std::cout << "Enemy missed!" << std::endl;
    setAlreadyShotUserSquare(guessSquare, interf);
    return 0;
}
/*
int enemyShoot(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], Interface *interf) {

    int length1 = userShips1[0]->getLength();
    int length2 = userShips2[0]->getLength();
    int length3 = userShips3[0]->getLength();
    int length4 = userShips4[0]->getLength();
    int numOfShips1 = 4;
    int numOfShips2 = 3;
    int numOfShips3 = 2;
    int numOfShips4 = 1;

    std::string guessSquare;

    //int randomNumber = rand() % 10;
    //int randomLetter = (rand() % 10) + 65;

    //std::string randomLetterStr(1, char(randomLetter));
    //std::string randomNumberStr = std::to_string(randomNumber);

    //guessSquare = randomLetterStr + randomNumberStr;

    std::cout << "Pick temporarily for the enemy: " << std::endl;
    std::cin >> guessSquare;

    std::cout << "Enemy is shooting at square " << guessSquare << "..." << std::endl;
    Sleep(2000);

    for(int i = 0; i < numOfShips1; i++) {
        for(int j = 0; j < length1; j++) {
            if(userShips1[i]->getShipSquares()[j] == guessSquare) {
                if(userShips1[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " <<  guessSquare << ", and destroyed your whole ship!" << std::endl;
                    userShips1[i]->setAlive(false);
                } else {
                    std::cout << "Enemy has already destroyed this part of the ship!" << std::endl;
                    return 0;
                }
                setDestroyedUserShipWhole(guessSquare, interf);
                return 1;
            }
        }
    }
    //wzorzec
    for(int i = 0; i < numOfShips2; i++) {
        for (int j = 0; j < length2; j++) {
            if (userShips2[i]->getShipSquares()[j] == guessSquare) {
                if (userShips2[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips2[i]->getNumOfAliveParts();
                    if(numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips2[i]->setNumOfAliveParts(numOfAliveParts);
                        if(numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                            for(int k = 0; k < length2; k++) {
                                setDestroyedUserShipWhole(userShips2[i]->getShipSquares()[k], interf);
                            }
                            userShips2[i]->setAlive(false);
                            return 1;
                        }
                    } else if(numOfAliveParts == 0) {
                        userShips2[i]->setAlive(false);
                    }
                } else {
                    std::cout << "Enemy has already destroyed this part of the ship!" << std::endl;
                    return 0;
                }
                setDestroyedUserShipPart(guessSquare, interf);
                return 1;
            }
        }
    }
    for(int i = 0; i < numOfShips3; i++) {
        for (int j = 0; j < length3; j++) {
            if (userShips3[i]->getShipSquares()[j] == guessSquare) {
                if (userShips3[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips3[i]->getNumOfAliveParts();
                    if(numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips3[i]->setNumOfAliveParts(numOfAliveParts);
                        if(numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                            for(int k = 0; k < length3; k++) {
                                setDestroyedUserShipWhole(userShips3[i]->getShipSquares()[k], interf);
                            }
                            userShips3[i]->setAlive(false);
                            return 1;
                        }
                    } else if(numOfAliveParts == 0) {
                        userShips3[i]->setAlive(false);
                    }
                } else {
                    std::cout << "Enemy has already destroyed this part of the ship!" << std::endl;
                    return 0;
                }
                setDestroyedUserShipPart(guessSquare, interf);
                return 1;
            }
        }
    }
    for(int i = 0; i < numOfShips4; i++) {
        for(int j = 0; j < length4; j++) {
            if(userShips4[i]->getShipSquares()[j] == guessSquare) {
                if (userShips4[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips4[i]->getNumOfAliveParts();
                    if(numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips4[i]->setNumOfAliveParts(numOfAliveParts);
                        if(numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                            for(int k = 0; k < length4; k++) {
                                setDestroyedUserShipWhole(userShips4[i]->getShipSquares()[k], interf);
                            }
                            userShips4[i]->setAlive(false);
                            return 1;
                        }
                    } else if(numOfAliveParts == 0) {
                        userShips4[i]->setAlive(false);
                    }
                } else {
                    std::cout << "Enemy has already destroyed this part of the ship!" << std::endl;
                    return 0;
                }
                setDestroyedUserShipPart(guessSquare, interf);
                return 1;
            }
        }
    }
    std::cout << "Enemy missed!" << std::endl;
    setAlreadyShotUserSquare(guessSquare, interf);
    return 0;
}
*/
int main() {
    srand(time(nullptr));

    Interface interf;
    printWelcomeScreen();

    int numOfShips1 = 4;
    int numOfShips2 = 3;
    int numOfShips3 = 2;
    int numOfShips4 = 1;
    int numOfAliveEnemyShipPts = 4;
    int numOfAliveUserShipPts = 20;
    std::string enemyShots[100];
    int numOfEnemyShots;
    int numOfTries;

    //initialize memory for user ships
    Ship *userShips1[numOfShips1];
    for(int i = 0; i < numOfShips1; i++) userShips1[i] = new Ship1();
    Ship *userShips2[numOfShips2];
    for(int i = 0; i < numOfShips2; i++) userShips2[i] = new Ship2();
    Ship *userShips3[numOfShips3];
    for(int i = 0; i < numOfShips3; i++) userShips3[i] = new Ship3();
    Ship *userShips4[numOfShips4];
    for(int i = 0; i < numOfShips4; i++) userShips4[i] = new Ship4();

    //initialize memory for enemy ships
    Ship *enemyShips1[numOfShips1];
    for(int i = 0; i < numOfShips1; i++) enemyShips1[i] = new Ship1();
    Ship *enemyShips2[numOfShips2];
    for(int i = 0; i < numOfShips2; i++) enemyShips2[i] = new Ship2();
    Ship *enemyShips3[numOfShips3];
    for(int i = 0; i < numOfShips3; i++) enemyShips3[i] = new Ship3();
    Ship *enemyShips4[numOfShips4];
    for(int i = 0; i < numOfShips4; i++) enemyShips4[i] = new Ship4();

    interf.printInterface();
/*
    for(int i = 0; i < numOfShips1; i++) {
        if(pickUserShip(&interf, userShips1[i]) == -1) {
            i--;
        }
    }
    //picking squares for user ships
  */
    for(int i = 0; i < numOfShips1; i++) {
        if(pickUserShip(&interf, userShips1[i])== -1) {
            i--;
        }
    }
    for(int i = 0; i < numOfShips2; i++) {
        if(pickUserShip(&interf, userShips2[i])== -1) {
            i--;
        }
    }
    for(int i = 0; i < numOfShips3; i++) {
        if(pickUserShip(&interf, userShips3[i])== -1) {
            i--;
        }
    }
    for(int i = 0; i < numOfShips4; i++) {
        if(pickUserShip(&interf, userShips4[i])== -1) {
            i--;
        }
    }

    //picking squares for enemy ships
    /*
    std::string shipSquares1[1];
    shipSquares1[0] = "A0";
    enemyShips1[0]->initShip(shipSquares1);
    setTakenByEnemyShip(shipSquares1[0], &interf);
    std::cout << "HERE" << std::endl;
    shipSquares1[0] = "C0";
    enemyShips1[1]->initShip(shipSquares1);
    setTakenByEnemyShip(shipSquares1[0], &interf);

    shipSquares1[0] = "E0";
    enemyShips1[2]->initShip(shipSquares1);
    setTakenByEnemyShip(shipSquares1[0], &interf);

    shipSquares1[0] = "G0";
    enemyShips1[3]->initShip(shipSquares1);
    setTakenByEnemyShip(shipSquares1[0], &interf);

    std::string shipSquares2[2];
    shipSquares2[0] = "A2";
    setTakenByEnemyShip(shipSquares2[0], &interf);
    shipSquares2[1] = "A3";
    setTakenByEnemyShip(shipSquares2[1], &interf);
    enemyShips2[0]->initShip(shipSquares2);

    shipSquares2[0] = "C2";
    setTakenByEnemyShip(shipSquares2[0], &interf);
    shipSquares2[1] = "C3";
    setTakenByEnemyShip(shipSquares2[1], &interf);
    enemyShips2[1]->initShip(shipSquares2);

    shipSquares2[0] = "E2";
    setTakenByEnemyShip(shipSquares2[0], &interf);
    shipSquares2[1] = "E3";
    setTakenByEnemyShip(shipSquares2[1], &interf);
    enemyShips2[2]->initShip(shipSquares2);

    std::string shipSquares3[3];
    shipSquares3[0] = "A5";
    setTakenByEnemyShip(shipSquares3[0], &interf);
    shipSquares3[1] = "A6";
    setTakenByEnemyShip(shipSquares3[1], &interf);
    shipSquares3[2] = "A7";
    setTakenByEnemyShip(shipSquares3[2], &interf);
    enemyShips3[0]->initShip(shipSquares3);

    shipSquares3[0] = "C5";
    setTakenByEnemyShip(shipSquares3[0], &interf);
    shipSquares3[1] = "C6";
    setTakenByEnemyShip(shipSquares3[1], &interf);
    shipSquares3[2] = "C7";
    setTakenByEnemyShip(shipSquares3[2], &interf);
    enemyShips3[1]->initShip(shipSquares3);

    std::cout << "HERE SHOULD BE A0: " << std::endl;
    std::cout << "HERE SHOULD BE C0: " << *enemyShips1[1]->getShipSquares() << std::endl;

    std::string shipSquares[4];
    shipSquares[0] = "A9";
    setTakenByEnemyShip(shipSquares[0], &interf);
    shipSquares[1] = "B9";
    setTakenByEnemyShip(shipSquares[1], &interf);
    shipSquares[2] = "C9";
    setTakenByEnemyShip(shipSquares[2], &interf);
    shipSquares[3] = "D9";
    setTakenByEnemyShip(shipSquares[3], &interf);
    enemyShips4[0]->initShip(shipSquares);
    */
    //pickEnemyShips(&interf, enemyShips1);

    for(int i = 0; i < numOfShips1; i++) pickEnemyShip(&interf, enemyShips1[i]);
    /*
    for(int i = 0; i < numOfShips2; i++) pickEnemyShip(&interf, userShips2[i]);
    for(int i = 0; i < numOfShips3; i++) pickEnemyShip(&interf, userShips3[i]);
    for(int i = 0; i < numOfShips4; i++) pickEnemyShip(&interf, userShips4[i]);
    */

    interf.printInterface();

    std::string previouslyShotSquare;
    bool hasTarget = false;

    bool isUndecided = true;
    while(isUndecided) {

        int wasEnemyHit = userShoot(enemyShips1, &interf);
        interf.printInterface();
        while(wasEnemyHit) {
            numOfAliveEnemyShipPts -= wasEnemyHit;
            if (numOfAliveEnemyShipPts == 0) {
                std::cout << "You have won the game! Congratulations!" << std::endl;
                interf.printInterface();
                isUndecided = false;
                break;
            }
            wasEnemyHit = userShoot(enemyShips1, &interf);
            interf.printInterface();
        }
        if(!isUndecided) break;

        int wasUserHit = enemyShoot(userShips1, userShips2, userShips3, userShips4, &interf, previouslyShotSquare, enemyShots, numOfEnemyShots,&hasTarget);
        interf.printInterface();
        while(wasUserHit) {
            numOfAliveUserShipPts -= wasUserHit;
            if(numOfAliveUserShipPts == 0) {
                std::cout << "Enemy has destroyes all your ships and won the game! You lost!" << std::endl;
                interf.printInterface();
                isUndecided = false;
                break;
            }
            wasUserHit = enemyShoot(userShips1, userShips2, userShips3, userShips4, &interf, previouslyShotSquare, enemyShots, numOfEnemyShots, &hasTarget);
            interf.printInterface();
        }

    }


    return 0;
}