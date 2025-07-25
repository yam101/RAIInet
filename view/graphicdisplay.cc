#include "graphicdisplay.h"
#include <sstream>

GraphicDisplay::GraphicDisplay() : window(500, 500) {}

void GraphicDisplay::drawBoard(const std::vector<std::vector<char>> &board)
{
    int yStart = 150;
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            char c = board[row][col];
            int x = padding + col * cellSize;
            int y = yStart + row * cellSize;

            // Fill cell background (optional)
            window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);

            // Draw symbol
            std::string str(1, c);
            window.drawString(x + cellSize / 4, y + cellSize / 2, str);
        }
    }
}

void GraphicDisplay::drawLinks(const GameState &state, int ownerIndex, int yOffset)
{
    int printedCount = 0;
    for (const auto &pair : state.linkStates)
    {
        const LinkState &link = pair.second;
        if (link.ownerIndex != ownerIndex)
            continue;

        std::stringstream ss;
        ss << link.label << ": ";
        if (link.isRevealed)
        {
            ss << (link.type == LinkType::Data ? 'D' : 'V') << link.strength;
        }
        else
        {
            ss << "?";
        }

        int x = padding + (printedCount % 4) * 100;
        int y = yOffset + (printedCount / 4) * 20;

        window.drawString(x, y, ss.str());
        printedCount++;
    }
}

void GraphicDisplay::drawPlayerInfo(const PlayerState &player, int playerIndex, int yOffset)
{
    std::stringstream ss;
    ss << "Player " << playerIndex + 1 << " Downloads: "
       << player.dataDownloads << "D, "
       << player.virusDownloads << "V";

    window.drawString(padding, yOffset, ss.str());

    std::stringstream as;
    as << "Abilities: " << player.abilityCount;
    window.drawString(padding, yOffset + 20, as.str());
}

void GraphicDisplay::display(const GameState &state)
{
    window.fillRectangle(0, 0, window.getWidth(), window.getHeight(), Xwindow::White);

    drawPlayerInfo(state.players[0], 0, 10);
    drawLinks(state, 0, 40);

    drawBoard(state.boardState);

    drawPlayerInfo(state.players[1], 1, 360);
    drawLinks(state, 1, 390);
}
