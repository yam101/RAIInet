#include "cell.h"
#include <iostream>

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
    {
        // std::cout << feature->print() << std::endl;
        return feature->print(); // returns 'm', 'w', 'S', '='
    }

    return '.'; // normal empty cell
}
