#include "board.h"
#include "link.h"
#include "player.h"

Board::Board(int size) : boardSize{size}, grid{size, std::vector<Cell>(size)} {}

bool Board::isValidPosition(const Position &pos) const
{
    return pos.row >= 0 && pos.row < boardSize && pos.col >= 0 && pos.col < boardSize;
}

Position Board::findLinkPosition(Link &link) const
{
    for (int r = 0; r < boardSize; ++r)
    {
        for (int c = 0; c < boardSize; ++c)
        {
            if (grid[r][c].getLink() == &link)
            {
                return Position{r, c};
            }
        }
    }
    return Position{-1, -1}; // return (-1, -1) if not found
}

void Board::placeLink(Link &link, const Position &pos)
{
    if (!isValidPosition(pos))
        throw std::out_of_range("Cannot place link, invalid position.");
    grid[pos.row][pos.col].setLink(link);
}

void Board::removeLink(const Position &pos)
{
    if (!isValidPosition(pos))
        throw std::out_of_range("Cannot remove link, invalid position.");
    grid[pos.row][pos.col].removeLink();
}

void Board::moveLink(Link &link, const Position &to)
{
    if (!isValidPosition(to))
    {
        throw std::out_of_range("Invalid destination");
    }

    Position from = findLinkPosition(link);
    if (from == Position{-1, -1}) // Link not found
    {
        throw std::invalid_argument("Link not found on board");
    }
    removeLink(from);
    placeLink(link, to);
}

Link &Board::getLinkAt(const Position &pos) const
{
    if (!isValidPosition(pos))
        throw std::out_of_range("Cannot get link, invalid position");
    return grid[pos.row][pos.col].getLink();
}

void Board::setCellType(const Position &pos, CellType type, Player *owner)
{
    if (!isValidPosition(pos))
        return;
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