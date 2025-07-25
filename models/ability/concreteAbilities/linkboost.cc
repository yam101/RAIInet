#include "linkboost.h"

std::string LinkBoost::name() const
{
    return "LinkBoost";
}

AbilityContextRequest LinkBoost::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsLinkA = true;
    request.linkAOwner = LinkOwner::User;
    request.linkALabel = args[0][0]; // assumes first arg is the linkID

    return request;
}

void LinkBoost::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    Link &link = *ctx.linkA;
    link.setMovementStrategy(std::make_unique<BoostedMove>()); // apply new movementStrat
}

int LinkBoost::numParams() const
{
    return 1;
}