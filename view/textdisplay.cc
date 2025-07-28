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
    out << "Downloaded: ";
    out << player.dataDownloads << "D, ";
    out << player.virusDownloads << "V ";
    out << std::endl;
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

        out << link.label << ": ";
        if (viewerIndex != ownerIndex && !link.isRevealed)
            out << " ?";
        else
        {
            out << std::string(1, linkTypeString(link.type)) << link.strength;
        }
        out << " ";
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
    out << "Abilities: " << player.abilityCount << std::endl;
    printLinks(state, playerIndex, viewerIndex);
}

std::string TextDisplay::boardStateString(const std::vector<std::vector<char>> &state)
{
    std::ostringstream oss;

    for (const auto &row : state)
    {
        for (char c : row)
        {
            oss << c;
        }
        oss << '\n';
    }

    return oss.str();
}

void TextDisplay::display(const GameState &state)
{
    out << "Player 1" << std::endl;
    printPlayer(state, 0);

    out << "========" << std::endl;
    out << boardStateString(state.boardState);
    out << "========" << std::endl;

    out << "Player 2" << std::endl;
    printPlayer(state, 1);

    out << std::endl;
}

void TextDisplay::displayWin(const WinState &state)
{
    out << "Player " << (state.winnerId + 1) << " wins!" << std::endl;
    for (int loserId : state.loserIds)
    {
        out << "Player " << (loserId + 1) << " lost" << std::endl;
    }
}
