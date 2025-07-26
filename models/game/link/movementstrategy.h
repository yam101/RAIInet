#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include "../../position.h"
#include "../../direction.h"

class MovementStrategy
{
public:
    virtual ~MovementStrategy() = default;

    // NVI
    Position getNewPos(const Position &from, Direction dir) const;

protected:
    virtual Position doGetNewPos(const Position &from, Direction dir) const = 0;
};

#endif
