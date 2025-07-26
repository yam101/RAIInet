#ifndef FIREWALL_ABILITY_H
#define FIREWALL_ABILITY_H

#include "../ability.h"
#include "../../position.h"
#include "../../game/board/board.h"

class FirewallAbility : public Ability
{
public:
    std::string name() const override;

protected:
    AbilityContextRequest generateContextRequest(const std::vector<std::string> &args) const override;
    void execute(const std::vector<std::string> &args, const AbilityContext &ctx) override;
    int numParams() const override;
};

#endif
