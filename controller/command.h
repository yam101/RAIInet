#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

using namespace std;

enum class CommandType
{
    Move,
    Abilities,
    Ability,
    Board,
    Sequence,
    Quit,
};

struct Command
{
    CommandType type;
    vector<string> params;

    Command(CommandType type, vector<string> params) : type(type),
                                                       params(move(params)) // avoid copying of vector
    {
    }
};

#endif
