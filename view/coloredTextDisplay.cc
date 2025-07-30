#include "coloredTextDisplay.h"
#include <sstream>

ColoredTextDisplay::ColoredTextDisplay(std::ostream &stream) : TextDisplay(stream) {}


// implement fomatting methods to apply colors


std::string ColoredTextDisplay::formatBaseText(const std::string& text) const
{
    return BASE_COLOUR + text;
}

std::string ColoredTextDisplay::formatServerPort(const std::string& text) const
{
    return BLUE + text + BASE_COLOUR;
}

std::string ColoredTextDisplay::formatFirewall(const std::string& text) const
{
    return ORANGE + text + BASE_COLOUR;
}

std::string ColoredTextDisplay::formatRevealedData(const std::string& text) const
{
    return GREEN + text + BASE_COLOUR;
}

std::string ColoredTextDisplay::formatRevealedVirus(const std::string& text) const
{
    return RED + text + BASE_COLOUR;
}

std::string ColoredTextDisplay::formatCurrentPlayerHeader(const std::string& text) const
{
    return REVERSE + text + UNREVERSE;
}

std::string ColoredTextDisplay::formatWinMessage(const std::string& text) const
{
    return YELLOW + text;
}

std::string ColoredTextDisplay::formatReset() const
{
    return RESET;
}