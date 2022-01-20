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

    int numOfShots = 0;
    std::string shotSquares[100];

    int difficulty;

public:
    Enemy(int numOfShips1, int numOfShips2, int numOfShips3, int numOfShips4, int numOfAliveShipPts);

    /**
     * this function sets the difficulty of the enemy to diffValue
     * @param diffValue difficulty of the enemy
     */
    void setDifficulty(int diffValue);

    /**
     * this function returns the difficulty of the enemy
     * @return difficulty of the enemy
     */
    int getDifficulty();

    /**
      * this function sets the number of alive enemy ships to num
      * @param num number of alive enemy ships
      */
    void setNumOfAliveShipPts(int num);

    /**
     * this  function returns number of alive enemy ships
     * @return number of alive enemy ships
     */
    int getNumOfAliveShipPts();

    /**
     *  this function sets the number of enemy ships of length 1
     * @param num number of ships of length 1
     */
    void setNumOfShips1(int num);

    /**
     *  this function sets the number of enemy ships of length 2
     * @param num number of ships of length 2
     */
    void setNumOfShips2(int num);

    /**
     *  this function sets the number of enemy ships of length 3
     * @param num number of ships of length 3
     */
    void setNumOfShips3(int num);

    /**
     *  this function sets the number of enemy ships of length 4
     * @param num number of ships of length 4
     */
    void setNumOfShips4(int num);

    /**
     * this function returns the number of enemy ships of length 1
     * @return number of enemy ships of length 1
     */
    int getNumOfShips1();

    /**
     * this function returns the number of enemy ships of length 2
     * @return number of enemy ships of length 2
     */
    int getNumOfShips2();

    /**
     * this function returns the number of enemy ships of length 3
     * @return number of enemy ships of length 3
     */
    int getNumOfShips3();

    /**
     * this function returns the number of enemy ships of length 4
     * @return number of enemy ships of length 4
     */
    int getNumOfShips4();

    /**
     * this function sets the number of enemy shots to num
     * @param num number of enemy shots
     */
    void setNumOfShots(int num);

    /**
     * this function returns the number of enemy shots
     * @return number of enemy shots
     */
    int getNumOfShots();

    /**
     * this function saves a newly shot square as an already shot square
     * @param numberOfShots number of enemy shots, used as and index
     * @param newSquare newly shot square
     */
    void setShotSquare(int numberOfShots, std::string newSquare);

    /**
     * this function returns the value of the array with already shot squares at index numberOfShots
     * @param numberOfShots number of enemy shots, used as an index
     * @return the value of the array with already shot squares at index numberOfShots
     */
    std::string getShotSquare(int numberOfShots);

    /**
     * decrements the number of alive enemy ship parts
     */
    void operator--();

};

#endif //BATTLESHIPS_ENEMY_H
