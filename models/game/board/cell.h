#ifndef CELL_H
#define CELL_H

#include <memory>
#include <string>
#include "link.h"
#include "cellfeature.h"

class Cell
{
    Link *link = nullptr;
    std::unique_ptr<CellFeature> feature;

public:
    Cell();
    void setLink(Link *l);
    Link *getLink() const;
    void removeLink();

    void setFeature(std::unique_ptr<CellFeature> feat);
    CellFeature *getFeature() const;

    void onEnter(Link &link, Player &enteringPlayer);
    bool canEnter(Player &player) const;

    char print(int viewerId) const;
};

#endif

// #ifndef CELL_H
// #define CELL_H

// #include <string>

// class Link;
// class Player;

// enum class CellType
// {
//     Normal,
//     Firewall,
//     ServerPort
// };

// class Cell
// {
//     Link *link;
//     CellType type;
//     Player *owner; // for Firewall/Server ownership
// public:
//     Cell();

//     Link *getLink() const;
//     CellType getType() const;
//     Player *getOwner() const;

//     void setLink(Link &l);
//     void removeLink();
//     void setType(CellType t, Player *owner = nullptr);

//     char print() const;
// };

// #endif
