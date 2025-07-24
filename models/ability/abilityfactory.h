#ifndef ABILITY_FACTORY_H
#define ABILITY_FACTORY_H

#include <memory>
#include "ability.h"

class AbilityFactory
{
public:
    virtual ~AbilityFactory() = default;

    // Given a single-letter code, return a new Ability*
    virtual std::unique_ptr<Ability> createAbility(char code) const = 0;
};

#endif
