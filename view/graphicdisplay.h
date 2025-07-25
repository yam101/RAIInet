#pragma once

#include "view.h"
#include "window.h"
#include "../controller/gameState.h"

class GraphicDisplay : public View {
    Xwindow window;

    static constexpr int cellSize = 40;
    static constexpr int padding = 10;
    static constexpr int textYOffset = 30;

    void drawBoard(const std::vector<std::vector<char>> &board);
    void drawLinks(const GameState &state, int ownerIndex, int yOffset);
    void drawPlayerInfo(const PlayerState &player, int playerIndex, int yOffset);

protected:
    void display(const GameState &state) override;

public:
    GraphicDisplay();
    ~GraphicDisplay() override = default;
};
