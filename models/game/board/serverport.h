#ifndef SERVER_PORT_H
#define SERVER_PORT_H

#include "cell.h"

class ServerPort : public Cell
{
    Player &downloader;
    Player &owner;

public:
    ServerPort(Player &downloader, Player &owner);

    Player &getDownloader() const;
    Player &getOwner() const;

    void onEnter(Link &link, Player &enteringPlayer) override;
    char print() const override;
};

#endif
