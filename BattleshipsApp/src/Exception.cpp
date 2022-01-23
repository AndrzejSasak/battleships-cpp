#include "../include/Exception.h"

Exception::Exception(std::string msg) : msg(msg), errorCode(errorCode) {}

Exception::Exception(std::string msg, short errorCode) : msg(msg), errorCode(errorCode) {}



