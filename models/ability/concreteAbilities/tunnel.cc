#include "tunnel.h"
#include "../../game/board/board.h"

std::string Tunnel::name() const
{
    return "Tunnel";
}

AbilityContextRequest Tunnel::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsLinkA = true;
    request.linkALabel = args[0][0]; // assumes first argument is link ID
    request.linkAOwner = LinkOwner::User;

    request.needsLinkB = true;
    request.linkBLabel = args[0][0]; // assumes first argument is link ID
    request.linkBOwner = LinkOwner::User;

    request.needsBoard = true;
    return request;
}

void Tunnel::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    Position posA = ctx.board->findLinkPosition(*ctx.linkA);
    Position posB = ctx.board->findLinkPosition(*ctx.linkB);

    ctx.board->removeLink(posA);
    ctx.board->moveLink(*ctx.linkB, posA);
    ctx.board->placeLink(*ctx.linkA, posB);
}

int Tunnel::numParams() const
{
    return 1;
}
