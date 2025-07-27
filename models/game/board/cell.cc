#include "cell.h"
#include <iostream>

Cell::Cell(): link{nullptr} {}

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
    // only allow 1 of each type
    for (const auto &existingFeature : features) {
        if (typeid(*existingFeature) == typeid(*feat)) {
            throw std::runtime_error("Cell already has a feature of this type.");
        }
    }
    features.push_back(std::move(feat));
}

bool Cell::hasLink() const
{
    return link != nullptr;
}

void Cell::onEnter(Link &link, Player &enteringPlayer) const
{
    for (const auto &feature : features)
    {
        feature->onEnter(link, enteringPlayer);
    }
}

char Cell::print() const
{
    if (link)
        return link->getLabel(); // always show real label
    
    // print the 1st feature w a special print function
    for (const auto &feature : features)
    {
        if (feature->print() != '.')
            return feature->print();
    }

    return '.'; // normal empty cell
}
