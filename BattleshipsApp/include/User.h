//
// Created by endriu on 08.01.2022.
//

#ifndef BATTLESHIPS_USER_H
#define BATTLESHIPS_USER_H
#include <iostream>

class User {
private:
    int numOfAliveShipPts;
    int numOfShips1;
    int numOfShips2;
    int numOfShips3;
    int numOfShips4;

    int numOfShots;
    std::string shotSquares[100];

public:

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

    void operator--();

};

#endif //BATTLESHIPS_USER_H
