//
// Created by endriu on 15.12.2021.
//

#include <iostream>
#include "../include/Ship4.h"
#include "../include/Ship3.h"
#include "../include/Ship2.h"
#include "../include/Ship1.h"
#include <ctime>
#include <lib.h>


int main(int argc, char *argv[]) {
    srand(time(nullptr));

    std::fstream usersFile("../../BattleshipsApp/users_database/users.txt");
    if(argc == 3) selectUser(argv[1], argv[2], &usersFile);

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

    pickAllUserShips(userShips1, userShips2, userShips3, userShips4, &user, &interf);
    pickAllEnemyShips(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &enemy, &interf);
    interf.printInterface();


    //game loop
    bool isUndecided = true;
    while(isUndecided) {

        int wasEnemyHit = userShoot(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &interf, &user, &enemy);
        interf.printInterface();
        while(wasEnemyHit) {
           // enemy.setNumOfAliveShipPts(enemy.getNumOfAliveShipPts() - wasEnemyHit);
            --enemy;
            if (enemy.getNumOfAliveShipPts() == 0) {
                std::cout << "You have won the game! Congratulations!" << std::endl;
                interf.printInterface();
                isUndecided = false;
                break;
            }
            wasEnemyHit = userShoot(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &interf, &user, &enemy);
            interf.printInterface();
        }
        if(!isUndecided) break;

        //3 is number of shots the enemy takes
        for(int i = 0; i < 3; i++) {
            int wasUserHit = enemyShoot(userShips1, userShips2, userShips3, userShips4, &interf, &enemy, &user);
            if(wasUserHit) {
                //user.setNumOfAliveShipPts(user.getNumOfAliveShipPts() - wasUserHit);
                --user;
                   std::cout << "ALIVE PTS: " << user.getNumOfAliveShipPts() << std::endl;
                    if(user.getNumOfAliveShipPts() == 0) {
                        std::cout << "Enemy has destroyed all your ships and won the game! You lost!" << std::endl;
                        isUndecided = false;
                        break;
                    }
            }
        }

        interf.printInterface();
    }

    deallocateEnemyShipsMemory(&enemy, userShips1, userShips2, userShips3, userShips4);
    deallocateUserShipsMemory(&user, userShips1, userShips2, userShips3, userShips4);

    return 0;
}