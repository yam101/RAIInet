#ifndef NORMAL_CELL_H
#define NORMAL_CELL_H

#include "cellfeature.h"

class NormalCell : public CellFeature
{
public:
    char print() const override
    {
        return '.';
    };
};

#endif
