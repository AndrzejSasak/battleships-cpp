//
// Created by endriu on 17.01.2022.
//

#include "../include/Exception.h"

Exception::Exception(std::string msg) : msg(msg), errorCode(errorCode) {}

Exception::Exception(std::string msg, short errorCode) : msg(msg), errorCode(errorCode) {}


//Exception::Exception(std::string msg, Exception::errorCodes) : msg(msg), errorCode {}

//Exception::Exception(std::string msg, short errorCode) : msg(msg), errorCode(errorCode) {}



