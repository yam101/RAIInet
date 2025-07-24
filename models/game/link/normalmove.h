#ifndef NORMAL_MOVE_H
#define NORMAL_MOVE_H

#include "movementstrategy.h"

class NormalMove : public MovementStrategy
{
protected:
    Position doGetNewPos(const Position &from, Direction dir) const override;
};

#endif
