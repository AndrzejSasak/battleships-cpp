//
// Created by endriu on 17.01.2022.
//

#ifndef BATTLESHIPS_EXCEPTION_H
#define BATTLESHIPS_EXCEPTION_H

#include <iostream>
#include <exception>



class Exception : public std::exception {
private:
    std::string msg;
    short errorCode;
    std::string errorTypes[8] = {"", //0
                                 "WRONG_INPUT", //1
                                 "SQUARES_APART", //2
                                 "SQUARE_TAKEN", //3
                                 "SQUARE_DUPLICATE", //4
                                 "OTHER", //5
                                 "ERR_OPENING_FILE", //6
                                 "ERR_CLOSING_FILE" //7
    };
    std::string errorFinalMsg;
public:

    Exception(std::string msg);

    Exception(std::string msg, short errorCode);

    /**
     * this function return the error message
     * @return error message
     */
    const char *what() {
        errorFinalMsg = msg + ": " + errorTypes[errorCode];
        return  errorFinalMsg.c_str();
    }



};


#endif //BATTLESHIPS_EXCEPTION_H
