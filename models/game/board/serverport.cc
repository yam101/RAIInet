#include "serverport.h"
#include "../../player/player.h"

ServerPort::ServerPort(Player &downloader, Player &owner) : downloader{downloader}, owner{owner} {}

Player &ServerPort::getDownloader() const
{
    return downloader;
}

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

    downloader.downloadLink(link);
}

char ServerPort::print() const
{
    return 'S';
}
