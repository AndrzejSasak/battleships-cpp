//
// Created by endriu on 08.01.2022.
//

#ifndef BATTLESHIPS_ENEMY_H
#define BATTLESHIPS_ENEMY_H

#include <iostream>

class Enemy {
private:
    int numOfAliveShipPts;
    int numOfShips1;
    int numOfShips2;
    int numOfShips3;
    int numOfShips4;

    int numOfShots;
    std::string shotSquares[100];

    //exclusive for enemy
    bool hasTarget;
    std::string previouslyShotSquare;
public:
    Enemy();

    void setNumOfAliveShipPts(int num);
    int getNumOfAliveShipPts();

    void setNumOfShips1(int num);
    void setNumOfShips2(int num);
    void setNumOfShips3(int num);
    void setNumOfShips4(int num);
    int getNumOfShips1();
    int getNumOfShips2();
    int getNumOfShips3();
    int getNumOfShips4();

    void setNumOfShots(int num);
    int getNumOfShots();

    void setShotSquare(int index, std::string value);
    std::string getShotSquare(int index);

    //exclusive for enemy
    void setHasTarget(bool newHasTarget);
    bool getHasTarget();

    void setPrevShotSquare(std::string newPrev);
    std::string getPrevShotSquare();



};

#endif //BATTLESHIPS_ENEMY_H
