#ifndef CELL_H
#define CELL_H

#include <string>

class Link;
class Player;

enum class CellType
{
    Normal,
    Firewall,
    ServerPort
};

class Cell
{
    Link *link;
    CellType type;
    Player *owner; // for Firewall/Server ownership
public:
    Cell();

    Link *getLink() const;
    CellType getType() const;
    Player *getOwner() const;

    void setLink(Link *l);
    void setType(CellType t, Player *owner = nullptr);

    char print() const;
};

#endif
