#include "polarize.h"

std::string Polarize::name() const
{
    return "Polarize";
}

AbilityContextRequest Polarize::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsLinkA = true;
    request.linkALabel = args[0][0]; // assumes first argument is link ID
    request.linkAOwner = LinkOwner::Any; // any player's link can be polarized
    return request;
}

void Polarize::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    LinkType type = ctx.linkA->getType();
    if (type == LinkType::Virus) // virus -> data
    {
        ctx.linkA->setType(LinkType::Data);
    }
    else // data -> virus
    {
        ctx.linkA->setType(LinkType::Virus);
    }
}

int Polarize::numParams() const
{
    return 1; // link label
}
