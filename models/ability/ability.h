#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <vector>
#include <stdexcept>
#include "abilitycontext.h"
#include "abilitycontextrequest.h"
#include "abilitycontextprovider.h"

// nvi + template method patterns for one-time-use abilities
class Ability
{
    bool used = false;

public:
    virtual ~Ability() {}

    // NVI idiom - shared interface
    void use(const std::vector<std::string> &args, const AbilityContextProvider &provider)
    {
        if (used)
        {
            throw std::runtime_error("Ability has already been used.");
        }
        validateNumParams(args);
        AbilityContextRequest request = generateContextRequest(args);
        AbilityContext context = provider.getContext(request);
        execute(args, context);
        used = true;
    }

    bool isUsed() const { return used; }

    virtual std::string name() const = 0;

protected:
    virtual AbilityContextRequest generateContextRequest(const std::vector<std::string> &args) const = 0;
    virtual void execute(const std::vector<std::string> &args, const AbilityContext &ctx) = 0;

    // shared validation based on numParams()
    void validateNumParams(const std::vector<std::string> &args) const
    {
        if (args.size() != static_cast<std::size_t>(numParams()))
        {
            throw std::invalid_argument(
                "Ability '" + name() + "' expected " + std::to_string(numParams()) +
                " arguments but got " + std::to_string(args.size()) + ".");
        }
    }

    virtual int numParams() const = 0;
};

#endif
