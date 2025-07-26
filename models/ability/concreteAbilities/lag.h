#ifndef LAG_H
#define LAG_H

#include "../ability.h"
#include "../../game/link/link.h"
#include "../../position.h"
#include "../../game/turnhandler.h"

class Lag : public Ability
{
public:
    std::string name() const override;

protected:
    AbilityContextRequest generateContextRequest(const std::vector<std::string> &args) const override;
    void execute(const std::vector<std::string> &args, const AbilityContext &ctx) override;
    int numParams() const override;
};

#endif
