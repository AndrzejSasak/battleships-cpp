#ifndef JIPP2_LIB_H
#define JIPP2_LIB_H

#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include "../../BattleshipsApp/include/Ship.h"
#include "../../BattleshipsApp/include/Ship1.h"
#include "../../BattleshipsApp/include/Ship2.h"
#include "../../BattleshipsApp/include/Ship3.h"
#include "../../BattleshipsApp/include/Ship4.h"
#include "../../BattleshipsApp/include/User.h"
#include "../../BattleshipsApp/include/Interface.h"
#include "../../BattleshipsApp/include/Enemy.h"
#include "../../BattleshipsApp/include/Exception.h"

/**
 * prints a welcome message
 */
void printWelcomeScreen();

/**
 * this function reads squares from file and saves them to a ship square of enemy
 * @param line line from a file
 * @param index1 index of a letter in file
 * @param index2 index of a number in file
 * @return ship square concatenated from index1 and index2
 */
std::string readSquares(std::string line, int index1, int index2);

//overloaded functions depending on which player's number of alive ships is returned
/**
 * this function returns the number of alive ships of the user
 * @param ships1 user ships of length 1
 * @param ships2 user ships of length 2
 * @param ships3 user ships of length 3
 * @param ships4 user ships of length 4
 * @param user instance of the user player
 * @return the number of alive ships of the user
 */
int getNumOfAliveShips(Ship *ships1[], Ship *ships2[], Ship *ships3[], Ship *ships4[], User *user);

/**
 * this function returns the number of alive ships of the enemy
 * @param ships1 enemy ships of length 1
 * @param ships2 enemy ships of length 2
 * @param ships3 enemy ships of length 3
 * @param ships4 enemy ships of length 4
 * @param user instance of the enemy player
 * @return the number of alive ships of the enemy
 */
int getNumOfAliveShips(Ship *ships1[], Ship *ships2[], Ship *ships3[], Ship *ships4[], Enemy *enemy);

/**
 * this function is used to get difficulty from the user from standard input
 * @param enemy instance of the enemy player
 */
void pickDifficulty(Enemy *enemy);

/**
 * this function is used for reading all users and their corresponding passwords from a database into a map container and
 * checking if the entered user exists in the database.
 * @param argv1 username
 * @param argv2 password
 * @param usersFile database of users to which users will be saved and from which users will be read
 */
void selectUser(char *argv1, char *argv2, std::fstream *usersFile);

/**
 * this function transfers data from a map container to the database output file
 * @param ofstream output stream for saving users to database
 * @param map map which contains all users during the execution of the program
 */
void saveUsersToDatabase(std::ofstream *ofstream, std::map<std::string, std::string> *map);

/**
 * this function inserts a new user into a map container with all other users.
 * @param name name of the user
 * @param password password of the user
 * @param map map which contains all users during the execution of the program
 */
void addNewUserToDatabase(std::string name, std::string password, std::map<std::string, std::string> *map);

/**
 * this function reads chooses a board from a file and initializes all enemy ships based on the baord
 * @param enemyShips1 enemy ships of length 1
 * @param enemyShips2 enemy ships of length 2
 * @param enemyShips3 enemy ships of length 3
 * @param enemyShips4 enemy ships of length 4
 * @param enemy instance of the enemy player
 * @param interf instance of the interface
 */
void pickAllEnemyShips(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[], Enemy *enemy, Interface *interf);

/**
 * this function invokes functions responsible for picking user ships of length 1, 2, 3 and 4
 * @param userShips1 user ships of length 1
 * @param userShips2 user ships of length 2
 * @param userShips3 user ships of length 3
 * @param userShips4 user ships of length 4
 * @param user instance of the user player
 * @param interf instance of the interface
 */
void pickAllUserShips(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], User *user, Interface *interf);

/**
 * this function reads ship squares from the standard input and initializes the interface and user ships
 * based on the input
 * @param interf instance of the interface
 * @param userShip instance of a user ship
 */
void pickUserShip(Interface *interf, Ship *userShip);

/**
 * this function translates input squares in form of [A-J][0-9] to a index corresponding to its square
 * @param square square in a form of a string for example A0, A1, A2...
 * @return square index corresponding its square for example 0 for A0, 10 for B0, 99 for J9
 */
int parseSquareInputToIndex(std::string square);

