#include "cell.h"

Cell::Cell() {}

void Cell::setLink(Link &l)
{
    link = &l;
}

Link &Cell::getLink() const
{
    if (!link)
    {
        throw std::runtime_error("No link set in this cell.");
    }
    return *link;
}

void Cell::removeLink()
{
    link = nullptr;
}

void Cell::setFeature(std::unique_ptr<CellFeature> feat)
{
    feature = std::move(feat);
}

template<typename T>
T& Cell::getFeature() const {
    static_assert(std::is_base_of<CellFeature, T>::value, "getFeature type T must be derived from CellFeature");
    if (!feature) throw std::runtime_error("Cell feature not set.");
    T* ptr = dynamic_cast<T*>(feature.get());
    if (!ptr) throw std::runtime_error("Wrong feature type.");
    return *ptr;
}
bool Cell::hasLink() const
{
    return link != nullptr;
}


void Cell::onEnter(Link &link, Player &enteringPlayer) const
{
    if (feature)
    {
        feature->onEnter(link, enteringPlayer);
    }
}

char Cell::print() const
{
    if (link)
        return link->getLabel(); // always show real label
    if (feature)
        return feature->print(); // returns 'm', 'w', 'S', '='
    return '.';                  // normal empty cell
}
