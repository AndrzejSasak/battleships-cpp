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

/**
 * prints a welcome message
 */
void printWelcomeScreen();

/**
 *
 * @param argv1 username
 * @param argv2 password
 * @param usersFile database of users to which users will be saved and from which users will be read
 */
void selectUser(char *argv1, char *argv2, std::fstream *usersFile);

/**
 *
 * @param ofstream output stream for saving users to database
 * @param map map which contains all users during the execution of the program
 */
void saveUsersToDatabase(std::ofstream *ofstream, std::map<std::string, std::string> *map);

/**
 *
 * @param name name of the user
 * @param password password of the user
 * @param map map which contains all users during the execution of the program
 */
void addNewUserToDatabase(std::string name, std::string password, std::map<std::string, std::string> *map);

/**
 *
 * @param enemyShips1 enemy ships of length 1
 * @param enemyShips2 enemy ships of length 2
 * @param enemyShips3 enemy ships of length 3
 * @param enemyShips4 enemy ships of length 4
 * @param enemy instance of the enemy player
 * @param interf instance of the interface
 */
void pickAllEnemyShips(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[], Enemy *enemy, Interface *interf);

/**
 *
 * @param userShips1 user ships of length 1
 * @param userShips2 user ships of length 2
 * @param userShips3 user ships of length 3
 * @param userShips4 user ships of length 4
 * @param user instance of the user player
 * @param interf instance of the interface
 */
void pickAllUserShips(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], User *user, Interface *interf);

/**
 *
 * @param interf instance of the interface
 * @param userShip instance of a user ship
 */
void pickUserShip(Interface *interf, Ship *userShip);

/**
 *
 * @param square square in a form of a string for example A0, A1, A2...
 * @return square index corresponding its square for example 0 for A0, 10 for B0, 99 for J9
 */
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
