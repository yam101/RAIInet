#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "position.h"
#include "cell.h"

class Link;
class Player;

class Board
{
    int boardSize;
    std::vector<std::vector<Cell>> grid;

public:
    Board(int size = 8); // default to 8x8

    void placeLink(Link *link, const Position &pos);
    void removeLink(const Position &pos);
    void moveLink(const Position &from, const Position &to);

    Link *getLinkAt(const Position &pos) const;

    void setCellType(const Position &pos, CellType type, Player *owner = nullptr);
    Cell &at(const Position &pos);
    const Cell &at(const Position &pos) const;

    std::string printBoard() const;
};

#endif
