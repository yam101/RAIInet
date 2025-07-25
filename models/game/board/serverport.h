#ifndef SERVER_PORT_H
#define SERVER_PORT_H

#include "cellfeature.h"

class ServerPort : public CellFeature
{
    Player &downloader;
    Player &owner;

public:
    ServerPort(Player &downloader, Player &owner);

    Player &getDownloader() const;
    Player &getOwner() const;

    void onEnter(Link &link, Player &enteringPlayer) const override;
    char print() const override;
};

#endif
