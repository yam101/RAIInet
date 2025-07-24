#ifndef BOOSTED_MOVE_H
#define BOOSTED_MOVE_H

#include "movementstrategy.h"

class BoostedMove : public MovementStrategy
{
protected:
    Position doGetNewPos(const Position &from, Direction dir) const override;
};

#endif
