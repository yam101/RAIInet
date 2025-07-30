#ifndef FIREWALL_H
#define FIREWALL_H

#include "cellfeature.h"

class Firewall : public CellFeature
{
    Player &owner; // player who owns this firewall

public:
    Firewall(Player &owner);
    Player &getOwner() const;

    void onEnter(Link &link, Player &enteringPlayer) const override;
    char print() const override;
};

#endif
