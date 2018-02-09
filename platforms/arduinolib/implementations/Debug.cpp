#include "../../../src/Debug.h"
#include "Arduino.h"

/*void Debug::Info(unsigned char* str){
    Serial.println((const char*) str);
}*/

void Debug::Info(char* str){
    Serial.println((const char*) str);
}

void Debug::Info(const char* str){
    Serial.println((const char*) str);
}



void Debug::Error(char* str){
    Serial.println(str);
}

void Debug::Error(const char* str){
    Serial.println(str);
}