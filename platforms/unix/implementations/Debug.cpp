#include "../../src/Debug.h"
#include "Arduino.h"

#include <iostream>

void Debug::Info(char* str){
    std::cout << str;
}

void Debug::Info(const char* str){
    std::cout << str;
}



void Debug::Error(char* str){
    std::cout << str;
}

void Debug::Error(const char* str){
    std::cout << str;
}