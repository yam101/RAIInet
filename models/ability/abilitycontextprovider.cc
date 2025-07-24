#include "abilitycontextprovider.h"
#include "game.h"

// fwd def
class Board;
class Player;
class Link;
class TurnHandler;

AbilityContextProvider::AbilityContextProvider(Game &game)
    : game(game)
{
}

Link &AbilityContextProvider::getUserLink(const char label)
{
    Player &user = game.getCurrentPlayer();
    if (!user.hasLink(label))
    {
        throw std::runtime_error("Ability user Link with label '" + label + "' not found.");
    }
    return user.getLink(label);
}

Link &AbilityContextProvider::getAnyLink(const char &label)
{
    for (Player &p : game.getPlayers())
    {
        if (p.hasLink(label))
        {
            return p.getLink(label);
        }
    }
    throw std::runtime_error("Link with label '" + label + "' not found.");
}

Link &AbilityContextProvider::getOpponentLink(const char &label)
{
    Player &user = game.getCurrentPlayer();
    for (Player &p : game.getPlayers())
    {
        if (&p == &user)
            continue; // skip user

        if (p.hasLink(label))
        {
            return p.getLink(label);
        }
    }
    throw std::runtime_error("Opponent Link with label '" + label + "' not found.");
}

AbilityContext AbilityContextProvider::getContext(const AbilityContextRequest &request)
{
    AbilityContext ctx;

    if (request.needsBoard)
    {
        ctx.board = &game.getBoard();
    }

    if (request.needsUser)
    {
        ctx.user = &game.getCurrentPlayer();
    }

    if (request.needsLinkA)
    {
        switch (request.linkAOwner)
        {
        case LinkOwner::User:
            ctx.linkA = &getUserLink(request.linkALabel);
            break;
        case LinkOwner::Opponent:
            ctx.linkA = &getOpponentLink(request.linkALabel);
            break;
        case LinkOwner::Any:
            ctx.linkA = &getAnyLink(request.linkALabel);
            break;
        }
    }
    if (request.needsLinkB)
    {
        switch (request.linkBOwner)
        {
        case LinkOwner::User:
            ctx.linkB = &getUserLink(request.linkBLabel);
            break;
        case LinkOwner::Opponent:
            ctx.linkB = &getOpponentLink(request.linkBLabel);
            break;
        case LinkOwner::Any:
            ctx.linkB = &getAnyLink(request.linkBLabel);
            break;
        }
    }

    if (request.needsTurnHandler)
    {
        ctx.turnHandler = &game.getTurnHandler();
    }

    if (request.needsGame)
    {
        ctx.game = &game;
    }

    return ctx;
}
