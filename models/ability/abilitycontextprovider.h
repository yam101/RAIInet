#ifndef ABILITYCONTEXTPROVIDER_H
#define ABILITYCONTEXTPROVIDER_H

#include "abilitycontext.h"
#include "abilitycontextrequest.h"

class Game;
class Player;

class AbilityContextProvider
{
public:
    explicit AbilityContextProvider(Game &game);

    AbilityContext getContext(const AbilityContextRequest &request);

private:
    Game &game;
};

#endif
