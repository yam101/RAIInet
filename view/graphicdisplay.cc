#include "graphicdisplay.h"
#include <sstream>

GraphicDisplay::GraphicDisplay() : window{nullptr} {}

void GraphicDisplay::drawCell(int row, int col, char content, int color, int boardSize) const {
    int x = margin + col * cellSize;
    int y = margin + row * cellSize;
    window->fillRectangle(x, y, cellSize, cellSize, color);
    std::string s(1, content);
    window->drawString(x + cellSize/2 - 8, y + cellSize/2 + 5, s);
}

void GraphicDisplay::drawBoard(const std::vector<std::vector<char>> &boardState) const {
    int boardSize = boardState.size();
    for (int r = 0; r < boardSize; ++r) {
        for (int c = 0; c < boardSize; ++c) {
            char content = boardState[r][c];
            int color = Xwindow::White;
            // You can add more color logic here if you encode more info in boardState
            drawCell(r, c, content, color, boardSize);
        }
    }
}

void GraphicDisplay::drawPlayerInfo(const std::vector<PlayerState> &players, int currentPlayer, int boardSize) const {
    int y = boardSize * cellSize + margin + 20;
    for (int p = 0; p < 2; ++p) {
        const PlayerState &player = players[p];
        std::ostringstream oss;
        oss << "Player " << (p+1) << ": ";
        oss << player.dataDownloads << "D, ";
        oss << player.virusDownloads << "V  ";
        oss << "Abilities: " << player.abilityCount << "  ";
        oss << "Links: ";
        int count = 0;
        for (const auto &link : player.links) {
            oss << link.label << ":" << (link.type == LinkType::Data ? 'D' : 'V') << link.strength << " ";
            if (++count % 4 == 0) oss << "  ";
        }
        window->drawString(margin, y + p*30, oss.str());
    }
}

void GraphicDisplay::display(const GameState &state) {
    int boardSize = state.boardState.size();
    if (!window) {
        window = std::make_unique<Xwindow>(
            boardSize * cellSize + 2 * margin,
            boardSize * cellSize + infoHeight + 2 * margin
        );
    }
    // Clear window
    window->fillRectangle(0, 0, window->getWidth(), window->getHeight(), Xwindow::White);
    drawBoard(state.boardState);
    drawPlayerInfo(state.players, state.currentPlayer, boardSize);
} 