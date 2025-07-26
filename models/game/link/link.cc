#include "link.h"

Link::Link(char label, Player &owner, LinkType type, int strength)
    : label{label},
      owner{owner},
      type{type},
      strength{strength},
      revealed{false},
      downloaded{false},
      movementStrategy{std::make_unique<NormalMove>()} {}

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

void Link::setMovementStrategy(std::unique_ptr<MovementStrategy> strategy)
{
    movementStrategy = std::move(strategy);
}

MovementStrategy &Link::getMovementStrategy() const
{
    return *movementStrategy;
}