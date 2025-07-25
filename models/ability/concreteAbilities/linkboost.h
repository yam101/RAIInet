#ifndef LINKBOOST_H
#define LINKBOOST_H

#include "ability.h"
#include "../../game/link/boostedmove.h"

class LinkBoost : public Ability
{
public:
    std::string name() const override;

protected:
    AbilityContextRequest generateContextRequest(const std::vector<std::string> &args) const override;
    void execute(const std::vector<std::string> &args, const AbilityContext &ctx) override;
    int numParams() const override;
};

#endif
