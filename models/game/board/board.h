#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "position.h"
#include "cell.h"
#include "link.h"
#include "player.h"
#include "firewall.h"

class Link;
class Player;

class Board
{
    int boardSize;
    std::vector<std::vector<Cell>> grid;

public:
    Board(int size = 8); // default to 8x8

    void placeLink(Link &link, const Position &pos);
    void removeLink(const Position &pos);
    void moveLink(Link &link, const Position &to);

    // helper function to find the position of a link using the label
    Position findLinkPosition(Link &link) const;
    // helper function to check if a position is valid
    bool isValidPosition(const Position &pos) const;

    Link &getLinkAt(const Position &pos) const;

    void placeFireWall(const Position &pos, Player &owner);
    Cell &at(const Position &pos);
    const Cell &at(const Position &pos) const;

    std::string printBoard() const;
};

#endif
