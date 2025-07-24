#ifndef NORMAL_CELL_H
#define NORMAL_CELL_H

#include "cell.h"

class NormalCell : public Cell
{
public:
    char print(int viewerId) const override
    {
        return '.';
    };
};

#endif
