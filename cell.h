#ifndef CELL_H
#define CELL_H

#include <string>
#include "celltype.h"

class Link;
class Player;

class Cell
{
    Link *link;
    CellType type;
    Player *owner; // for Firewall/Server ownership
public:
    Cell();

    Link *getLink() const;
    void setLink(Link *l);

    CellType getType() const;
    void setType(CellType t, Player *owner = nullptr);

    Player *getOwner() const;

    std::string print() const;
};

#endif
