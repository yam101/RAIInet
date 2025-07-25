#include "textinputhandler.h"
#include <sstream>
#include <unordered_map>
#include <iostream>

// helper - allow user to use any case
static std::string toLower(const std::string &s)
{
    std::string result;
    result.reserve(s.size());
    for (char c : s)
        result += std::tolower(c);
    return result;
}

static const std::unordered_map<std::string, CommandType> commandMap = {
    {"move", CommandType::Move},
    {"abilities", CommandType::Abilities},
    {"ability", CommandType::Ability},
    {"board", CommandType::Board},
    {"sequence", CommandType::Sequence},
    {"quit", CommandType::Quit},
    {"end-of-file", CommandType::Quit}};

TextInputHandler::TextInputHandler(std::istream &in) : in(in) {}

Command TextInputHandler::parseInput()
{
    std::string line;

    while (true)
    {
        if (!std::getline(in, line))
        {
            // eof so quit
            return Command(CommandType::Quit, {});
        }

        std::istringstream iss(line);
        std::string curWord;

        if (!(iss >> curWord))
        {
            throw std::invalid_argument("No command given");
        }

        auto it = commandMap.find(toLower(curWord));
        if (it == commandMap.end())
        {
            throw std::invalid_argument("Unknown command: " + curWord);
        }

        CommandType type = it->second;

        std::vector<std::string> params;
        std::string token;
        while (iss >> token)
        {
            params.push_back(token);
        }

        return Command(type, std::move(params)); // success: return parsed command
    }
}
