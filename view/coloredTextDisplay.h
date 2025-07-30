#ifndef COLORED_TEXT_DISPLAY_H
#define COLORED_TEXT_DISPLAY_H

#include "textdisplay.h"

class ColoredTextDisplay : public TextDisplay
{
    // style constants for cli - these apply colors
    static constexpr const char *BASE_COLOUR = "\033[36m";
    static constexpr const char *RESET = "\033[0m";
    static constexpr const char *RED = "\033[31m";
    static constexpr const char *BLUE = "\033[38;5;33m";
    static constexpr const char *ORANGE = "\033[33m";
    static constexpr const char *YELLOW = "\033[33m";
    static constexpr const char *GREEN = "\033[32m";
    static constexpr const char *GRAY = "\033[90m";
    static constexpr const char *REVERSE = "\033[1;7;96m";
    static constexpr const char *UNREVERSE = "\033[22;27;36m";

public:
    explicit ColoredTextDisplay(std::ostream &stream);

protected:
    // override formatting methods to apply colors
    std::string formatBaseText(const std::string& text) const override;
    std::string formatServerPort(const std::string& text) const override;
    std::string formatFirewall(const std::string& text) const override;
    std::string formatRevealedData(const std::string& text) const override;
    std::string formatRevealedVirus(const std::string& text) const override;
    std::string formatCurrentPlayerHeader(const std::string& text) const override;
    std::string formatWinMessage(const std::string& text) const override;
    std::string formatReset() const override;
};

#endif