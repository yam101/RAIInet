#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"
#include <iostream>

class TextDisplay : public View
{
    std::ostream &out;

    void printDownloads(const PlayerState &player) const;
    void printLinks(const GameState &state, int ownerIndex) const;
    void printPlayer(const GameState &state, int playerIndex) const;
    char linkTypeString(LinkType type) const;

public:
    static std::string boardStateString(const std::vector<std::vector<char>> &state);
    explicit TextDisplay(std::ostream &out);

protected:
    void display(const GameState &state) override;
};

#endif
