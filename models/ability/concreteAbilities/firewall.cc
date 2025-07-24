#include "firewall.h"
#include "../../position.h"
#include "../../game/board.h"

std::string Firewall::name() const
{
    return "Firewall";
}

int Firewall::numParams() const
{
    return 2;
}

AbilityContextRequest Firewall::generateContextRequest(const std::vector<std::string> &args) const
{
    AbilityContextRequest request;
    request.needsBoard = true;
    request.needsUser = true;
    return request;
}

void Firewall::execute(const std::vector<std::string> &args, const AbilityContext &ctx)
{
    // should I check if arg is castable to int?
    if (args[0].isNumeric)
        ... int x = static_cast<int>(args[0]);
    int y = static_cast<int>(args[1]);
    // TODO: verify position is accurate
    Cell &cell = board.at(Position{x, y});

    cell.addFirewall... idk lol
}
