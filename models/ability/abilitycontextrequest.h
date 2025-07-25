
#ifndef ABILITY_CONTEXT_REQUEST_H
#define ABILITY_CONTEXT_REQUEST_H

#include "../../position.h"

enum class LinkOwner
{
    User,
    Opponent,
    Any
};

struct AbilityContextRequest
{
    bool needsBoard = false;
    bool needsUser = false;
    bool needsTurnHandler = false;

    bool needsLinkA = false;
    char linkALabel = '\0';
    LinkOwner linkAOwner = LinkOwner::User;

    bool needsLinkB = false;
    char linkBLabel = '\0';
    LinkOwner linkBOwner = LinkOwner::User;

    bool needsGame = false; // only set to true if NO other options
};

#endif
