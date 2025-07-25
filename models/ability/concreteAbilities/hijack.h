#ifndef HIJACK_H
#define HIJACK_H

#include "ability.h"
#include "../../game/link/link.h"
#include "../../position.h"

class Hijack : public Ability
{
public:
    std::string name() const override;

protected:
    AbilityContextRequest generateContextRequest(const std::vector<std::string> &args) const override;
    void execute(const std::vector<std::string> &args, const AbilityContext &ctx) override;
    int numParams() const override;
};

#endif
