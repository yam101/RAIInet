#include "textdisplay.h"
#include <sstream>

TextDisplay::TextDisplay(std::ostream &stream) : out(stream) {}

char TextDisplay::linkTypeString(LinkType type) const
{
    switch (type)
    {
    case LinkType::Data:
        return 'D';
    case LinkType::Virus:
        return 'V';
    }
    return '\0';
}

void TextDisplay::printDownloads(const PlayerState &player) const
{
    std::string downloadsStr = "Downloaded: " + std::to_string(player.dataDownloads) + "D, " + std::to_string(player.virusDownloads) + "V ";
    out << formatBaseText(downloadsStr) << std::endl;
}

void TextDisplay::printLinks(const GameState &state, int ownerIndex, int viewerIndex) const
{
    int printedCount = 0;
    for (const auto &pair : state.linkStates)
    {
        const LinkState &link = pair.second;

        // skip links that don't belong to this player
        if (link.ownerIndex != ownerIndex)
            continue;

        out << formatBaseText(std::string(1, link.label) + ": ");
        
        if (viewerIndex != ownerIndex && !link.isRevealed)
        {
            out << formatBaseText(" ?");
        }
        else
        {
            std::string linkInfo = std::string(1, linkTypeString(link.type)) + std::to_string(link.strength);
            // apply specific formatting based on link type
            if (link.type == LinkType::Data)
            {
                out << formatRevealedData(linkInfo);
            }
            else
            {
                out << formatRevealedVirus(linkInfo);
            }
        }
        out << formatBaseText(" ");
        
        printedCount++;
        if (printedCount % 4 == 0)
        {
            out << std::endl;
        }
    }
    if (printedCount % 4 != 0)
    {
        out << std::endl;
    }
}

void TextDisplay::printPlayer(const GameState &state, int playerIndex) const
{
    const PlayerState &player = state.players[playerIndex];
    const int viewerIndex = state.currentPlayer;
    printDownloads(player);
    
    std::string abilitiesStr = "Abilities: " + std::to_string(player.abilityCount);
    out << formatBaseText(abilitiesStr) << std::endl;
    printLinks(state, playerIndex, viewerIndex);
}

std::string TextDisplay::boardStateString(const std::vector<std::vector<char>> &state)
{
    // create temporary instance and delegate to non-static method with empty link data
    TextDisplay temp(std::cout); // stream doesn't matter since we're not writing to it
    std::map<char, LinkState> emptyLinks; // thse are only used for link colors - since we;re not coloring, use an empty map
    return temp.boardStateString(state, emptyLinks, 0);
}

std::string TextDisplay::boardStateString(const std::vector<std::vector<char>> &state,
                                         const std::map<char, LinkState> &linkStates,
                                         int currentPlayer) const
{
    std::ostringstream oss;

    for (const auto &row : state)
    {
        for (char c : row)
        {
            std::string cellStr(1, c);
            
            // check if it's a special cell type
            if (c == 'S')
            {
                oss << formatServerPort(cellStr);
            }
            else if (c == 'm' || c == 'w')
            {
                oss << formatFirewall(cellStr);
            }
            else if (c != '.' && c != 'm' && c != 'w' && c != 'S')
            {
                // might be a link character
                auto it = linkStates.find(c);
                if (it != linkStates.end())
                {
                    const LinkState &link = it->second;

                    // format based on visibility and ownership
                    if (link.ownerIndex == currentPlayer || link.isRevealed)
                    {
                        // revealed or owned - format by type
                        if (link.type == LinkType::Data)
                        {
                            oss << formatRevealedData(cellStr);
                        }
                        else
                        {
                            oss << formatRevealedVirus(cellStr);
                        }
                    }
                    else
                    {
                        // unrevealed opponent link - just base formatting
                        oss << formatBaseText(cellStr);
                    }
                }
                else
                {
                    // fallback for unknown chars
                    oss << formatBaseText(cellStr);
                }
            }
            else
            {
                // regular cells like '.'
                oss << formatBaseText(cellStr);
            }
        }
        oss << '\n';
    }

    return oss.str();
}

void TextDisplay::display(const GameState &state)
{
    // apply base formatting - for colored displays this sets the base color
    out << formatBaseText("");
    
    // show current player header - base class returns empty, colored class shows it
    std::string header = formatCurrentPlayerHeader("  = NOW PLAYING: PLAYER " + std::to_string(state.currentPlayer + 1) + " =  ");
    if (!header.empty()) {
        out << header << "\n\n";
    }

    out << formatBaseText("Player 1") << std::endl;
    printPlayer(state, 0);

    out << formatBaseText("========") << std::endl;
    out << boardStateString(state.boardState, state.linkStates, state.currentPlayer);
    out << formatBaseText("========") << std::endl;

    out << formatBaseText("Player 2") << std::endl;
    printPlayer(state, 1);

    out << formatReset() << std::endl;
}

void TextDisplay::displayWin(const WinState &state)
{
    out << formatWinMessage("Player " + std::to_string(state.winnerId + 1) + " wins!") << formatReset() << std::endl;

    for (int loserId : state.loserIds)
    {
        out << formatBaseText("Player " + std::to_string(loserId + 1) + " lost") << std::endl;
    }
}
