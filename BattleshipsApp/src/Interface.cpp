//
// Created by endriu on 15.12.2021.
//

#include "../include/Interface.h"
#include "../include/Ship.h"

#include <iostream>

#define TAKENBYSHIP "@"
#define FREESQUARE "."
#define SURROUNDINGSHIP ","
#define DESTROYEDSHIPPART "x"
#define DESTROYEDSHIPFINAL "X"
#define ALREADYSHOTSQUARE "A"

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
        std::cout << userArea[i] + " ";
        if(i == 0) {
            continue;
        } else if (i%10 == 9) std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
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
        std::cout << enemyArea[i] + " ";
        if(i == 0) {
            continue;
        } else if (i%10 == 9) std::cout << std::endl;
    }
}

//sets an unused user square to a ship square
void setTakenByUserShip(std::string newSquare, Interface* interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    interface->userArea[squareIndex] = TAKENBYSHIP;

    if(newSquare[0] != 'A' && newSquare[0] != 'J' && newSquare[1] != '0' && newSquare[1] != '9') {
        if (interface->userArea[squareIndex-11] != TAKENBYSHIP) interface->userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-10] != TAKENBYSHIP) interface->userArea[squareIndex-10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-9] != TAKENBYSHIP) interface->userArea[squareIndex-9] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-1] != TAKENBYSHIP) interface->userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+1] != TAKENBYSHIP) interface->userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+9] != TAKENBYSHIP) interface->userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+10] != TAKENBYSHIP) interface->userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+11] != TAKENBYSHIP) interface->userArea[squareIndex+11] = SURROUNDINGSHIP;
        return;
    } else if (newSquare[1] == '0' && newSquare[0] != 'A' && newSquare[0] != 'J') {
        if (interface->userArea[squareIndex-10] != TAKENBYSHIP) interface->userArea[squareIndex-10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-9] != TAKENBYSHIP) interface->userArea[squareIndex-9] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+1] != TAKENBYSHIP) interface->userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+10] != TAKENBYSHIP) interface->userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+11] != TAKENBYSHIP)interface->userArea[squareIndex+11] = SURROUNDINGSHIP;
        return;
    } else if (newSquare[1] == '9' && newSquare[0] != 'A' && newSquare[0] != 'J') {
        if (interface->userArea[squareIndex-10] != TAKENBYSHIP) interface->userArea[squareIndex-10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-11] != TAKENBYSHIP)interface->userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+1] != TAKENBYSHIP) interface->userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+9] != TAKENBYSHIP) interface->userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+10] != TAKENBYSHIP)interface->userArea[squareIndex+10] = SURROUNDINGSHIP;
        return;
    } else if (newSquare[0] == 'A' && newSquare[1] != '0' && newSquare[1] != '9') {
        if (interface->userArea[squareIndex-1] != TAKENBYSHIP) interface->userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+1] != TAKENBYSHIP) interface->userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+9] != TAKENBYSHIP) interface->userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+10] != TAKENBYSHIP) interface->userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+11] != TAKENBYSHIP) interface->userArea[squareIndex+11] = SURROUNDINGSHIP;
        return;
    } else if (newSquare[0] == 'J' && newSquare[1] != '0' && newSquare[1] != '9') {
        if (interface->userArea[squareIndex-1] != TAKENBYSHIP) interface->userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+1] != TAKENBYSHIP) interface->userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-11] != TAKENBYSHIP) interface->userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-10] != TAKENBYSHIP) interface->userArea[squareIndex-10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-9] != TAKENBYSHIP) interface->userArea[squareIndex-9] = SURROUNDINGSHIP;
        return;
    } else if(newSquare[0] == 'A' && newSquare[1] == '0') {
        if (interface->userArea[squareIndex+1] != TAKENBYSHIP) interface->userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+10] != TAKENBYSHIP) interface->userArea[squareIndex+10] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+11] != TAKENBYSHIP) interface->userArea[squareIndex+11] = SURROUNDINGSHIP;
        return;
    } else if(newSquare[0] == 'J' && newSquare[1] == '0') {
        if (interface->userArea[squareIndex+1] != TAKENBYSHIP) interface->userArea[squareIndex+1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-9] != TAKENBYSHIP) interface->userArea[squareIndex-9] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-10] != TAKENBYSHIP) interface->userArea[squareIndex-10] = SURROUNDINGSHIP;
        return;
    } else if(newSquare[0] == 'A' && newSquare[1] == '9') {
        if (interface->userArea[squareIndex-1] != TAKENBYSHIP) interface->userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+9] != TAKENBYSHIP) interface->userArea[squareIndex+9] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex+10] != TAKENBYSHIP) interface->userArea[squareIndex+10] = SURROUNDINGSHIP;
        return;
    } else if(newSquare[0] == 'J' && newSquare[1] == '9') {
        if (interface->userArea[squareIndex-1] != TAKENBYSHIP) interface->userArea[squareIndex-1] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-11] != TAKENBYSHIP) interface->userArea[squareIndex-11] = SURROUNDINGSHIP;
        if (interface->userArea[squareIndex-10] != TAKENBYSHIP) interface->userArea[squareIndex-10] = SURROUNDINGSHIP;
        return;
    }

}

//sets an unused enemy square to a ship square
//mozna poprzeciazac funkcje
void setTakenByEnemyShip(std::string newSquare, Interface* interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    //interf->enemyArea[squareIndex] = TAKENBYSHIP;
}

void setDestroyedUserShipPart(std::string newSquare, Interface* interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    interface->userArea[squareIndex] = DESTROYEDSHIPPART;
}

void setDestroyedUserShipWhole(std::string newSquare, Interface* interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    interface->userArea[squareIndex] = DESTROYEDSHIPFINAL;
}

void setDestroyedEnemyShipWhole(std::string newSquare, Interface* interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    interface->enemyArea[squareIndex] = DESTROYEDSHIPFINAL;
}

void setDestroyedEnemyShipPart(std::string newSquare, Interface *interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    interface->enemyArea[squareIndex] = DESTROYEDSHIPPART;
}

bool isTakenByShip(std::string newSquare, Interface* interface) {
    int isTaken = false;
    int squareIndex = parseSquareInputToIndex(newSquare);
    if(interface->userArea[squareIndex] == TAKENBYSHIP || interface->userArea[squareIndex] == SURROUNDINGSHIP) {
        isTaken = true;
    }
    return isTaken;
}

//mozna przeciazyc setAlreadyShotUserSquare oraz setAlreadyShotEnemySquare
void setAlreadyShotUserSquare(std::string newSquare, Interface *interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    interface->userArea[squareIndex] = ALREADYSHOTSQUARE;
}

void setAlreadyShotEnemySquare(std::string newSquare, Interface *interface) {
    int squareIndex = parseSquareInputToIndex(newSquare);
    interface->enemyArea[squareIndex] = ALREADYSHOTSQUARE;
}
