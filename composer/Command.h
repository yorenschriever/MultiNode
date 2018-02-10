#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <string>
#include "../src/Value.h"

struct Command {   ;
    char* name; 
    std::map<std::string, Value> params;
};

#endif