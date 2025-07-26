#pragma once

#include "view.h"
#include "window.h"
#include "../controller/gameState.h"

class GraphicDisplay : public View {
    Xwindow window;
    const int boardHeight;

    static constexpr int cellSize = 40;
    static constexpr int padding = 20;
    static constexpr int playerInfoHeight = 20;
    static constexpr int linksHeight = 40;

    void drawBoard(const std::vector<std::vector<char>> &board, const std::map<char, LinkState> linkStates, int currentPlayer, int yOffset);
    void drawLinks(const GameState &state, int ownerIndex, int yOffset);
    void drawPlayerInfo(const PlayerState &player, int playerIndex, int yOffset);

protected:
    void display(const GameState &state) override;

public:
    GraphicDisplay(int boardSize = 8);
    ~GraphicDisplay() override = default;
};
