#ifndef CELL_H
#define CELL_H

#include <memory>
#include <string>
#include <vector>
#include "../link/link.h"
#include "cellfeature.h"
#include "downloadedge.h"

class Cell
{
    Link *link; // cell does NOT own this link (not responsible for mem management)
    std::vector<std::unique_ptr<CellFeature>> features;

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
        for (const auto &feature : features) {
            T *ptr = dynamic_cast<T *>(feature.get());
            if (ptr) {
                return *ptr;
            }
        }
        throw std::runtime_error("No feature of type " + std::string(typeid(T).name()) + " found.");
    }

    template <typename T>
    bool hasFeature() const
    {
        static_assert(std::is_base_of<CellFeature, T>::value, "T must derive from CellFeature");
        for (const auto &feature : features) {
            if (dynamic_cast<T *>(feature.get()) != nullptr) {
                return true;
            }
        }
        return false;
    }
};

#endif
