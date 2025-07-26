#ifndef BOOSTED_MOVE_H
#define BOOSTED_MOVE_H

#include "movementstrategy.h"

class BoostedMove : public MovementStrategy
{
protected:
    std::vector<Position> doGetPath(const Position &from, Direction dir) const override;
};

#endif
