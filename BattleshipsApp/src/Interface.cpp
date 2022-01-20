//
// Created by endriu on 15.12.2021.
//

#include "../include/Interface.h"
#include "../include/Ship.h"
#include <lib.h>
#include <iostream>


#define TAKENBYSHIP "@"
#define FREESQUARE "."
#define SURROUNDINGSHIP ","
#define DESTROYEDSHIPPART "x"
#define DESTROYEDSHIPFINAL "X"
#define ALREADYSHOTSQUARE "*"

Interface::Interface() {
    for(int i = 0; i < 100; ++i) {
        userArea[i] = FREESQUARE;
    }
    for(int i = 0; i < 100; ++i) {
        enemyArea[i] = FREESQUARE;
    }
}

//prints interf
void Interface::printInterface()  {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout << "YOUR AREA:" << std::endl;
    std::cout << "  0 1 2 3 4 5 6 7 8 9" << std::endl;
    for(int i = 0; i < 100; ++i) {
        switch(i) {
            case 0: std::cout << "A ";
                break;
            case 10: std::cout << "B ";
                break;
            case 20: std::cout << "C ";
                break;
            case 30: std::cout << "D ";
                break;
            case 40: std::cout << "E ";
                break;
            case 50: std::cout << "F ";
                break;
            case 60: std::cout << "G ";
                break;
            case 70: std::cout << "H ";
                break;
            case 80: std::cout << "I ";
                break;
            case 90: std::cout << "J ";
                break;
            default:
                break;
        }
        pickUserAreaColors(hConsole, i);
        if(i == 0) {
            continue;
        } else if (i%10 == 9) std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "ENEMY'S AREA" << std::endl;
    std::cout << "  0 1 2 3 4 5 6 7 8 9" << std::endl;
    for(int i = 0; i  < 100; ++i) {
        switch(i) {
            case 0: std::cout << "A ";
                break;
            case 10: std::cout << "B ";
                break;
            case 20: std::cout << "C ";
                break;
            case 30: std::cout << "D ";
                break;
            case 40: std::cout << "E ";
                break;
            case 50: std::cout << "F ";
                break;
            case 60: std::cout << "G ";
                break;
            case 70: std::cout << "H ";
                break;
            case 80: std::cout << "I ";
                break;
            case 90: std::cout << "J ";
                break;
            default:
                break;
        }
        pickEnemyAreaColors(hConsole, i);
        if(i == 0) {
            continue;
        } else if (i%10 == 9) std::cout << std::endl;
    }
}

void Interface::pickEnemyAreaColors(HANDLE hConsole, int i) {
    if(enemyArea[i] == TAKENBYSHIP) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << enemyArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    } else if(enemyArea[i] == DESTROYEDSHIPPART) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << enemyArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    } else if(enemyArea[i] == DESTROYEDSHIPFINAL ) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY );
        std::cout << enemyArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    } else if (enemyArea[i] == ALREADYSHOTSQUARE) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << enemyArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    } else {
        std::cout << enemyArea[i] + " ";
    }
}

void Interface::pickUserAreaColors(HANDLE hConsole, int i) {
    if(userArea[i] == TAKENBYSHIP) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << userArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    } else if(userArea[i] == DESTROYEDSHIPPART) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        std::cout << userArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    } else if(userArea[i] == DESTROYEDSHIPFINAL) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        std::cout << userArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    } else if (userArea[i] == ALREADYSHOTSQUARE) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
        std::cout << userArea[i];
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << " ";
    }  else {
        std::cout << userArea[i] + " ";
    }
}

void Interface::checkSurroundings(int squareIndex, int surroundingSquareIndex)  {
    if (userArea[squareIndex + surroundingSquareIndex] != TAKENBYSHIP) {
        userArea[squareIndex + surroundingSquareIndex] = SURROUNDINGSHIP;
    }
}