//overloaded functions depending on who is shooting
/**
 * this function iterates through all ships squares of *ships[] and checks if the guess square of the enemy is
 * the same as one of the user ship squares
 * @param ships array of ships
 * @param guessSquareOfEnemy square guessed by the enemy
 * @param interf instance of the interface
 * @param playerShotAt player that is being shot at (user)
 * @return
 */
bool checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfEnemy, Interface *interf, User *playerShotAt);

/**
 * this function iterates through all ships of *ships[] and check if the guess square of user is
 * the same as one the enemy ship squares
 * @param ships array of ships
 * @param guessSquareOfUser square guessed by the user
 * @param interf instance of the interface
 * @param playerShotAt player that is being shot at (enemy)
 * @return true if guess was correct, false if guess was not correct
 */
bool checkIfGuessWasCorrect(Ship *ships[], std::string guessSquareOfUser, Interface *interf, Enemy *playerShotAt);

/**
 * this function checks if the new guess square has already been shot
 * @tparam T player that is shooting
 * @param guessSquare guess square of the player shooting
 * @param playerShooting of type User or Enemy
 * @return -1 if square was already shot, 0 if the guess square is a newly input square
 */
template <typename T>
int checkIfSquareWasAlreadyShot(std::string &guessSquare, T *playerShooting);

/**
 * this function reads a user guess square from standard input and checks if the square was already shot
 * and if the guess is correct
 * @param enemyShips1 enemy ships of length 1
 * @param enemyShips2 enemy ships of length 2
 * @param enemyShips3 enemy ships of length 3
 * @param enemyShips4 enemy ships of length 4
 * @param interf instance of the interface
 * @param user instance of the user player
 * @param playerShotAt player that is being shot at (enemy)
 * @return 1 if user hits a target, 0 if user does not hit a target
 */
int userShoot(Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship* enemyShips4[], Interface *interf, User *user, Enemy *playerShotAt);

/**
 * this function picks a random square to be shot by the enemy, checks if the square was already shot and
 * determines if the guess is correct
 * @param userShips1 user ships of length 1
 * @param userShips2 user ships of length 2
 * @param userShips3 user ships of length 3
 * @param userShips4 user ships of length 4
 * @param interf instance of the interface
 * @param enemy instance of the enemy player
 * @param playerShotAt player that is being shot at (user)
 * @return 1 if enemy hits a target, 0 if enemy does not hit a target
 */
int enemyShoot(Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[], Interface *interf, Enemy *enemy, User *playerShotAt);

/**
 * this function picks a random square to be shot by the enemy
 * @param guessSquare square being chosen by the enemy
 */
void chooseSquare( std::string &guessSquare);

/**
 * thsi function allocates memory for user ships
 * @param user instance of the user player
 * @param userShips1 user ships of length 1
 * @param userShips2 user ships of length 2
 * @param userShips3 user ships of length 3
 * @param userShips4 user ships of length 4
 */
void allocateUserShipsMemory(User *user, Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[]);

/**
 * this function allocates memory for enemy ships
 * @param enemy instance of the enemy player
 * @param enemyShips1 enemy ships of length 1
 * @param enemyShips2 enemy ships of length 2
 * @param enemyShips3 enemy ships of length 3
 * @param enemyShips4 enemy ships of length 4
 */
void allocateEnemyShipsMemory(Enemy *enemy, Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[]);

/**
 * this function deallocates memory of the user ships
 * @param user instance of the user player
 * @param userShips1 user ships of length 1
 * @param userShips2 user ships of length 2
 * @param userShips3 user ships of length 3
 * @param userShips4 user ships of length 4
 */
void deallocateUserShipsMemory(User *user, Ship *userShips1[], Ship *userShips2[], Ship *userShips3[], Ship *userShips4[]);

/**
 *this function deallocates memory of the enemy ships
 * @param enemy instance of the enemy player
 * @param enemyShips1 enemy ships of length 1
 * @param enemyShips2 enemy ships of length 2
 * @param enemyShips3 enemy ships of length 3
 * @param enemyShips4 enemy ships of length 4
 */
void deallocateEnemyShipsMemory(Enemy *enemy, Ship *enemyShips1[], Ship *enemyShips2[], Ship *enemyShips3[], Ship *enemyShips4[]);

#endif //JIPP2_LIB_H




