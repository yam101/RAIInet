#ifndef POSITION_H
#define POSITION_H

struct Position
{
    int row;
    int col;

    // overloaded operator= (checks if two positions are equal)
    bool operator==(const Position &other) const
    {
        return row == other.row && col == other.col;
    }

    // overloaded operator!= (checks if two positions are not equal)
    bool operator!=(const Position &other) const
    {
        return !(*this == other);
    }
};

#endif
