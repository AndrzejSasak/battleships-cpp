//
// Created by endriu on 15.12.2021.
//

#include "../include/lib.h"

void printWelcomeScreen() {
    std::cout << "Welcome to the Battleships game!" << std::endl;
}

void selectUser(char *argv1, char *argv2, std::fstream *usersFile) {
    std::map<std::string, std::string> map;
    std::string name(argv1);
    std::string password(argv2);

    usersFile->open("../../BattleshipsApp/users_database/users.txt", std::ios::in);
    if(!usersFile->is_open()) {
        std::cout << "ERROR OPENING FILE TO READ" << std::endl;
    }
    std::ifstream usersIn("../../BattleshipsApp/users_database/users.txt");

    while(usersIn) {
        std::string usernameTemp;
        std::string userpasswordTemp;
        usersIn >> usernameTemp;
        usersIn >> userpasswordTemp;
        map[usernameTemp] = userpasswordTemp;
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
    usersFile->close();

    addNewUserToDatabase(name, password, &map);

    std::ofstream usersOut("../../BattleshipsApp/users_database/users.txt");
    saveUsersToDatabase(&usersOut, &map);

    usersOut.close();
}

void saveUsersToDatabase(std::ofstream *usersOut, std::map<std::string, std::string> *map) {
    std::fstream usersFile;
    usersFile.open("../../BattleshipsApp/users_database/users.txt", std::ios::out);

    if(!usersOut->is_open()) {
        std::cout << "FILE IS CLOSED" << std::endl;
        return;
    }

    for(auto &pair: *map) {
        std::string usernameTemp = pair.first;
        const char *username = usernameTemp.c_str();
        usersOut->write(username, usernameTemp.length());

        usersOut->put(' ');
        std::string passwordTemp = pair.second;
        const char *password = passwordTemp.c_str();
        usersOut->write(password, passwordTemp.length());

        *usersOut << std::endl;
    }
}

void addNewUserToDatabase(std::string name, std::string password, std::map<std::string, std::string> *map) {
    std::pair<std::string, std::string> newUser;
    newUser.first = name;
    newUser.second = password;
    map->insert(newUser);
}

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
        for(int i = 0; i < enemyShips1[0]->getLength(); i++)  interf->setTakenByEnemyShip(shipSquare[i], interf);
    }
    for(int i = 0; i < enemy->getNumOfShips2(); i++) {
        getline(board, line);
        std::string shipSquare[2];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        enemyShips2[i]->initShip(shipSquare);
        for(int i = 0; i < enemyShips2[0]->getLength(); i++)  interf->setTakenByEnemyShip(shipSquare[i], interf);
    }
    for(int i = 0; i < enemy->getNumOfShips3(); i++) {
        getline(board, line);
        std::string shipSquare[3];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        shipSquare[2] = std::string(1, line[4]) + std::string(1, line[5]);
        enemyShips3[i]->initShip(shipSquare);
        for(int i = 0; i < enemyShips3[0]->getLength(); i++)  interf->setTakenByEnemyShip(shipSquare[i], interf);
    }
    for(int i = 0; i < enemy->getNumOfShips4(); i++) {
        getline(board, line);
        std::string shipSquare[4];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        shipSquare[2] = std::string(1, line[4]) + std::string(1, line[5]);
        shipSquare[3] = std::string(1, line[6]) + std::string(1, line[7]);
        enemyShips4[i]->initShip(shipSquare);
        for(int i = 0; i < enemyShips4[0]->getLength(); i++)  interf->setTakenByEnemyShip(shipSquare[i], interf);
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
        if (interf->isTakenByShip(shipSquares[i], interf) == 1) {
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
        interf->setTakenByUserShip(shipSquares[i], interf);
    }
    userShip->initShip(shipSquares);

    return 0;
}

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
                    interf->setDestroyedUserShipWhole(guessSquareOfEnemy, interf);
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
                                    interf->setDestroyedUserShipWhole(ships[i]->getShipSquares()[k], interf);
                                }
                                ships[i]->setAlive(false);
                                return 1;
                            }
                        }
                        interf->setDestroyedUserShipPart(guessSquareOfEnemy, interf);
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
                        interf->setDestroyedEnemyShipWhole(guessSquareOfUser, interf);
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
                                    interf->setDestroyedEnemyShipWhole(ships[i]->getShipSquares()[k], interf);
                                }
                                ships[i]->setAlive(false);
                                return 1;
                            }

                        }
                    } else {
                        std::cout << "You have already destroyed this part of the ship!" << std::endl;
                        return 0;
                    }
                    interf->setDestroyedEnemyShipPart(guessSquareOfUser, interf);
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
        interf->setAlreadyShotEnemySquare(guessSquare, interf);
        return status[0];
    }

    return -1;
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
    //Sleep(1000);

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
        interf->setAlreadyShotUserSquare(guessSquare, interf);
        return status[0];
    }

    std::cout << "Enemy missed!" << std::endl;
    interf->setAlreadyShotUserSquare(guessSquare, interf);

    return 0;
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

int parseSquareInputToIndex(std::string square) {
    int squareIndex = 0;

    switch(square[0]) {
        case 'A': {
            squareIndex = 0 + (unsigned char)square[1] - 48;
        }
            break;
        case 'B': {
            squareIndex = 10 + (unsigned char)square[1] - 48;
        }
            break;
        case 'C': {
            squareIndex = 20 + (unsigned char)square[1] - 48;
        }
            break;
        case 'D': {
            squareIndex = 30 + (unsigned char)square[1] - 48;
        }
            break;
        case 'E': {
            squareIndex = 40 + (unsigned char)square[1] - 48;
        }
            break;
        case 'F': {
            squareIndex = 50 + (unsigned char)square[1] - 48;
        }
            break;
        case 'G': {
            squareIndex = 60 + (unsigned char)square[1] - 48;
        }
            break;
        case 'H': {
            squareIndex = 70 + (unsigned char)square[1] - 48;
        }
            break;
        case 'I': {
            squareIndex = 80 + (unsigned char) square[1] - 48;
        }
            break;
        case 'J': {
            squareIndex = 90 + (unsigned char)square[1] - 48;
        }
            break;
        default: {
            std::cout << "\nWRONG INPUT\n" << std::endl;
        }
    }
    return squareIndex;
}