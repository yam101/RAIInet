#include "hijack.h"
#include "../../game/game.h"

std::string Hijack::name() const
{
    return "Hijack";
}

AbilityContextRequest Hijack::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsLinkA = true;
    request.linkALabel = args[0][0]; // assumes first argument is link ID
    request.linkAOwner = LinkOwner::Opponent;

    request.needsUser = true;
    request.needsGame = true; // have to access the game object directly to access move logic:(
    return request;
}

void Hijack::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    if (!ctx.linkA->isRevealed())
    {
        throw std::runtime_error("Hijack must be used on a revealed link");
    }

    ctx.game->moveLinkHelper(*ctx.linkA, ctx.game->parseDirection(args[1])); // skip checking ownership, just move
}

int Hijack::numParams() const
{
    return 2; // link label, direction
}
