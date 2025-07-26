#ifndef TEXT_INPUT_HANDLER_H
#define TEXT_INPUT_HANDLER_H

#include <istream>
#include <fstream>
#include "inputhandler.h"
#include "command.h"

class TextInputHandler : public InputHandler {
    std::unique_ptr<std::istream> in;

public:
    virtual ~TextInputHandler() = default;
    TextInputHandler(); // default ctor - uses std::cin
    explicit TextInputHandler(const std::string& filename); // for files

protected:
    Command parseInput() override; // override pure virtual function
};

#endif
