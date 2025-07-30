#ifndef SERVER_PORT_H
#define SERVER_PORT_H

#include "cellfeature.h"

class ServerPort : public CellFeature
{
    Player &owner; // player who owns this server port

public:
    ServerPort(Player &owner);

    Player &getOwner() const;

    void onEnter(Link &link, Player &enteringPlayer) const override;
    char print() const override;
};

#endif
