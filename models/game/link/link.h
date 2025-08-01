#ifndef LINK_H
#define LINK_H

#include <string>
#include <memory>
#include "linkType.h"
#include "movementstrategy.h"
#include "normalmove.h"

class Player;

class Link
{
    char label; // a-h for player 1, A-H for player 2
    Player &owner;
    LinkType type;
    int strength;
    bool revealed;
    bool downloaded;
    std::unique_ptr<MovementStrategy> movementStrategy;

public:
    Link(char label, Player &owner, LinkType type, int strength);

    char getLabel() const;
    Player &getOwner() const;
    LinkType getType() const;
    int getStrength() const;
    bool isRevealed() const;
    bool isDownloaded() const;
    MovementStrategy &getMovementStrategy() const;

    void setType(LinkType t);
    void markDownloaded();
    void reveal();
    void setMovementStrategy(std::unique_ptr<MovementStrategy> strategy);
};

#endif
