#include "textdisplay.h"

TextDisplay::TextDisplay(std::ostream &out) : out{out} {}

char TextDisplay::linkTypeString(LinkType type)
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

void TextDisplay::printDownloads(const Player &player) const
{
    out << "Downloaded: ";

    int i = 0;
    int size = player.numDownloads.size();

    for (const auto &[type, num] : player.numDownloads)
    {
        out << num << linkTypeString(type);

        if (++i < size) // no trailing comma
            out << ", ";
    }
}

void TextDisplay::printLinks(const Player &player, bool isCurrentPlayer) const
{
    int printedCount = 0;
    for (const auto &[label, linkPtr] : player.getLinks())
    {
        out << label << ": ";
        if (isCurrentPlayer)
        {
            out << linkTypeString(linkPtr->getType()) << linkPtr->getStrength();
        }
        else
        {
            out << "?";
        }

        out << " ";
        printedCount++;
        if (printedCount % 4 == 0) // newline every 4 links
        {
            out << std::endl;
        }
    }
    if (printedCount % 4 != 0) // in case link count is not multiple of 4, print newline anyways
    {
        out << std::endl;
    }
}

void TextDisplay::printPlayer(const Player &player, bool isCurrentPlayer) const
{
    printDownloads(player);
    out << "Abilities: " << player.getAbilityCount() << std::endl;
    printLinks(player, isCurrentPlayer);
}

void TextDisplay::display(const std::vector<Player> &players, const Board &board, int currentPlayer) const
{
    out << "Player 1" << std::endl;
    printPlayer(players[0], currentPlayer == 0);

    out << "========" << std::endl;
    out << board.print();
    out << "========" << std::endl;

    out << "Player 2" << std::endl;
    printPlayer(players[1], currentPlayer == 1);

    out << std::endl;
}
