#include "lag.h"
#include "../../game/link.h"
#include "../../position.h"

std::string Lag::name() const
{
    return "Lag";
}

AbilityContextRequest Lag::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsTurnHandler = true;
    return request;
}

void Lag::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    ctx.turnHandler->skipNextTurn();
}

int Lag::numParams() const
{
    return 0;
}
