#ifndef ABILITYCONTEXTPROVIDER_H
#define ABILITYCONTEXTPROVIDER_H

#include "abilitycontext.h"
#include "abilitycontextrequest.h"
#include "../game/game.h"

class Player;

class AbilityContextProvider
{
    Link &getUserLink(const char label);
    Link &getAnyLink(const char label);
    Link &getOpponentLink(const char label);

public:
    explicit AbilityContextProvider(Game &game);

    AbilityContext getContext(const AbilityContextRequest &request);

private:
    Game &game;
};

#endif
