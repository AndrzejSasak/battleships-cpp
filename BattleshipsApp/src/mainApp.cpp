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
#include "../include/Enemy.h"
#include "../include/User.h"
#include <ctime>
#include <windows.h>
#include <fstream>
#include <map>
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
/*
void pickEnemyShip(Interface *interf, Ship *enemyShip) {

}
 */
/*
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
*/
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

int checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfEnemy, Interface *interf, User *playerShotAt) {
    int lengthOfShip = ships[0]->getLength();
    int numOfShips;
    if(lengthOfShip == 1)  numOfShips = playerShotAt->getNumOfShips1();
    if(lengthOfShip == 2)  numOfShips = playerShotAt->getNumOfShips2();
    if(lengthOfShip == 3)  numOfShips = playerShotAt->getNumOfShips3();
    if(lengthOfShip == 4)  numOfShips = playerShotAt->getNumOfShips4();
    if(lengthOfShip == 1) {
        for (int i = 0; i < numOfShips; i++) {
            for (int j = 0; j < lengthOfShip; j++) {
                if (ships[i]->getShipSquares()[j] == guessSquareOfEnemy) {
                    if (ships[i]->getIsAlive()) {
                        std::cout << "Enemy guessed correctly: " << guessSquareOfEnemy << ", and destroyed your whole ship!"<< std::endl;
                        ships[i]->setAlive(false);
                    }
                    setDestroyedUserShipWhole(guessSquareOfEnemy, interf);
                    return 1;
                }
            }
        }
    } else {
        for (int i = 0; i < numOfShips; i++) {
            for (int j = 0; j < lengthOfShip; j++) {
                if (ships[i]->getShipSquares()[j] == guessSquareOfEnemy) {
                    if (ships[i]->getIsAlive()) {
                        std::cout << "Enemy guessed correctly: " << guessSquareOfEnemy
                                  << " and destroyed this part of your ship!" << std::endl;
                        int numOfAliveParts = playerShotAt->getNumOfAliveShipPts();
                        if (numOfAliveParts > 0) {
                            numOfAliveParts--;
                            ships[i]->setNumOfAliveParts(numOfAliveParts);
                            if (numOfAliveParts == 0) {
                                std::cout << "This was the last part of the ship! You have destroyed the whole ship!"
                                          << std::endl;
                                for (int k = 0; k < lengthOfShip; k++) {
                                    setDestroyedUserShipWhole(ships[i]->getShipSquares()[k], interf);
                                }
                                ships[i]->setAlive(false);
                                return 1;
                            }
                        }
                        setDestroyedUserShipPart(guessSquareOfEnemy, interf);
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfUser, Interface *interf, Enemy *playerShotAt) {

    int lengthOfShip = ships[0]->getLength();
    int numOfShips;
    if(lengthOfShip == 1)  numOfShips = playerShotAt->getNumOfShips1();
    if(lengthOfShip == 2)  numOfShips = playerShotAt->getNumOfShips2();
    if(lengthOfShip == 3)  numOfShips = playerShotAt->getNumOfShips3();
    if(lengthOfShip == 4)  numOfShips = playerShotAt->getNumOfShips4();

    if(lengthOfShip == 1) {
        for(int i = 0; i < numOfShips; i++) {
            for(int j = 0; j < lengthOfShip; j++) {
                if(ships[i]->getShipSquares()[j] == guessSquareOfUser) {
                    if(ships[i]->getIsAlive()) {
                        std::cout << "You guessed correctly! You destroyed this playerShotAt ship!" << std::endl;
                        ships[i]->setAlive(false);
                        setDestroyedEnemyShipWhole(guessSquareOfUser, interf);
                        //setSurroundingsTaken(ships[i], interf);
                        return 1;
                    } else {
                        std::cout << "You have already destroyed this ship!" << std::endl;
                        return 0;
                    }
                }
            }
        }
    } else {
        for(int i = 0; i < numOfShips; i++) {
            for(int j = 0; j < lengthOfShip; j++) {
                if(ships[i]->getShipSquares()[j] == guessSquareOfUser) {
                    if(ships[i]->getIsAlive()) {
                        std::cout << "You guessed correctly! You destroyed this part of the playerShotAt ship!" << std::endl;
                        //ships[i]->setAlive(false);
                        int numOfAliveParts = ships[i]->getNumOfAliveParts();
                        if(numOfAliveParts > 0) {
                            numOfAliveParts--;
                            ships[i]->setNumOfAliveParts(numOfAliveParts);
                            if(numOfAliveParts == 0) {
                                std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                                for (int k = 0; k < lengthOfShip; k++) {
                                    setDestroyedEnemyShipWhole(ships[i]->getShipSquares()[k], interf);
                                }
                                ships[i]->setAlive(false);
                                return 1;
                            }

                        }
                    } else {
                        std::cout << "You have already destroyed this part of the ship!" << std::endl;
                        return 0;
                    }
                    setDestroyedEnemyShipPart(guessSquareOfUser, interf);
                    return 1;
                }
            }
        }
    }
    return 0;
}

int userShoot(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship* enemyShips4[], Interface *interf, Enemy *enemy) {
    std::string guessSquare;
    std::cout << "Shoot at a square: " << std::endl;
    std::cin >> guessSquare;
    //guessSquare = "A0";

    int status[4] = {0, 0, 0, 0};
    status[0] = checkIfGuessWasCorrect(enemyShips1, guessSquare, interf, enemy);
    status[1] = checkIfGuessWasCorrect(enemyShips2, guessSquare, interf, enemy);
    status[2] = checkIfGuessWasCorrect(enemyShips3, guessSquare, interf, enemy);
    status[3] = checkIfGuessWasCorrect(enemyShips4, guessSquare, interf, enemy);

    if(status[0] == 1) {
        return status[0];
    } else if(status[1] == 1) {
        return status[1];
    } else if(status[2] == 1) {
        return status[2];
    } else if(status[3] == 1) {
        return status[3];
    } else {
        std::cout << "You missed!" << std::endl;
        setAlreadyShotEnemySquare(guessSquare, interf);
        return status[0];
    }

    return -1;
}

void chooseSquare( std::string &guessSquare) {
    int randomNumber = rand() % 10;
    int randomLetter = (rand() % 10) + 65;
    std::string randomLetterStr(1, char(randomLetter));
    std::string randomNumberStr = std::to_string(randomNumber);
    guessSquare = randomLetterStr + randomNumberStr;
}

void checkIfSquareWasAlreadyShot(std::string &guessSquare, Enemy *enemy) {
    for(int i = 0; i < enemy->getNumOfShots(); i++) {
        if(enemy->getShotSquare(i) == guessSquare) {
            chooseSquare(guessSquare);
            i = 0;
        }
    }
}

int enemyShoot(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], Interface *interf, Enemy *enemy, User *playerShotAt) {

    /*
    int length1 = userShips1[0]->getLength();
    int length2 = userShips2[0]->getLength();
    int length3 = userShips3[0]->getLength();
    int length4 = userShips4[0]->getLength();
    int numOfShips1 = 4;
    int numOfShips2 = 3;
    int numOfShips3 = 2;
    int numOfShips4 = 1;
    */
    std::string guessSquare;

    chooseSquare(guessSquare);
    checkIfSquareWasAlreadyShot(guessSquare, enemy);

    enemy->setShotSquare(enemy->getNumOfShots(), guessSquare);
    enemy->setNumOfShots(enemy->getNumOfShots() + 1);
    std::cout << "NUM OF SHOTS: " << enemy->getNumOfShots() << std::endl;

    std::cout << "Enemy is shooting at square " << guessSquare << "..." << std::endl;
    Sleep(1000);

    int status[4] = {0, 0, 0, 0};
    status[0] = checkIfGuessWasCorrect(userShips1, guessSquare, interf, playerShotAt);
    status[1] = checkIfGuessWasCorrect(userShips2, guessSquare, interf, playerShotAt);
    status[2] = checkIfGuessWasCorrect(userShips3, guessSquare, interf, playerShotAt);
    status[3] = checkIfGuessWasCorrect(userShips4, guessSquare, interf, playerShotAt);

    if(status[0] == 1) {
        return status[0];
    } else if(status[1] == 1) {
        return status[1];
    } else if(status[2] == 1) {
        return status[2];
    } else if(status[3] == 1) {
        return status[3];
    } else {
        std::cout << "Enemy missed!" << std::endl;
        setAlreadyShotUserSquare(guessSquare, interf);
        return status[0];
    }

    /*
    for (int i = 0; i < numOfShips1; i++) {
        for (int j = 0; j < length1; j++) {
            if (userShips1[i]->getShipSquares()[j] == guessSquare) {
                if (userShips1[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare << ", and destroyed your whole ship!"<< std::endl;
                    userShips1[i]->setAlive(false);
                }
                setDestroyedUserShipWhole(guessSquare, interf);
                return 1;
            }
        }
    }
    //wzorzec
    for (int i = 0; i < numOfShips2; i++) {
        for (int j = 0; j < length2; j++) {
            if (userShips2[i]->getShipSquares()[j] == guessSquare) {
                if (userShips2[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare
                    << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips2[i]->getNumOfAliveParts();
                    if (numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips2[i]->setNumOfAliveParts(numOfAliveParts);
                        if (numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!"
                            << std::endl;
                            for (int k = 0; k < length2; k++) {
                                setDestroyedUserShipWhole(userShips2[i]->getShipSquares()[k], interf);
                            }
                            userShips2[i]->setAlive(false);
                            return 1;
                        }
                    }
                    setDestroyedUserShipPart(guessSquare, interf);
                    return 1;
                }
            }
        }
    }
    for (int i = 0; i < numOfShips3; i++) {
        for (int j = 0; j < length3; j++) {
            if (userShips3[i]->getShipSquares()[j] == guessSquare) {
                if (userShips3[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare
                    << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips3[i]->getNumOfAliveParts();
                    if (numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips3[i]->setNumOfAliveParts(numOfAliveParts);
                        if (numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!"
                            << std::endl;
                            for (int k = 0; k < length3; k++) {
                                setDestroyedUserShipWhole(userShips3[i]->getShipSquares()[k], interf);
                            }
                            userShips3[i]->setAlive(false);
                            return 1;
                        }
                    } else if (numOfAliveParts == 0) {
                        userShips3[i]->setAlive(false);
                    }
                    setDestroyedUserShipPart(guessSquare, interf);
                    return 1;
                }
            }
        }
    }
    for (int i = 0; i < numOfShips4; i++) {
        for (int j = 0; j < length4; j++) {
            if (userShips4[i]->getShipSquares()[j] == guessSquare) {
                if (userShips4[i]->getIsAlive()) {
                    std::cout << "Enemy guessed correctly: " << guessSquare
                    << " and destroyed this part of your ship!" << std::endl;
                    int numOfAliveParts = userShips4[i]->getNumOfAliveParts();
                    if (numOfAliveParts > 0) {
                        numOfAliveParts--;
                        userShips4[i]->setNumOfAliveParts(numOfAliveParts);
                        if (numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!"
                            << std::endl;
                            for (int k = 0; k < length4; k++) {
                                setDestroyedUserShipWhole(userShips4[i]->getShipSquares()[k], interf);
                            }
                            userShips4[i]->setAlive(false);
                            return 1;
                        }
                    } else if (numOfAliveParts == 0) {
                        userShips4[i]->setAlive(false);
                    }
                    setDestroyedUserShipPart(guessSquare, interf);
                    return 1;
                }
            }
        }
    }
     */
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

void pickAllEnemyShips(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[], Enemy *enemy, Interface *interf) {
    std::fstream fboard;
    int boardNumber = rand() % 2 + 1;
    std::string boardNumberStr = std::to_string(boardNumber);
    std::string boardFilepath = "../../BattleshipsApp/boards/board" + boardNumberStr + ".txt";
    std::cout << "Board chosen: " << boardFilepath << std::endl;
    fboard.open(boardFilepath, std::ios::in);
    if(!fboard.is_open()) {
        std::cout << "ERROR OPENING FILE" << std::endl;
    }

    std::ifstream board(boardFilepath);
    std::string line;
    for(int i = 0; i < enemy->getNumOfShips1(); i++) {
        getline(board, line);
        std::string shipSquare[1];
        shipSquare[0] = line;
        enemyShips1[i]->initShip(shipSquare);
        for(int i = 0; i < enemyShips1[0]->getLength(); i++)  setTakenByEnemyShip(shipSquare[i], interf);
    }
    for(int i = 0; i < enemy->getNumOfShips2(); i++) {
        getline(board, line);
        std::string shipSquare[2];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        enemyShips2[i]->initShip(shipSquare);
        for(int i = 0; i < enemyShips2[0]->getLength(); i++)  setTakenByEnemyShip(shipSquare[i], interf);
    }
    for(int i = 0; i < enemy->getNumOfShips3(); i++) {
        getline(board, line);
        std::string shipSquare[3];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        shipSquare[2] = std::string(1, line[4]) + std::string(1, line[5]);
        enemyShips3[i]->initShip(shipSquare);
        for(int i = 0; i < enemyShips3[0]->getLength(); i++)  setTakenByEnemyShip(shipSquare[i], interf);
    }
    for(int i = 0; i < enemy->getNumOfShips4(); i++) {
        getline(board, line);
        std::string shipSquare[4];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        shipSquare[2] = std::string(1, line[4]) + std::string(1, line[5]);
        shipSquare[3] = std::string(1, line[6]) + std::string(1, line[7]);
        enemyShips4[i]->initShip(shipSquare);
        for(int i = 0; i < enemyShips4[0]->getLength(); i++)  setTakenByEnemyShip(shipSquare[i], interf);
    }
    board.close();
}

void pickAllUserShips(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], User *user, Interface *interf) {
    for(int i = 0; i < user->getNumOfShips1(); i++) {
        if(pickUserShip(interf, userShips1[i])== -1) {
            i--;
        }
    }
    for(int i = 0; i < user->getNumOfShips2(); i++) {
        if(pickUserShip(interf, userShips2[i])== -1) {
            i--;
        }
    }
    for(int i = 0; i < user->getNumOfShips3(); i++) {
        if(pickUserShip(interf, userShips3[i])== -1) {
            i--;
        }
    }
    for(int i = 0; i < user->getNumOfShips4(); i++) {
        if (pickUserShip(interf, userShips4[i]) == -1) {
            i--;
        }
    }
}

void selectUser(char *argv1, char *argv2) {
    std::map<std::string, std::string> map;
    std::string name(argv1);
    std::string password(argv2);

    std::fstream usersFile;
    usersFile.open("../../BattleshipsApp/users_database/users.txt", std::ios::in);
    if(!usersFile.is_open()) {
        std::cout << "ERROR OPENING FILE TO READ" << std::endl;
    }
    std::ifstream usersIn("../../BattleshipsApp/users_database/users.txt");

    while(usersIn) {
        std::string username;
        std::string userpassword;
        usersIn >> username;
        usersIn >> userpassword;
        map[username] = userpassword;
    }
    if(map.find(name) != map.end() && map[name] == password) {
        std::cout << "Welcome " << map.find(name)->first << "!" << std::endl;
        std::cout << "Successfully logged in!" << std::endl;
    } else if (map.find(name) != map.end() && map[name] != password) {
        std::cout << "Wrong password for the entered username!" << std::endl;
        exit(1);
    } else if(map.find(name) == map.end()) {
        std::cout << "Entered name is new in the database. Welcome new user!" << std::endl;
    }

    std::pair<std::string, std::string> newUser;
    newUser.first = name;
    newUser.second = password;
    map.insert(newUser);

    std::cout << map.find(name)->first << std::endl;
    std::cout << map.find(name)->second << std::endl;
    //now save all the users from map to file
    usersFile.close();
    usersFile.open("../../BattleshipsApp/users_database/users.txt", std::ios::out);
    std::ofstream usersOut("../../BattleshipsApp/users_database/users.txt");

    if(!usersOut.is_open()) {
        std::cout << "ERROR OPENING FILE TO WRITE" << std::endl;
    }

    std::cout << "HASLO" << map["carlos"] << std::endl;

    for(auto &pair: map) {
        std::cout << "HERE" << std::endl;
        std::string username = pair.first;
        std::cout << username.length() << std::endl;
        for(int i = 0; i < username.length(); i++) {
            std::cout << username[i] << std::endl;
            usersOut.put(username[i]);
        }
        usersOut.put(' ');
        std::string userpassword = pair.second;
        for(int i = 0; i < userpassword.length(); i++) {
            std::cout << userpassword[i] << std::endl;
            usersOut.put(userpassword[i]);
        }
        usersOut << std::endl;
    }
    std::cout << "SLEEPING" << std::endl;
    Sleep(3000);
    usersOut.close();
    exit(10);



}

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    if(argc == 3) selectUser(argv[1], argv[2]);

    printWelcomeScreen();

    Interface interf;
    Enemy enemy;
    User user;

    enemy.setNumOfShips1(4);
    enemy.setNumOfShips2(3);
    enemy.setNumOfShips3(2);
    enemy.setNumOfShips4(1);
    enemy.setNumOfAliveShipPts(20);

    user.setNumOfShips1(4);
    user.setNumOfShips2(3);
    user.setNumOfShips3(2);
    user.setNumOfShips4(1);
    user.setNumOfAliveShipPts(20);

    //initialize memory for enemy ships
    Ship *userShips1[user.getNumOfShips1()];
    for(int i = 0; i < user.getNumOfShips1(); i++) userShips1[i] = new Ship1();
    Ship *userShips2[user.getNumOfShips2()];
    for(int i = 0; i < user.getNumOfShips2(); i++) userShips2[i] = new Ship2();
    Ship *userShips3[user.getNumOfShips3()];
    for(int i = 0; i < user.getNumOfShips3(); i++) userShips3[i] = new Ship3();
    Ship *userShips4[user.getNumOfShips4()];
    for(int i = 0; i < user.getNumOfShips4(); i++) userShips4[i] = new Ship4();

    //initialize memory for enemy ships
    Ship *enemyShips1[enemy.getNumOfShips1()];
    for(int i = 0; i < user.getNumOfShips1(); i++) enemyShips1[i] = new Ship1();
    Ship *enemyShips2[user.getNumOfShips2()];
    for(int i = 0; i < user.getNumOfShips2(); i++) enemyShips2[i] = new Ship2();
    Ship *enemyShips3[user.getNumOfShips3()];
    for(int i = 0; i < user.getNumOfShips3(); i++) enemyShips3[i] = new Ship3();
    Ship *enemyShips4[user.getNumOfShips4()];
    for(int i = 0; i < user.getNumOfShips4(); i++) enemyShips4[i] = new Ship4();

    interf.printInterface();

    pickAllUserShips(userShips1, userShips2, userShips3, userShips4, &user, &interf);
    pickAllEnemyShips(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &enemy, &interf);
    interf.printInterface();


    //game loop
    bool isUndecided = true;
    while(isUndecided) {

        int wasEnemyHit = userShoot(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &interf, &enemy);
        interf.printInterface();
        while(wasEnemyHit) {
            enemy.setNumOfAliveShipPts(enemy.getNumOfAliveShipPts() - wasEnemyHit);
            if (enemy.getNumOfAliveShipPts() == 0) {
                std::cout << "You have won the game! Congratulations!" << std::endl;
                interf.printInterface();
                isUndecided = false;
                break;
            }
            wasEnemyHit = userShoot(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &interf, &enemy);
            interf.printInterface();
        }
        if(!isUndecided) break;

        int wasUserHit = enemyShoot(userShips1, userShips2, userShips3, userShips4, &interf, &enemy, &user);

        while(wasUserHit) {
            user.setNumOfAliveShipPts(user.getNumOfAliveShipPts() - wasUserHit);
            std::cout << "ALIVE PTS: " << user.getNumOfAliveShipPts() << std::endl;
            if(user.getNumOfAliveShipPts() == 0) {
                std::cout << "Enemy has destroyes all your ships and won the game! You lost!" << std::endl;
                isUndecided = false;
                break;
            }
            wasUserHit = enemyShoot(userShips1, userShips2, userShips3, userShips4, &interf, &enemy, &user);
        }
        interf.printInterface();
    }


    return 0;
}