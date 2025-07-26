#ifndef CELL_FEATURE_H
#define CELL_FEATURE_H

#include "../link/link.h"
#include "../../player/player.h"

class CellFeature
{
public:
    virtual ~CellFeature() = default;

    virtual void onEnter(Link &link, Player &player) const {}
    virtual char print() const = 0;
};

#endif
