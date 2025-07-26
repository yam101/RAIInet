#include "board.h"
#include "serverport.h"

Board::Board(int size) : boardSize{size}
{
    grid.resize(size);
    for (int i = 0; i < size; ++i)
    {
        grid[i].resize(size); // default-construct each cell
    }
}

bool Board::isValidPosition(const Position &pos) const
{
    return pos.row >= 0 && pos.row < boardSize && pos.col >= 0 && pos.col < boardSize;
}

Position Board::findLinkPosition(Link &link) const
{
    if (link.isDownloaded())
    {
        throw std::runtime_error("Downloaded link is not on the board.");
    }

    for (int r = 0; r < boardSize; ++r)
    {
        for (int c = 0; c < boardSize; ++c)
        {
            if (grid[r][c].hasLink() && &grid[r][c].getLink() == &link)
            {
                return Position{r, c};
            }
        }
    }
    throw std::runtime_error("Link not found on board."); // BIG PROBLEM
}

void Board::placeFireWall(const Position &pos, Player &owner)
{
    if (!isValidPosition(pos))
        throw std::out_of_range("Cannot place firewall, invalid position.");

    Cell &cell = at(pos);
    if (cell.hasFeature<Firewall>())
    {
        throw std::runtime_error("Cannot place firewall: cell already has a firewall.");
    }
    if (cell.hasLink())
    {
        throw std::runtime_error("Cannot place firewall: cell has a link.");
    }
    if (cell.hasFeature<ServerPort>())
    {
        throw std::runtime_error("Cannot place firewall: cell has a server port.");
    }
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

std::vector<std::vector<char>> Board::getState() const
{
    std::vector<std::vector<char>> state;
    for (const auto &row : grid)
    {
        std::vector<char> rowState;
        for (const auto &cell : row)
        {
            rowState.push_back(cell.print());
        }
        state.push_back(rowState);
    }
    return state;
}

int Board::getSize() const
{
    return boardSize;
}

void Board::setup(std::vector<Player> &players)
{
    // place serverports
    at({0, 3}).setFeature(std::make_unique<ServerPort>(players[0]));
    at({0, 4}).setFeature(std::make_unique<ServerPort>(players[0]));
    at({boardSize - 1, 3}).setFeature(std::make_unique<ServerPort>(players[1]));
    at({boardSize - 1, 4}).setFeature(std::make_unique<ServerPort>(players[1]));

    // top row download edges
    for (int col = 0; col < boardSize; ++col)
    {
        if (col == 3 || col == 4)
            continue;
        at({0, col}).setFeature(std::make_unique<DownloadEdge>(players[1], Direction::Up));
    }

    // bottom row download edges
    for (int col = 0; col < boardSize; ++col)
    {
        if (col == 3 || col == 4)
            continue;
        at({boardSize - 1, col}).setFeature(std::make_unique<DownloadEdge>(players[0], Direction::Down));
    }

    // player 0 links
    const std::vector<Position> p0Positions = {// init positions
                                               {0, 0},
                                               {0, 1},
                                               {0, 2},
                                               {1, 3},
                                               {1, 4},
                                               {0, 5},
                                               {0, 6},
                                               {0, 7}};

    int i = 0;
    for (auto &pair : players[0].getLinks())
    {
        if (i >= p0Positions.size())
            throw std::runtime_error("Player 0 has too many links");

        placeLink(*pair.second, p0Positions[i]);
        ++i;
    }

    // player 1 links
    const std::vector<Position> p1Positions = {// init positions
                                               {boardSize - 1, 0},
                                               {boardSize - 1, 1},
                                               {boardSize - 1, 2},
                                               {boardSize - 2, 3},
                                               {boardSize - 2, 4},
                                               {boardSize - 1, 5},
                                               {boardSize - 1, 6},
                                               {boardSize - 1, 7}};

    i = 0;
    for (auto &pair : players[1].getLinks())
    {
        if (i >= p1Positions.size())
            throw std::runtime_error("Player 0 has too many links");

        placeLink(*pair.second, p1Positions[i]);
        ++i;
    }
}