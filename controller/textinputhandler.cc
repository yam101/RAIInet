#include "textinputhandler.h"
#include <sstream>
#include <iostream>

// helper - allow user to use any case
static std::string toLower(const std::string &s)
{
    std::string result;
    result.reserve(s.size()); // allocate space
    for (char c : s)
        result += std::tolower(c);
    return result;
}

// store reference to input stream
TextInputHandler::TextInputHandler(std::istream& stream) : in(stream) {}

Command TextInputHandler::parseInput()
{
    std::string line;

    while (true)
    {
        if (!std::getline(in, line))
        {
            if (in.eof()) {
                return Command(CommandType::Quit, {});
            } else {
                throw std::runtime_error("Stream error occurred");
            }
        }

        std::istringstream iss(line);
        std::string curWord;

        // extract first word as command
        if (!(iss >> curWord))
        {
            throw std::invalid_argument("No command given");
        }

        const auto& commandMap = getCommandMap(); // use virtual method
        auto it = commandMap.find(toLower(curWord));
        if (it == commandMap.end())
        {
            throw std::invalid_argument("Unknown command: " + curWord);
        }

        CommandType type = it->second;

        // extract remaining words as parameters
        std::vector<std::string> params;
        std::string token;
        while (iss >> token)
        {
            params.push_back(token);
        }

        return Command(type, std::move(params)); // success: return parsed command
    }
}
