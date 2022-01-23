#ifndef JIPP2_INTERFACE_H
#define JIPP2_INTERFACE_H

#include <iostream>

class Interface {
private:
    std::string userArea[100];
    std::string enemyArea[100];
public:
    Interface();

    /**
     * this function prints the interface
     */
    void printInterface();

    /**
     * this function checks if a square at surroundingSquareIndex is a taken square and sets
     * the square at squareIndex if the square surroundings are not taken
     * @param squareIndex index of the square to be chosen
     * @param surroundingSquareIndex index of the square next to the square at index squareIndex
     */
    void checkSurroundings(int squareIndex, int surroundingSquareIndex);

    /**
     * this function sets the square newSquare as taken by a user ship
     * @param newSquare square to be taken
     */
    void setTakenByUserShip(std::string newSquare);

    /**
     * this function sets the square newSquare as taken by an enemy ship
     * @param newSquare square to be taken
     */
    void setTakenByEnemyShip(std::string newSquare);

    /**
     * this function sets the square newSquare as a destroyed part of a user ship
     * @param newSquare square to be a destroyed part
     */
    void setDestroyedUserShipPart(std::string newSquare);

    /**
     * this function sets the square newSquare as a destroyed part of an enemy ship
     * @param newSquare square to be a destroyed part
     */
    void setDestroyedEnemyShipPart(std::string newSquare);

    /**
     * this function checks if the square newSquare is taken by a ship or its surroundings
     * @param newSquare square to be checked if taken
     * @return true if square is already taken, false if square is not taken
     */
    bool isTakenByShip(std::string newSquare);

    /**
     * this function sets the square newSquare as already shot user square
     * @param newSquare square to be set as already shot
     */
    void setAlreadyShotUserSquare(std::string newSquare);

    /**
     * this function sets the square as already shot enemy square
     * @param newSquare square to be set as already shot
     */
    void setAlreadyShotEnemySquare(std::string newSquare);

    /**
     * this function sets the square newSquare as a destroyed whole user ship
     * @param newSquare square to be set as a destroyed whole
     */
    void setDestroyedUserShipWhole(std::string newSquare);

    /**
     * this function sets the square newSquare as a destroyed whole enemy ship
     * @param newSquare square to be set as a destroyed whole
     */
    void setDestroyedEnemyShipWhole(std::string newSquare);

    /**
     * this functions picks colors of the user based area on types of squares
     * @param hConsole object used for manipulating colors
     * @param i index
     */
    void pickUserAreaColors(void *hConsole, int i);

    /**
     * this functions picks colors of the enemy area based on types of squares
     * @param hConsole object used for manipulating colors
     * @param i index
     */
    void pickEnemyAreaColors(void *hConsole, int i);
};

#endif //JIPP2_INTERFACE_H
