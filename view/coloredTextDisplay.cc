#include "coloredTextDisplay.h"
#include <sstream>

ColoredTextDisplay::ColoredTextDisplay(std::ostream& stream) : TextDisplay(stream) {}

void ColoredTextDisplay::display(const GameState &state)
{
    out << BASE_COLOUR; // colour output to differentiate view output from UI in CLI

    out << REVERSE << "  = NOW PLAYING: PLAYER " << (state.currentPlayer + 1) << " =  " << UNREVERSE << std::endl
        << std::endl;

    out << "Player 1" << std::endl;
    printPlayer(state, 0);

    out << "========" << std::endl;
    out << boardStateString(state.boardState, state.linkStates, state.currentPlayer);
    out << "========" << std::endl;

    out << "Player 2" << std::endl;
    printPlayer(state, 1);

    out << RESET << std::endl;  // reset to colour to default at the end
}

std::string ColoredTextDisplay::boardStateString(const std::vector<std::vector<char>> &state,
                                                 const std::map<char, LinkState> &linkStates,
                                                 int currentPlayer) const
{
    std::ostringstream oss;

    for (const auto &row : state)
    {
        for (char c : row)
        {
            // check if it's a link character
            if (c == 'S')
            {
                oss << BLUE << c << BASE_COLOUR;
            }
            else if (c == 'm' || c == 'w')
            {
                oss << ORANGE << c << BASE_COLOUR;
            }
            else if (c != '.' && c != 'm' && c != 'w' && c != 'S')
            {
                auto it = linkStates.find(c);
                if (it != linkStates.end())
                {
                    const LinkState &link = it->second;

                    // color based on visibility and ownership
                    if (link.ownerIndex == currentPlayer || link.isRevealed)
                    {
                        // revealed or owned - color by type
                        if (link.type == LinkType::Data)
                        {
                            oss << GREEN << c << BASE_COLOUR;
                        }
                        else
                        {
                            oss << RED << c << BASE_COLOUR;
                        }
                    }
                    else
                    {
                        // unrevealed opponent link - use base color
                        oss << c;
                    }
                }
                else
                {
                    oss << c; // fallback
                }
            }
            else
            {
                oss << c; // non-link cells
            }
        }
        oss << '\n';
    }

    return oss.str();
}