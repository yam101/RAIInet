#ifndef FR_INPUT_HANDLER_H
#define FR_INPUT_HANDLER_H

#include "textinputhandler.h"

// concrete implementation french command mapping
class FrInputHandler : public TextInputHandler {
public:
    explicit FrInputHandler(std::istream& stream);

protected:
    const std::unordered_map<std::string, CommandType>& getCommandMap() const override;
};

#endif 