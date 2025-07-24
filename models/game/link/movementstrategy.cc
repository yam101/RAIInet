#include "movementstrategy.h"

Position MovementStrategy::getNewPos(const Position &from, Direction dir) const
{
    return doGetNewPos(from, dir);
}