#include "../../../src/Debug.h"

#include <iostream>

void Debug::Info(char* str){
    std::cout << str << "\n";
}

void Debug::Info(const char* str){
    std::cout << str << "\n";
}



void Debug::Error(char* str){
    std::cout << str << "\n";
}

void Debug::Error(const char* str){
    std::cout << str << "\n";
}