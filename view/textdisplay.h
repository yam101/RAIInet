#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include "view.h"
#include <iostream>

class TextDisplay : public View
{
    std::ostream &out;

    void printDownloads(const Player &player) const;
    void printLinks(const Player &player, bool isCurrentPlayer) const;
    void printPlayer(const Player &player, bool isCurrentPlayer) const;
    char linkTypeString(LinkType type) const;

public:
    explicit TextDisplay(std::ostream &out);

protected:
    void display(const std::vector<Player> &players, const Board &board, int currentPlayer) const override;
};

#endif
