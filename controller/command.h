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
    CommandType type;
    std::vector<std::string> params;

    Command(CommandType type, std::vector<std::string> params) : type(type),
                                                                 params(std::move(params))

    // avoid copying of vector
    {
    }
};

#endif
