#include "abilitycontextprovider.h"
#include "../player/player.h"
#include "../game/game.h"

// fwd def
class Board;
class Link;
class TurnHandler;

AbilityContextProvider::AbilityContextProvider(Game &game)
    : game(game)
{
}

Link &AbilityContextProvider::getUserLink(const char label) const
{
    Player &user = game.getCurrentPlayer();
    if (!user.hasLink(label))
    {
        throw std::runtime_error("Ability user Link with label '" + std::string(1, label) + "\' not found.");
    }
    return user.getLink(label);
}

Link &AbilityContextProvider::getAnyLink(const char label) const
{
    for (const Player &p : game.getPlayers()) // loop thru players to find link
    {
        if (p.hasLink(label))
        {
            return p.getLink(label);
        }
    }
    throw std::runtime_error("Link with label '" + std::string(1, label) + "' not found.");
}

Link &AbilityContextProvider::getOpponentLink(const char label) const
{
    Player &user = game.getCurrentPlayer(); // loop trhu players
    for (const Player &p : game.getPlayers())
    {
        if (&p == &user)
            continue; // skip user - opponents only

        if (p.hasLink(label))
        {
            return p.getLink(label);
        }
    }
    throw std::runtime_error("Opponent Link with label '" + std::string(1, label) + "' not found.");
}

// build context from request
AbilityContext AbilityContextProvider::getContext(const AbilityContextRequest &request) const
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
        // abilities cannot target downloaded links
        if (ctx.linkA->isDownloaded())
        {
            throw std::runtime_error("Cannot apply ability to downloaded link '" + std::string(1, request.linkALabel) + "'.");
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
        if (ctx.linkB->isDownloaded())
        {
            throw std::runtime_error("Cannot apply ability to downloaded link '" + std::string(1, request.linkBLabel) + "'.");
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
