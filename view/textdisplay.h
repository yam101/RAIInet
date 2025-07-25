#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"
#include <iostream>

class TextDisplay : public View
{
    std::ostream &out;

    void printDownloads(const PlayerState &player) const;
    void printLinks(const GameState &state, int currentPlayer) const;
    void printPlayer(const GameState &state, int currentPlayer) const;
    char linkTypeString(LinkType type) const;

private:
    void printBoardState(const std::vector<std::vector<char>> &state) const;

public:
    explicit TextDisplay(std::ostream &out);

protected:
    void display(const GameState &state) override;
};

#endif
