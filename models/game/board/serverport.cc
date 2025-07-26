#include "serverport.h"
#include "../../player/player.h"

ServerPort::ServerPort(Player &owner) : owner{owner} {}

Player &ServerPort::getOwner() const
{
    return owner;
}

void ServerPort::onEnter(Link &link, Player &enteringPlayer) const
{
    // can't enter your own server port
    if (&enteringPlayer == &owner)
    {
        throw std::invalid_argument("Cannot move onto your own server port.");
    }

    owner.downloadLink(link);
}

char ServerPort::print() const
{
    return 'S';
}
