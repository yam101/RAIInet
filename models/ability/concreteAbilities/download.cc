#include "download.h"
#include "../../player/player.h"

std::string Download::name() const
{
    return "Download";
}

int Download::numParams() const
{
    return 1;
}

AbilityContextRequest Download::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;

    request.needsLinkA = true;
    request.linkAOwner = LinkOwner::Opponent;
    request.linkALabel = args[0][0];

    request.needsUser = true;
    return request;
}

void Download::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    ctx.user->downloadLink(*ctx.linkA);
}
