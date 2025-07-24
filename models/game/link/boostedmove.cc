#include "boostedmove.h"
#include <cmath>

Position BoostedMove::doGetNewPos(const Position &from, Direction dir) const
{
    Position to = from;
    switch (dir)
    {
    case Direction::Up:
        to.row -= 2;
        break;
    case Direction::Down:
        to.row += 2;
        break;
    case Direction::Left:
        to.col -= 2;
        break;
    case Direction::Right:
        to.col += 2;
        break;
    }
    return to;
}