#ifndef ABILITYCONTEXTPROVIDER_H
#define ABILITYCONTEXTPROVIDER_H

#include "abilitycontext.h"
#include "abilitycontextrequest.h"
#include "../game/game.h"

class Player;

class AbilityContextProvider
{
    Link &getUserLink(const char label) const;
    Link &getAnyLink(const char label) const;
    Link &getOpponentLink(const char label) const;

public:
    explicit AbilityContextProvider(Game &game); //explicity bc 1 arg constructor

    AbilityContext getContext(const AbilityContextRequest &request) const;

private:
    Game &game;
};

#endif
