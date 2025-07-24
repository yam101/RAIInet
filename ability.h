#ifndef ABILITY_H
#define ABILITY_H

#include <vector>
#include <string>

struct AbilityContext;

class Ability
{
protected:
    bool used = false;

public:
    virtual ~Ability() = default;
    virtual std::string name() const = 0;
    virtual bool use(AbilityContext &ctx, const std::vector<std::string> &args) = 0;
    bool isUsed() const;
    // void markUsed();
};

#endif
