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

    int numOfShots = 0;
    std::string shotSquares[100];

public:

    User(int numOfShips1, int numOfShips2, int numOfShips3, int numOfShips4, int numOfAliveShipPts);

    /**
     * this function sets the number of alive user ships to num
     * @param num number of alive user ships
     */
    void setNumOfAliveShipPts(int num);

    /**
     * this  function returns number of alive user ships
     * @return number of alive user ships
     */
    int getNumOfAliveShipPts();

    /**
     *  this function sets the number of user ships of length 1
     * @param num number of ships of length 1
     */
    void setNumOfShips1(int num);

    /**
     *  this function sets the number of user ships of length 2
     * @param num number of ships of length 2
     */
    void setNumOfShips2(int num);

    /**
     *  this function sets the number of user ships of length 3
     * @param num number of ships of length 3
     */
    void setNumOfShips3(int num);

    /**
     *  this function sets the number of user ships of length 4
     * @param num number of ships of length 4
     */
    void setNumOfShips4(int num);

    /**
     * this function returns the number of user ships of length 1
     * @return number of user ships of length 1
     */
    int getNumOfShips1();

    /**
     * this function returns the number of user ships of length 2
     * @return number of user ships of length 2
     */
    int getNumOfShips2();

    /**
     * this function returns the number of user ships of length 3
     * @return number of user ships of length 3
     */
    int getNumOfShips3();

    /**
     * this function returns the number of user ships of length 4
     * @return number of user ships of length 4
     */
    int getNumOfShips4();

    /**
     * this function sets the number of user shots to num
     * @param num number of user shots
     */
    void setNumOfShots(int num);

    /**
     * this function returns the number of user shots
     * @return number of user shots
     */
    int getNumOfShots();

    /**
     * this function saves a newly shot square as an already shot square
     * @param numberOfShots number of user shots, used as and index
     * @param newSquare newly shot square
     */
    void setShotSquare(int numberOfShots, std::string newSquare);

    /**
     * this function returns the value of the array with already shot squares at index numberOfShots
     * @param numberOfShots number of user shots, used as an index
     * @return the value of the array with already shot squares at index numberOfShots
     */
    std::string getShotSquare(int numberOfShots);

    /**
     * decrements the number of alive user ship parts
     */
    void operator--();

};

#endif //BATTLESHIPS_USER_H
