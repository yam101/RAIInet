#include "cell.h"

Cell::Cell() {}

void Cell::setLink(Link *l)
{
    link = l;
}

Link *Cell::getLink() const
{
    return link;
}

void Cell::removeLink()
{
    link = nullptr;
}

void Cell::setFeature(std::unique_ptr<CellFeature> feat)
{
    feature = std::move(feat);
}

CellFeature *Cell::getFeature() const
{
    return feature.get();
}

void Cell::onEnter(Link &link, Player &enteringPlayer)
{
    if (feature)
    {
        feature->onEnter(link, enteringPlayer);
    }
}

char Cell::print(int viewerId) const
{
    if (link)
        return link->getLabel(); // always show real label
    if (feature)
        return feature->print(); // returns 'm', 'w', 'S', '='
    return '.';                  // normal empty cell
}
