//
// Created by endriu on 15.12.2021.
//

#include "../include/lib.h"
#include "../../BattleshipsApp/include/Exception.h"

void printWelcomeScreen() {
    std::cout << "Welcome to the Battleships game!" << std::endl;
}

int getNumOfAliveShips(Ship *ships1[], Ship *ships2[], Ship *ships3[], Ship *ships4[], User *user) {
    int numOfAliveShips = 0;

    for(int i = 0; i < user->getNumOfShips1(); i++) {
        if(ships1[i]->getIsAlive()) numOfAliveShips++;
    }
    for(int i = 0; i < user->getNumOfShips2(); i++) {
        if(ships2[i]->getIsAlive()) numOfAliveShips++;
    }
    for(int i = 0; i < user->getNumOfShips3(); i++) {
        if(ships3[i]->getIsAlive()) numOfAliveShips++;
    }
    for(int i = 0; i < user->getNumOfShips4(); i++) {
        if(ships4[i]->getIsAlive()) numOfAliveShips++;
    }
    return numOfAliveShips;
}

int getNumOfAliveShips(Ship *ships1[], Ship *ships2[], Ship *ships3[], Ship *ships4[], Enemy *enemy) {
    int numOfAliveShips = 0;

    for(int i = 0; i < enemy->getNumOfShips1(); i++) {
        if(ships1[i]->getIsAlive()) numOfAliveShips++;
    }
    for(int i = 0; i < enemy->getNumOfShips2(); i++) {
        if(ships2[i]->getIsAlive()) numOfAliveShips++;
    }
    for(int i = 0; i < enemy->getNumOfShips3(); i++) {
        if(ships3[i]->getIsAlive()) numOfAliveShips++;
    }
    for(int i = 0; i < enemy->getNumOfShips4(); i++) {
        if(ships4[i]->getIsAlive()) numOfAliveShips++;
    }
    return numOfAliveShips;
}

void pickDifficulty(Enemy *enemy) {
    std::cout << "Please pick the difficulty of the enemy (1 for easy, 2 for medium, 3 for hard):" << std::endl;
    int difficulty;
    std::cin >> difficulty;

    if(difficulty == 1 || difficulty == 2 || difficulty == 3) {
        enemy->setDifficulty(difficulty);
        switch(difficulty) {
            case 1: std::cout << "Difficulty picked: easy" << std::endl;
            break;
            case 2: std::cout << "Difficulty picked: medium" << std::endl;
            break;
            case 3: std::cout << "Difficulty picked: hard" << std::endl;
            break;
            default: std::cout << "\nWRONG INPUT\n" << std::endl;
        }
    } else {
        throw Exception("difficulty was not picked properly", 1);
    }

}

