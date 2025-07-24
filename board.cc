#include "board.h"
#include "link.h"
#include "player.h"

Board::Board(int size) : boardSize{size}, grid{size, std::vector<Cell>(size)} {}

// bool Board::isValidPosition(const Position &pos) const
// {
//     return pos.row >= 0 && pos.row < boardSize && pos.col >= 0 && pos.col < boardSize;
// }

void Board::placeLink(Link *link, const Position &pos)
{
    // if (!isValidPosition(pos))
    //     return;
    grid[pos.row][pos.col].setLink(link);
}

void Board::removeLink(const Position &pos)
{
    // if (!isValidPosition(pos))
    //     return;
    grid[pos.row][pos.col].setLink(nullptr);
}

void Board::moveLink(const Position &from, const Position &to)
{
    // if (!isValidPosition(from) || !isValidPosition(to))
    //     return;
    Link *link = getLinkAt(from);
    if (!link)
        return;

    removeLink(from);
    placeLink(link, to);
}

Link *Board::getLinkAt(const Position &pos) const
{
    // if (!isValidPosition(pos))
    //     return nullptr;
    return grid[pos.row][pos.col].getLink();
}

void Board::setCellType(const Position &pos, CellType type, Player *owner)
{
    // if (!isValidPosition(pos))
    //     return;
    grid[pos.row][pos.col].setType(type, owner);
}

Cell &Board::at(const Position &pos)
{
    return grid[pos.row][pos.col];
}

const Cell &Board::at(const Position &pos) const
{
    return grid[pos.row][pos.col];
}

std::string Board::printBoard() const
{
    std::string output;
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            output += cell.print();
        }
        output += "\n";
    }
    return output;
}