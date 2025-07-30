#ifndef ABILITY_FACTORY_H
#define ABILITY_FACTORY_H

#include <memory>
#include "ability.h"

// factory pattern 
// make abilities from single-char labels (B, D, F, H, L, P, S, T)
class AbilityFactory
{
public:
    virtual ~AbilityFactory() = default;

    // return a new concrete Ability* depending on the label
    virtual std::unique_ptr<Ability> createAbility(char label) const;
};

#endif
