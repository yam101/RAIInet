#include "firewall.h"

Firewall::Firewall(Player &owner) : owner{owner} {}

Player &Firewall::getOwner() const
{
    return owner;
}

void Firewall::onEnter(Link &link, Player &enteringPlayer) const
{
    if (&enteringPlayer != &owner)
    {
        link.reveal();

        // if virus, download it immediately (by its the virus's owner)
        if (link.getType() == LinkType::Virus)
        {
            link.getOwner().downloadLink(link);
        }
    }

    // nothing happens if the owner enters their own firewall
    // NOTE: Game remove the link from the board if downloaded (Firewall doesn't have board access)
}

char Firewall::print() const
{
    return owner.getId() == 0 ? 'm' : 'w';
}