#include "hijack.h"

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
    request.needsGame = true; // have to access the game object directly :(
    return request;
}

void Hijack::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    if (!ctx.linkA->isRevealed())
    {
        throw std::runtime_error("Hijack must be used on a revealed link");
    }

    ctx.game->moveLink(ctx.linkA->getLabel(), args[1]); // might need to call moveLinkHelper?
}

int Hijack::numParams() const
{
    return 1;
}
