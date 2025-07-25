#include "abilityfactory.h"
#include "concreteAbilities/download.h"
#include "concreteAbilities/firewall.h"
#include "concreteAbilities/hijack.h"
#include "concreteAbilities/lag.h"
#include "concreteAbilities/linkboost.h"
#include "concreteAbilities/polarize.h"
#include "concreteAbilities/scan.h"
#include "concreteAbilities/tunnel.h"
#include <stdexcept>


std::unique_ptr<Ability> AbilityFactory::createAbility(char label) const {
    switch (label) {
        case 'D': return std::make_unique<Download>();
        case 'F': return std::make_unique<Firewall>();
        case 'H': return std::make_unique<Hijack>();
        case 'L': return std::make_unique<Lag>();
        case 'B': return std::make_unique<LinkBoost>();
        case 'P': return std::make_unique<Polarize>();
        case 'S': return std::make_unique<Scan>();
        case 'T': return std::make_unique<Tunnel>();
        default:
            throw std::invalid_argument("Unknown ability: " + std::string(1, label));
    }
}

