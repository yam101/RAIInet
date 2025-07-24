#include "inputhandler.h"
#include <iostream>

Command InputHandler::getNextCommand() {
    try{
        Command cmd = parseInput();
        validateParamNumber(cmd);
        return cmd;
    } catch (const std::exception& e) {
        // assume a user error/typo--skip and try next line
        std::cerr << "Skipped invalid input. " << e.what() << "\n";
    }
}

void InputHandler::validateParamNumber(const Command& cmd) {
    switch (cmd.type) {
        case CommandType::Move:
            if (cmd.params.size() != 2)
                throw std::invalid_argument("Move command requires 2 parameters.");
            break;
        case CommandType::Ability:
            if (cmd.params.size() < 1 || cmd.params.size() > 3)
                throw std::invalid_argument("Ability command requires 1-3 parameters.");
            break;
        case CommandType::Abilities:
            if (!cmd.params.empty())
                throw std::invalid_argument("Abilities command takes no parameters.");
            break;
        case CommandType::Board:
            if (!cmd.params.empty())
                throw std::invalid_argument("Board command takes no parameters.");
            break;
        case CommandType::Quit:
            if (!cmd.params.empty())
                throw std::invalid_argument("Quit command takes no parameters.");
            break;
        case CommandType::Sequence:
            if (cmd.params.size() != 1)
                throw std::invalid_argument("Sequence command requires 1 parameter.");
    }
}
