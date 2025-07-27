#ifndef TEXT_INPUT_HANDLER_H
#define TEXT_INPUT_HANDLER_H

#include <istream>
#include <fstream>
#include <unordered_map>
#include "inputhandler.h"
#include "command.h"

class TextInputHandler : public InputHandler {
protected:
    std::istream& in; // reference, no ownership
    
    // pure virtual method for subclasses to provide language-specific command maps
    virtual const std::unordered_map<std::string, CommandType>& getCommandMap() const = 0;

public:
    virtual ~TextInputHandler() = default;
    explicit TextInputHandler(std::istream& stream);

protected:
    Command parseInput() override; // override pure virtual function
};

#endif
