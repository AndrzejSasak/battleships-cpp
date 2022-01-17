//
// Created by endriu on 15.12.2021.
//

#ifndef JIPP2_LIB_H
#define JIPP2_LIB_H
#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
//#include <windows.h>
#include "../../BattleshipsApp/include/Ship.h"
#include "../../BattleshipsApp/include/Ship1.h"
#include "../../BattleshipsApp/include/Ship2.h"
#include "../../BattleshipsApp/include/Ship3.h"
#include "../../BattleshipsApp/include/Ship4.h"
#include "../../BattleshipsApp/include/User.h"
#include "../../BattleshipsApp/include/Interface.h"
#include "../../BattleshipsApp/include/Enemy.h"

void printWelcomeScreen();

void selectUser(char *argv1, char *argv2, std::fstream *usersFile);
void saveUsersToDatabase(std::ofstream *ofstream, std::map<std::string, std::string> *map);
void addNewUserToDatabase(std::string name, std::string password, std::map<std::string, std::string> *map);

void pickAllEnemyShips(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[], Enemy *enemy, Interface *interf);
void pickAllUserShips(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], User *user, Interface *interf);
int pickUserShip(Interface *interf, Ship *userShip);
int parseSquareInputToIndex(std::string square);

//przeciazone metody w zaleznosci od tego kto strzela
int checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfEnemy, Interface *interf, User *playerShotAt);
int checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfUser, Interface *interf, Enemy *playerShotAt);

int userShoot(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship* enemyShips4[], Interface *interf, User *user, Enemy *playerShotAt);
int enemyShoot(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], Interface *interf, Enemy *enemy, User *playerShotAt);

void chooseSquare( std::string &guessSquare);

void allocateUserShipsMemory(User *user, Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[]);
void allocateEnemyShipsMemory(Enemy *enemy, Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[]);

void deallocateUserShipsMemory(User *user, Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[]);
void deallocateEnemyShipsMemory(Enemy *enemy, Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[]);
//szablony
//int checkIfSquareWasAlreadyShot(std::string &guessSquare, User *user);

#endif //JIPP2_LIB_H
