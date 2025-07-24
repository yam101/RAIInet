#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "commandtype.h"

using namespace std;

struct Command {
    CommandType type; 
    vector<string> params; 

    Command(CommandType type, vector<string> params): 
        type(type), 
        params(move(params)) // avoid copying of vector
        {}
};

#endif
