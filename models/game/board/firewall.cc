#include "firewall.h"

Firewall::Firewall(Player &owner) : owner{owner} {}

Player &Firewall::getOwner() const
{
    return owner;
}

Player &Firewall::getOwner() const
{
    return owner;
}

void Firewall::onEnter(Link &link, Player &enteringPlayer) const
{
    if (&enteringPlayer != &owner)
    {
        // Reveal the link if we move onto an opponent's firewall
        link.reveal();

        // If it's a virus, download it immediately (by its owner)
        if (link.getType() == LinkType::Virus)
        {
            link.getOwner().downloadLink(link);
        }
    }

    // nothing happens if the owner enters their own firewall
    // NOTE: The Game must still remove the link from the board if downloaded
    // This class doesn't touch the board
}

char Firewall::print() const
{
    return owner.getId() == 0 ? 'm' : 'w';
}