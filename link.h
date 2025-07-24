#ifndef LINK_H
#define LINK_H

#include <string>

enum class LinkType
{
    Data,
    Virus
};

class MovementStrategy;

class Link
{
    char label; // a-h for player 1, A-H for player 2
    int ownerId;
    LinkType type;
    int strength;
    bool revealed;
    std::unique_ptr<MovementStrategy> movementStrategy;

public:
    Link(char label, int ownerId, LinkType type, int strength);

    char getLabel() const;
    int getOwnerId() const;
    LinkType getType() const;
    int getStrength() const;
    bool isRevealesd() const;

    void reveal();
    void setMovementStrategy(std::unique_ptr<MovementStrategy> strategy);
};

#endif
