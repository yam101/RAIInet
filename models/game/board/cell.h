#ifndef CELL_H
#define CELL_H

#include <memory>
#include <string>
#include "link.h"
#include "cellfeature.h"
#include "downloadedge.h"

class Cell
{
    Link *link; // cell does NOT own this link (not responsible for mem management)
    std::unique_ptr<CellFeature> feature;

public:
    Cell(); // default ctor
    void setLink(Link &l);
    Link &getLink() const;
    bool hasLink() const;
    void removeLink();

    void setFeature(std::unique_ptr<CellFeature> feat);
    template <typename T>
    T &getFeature() const;

    void onEnter(Link &link, Player &enteringPlayer) const;

    char print() const;
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
