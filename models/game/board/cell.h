#ifndef CELL_H
#define CELL_H

#include <memory>
#include <string>
#include "../link/link.h"
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

    void onEnter(Link &link, Player &enteringPlayer) const;

    char print() const;

    // must define template in header
    template <typename T>
    T &getFeature() const
    {
        static_assert(std::is_base_of<CellFeature, T>::value, "getFeature type T must be derived from CellFeature");
        if (!feature)
            throw std::runtime_error("Cell feature not set.");
        T *ptr = dynamic_cast<T *>(feature.get());
        if (!ptr)
            throw std::runtime_error("Wrong feature type.");
        return *ptr;
    }

    template <typename T>
    bool hasFeature() const
    {
        static_assert(std::is_base_of<CellFeature, T>::value, "T must derive from CellFeature");
        return feature && dynamic_cast<T *>(feature.get()) != nullptr;
    }
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
