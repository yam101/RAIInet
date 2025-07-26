#include "firewallability.h"
#include "../../game/board/board.h"

std::string FirewallAbility::name() const
{
    return "Firewall";
}

int FirewallAbility::numParams() const
{
    return 2;
}

AbilityContextRequest FirewallAbility::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsBoard = true;
    request.needsUser = true;
    return request;
}

void FirewallAbility::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    try
    {
        int x = std::stoi(args[0]);
        int y = std::stoi(args[1]);

        Position pos{x, y};

        ctx.board->placeFireWall(pos, *ctx.user);
    }
    catch (const std::invalid_argument &e)
    {
        throw std::runtime_error("Invalid firewall position: arguments must be integers.");
    }
}
