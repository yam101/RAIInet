#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "command.h"

class InputHandler {
    void validateParamNumber(const Command& cmd); //check # parameters matches command type

    public:
        // NVI idiom - public interface
        Command getNextCommand();
        
        virtual ~InputHandler() = default; // must define a virtual destructor
    
    protected:
        // NVI ideom - custom business logic
        // parses whatever input format (input stream, gui, etc.) into Command object
        virtual Command parseInput() = 0;
    };    

#endif
