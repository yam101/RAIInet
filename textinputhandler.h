#ifndef TEXT_INPUT_HANDLER_H
#define TEXT_INPUT_HANDLER_H

#include <istream>
#include "inputhandler.h"
#include "command.h"

class TextInputHandler : public InputHandler {
    std::istream& in;

public:
    explicit TextInputHandler(std::istream& in);

protected:
    Command parseInput() override; // override pure virtual function
};

#endif
