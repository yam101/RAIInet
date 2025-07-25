#include "board.h"
#include "link.h"
#include "player.h"
#include "firewall.h"

Board::Board(int size) : boardSize{size}, grid{size, std::vector<Cell>(size)} {}

bool Board::isValidPosition(const Position &pos) const
{
    return pos.row >= 0 && pos.row < boardSize && pos.col >= 0 && pos.col < boardSize;
}

Position Board::findLinkPosition(Link &link) const
{
    if(link.isDownloaded())
    {
        throw std::runtime_error("Downloaded link is not on the board.");
    }

    for (int r = 0; r < boardSize; ++r)
    {
        for (int c = 0; c < boardSize; ++c)
        {
            if (&grid[r][c].getLink() == &link)
            {
                return Position{r, c};
            }
        }
    }
    throw std::runtime_error("Link not found on board."); // BIG PROBLEM
}

void Board::placeFireWall(const Position &pos, Player &owner){
    if (!isValidPosition(pos))
        throw std::out_of_range("Cannot place firewall, invalid position.");
    Cell &cell = at(pos);
    cell.setFeature(std::make_unique<Firewall>(owner));
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


Cell &Board::at(const Position &pos)
{
    if (!isValidPosition(pos))
        throw std::out_of_range("Cannot get cell, invalid position");
    return grid[pos.row][pos.col];
}

const Cell &Board::at(const Position &pos) const
{
    if (!isValidPosition(pos))
        throw std::out_of_range("Cannot get cell, invalid position");
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