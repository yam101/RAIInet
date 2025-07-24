#ifndef FIREWALL_H
#define FIREWALL_H

#include "ability.h"

class Firewall : public Ability
{
public:
    std::string name() const override;

protected:
    AbilityContextRequest generateContextRequest(const std::vector<std::string> &args) const override;
    void execute(const std::vector<std::string> &args, const AbilityContext &ctx) override;
    int numParams() const override;
};

#endif
