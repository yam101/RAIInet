#include "boostedmove.h"

std::vector<Position> BoostedMove::doGetPath(const Position &from, Direction dir) const
{
    Position mid = from, end = from;
    switch (dir)
    {
    case Direction::Up:
        mid.row -= 1;
        end.row -= 2;
        break;
    case Direction::Down:
        mid.row += 1;
        end.row += 2;
        break;
    case Direction::Left:
        mid.col -= 1;
        end.col -= 2;
        break;
    case Direction::Right:
        mid.col += 1;
        end.col += 2;
        break;
    }
    return {mid, end};
}