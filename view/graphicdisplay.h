#ifndef GRAPHICDISPLAY_H
#define GRAPHICDISPLAY_H

#include "view.h"
#include "window.h"
#include <memory>

class GraphicDisplay : public View {
    std::unique_ptr<Xwindow> window;
    static const int cellSize = 50;
    static constexpr int margin = 30;
    static constexpr int infoHeight = 120;

    void drawBoard(const std::vector<std::vector<char>> &boardState) const;
    void drawPlayerInfo(const std::vector<PlayerState> &players, int currentPlayer, int boardSize) const;
    void drawCell(int row, int col, char content, int color, int boardSize) const;
public:
    GraphicDisplay();
    ~GraphicDisplay() override = default;
protected:
    void display(const GameState &state) override;
};

#endif
