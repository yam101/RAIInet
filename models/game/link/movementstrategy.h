#ifndef MOVEMENT_STRATEGY_H
#define MOVEMENT_STRATEGY_H

#include "../../position.h"
#include "../../direction.h"
#include <vector>

class MovementStrategy
{
public:
    virtual ~MovementStrategy() = default;

    // NVI idiom - public interface
    // returns the sequence of positions this link will occupy when moving
    std::vector<Position> getPath(const Position &from, Direction dir) const
    {
        return doGetPath(from, dir);
    }

protected:
    // concrete subclasses implement this
    virtual std::vector<Position> doGetPath(const Position &from, Direction dir) const = 0;
};

#endif
