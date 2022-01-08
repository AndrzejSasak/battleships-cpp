//
// Created by endriu on 15.12.2021.
//

#include "../include/lib.h"

#include <iostream>

int parseSquareInputToIndex(std::string square) {
    int squareIndex = 0;

    switch(square[0]) {
        case 'A': {
            squareIndex = 0 + (unsigned char)square[1] - 48;
        }
            break;
        case 'B': {
            squareIndex = 10 + (unsigned char)square[1] - 48;
        }
            break;
        case 'C': {
            squareIndex = 20 + (unsigned char)square[1] - 48;
        }
            break;
        case 'D': {
            squareIndex = 30 + (unsigned char)square[1] - 48;
        }
            break;
        case 'E': {
            squareIndex = 40 + (unsigned char)square[1] - 48;
        }
            break;
        case 'F': {
            squareIndex = 50 + (unsigned char)square[1] - 48;
        }
            break;
        case 'G': {
            squareIndex = 60 + (unsigned char)square[1] - 48;
        }
            break;
        case 'H': {
            squareIndex = 70 + (unsigned char)square[1] - 48;
        }
            break;
        case 'I': {
            squareIndex = 80 + (unsigned char) square[1] - 48;
        }
            break;
        case 'J': {
            squareIndex = 90 + (unsigned char)square[1] - 48;
        }
            break;
        default: {
            std::cout << "\nWRONG INPUT\n" << std::endl;
        }
    }
    return squareIndex;
}