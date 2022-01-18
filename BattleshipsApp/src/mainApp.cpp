//
// Created by endriu on 15.12.2021.
//

#include <iostream>
//#include "../include/Ship4.h"
//#include "../include/Ship3.h"
//#include "../include/Ship2.h"
//#include "../include/Ship1.h"
#include <ctime>
#include <lib.h>
#include "../include/Exception.h"


int main(int argc, char *argv[]) {
    srand(time(nullptr));

    std::fstream usersFile("../../BattleshipsApp/users_database/users.txt");
    if(argc == 3) {
        try {
            selectUser(argv[1], argv[2], &usersFile);
        } catch (Exception &e) {
            std::cout << e.what() << std::endl;
            exit(-1);
        } catch (...) {
            std::cout << "ERROR HAPPENED" << std::endl;
            exit(-1);
        }
    }

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
    Ship *userShips2[user.getNumOfShips2()];
    Ship *userShips3[user.getNumOfShips3()];
    Ship *userShips4[user.getNumOfShips4()];
    allocateUserShipsMemory(&user, userShips1, userShips2, userShips3, userShips4);

    //initialize memory for enemy ships
    Ship *enemyShips1[enemy.getNumOfShips1()];
    Ship *enemyShips2[enemy.getNumOfShips2()];
    Ship *enemyShips3[enemy.getNumOfShips3()];
    Ship *enemyShips4[enemy.getNumOfShips4()];
    allocateEnemyShipsMemory(&enemy, enemyShips1, enemyShips2, enemyShips3, enemyShips4);

    interf.printInterface();

    bool isError = true;
    while(isError) {
        try {
            pickAllUserShips(userShips1, userShips2, userShips3, userShips4, &user, &interf);
            isError = false;
        } catch (Exception &e) {
            std::cout << e.what() << std::endl;
            std::cout << "ERROR HAPPENED!" << std::endl;
            std::cout << "PICK SHIPS AGAIN: " << std::endl;
            interf.resetUserArea();
            isError = true;
        } catch (...) {
            std::cout << "ERROR HAPPENED!" << std::endl;
            std::cout << "PICK SHIPS AGAIN: " << std::endl;
            interf.resetUserArea();
            isError = true;
        }
    }

    try {
        pickAllEnemyShips(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &enemy, &interf);
    } catch (Exception &e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    } catch (...) {
        std::cout << "ERROR HAPPENED!" << std::endl;
        exit(-1);
    }

    interf.printInterface();

    //game loop
    bool gameIsUndecided = true;
    while(gameIsUndecided) {

        int wasEnemyHit;
        isError = true;
        while(isError) {
            try {
                wasEnemyHit = userShoot(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &interf, &user, &enemy);
                isError = false;
            } catch (Exception &e) {
                std::cout << e.what() << std::endl;
                std::cout << "ERROR HAPPENED!" << std::endl;
                std::cout << "SHOOT AGAIN: " << std::endl;
                isError = true;
            } catch (...) {
                std::cout << "ERROR HAPPENED!" << std::endl;
                std::cout << "SHOOT AGAIN: " << std::endl;
                isError = true;
            }
        }

        interf.printInterface();
        while(wasEnemyHit) {
            //decrementing number of enemy's ship parts
            --enemy; //enemy.setNumOfAliveShipPts(enemy.getNumOfAliveShipPts() - wasUserHit);
            if (enemy.getNumOfAliveShipPts() == 0) {
                std::cout << "You have won the game! Congratulations!" << std::endl;
                interf.printInterface();
                gameIsUndecided = false;
                break;
            }
            isError = true;
            while(isError) {
                try {
                    wasEnemyHit = userShoot(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &interf, &user, &enemy);
                    isError = false;
                } catch (Exception &e) {
                    std::cout << e.what() << std::endl;
                    std::cout << "ERROR HAPPENED!" << std::endl;
                    std::cout << "SHOOT AGAIN: " << std::endl;
                    isError = true;
                } catch (...) {
                    std::cout << "ERROR HAPPENED!" << std::endl;
                    std::cout << "SHOOT AGAIN: " << std::endl;
                    isError = true;
                }
            }

            interf.printInterface();
        }
        if(!gameIsUndecided) break;

        //3 is number of shots the enemy takes
        for(int i = 0; i < 3; i++) {
            int wasUserHit = enemyShoot(userShips1, userShips2, userShips3, userShips4, &interf, &enemy, &user);
            if(wasUserHit) {
                //decrementing number of user's ship parts;
                --user;  //user.setNumOfAliveShipPts(user.getNumOfAliveShipPts() - wasUserHit);
                   std::cout << "ALIVE PTS: " << user.getNumOfAliveShipPts() << std::endl;
                    if(user.getNumOfAliveShipPts() == 0) {
                        std::cout << "Enemy has destroyed all your ships and won the game! You lost!" << std::endl;
                        gameIsUndecided = false;
                        break;
                    }
            }
        }

        interf.printInterface();
    }

    deallocateEnemyShipsMemory(&enemy, enemyShips1, enemyShips2, enemyShips3, enemyShips4);
    deallocateUserShipsMemory(&user, userShips1, userShips2, userShips3, userShips4);

    return 0;
}