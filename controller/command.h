#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

//all possible game commands (extend this if new commands added)
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
    std::vector<std::string> params; // keep as strings, leave it to controller to decide what params actually mean

    Command(CommandType type, std::vector<std::string> params) : type(type),
                                                                 params(std::move(params)) // invoke move ctor
    {
    }
};

#endif
