#include "download.h"
#include "../../game/board/board.h"
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
    request.needsBoard = true; // needed to remove downloaded link

    return request;
}

void Download::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    if (ctx.linkA->isDownloaded())
    {
        throw std::runtime_error("Link has already been downloaded.");
    }
    ctx.board->removeLink(ctx.board->findLinkPosition(*ctx.linkA)); // remove from board before downloading
    ctx.user->downloadLink(*ctx.linkA);
}