void selectUser(char *argv1, char *argv2, std::fstream *usersFile) {
    std::map<std::string, std::string> map;
    std::string name(argv1);
    std::string password(argv2);

    usersFile->open("../../BattleshipsApp/users_database/users.txt", std::ios::in);
    if(!usersFile->is_open()) {
        throw Exception("cannot open file", 6);
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
    if(usersFile->is_open()) {
        throw Exception("cannot close file", 7);
    }

    addNewUserToDatabase(name, password, &map);

    std::ofstream usersOut("../../BattleshipsApp/users_database/users.txt");

    saveUsersToDatabase(&usersOut, &map);

    usersOut.close();
    if(usersOut.is_open()) {
        throw Exception("cannot close file", 7);
    }
}

void saveUsersToDatabase(std::ofstream *usersOut, std::map<std::string, std::string> *map) {
    std::fstream usersFile;
    usersFile.open("../../BattleshipsApp/users_database/users.txt", std::ios::out);

    if(!usersOut->is_open()) {
        throw Exception("file is not open", 6);
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

    //choosing a board from a file
    int boardNumber = rand() % 2 + 1;
    std::string boardNumberStr = std::to_string(boardNumber);
    std::string boardFilepath = "../../BattleshipsApp/boards/board" + boardNumberStr + ".txt";
    std::cout << "Board chosen: " << boardFilepath << std::endl;

    fboard.open(boardFilepath, std::ios::in);
    if(!fboard.is_open()) {
        throw Exception("board file is not open", 6);
    }

    //reading ship squares individually from a previously chosen board
    std::ifstream board(boardFilepath);
    std::string line;
    for(int i = 0; i < enemy->getNumOfShips1(); i++) {
        getline(board, line);
        std::string shipSquare[1];
        shipSquare[0] = line;
        enemyShips1[i]->initShip(shipSquare);
        for(int j = 0; j < enemyShips1[0]->getLength(); j++) interf->setTakenByEnemyShip(shipSquare[j]);
    }
    for(int i = 0; i < enemy->getNumOfShips2(); i++) {
        getline(board, line);
        std::string shipSquare[2];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        enemyShips2[i]->initShip(shipSquare);
        for(int j = 0; j < enemyShips2[0]->getLength(); j++) interf->setTakenByEnemyShip(shipSquare[j]);
    }
    for(int i = 0; i < enemy->getNumOfShips3(); i++) {
        getline(board, line);
        std::string shipSquare[3];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        shipSquare[2] = std::string(1, line[4]) + std::string(1, line[5]);
        enemyShips3[i]->initShip(shipSquare);
        for(int j = 0; j < enemyShips3[0]->getLength(); j++) interf->setTakenByEnemyShip(shipSquare[j]);
    }
    for(int i = 0; i < enemy->getNumOfShips4(); i++) {
        getline(board, line);
        std::string shipSquare[4];
        shipSquare[0] = std::string(1, line[0]) + std::string(1, line[1]);
        shipSquare[1] = std::string(1, line[2]) + std::string(1, line[3]);
        shipSquare[2] = std::string(1, line[4]) + std::string(1, line[5]);
        shipSquare[3] = std::string(1, line[6]) + std::string(1, line[7]);
        enemyShips4[i]->initShip(shipSquare);
        for(int j = 0; j < enemyShips4[0]->getLength(); j++) interf->setTakenByEnemyShip(shipSquare[j]);
    }
    board.close();
    if(board.is_open()) {
        throw Exception("board file is open", 7);
    }
}

void pickAllUserShips(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], User *user, Interface *interf) {
    //picking ships of length 1
    for(int i = 0; i < user->getNumOfShips1(); i++) pickUserShip(interf, userShips1[i]);
    //picking ships of length 2
    for(int i = 0; i < user->getNumOfShips2(); i++) pickUserShip(interf, userShips2[i]);
    //picking ships of length 3
    for(int i = 0; i < user->getNumOfShips3(); i++) pickUserShip(interf, userShips3[i]);
    //picking ships of length 4
    for(int i = 0; i < user->getNumOfShips4(); i++) pickUserShip(interf, userShips4[i]);
}

void pickUserShip(Interface *interf, Ship *userShip) {
    int length = userShip->getLength();

    std::string shipSquares[length];

    std::cout << "Please pick the squares for your ship of length " << length << ":" << std::endl;
    int squareIndex[length];
    for(int i = 0; i < length; i++) {

        std::cin >> shipSquares[i];
        std::cout << "VALUE 1 = " << shipSquares[i-1].at(1) << std::endl;
        std::cout << "VALUE 2 = " << shipSquares[i].at(1) << std::endl;

        //checking if is input is in form of 2 char squares for example: A1, B5, J9 etc
        if(shipSquares[i].length() != 2) {
            throw Exception("square not assigned properly", 1);
        } else if((int)shipSquares[i].at(0) < 65 || (int)shipSquares[i].at(0) > 74) {
            throw Exception("square not assigned properly", 1);
        } else if((int)shipSquares[i].at(1) - 48 < 0 || (int)shipSquares[i].at(1) - 48 > 9) {
            throw Exception("square not assigned properly", 1);
        }

        //checking if the ship squares are next to each other //TO BE FIXED
        squareIndex[i] = parseSquareInputToIndex(shipSquares[i]);
        if(i > 0 && (squareIndex[i] != (squareIndex[i-1] - 10) && squareIndex[i] != (squareIndex[i-1]  + 10) && squareIndex[i] != (squareIndex[i-1] - 1) && squareIndex[i] != (squareIndex[i-1]+ 1))) {
            throw Exception("squares not assigned properly",2);
        } else if (i > 0 && shipSquares[i-1].at(1) == '9' && shipSquares[i].at(1) == '0') {
            throw Exception("squares not assigned properly",2);
        }
    }

    //checking if one of the squares on input is already taken by a ship or surrounding a ship
    for(int i = 0; i < length; i++) {
        if (interf->isTakenByShip(shipSquares[i]) == 1) {
            throw Exception("squares not assigned properly", 3);
        }
    }

    //checking if there are duplicate squares on input
    if(length > 1) {
        std::string *end = shipSquares + length;
        std::sort(shipSquares, end);
        bool containsDuplicates = (std::unique(shipSquares, end) != end);
        if (containsDuplicates == 1) {
            throw Exception("squares not assigned properly", 4);
        }
    }

    //assigning interface squares as taken
    for (int i = 0; i < length; i++) {
        interf->setTakenByUserShip(shipSquares[i]);
    }
    //initializing a user ship
    userShip->initShip(shipSquares);

}

bool checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfEnemy, Interface *interf, User *playerShotAt) {
    int lengthOfShip = ships[0]->getLength();
    int numOfShips;
    if(lengthOfShip == 1)  numOfShips = playerShotAt->getNumOfShips1();
    if(lengthOfShip == 2)  numOfShips = playerShotAt->getNumOfShips2();
    if(lengthOfShip == 3)  numOfShips = playerShotAt->getNumOfShips3();
    if(lengthOfShip == 4)  numOfShips = playerShotAt->getNumOfShips4();
    //checking through ships of length 1
    if(lengthOfShip == 1) {
        for (int i = 0; i < numOfShips; i++) {
            for (int j = 0; j < lengthOfShip; j++) {
                if (ships[i]->getShipSquares()[j] == guessSquareOfEnemy) {
                    std::cout << "Enemy guessed correctly: " << guessSquareOfEnemy << ", and destroyed your whole ship!"<< std::endl;
                    ships[i]->setAlive(false);
                    interf->setDestroyedUserShipWhole(guessSquareOfEnemy);
                    return true;
                }
            }
        }
    } else { //checking through ships of length 2, 3 and 4
        for (int i = 0; i < numOfShips; i++) {
            for (int j = 0; j < lengthOfShip; j++) {
                if (ships[i]->getShipSquares()[j] == guessSquareOfEnemy) {
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
                                interf->setDestroyedUserShipWhole(ships[i]->getShipSquares()[k]);
                            }
                            ships[i]->setAlive(false);
                            return true;
                        }
                    }
                    interf->setDestroyedUserShipPart(guessSquareOfEnemy);
                    return true;
                }
            }
        }
    }

    return false;
}

