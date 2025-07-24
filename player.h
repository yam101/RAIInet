#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include <memory>
#include "ability.h"
#include "abilityfactory.h"
#include "link.h"

class Link;

class Player
{
    int id;
    std::map<LinkType, int> numDownloads;
    std::map<char, Link *> links;
    std::vector<std::unique_ptr<Ability>> abilities;

public:
    virtual ~Player() = default;

    void addAbility(char code, const AbilityFactory &factory);
    // bool useAbility(int index, AbilityContext &ctx, const std::vector<std::string> &args);
    Ability *getAbility(int index) const;
    std::string printAbilities() const;

    int getId() const;

    void downloadLink(LinkType type);
    int getDownloadCount(LinkType type) const;
    bool hasWon() const;
};

#endif
