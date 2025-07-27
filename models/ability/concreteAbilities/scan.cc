#include "scan.h"

std::string Scan::name() const
{
    return "Scan";
}

AbilityContextRequest Scan::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsLinkA = true;
    request.linkALabel = args[0][0]; // assumes first argument is link ID
    request.linkAOwner = LinkOwner::Opponent;
    return request;
}

void Scan::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    if (ctx.linkA->isRevealed())
    {
        throw std::runtime_error("Link " + std::string(1, ctx.linkA->getLabel()) + " is already revealed.");
    }
    ctx.linkA->reveal();
}

int Scan::numParams() const
{
    return 1;
}
