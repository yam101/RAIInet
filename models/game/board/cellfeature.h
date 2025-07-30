#ifndef CELL_FEATURE_H
#define CELL_FEATURE_H

#include "../link/link.h"
#include "../../player/player.h"

class CellFeature
{
public:
    virtual ~CellFeature() = default;

    // called when a link enters this cell
    virtual void onEnter(Link &link, Player &player) const {}
    // return char representation of this feature
    virtual char print() const = 0;
};

#endif