//sets an unused user square to a ship square
void Interface::setTakenByUserShip(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    userArea[squareIndex] = TAKENBYSHIP;

    if(newSquare[0] != 'A' && newSquare[0] != 'J' && newSquare[1] != '0' && newSquare[1] != '9') {
        checkSurroundings(squareIndex, -11);
        checkSurroundings(squareIndex, -10);
        checkSurroundings(squareIndex, -9);
        checkSurroundings(squareIndex, -1);
        checkSurroundings(squareIndex, 1);
        checkSurroundings(squareIndex, 9);
        checkSurroundings(squareIndex, 10);
        checkSurroundings(squareIndex, 11);
        /*
        if (userArea[squareIndex-11] != TAKENBYSHIP) userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (userArea[squareIndex-10] != TAKENBYSHIP) userArea[squareIndex-10] = SURROUNDINGSHIP;
        if (userArea[squareIndex-9] != TAKENBYSHIP) userArea[squareIndex-9] = SURROUNDINGSHIP;
        if (userArea[squareIndex-1] != TAKENBYSHIP) userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+1] != TAKENBYSHIP) userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+9] != TAKENBYSHIP) userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (userArea[squareIndex+10] != TAKENBYSHIP) userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (userArea[squareIndex+11] != TAKENBYSHIP) userArea[squareIndex+11] = SURROUNDINGSHIP;
         */
        return;
    } else if (newSquare[1] == '0' && newSquare[0] != 'A' && newSquare[0] != 'J') {
        checkSurroundings(squareIndex, -10);
        checkSurroundings(squareIndex, -9);
        checkSurroundings(squareIndex, 1);
        checkSurroundings(squareIndex, 10);
        checkSurroundings(squareIndex, 11);
        /*
        if (userArea[squareIndex-10] != TAKENBYSHIP) userArea[squareIndex-10] = SURROUNDINGSHIP;
        if (userArea[squareIndex-9] != TAKENBYSHIP) userArea[squareIndex-9] = SURROUNDINGSHIP;
        if (userArea[squareIndex+1] != TAKENBYSHIP) userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+10] != TAKENBYSHIP) userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (userArea[squareIndex+11] != TAKENBYSHIP) userArea[squareIndex+11] = SURROUNDINGSHIP;
         */
        return;
    } else if (newSquare[1] == '9' && newSquare[0] != 'A' && newSquare[0] != 'J') {
        checkSurroundings(squareIndex, -11);
        checkSurroundings(squareIndex, -1);
        checkSurroundings(squareIndex, -10);
        checkSurroundings(squareIndex, 9);
        checkSurroundings(squareIndex, 10);
        /*
        if (userArea[squareIndex-11] != TAKENBYSHIP) userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (userArea[squareIndex+1] != TAKENBYSHIP) userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+9] != TAKENBYSHIP) userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (userArea[squareIndex+10] != TAKENBYSHIP)userArea[squareIndex+10] = SURROUNDINGSHIP;
         */
        return;
    } else if (newSquare[0] == 'A' && newSquare[1] != '0' && newSquare[1] != '9') {
        checkSurroundings(squareIndex, -1);
        checkSurroundings(squareIndex, 1);
        checkSurroundings(squareIndex, 9);
        checkSurroundings(squareIndex, 10);
        checkSurroundings(squareIndex, 11);
        /*
        if (userArea[squareIndex-1] != TAKENBYSHIP) userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+1] != TAKENBYSHIP) userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+9] != TAKENBYSHIP) userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (userArea[squareIndex+10] != TAKENBYSHIP) userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (userArea[squareIndex+11] != TAKENBYSHIP) userArea[squareIndex+11] = SURROUNDINGSHIP;
         */
        return;
    } else if (newSquare[0] == 'J' && newSquare[1] != '0' && newSquare[1] != '9') {
        checkSurroundings(squareIndex, -1);
        checkSurroundings(squareIndex, 1);
        checkSurroundings(squareIndex, -11);
        checkSurroundings(squareIndex, -10);
        checkSurroundings(squareIndex, -9);
        /*
        if (userArea[squareIndex-1] != TAKENBYSHIP) userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+1] != TAKENBYSHIP) userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (userArea[squareIndex-11] != TAKENBYSHIP) userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (userArea[squareIndex-10] != TAKENBYSHIP) userArea[squareIndex-10] = SURROUNDINGSHIP;
        if (userArea[squareIndex-9] != TAKENBYSHIP) userArea[squareIndex-9] = SURROUNDINGSHIP;
         */
        return;
    } else if(newSquare[0] == 'A' && newSquare[1] == '0') {
        checkSurroundings(squareIndex, 1);
        checkSurroundings(squareIndex, 10);
        checkSurroundings(squareIndex, 11);
        /*
        if (userArea[squareIndex+1] != TAKENBYSHIP) userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+10] != TAKENBYSHIP) userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (userArea[squareIndex+11] != TAKENBYSHIP) userArea[squareIndex+11] = SURROUNDINGSHIP;
         */
        return;
    } else if(newSquare[0] == 'J' && newSquare[1] == '0') {
        checkSurroundings(squareIndex, 1);
        checkSurroundings(squareIndex, -9);
        checkSurroundings(squareIndex, -10);
        /*
        if (userArea[squareIndex+1] != TAKENBYSHIP) userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (userArea[squareIndex-9] != TAKENBYSHIP) userArea[squareIndex-9] = SURROUNDINGSHIP;
        if (userArea[squareIndex-10] != TAKENBYSHIP) userArea[squareIndex-10] = SURROUNDINGSHIP;
         */
        return;
    } else if(newSquare[0] == 'A' && newSquare[1] == '9') {
        checkSurroundings(squareIndex, -1);
        checkSurroundings(squareIndex, 9);
        checkSurroundings(squareIndex, 10);
        /*
        if (userArea[squareIndex-1] != TAKENBYSHIP) userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (userArea[squareIndex+9] != TAKENBYSHIP) userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (userArea[squareIndex+10] != TAKENBYSHIP) userArea[squareIndex+10] = SURROUNDINGSHIP;
         */
        return;
    } else if(newSquare[0] == 'J' && newSquare[1] == '9') {
        checkSurroundings(squareIndex, -1);
        checkSurroundings(squareIndex, -11);
        checkSurroundings(squareIndex, -10);
        /*
        if (userArea[squareIndex-1] != TAKENBYSHIP) userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (userArea[squareIndex-11] != TAKENBYSHIP) userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (userArea[squareIndex-10] != TAKENBYSHIP) userArea[squareIndex-10] = SURROUNDINGSHIP;
         */
        return;
    }
}

