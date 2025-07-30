#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "../../position.h"
#include "cell.h"
#include "../link/link.h"
#include "../../player/player.h"
#include "firewall.h"

class Board
{
    int boardSize; 
    std::vector<std::vector<Cell>> grid; // 2D grid of cells

public:
    Board(int size = 8); // default to 8x8

    // place link at specified position
    void placeLink(Link &link, const Position &pos);
    // remove link from specified position
    void removeLink(const Position &pos);
    // move link to new position
    void moveLink(Link &link, const Position &to);

    // helper function to find the position of a link using the label
    Position findLinkPosition(Link &link) const;
    // helper function to check if a position is valid
    bool isValidPosition(const Position &pos) const;

    Link &getLinkAt(const Position &pos) const;

    void placeFireWall(const Position &pos, Player &owner);
    Cell &at(const Position &pos);
    const Cell &at(const Position &pos) const;

    // return string representation of board
    std::string printBoard() const;
    // get board size
    int getSize() const;
    // get 2D char array representing board state
    std::vector<std::vector<char>> getState() const;
    // initialize board with players and features
    void setup(std::vector<Player> &players);
};

#endif