bool checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfUser, Interface *interf, Enemy *playerShotAt) {

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
                    std::cout << "You guessed correctly! You destroyed this enemy ship!" << std::endl;
                    ships[i]->setAlive(false);
                    interf->setDestroyedEnemyShipWhole(guessSquareOfUser);
                    return true;
                }
            }
        }
    } else {
        //running through every square of every ship and checking if it is the same as the guess square
        for(int i = 0; i < numOfShips; i++) {
            for(int j = 0; j < lengthOfShip; j++) {
                if(ships[i]->getShipSquares()[j] == guessSquareOfUser) {
                    std::cout << "You guessed correctly! You destroyed this part of the enemy ship!" << std::endl;
                    int numOfAliveParts = ships[i]->getNumOfAliveParts();
                    if(numOfAliveParts > 0) {
                        numOfAliveParts--;
                        ships[i]->setNumOfAliveParts(numOfAliveParts);
                        if(numOfAliveParts == 0) {
                            std::cout << "This was the last part of the ship! You have destroyed the whole ship!" << std::endl;
                            for (int k = 0; k < lengthOfShip; k++) {
                                interf->setDestroyedEnemyShipWhole(ships[i]->getShipSquares()[k]);
                            }
                            ships[i]->setAlive(false);
                            return true;
                        }
                    }
                    interf->setDestroyedEnemyShipPart(guessSquareOfUser);
                    return true;
                }
            }
        }
    }

    return false ;
}

//templates
template <typename T>
int checkIfSquareWasAlreadyShot(std::string &guessSquare, T *playerShotAt) {
    for(int i = 0; i < playerShotAt->getNumOfShots(); i++) {
        if(playerShotAt->getShotSquare(i) == guessSquare) {
            return -1;
        }
    }
    return 0;
}

