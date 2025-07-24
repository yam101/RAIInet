#include "scan.h"
#include "../../game/link.h"

std::string Scan::name() const
{
    return "Scan";
}

AbilityContextRequest Scan::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsLinkA = true;
    request.linkALabel = args[0]; // assumes first argument is link ID
    request.linkAOwner = LinkOwner::Opponent;
    return request;
}

void Scan::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    ctx.linkA->reveal();
}

int Scan::numParams() const
{
    return 1;
}
