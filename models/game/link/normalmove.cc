#include "normalmove.h"

Position NormalMove::doGetNewPos(const Position &from, Direction dir) const
{
    Position to = from;
    switch (dir)
    {
    case Direction::Up:
        to.row -= 1;
        break;
    case Direction::Down:
        to.row += 1;
        break;
    case Direction::Left:
        to.col -= 1;
        break;
    case Direction::Right:
        to.col += 1;
        break;
    }
    return to;
}
