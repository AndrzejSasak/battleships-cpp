#include <iostream>
#include <ctime>
#include <lib.h>

int main(int argc, char *argv[]) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(nullptr));

    Interface interf;
    Enemy enemy(4, 3, 2, 1, 20);
    User user(4, 3, 2, 1, 20);

    //selecting the user
    std::fstream usersFile("../../BattleshipsApp/users_database/users.txt");
    if (argc == 3) {
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

    //picking difficulty
    bool isError = true;
    while (isError) {
        try {
            pickDifficulty(&enemy);
            isError = false;
        } catch (Exception &e) {
            std::cout << e.what() << std::endl;
            isError = true;
        } catch (...) {
            std::cout << "ERROR HAPPENED!" << std::endl;
            isError = true;
        }
    }

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

    //picking enemy ships
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
    //isError = true;
    while (gameIsUndecided) {
        //user turn
        int wasEnemyHit;
        isError = true;
        while (isError) {
            try {
                wasEnemyHit = userShoot(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &interf, &user, &enemy);
                isError = false;
            } catch (Exception &e) {
                std::cout << e.what() << std::endl;
                std::cout << "SHOOT AGAIN: " << std::endl;
                isError = true;
            } catch (...) {
                std::cout << "SHOOT AGAIN: " << std::endl;
                isError = true;
            }
        }
        while (wasEnemyHit == 1) {
            std::cout << "NUMBER OF YOUR ALIVE SHIPS: "
                      << getNumOfAliveShips(userShips1, userShips2, userShips3, userShips4, &user) << std::endl;
            std::cout << "NUMBER OF ENEMY ALIVE SHIPS: "
                      << getNumOfAliveShips(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &enemy)
                      << std::endl;
            interf.printInterface();
            //decrementing number of enemy's ship parts
            --enemy; //enemy.setNumOfAliveShipPts(enemy.getNumOfAliveShipPts() - wasUserHit);
            if (enemy.getNumOfAliveShipPts() == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                std::cout << "You have won the game! Congratulations!" << std::endl;
                std::cout << "You have won the game! Congratulations!" << std::endl;
                std::cout << "You have won the game! Congratulations!" << std::endl;
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
                interf.printInterface();
                gameIsUndecided = false;
                break;
            }
            isError = true;
            while (isError) {
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
        }
        //end of user's turn
        if (!gameIsUndecided) break;
        //enemy's turn
        for (int i = 0; i < enemy.getDifficulty(); i++) {
            int wasUserHit = enemyShoot(userShips1, userShips2, userShips3, userShips4, &interf, &enemy, &user);
            if (wasUserHit == 1) {
                //decrementing number of user's ship parts;;
                --user;  //user.setNumOfAliveShipPts(user.getNumOfAliveShipPts() - wasUserHit);
                if (user.getNumOfAliveShipPts() == 0) {
                    std::cout << "Enemy has destroyed all your ships and won the game! You lost!" << std::endl;
                    gameIsUndecided = false;
                    break;
                }
            }
        }
        //end of enemy's turn
        std::cout << "NUMBER OF YOUR ALIVE SHIPS: "
                  << getNumOfAliveShips(userShips1, userShips2, userShips3, userShips4, &user) << std::endl;
        std::cout << "NUMBER OF ENEMY ALIVE SHIPS: "
                  << getNumOfAliveShips(enemyShips1, enemyShips2, enemyShips3, enemyShips4, &enemy) << std::endl;
        interf.printInterface();
    }

    deallocateEnemyShipsMemory(&enemy, enemyShips1, enemyShips2, enemyShips3, enemyShips4);
    deallocateUserShipsMemory(&user, userShips1, userShips2, userShips3, userShips4);
    system("pause");
    return 0;
}