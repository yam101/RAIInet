#include "graphicdisplay.h"
#include <sstream>

GraphicDisplay::GraphicDisplay(int boardSize) 
: window(
    boardSize * cellSize + 2 * padding, 
    boardSize * cellSize + 2 * (playerInfoHeight + linksHeight) + 5 * padding), 
    boardHeight(boardSize * cellSize
    ) {}

void GraphicDisplay::drawBoard(const std::vector<std::vector<char>> &board, const std::map<char, LinkState> linkStates, int currentPlayer, int yOffset)
{
    for (int row = 0; row < board.size(); ++row)
    {
        for (int col = 0; col < board[row].size(); ++col)
        {
            char c = board[row][col];
            std::string str(1, c); //for drawstring
            int x = padding + col * cellSize;
            int y = yOffset + row * cellSize;

            // is a link
            if (c != '.' && c != 'm' && c != 'w' && c != 'S') {

                // search in linkStates for link w matching label char
                const LinkState link = linkStates.find(c)->second;

                if (link.ownerIndex == currentPlayer || link.isRevealed) {
                    window.fillRectangle(x, y, cellSize, cellSize,  (link.type == LinkType::Data ? Xwindow::Green : Xwindow::Red));
                }
                else {
                    window.fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);
                }
                window.drawString(x + cellSize / 4, y + cellSize / 2, str, Xwindow::White);
            } else {
                // white rect for non-link cells
                window.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                window.drawString(x + cellSize / 4, y + cellSize / 2, str);
            }
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
        if (state.currentPlayer == link.ownerIndex || link.isRevealed)
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
    window.processEvents();
    
    window.fillRectangle(0, 0, window.getWidth(), window.getHeight(), Xwindow::White);

    // Player 1 info
    int height = padding;
    drawPlayerInfo(state.players[0], 0, height);
    height += playerInfoHeight + padding;
    drawLinks(state, 0, height);
    height += linksHeight + padding;

    // board
    drawBoard(state.boardState, state.linkStates, state.currentPlayer, height);
    height += boardHeight + padding;
    
    // Player 2 info
    drawPlayerInfo(state.players[1], 1, height);
    height += playerInfoHeight + padding;
    drawLinks(state, 1, height);
    height += linksHeight + padding;
    
    window.flush(); // UGHGGHGH i hate xlib
    window.sync(); 
}
