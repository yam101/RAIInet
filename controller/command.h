#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

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
    CommandType type;                // the type of command (eg. Move, Ability, etc.)
    std::vector<std::string> params; // any parameters for the command (eg. link label, direction etc)

    // we avoid copying the vector by using std::move
    Command(CommandType type, std::vector<std::string> params)
        : type(type), params(std::move(params)) {}
};

#endif
