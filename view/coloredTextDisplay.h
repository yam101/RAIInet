#ifndef COLORED_TEXT_DISPLAY_H
#define COLORED_TEXT_DISPLAY_H

#include "textdisplay.h"

class ColoredTextDisplay : public TextDisplay
{
    // style constants for cli
    static constexpr const char *BASE_COLOUR = "\033[36m";
    static constexpr const char *RESET = "\033[0m";
    static constexpr const char *RED = "\033[31m";
    static constexpr const char *BLUE = "\033[38;5;33m";
    static constexpr const char *ORANGE = "\033[33m";
    static constexpr const char *GREEN = "\033[32m";
    static constexpr const char *GRAY = "\033[90m";
    static constexpr const char *REVERSE = "\033[1;7;96m";    
    static constexpr const char *UNREVERSE = "\033[22;27;36m";
public:
    explicit ColoredTextDisplay(std::ostream& stream);
protected:
    void display(const GameState &state) override;
    std::string boardStateString(const std::vector<std::vector<char>> &state,
                                 const std::map<char, LinkState> &linkStates,
                                 int currentPlayer) const;
};

#endif