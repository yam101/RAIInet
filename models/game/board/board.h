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

    // helper function to check if a position is valid
    bool isValidPosition(const Position &pos) const;

    // helper function to find the position of a link using the label
    Position findLinkPosition(Link &link) const;

public:
    Board(int size = 8); // default to 8x8

    void placeLink(Link &link, const Position &pos);
    void removeLink(const Position &pos);
    void moveLink(Link &link, const Position &to);

    Link &getLinkAt(const Position &pos) const;

    // void setCellType(const Position &pos, CellType type, Player *owner = nullptr);
    void placeFireWall(const Position &pos, Player &owner)
        Cell &at(const Position &pos);
    const Cell &at(const Position &pos) const;

    std::string printBoard() const;
};

#endif
