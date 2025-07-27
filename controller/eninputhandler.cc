#include "eninputhandler.h"

static const std::unordered_map<std::string, CommandType> englishCommandMap = {
    {"move", CommandType::Move},
    {"abilities", CommandType::Abilities},
    {"ability", CommandType::Ability},
    {"board", CommandType::Board},
    {"sequence", CommandType::Sequence},
    {"quit", CommandType::Quit}};

EnInputHandler::EnInputHandler(std::istream& stream) : TextInputHandler(stream) {}

const std::unordered_map<std::string, CommandType>& EnInputHandler::getCommandMap() const
{
    return englishCommandMap;
} 