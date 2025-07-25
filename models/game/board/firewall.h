#ifndef FIREWALL_H
#define FIREWALL_H

#include "cellfeature.h"

class Firewall : public CellFeature
{
    Player &owner;

public:
    Firewall(Player &owner);
    Player &getOwner() const;

    void onEnter(Link &link, Player &enteringPlayer) const override;
    char print() const override;
};

#endif
