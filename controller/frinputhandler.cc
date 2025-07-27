#include "frinputhandler.h"

static const std::unordered_map<std::string, CommandType> frenchCommandMap = {
    {"bouger", CommandType::Move},
    {"capacites", CommandType::Abilities},
    {"capacite", CommandType::Ability},
    {"plateau", CommandType::Board},
    {"sequence", CommandType::Sequence},
    {"quitter", CommandType::Quit}};

FrInputHandler::FrInputHandler(std::istream& stream) : TextInputHandler(stream) {}

const std::unordered_map<std::string, CommandType>& FrInputHandler::getCommandMap() const
{
    return frenchCommandMap;
} 