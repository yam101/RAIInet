#include "link.h"
#include "movementstrategy.h"

Link::Link(char label, Player &owner, LinkType type, int strength)
    : label{label},
      owner{owner},
      type{type},
      strength{strength},
      revealed{false},
      downloaded{false},
      movementStrategy(nullptr) {}

char Link::getLabel() const
{
    return label;
}

Player &Link::getOwner() const
{
    return owner;
}

LinkType Link::getType() const
{
    return type;
}

int Link::getStrength() const
{
    return strength;
}

bool Link::isRevealed() const
{
    return revealed;
}

bool Link::isDownloaded() const
{
    return downloaded;
}

void Link::setType(LinkType t)
{
    type = t;
}

void Link::markDownloaded()
{
    downloaded = true;
}

void Link::reveal()
{
    revealed = true;
}

void Link::setMovementStrategy(MovementStrategy &strategy)
{
    movementStrategy.reset(&strategy); // transfers ownership
}

MovementStrategy &Link::getMovementStrategy() const
{
    return *movementStrategy;
}