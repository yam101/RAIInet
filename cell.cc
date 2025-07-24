#include "cell.h"
#include "link.h"
#include "player.h"

Cell::Cell() : link{nullptr}, type{CellType::Normal}, owner{nullptr} {}

Link *Cell::getLink() const
{
    return link;
}

CellType Cell::getType() const
{
    return type;
}

Player *Cell::getOwner() const
{
    return owner;
}

void Cell::setLink(Link *l)
{
    link = l;
}

void Cell::setType(CellType t, Player *p)
{
    type = t;
    owner = p;
}

char Cell::print() const
{
    if (link)
        return link->getLabel();

    switch (type)
    {
    case CellType::Firewall:
        return owner->getId() == 0 ? 'm' : 'w';
    case CellType::ServerPort:
        return 'S';
    case CellType::Normal:
    default:
        return '.';
    }
}