int userShoot(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship* enemyShips4[], Interface *interf, User *user, Enemy *playerShotAt) {
    std::string guessSquare;
    std::cout << "Shoot at a square: " << std::endl;

    //example of catching errors
    std::cin >> guessSquare;
    if(guessSquare.length() != 2) {
        throw Exception("could not interpret input properly", 1);
    } else if ((int)guessSquare[0] < 65 || (int)guessSquare[0] > 74) {
        throw Exception("could not interpret input properly", 1);
    } else if ( (int)guessSquare[1] - 48 < 0 || (int)guessSquare[1] - 48 > 9) {
        throw Exception("could not interpret input properly", 1);
    }

    int wasShot = checkIfSquareWasAlreadyShot(guessSquare, user);
    while(wasShot != 0) {
        std::cout <<  "You have already shot at this square! Please shoot another square: " << std::endl;
        std::cin >> guessSquare;
        if(guessSquare.length() != 2) {
            throw Exception("could not interpret input properly", 1);
        } else if ((int)guessSquare[0] < 65 || (int)guessSquare[0] > 74) {
            throw Exception("could not interpret input properly", 1);
        } else if ( (int)guessSquare[1] - 48 < 0 || (int)guessSquare[1] - 48 > 9) {
            throw Exception("could not interpret input properly", 1);
        }
        wasShot = checkIfSquareWasAlreadyShot(guessSquare, user);
    }

    user->setShotSquare(user->getNumOfShots(), guessSquare);
    user->setNumOfShots(user->getNumOfShots() + 1);

    bool status[4] = {false, false, false, false};
    status[0] = checkIfGuessWasCorrect(enemyShips1, guessSquare, interf, playerShotAt);
    status[1] = checkIfGuessWasCorrect(enemyShips2, guessSquare, interf, playerShotAt);
    status[2] = checkIfGuessWasCorrect(enemyShips3, guessSquare, interf, playerShotAt);
    status[3] = checkIfGuessWasCorrect(enemyShips4, guessSquare, interf, playerShotAt);

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
        interf->setAlreadyShotEnemySquare(guessSquare);
        return status[0];
    }

    return -1;
}


int enemyShoot(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], Interface *interf, Enemy *enemy, User *playerShotAt) {

    std::string guessSquare;

    chooseSquare(guessSquare);
    int wasShot = checkIfSquareWasAlreadyShot(guessSquare, enemy);
    while(wasShot != 0) {
       // std::cout <<  "Enemy has already shot at this square! Enemy is choosing another square. " << std::endl;
        chooseSquare(guessSquare);
        wasShot = checkIfSquareWasAlreadyShot(guessSquare, enemy);
    }

    enemy->setShotSquare(enemy->getNumOfShots(), guessSquare);
    enemy->setNumOfShots(enemy->getNumOfShots() + 1);
    //std::cout << "NUM OF SHOTS: " << enemy->getNumOfShots() << std::endl;

    //std::cout << "Enemy is shooting at square " << guessSquare << "..." << std::endl;

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
        interf->setAlreadyShotUserSquare(guessSquare);
        return status[0];
    }

}

void chooseSquare( std::string &guessSquare) {
    int randomNumber = rand() % 10;
    int randomLetter = (rand() % 10) + 65;
    std::string randomLetterStr(1, char(randomLetter));
    std::string randomNumberStr = std::to_string(randomNumber);
    guessSquare = randomLetterStr + randomNumberStr;
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

void allocateUserShipsMemory(User *user, Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[]) {
    for(int i = 0; i < user->getNumOfShips1(); i++) userShips1[i] = new Ship1();
    for(int i = 0; i < user->getNumOfShips2(); i++) userShips2[i] = new Ship2();
    for(int i = 0; i < user->getNumOfShips3(); i++) userShips3[i] = new Ship3();
    for(int i = 0; i < user->getNumOfShips4(); i++) userShips4[i] = new Ship4();
}

void allocateEnemyShipsMemory(Enemy *enemy, Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[]) {
    for(int i = 0; i < enemy->getNumOfShips1(); i++) enemyShips1[i] = new Ship1();
    for(int i = 0; i < enemy->getNumOfShips2(); i++) enemyShips2[i] = new Ship2();
    for(int i = 0; i < enemy->getNumOfShips3(); i++) enemyShips3[i] = new Ship3();
    for(int i = 0; i < enemy->getNumOfShips4(); i++) enemyShips4[i] = new Ship4();
}

void deallocateUserShipsMemory(User *user, Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[]) {
    for(int i = 0; i < user->getNumOfShips1(); i++) delete userShips1[i];
    for(int i = 0; i < user->getNumOfShips2(); i++) delete userShips2[i];
    for(int i = 0; i < user->getNumOfShips3(); i++) delete userShips3[i];
    for(int i = 0; i < user->getNumOfShips4(); i++) delete userShips4[i];
}

void deallocateEnemyShipsMemory(Enemy *enemy, Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[]) {
    for(int i = 0; i < enemy->getNumOfShips1(); i++) delete enemyShips1[i];
    for(int i = 0; i < enemy->getNumOfShips2(); i++) delete enemyShips2[i];
    for(int i = 0; i < enemy->getNumOfShips3(); i++) delete enemyShips3[i];
    for(int i = 0; i < enemy->getNumOfShips4(); i++) delete enemyShips4[i];
}