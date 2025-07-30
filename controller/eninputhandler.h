#ifndef EN_INPUT_HANDLER_H
#define EN_INPUT_HANDLER_H

#include "textinputhandler.h"

// concrete implementation english command mapping
class EnInputHandler : public TextInputHandler {
public:
    explicit EnInputHandler(std::istream& stream);

protected:
    const std::unordered_map<std::string, CommandType>& getCommandMap() const override;
};

#endif 