[[maybe_unused]] void Interface::setTakenByEnemyShip(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    enemyArea[squareIndex] = TAKENBYSHIP;
}

void Interface::setDestroyedUserShipPart(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    userArea[squareIndex] = DESTROYEDSHIPPART;
}

void Interface::setDestroyedUserShipWhole(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    userArea[squareIndex] = DESTROYEDSHIPFINAL;
}

void Interface::setDestroyedEnemyShipWhole(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    enemyArea[squareIndex] = DESTROYEDSHIPFINAL;
}

void Interface::setDestroyedEnemyShipPart(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    enemyArea[squareIndex] = DESTROYEDSHIPPART;
}

bool Interface::isTakenByShip(std::string newSquare) {
    int isTaken = false;
    int squareIndex = parseSquareInputToIndex(newSquare);
    if(userArea[squareIndex] == TAKENBYSHIP || userArea[squareIndex] == SURROUNDINGSHIP) {
        isTaken = true;
    }
    return isTaken;
}

void Interface::setAlreadyShotUserSquare(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    userArea[squareIndex] = ALREADYSHOTSQUARE;
}

void Interface::setAlreadyShotEnemySquare(std::string newSquare) {
    int squareIndex = parseSquareInputToIndex(newSquare);
   enemyArea[squareIndex] = ALREADYSHOTSQUARE;
}

