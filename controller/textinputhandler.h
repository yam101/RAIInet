#ifndef TEXT_INPUT_HANDLER_H
#define TEXT_INPUT_HANDLER_H

#include <istream>
#include <fstream>
#include "inputhandler.h"
#include "command.h"

class TextInputHandler : public InputHandler {
    std::istream& in; // reference, no ownership

public:
    virtual ~TextInputHandler() = default;
    explicit TextInputHandler(std::istream& stream);

protected:
    Command parseInput() override; // override pure virtual function
};

#endif
