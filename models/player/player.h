#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include <memory>
#include "../ability/ability.h"
#include "../ability/abilityfactory.h"
#include "../game/link/link.h"

class Link;

class Player
{
    int id;
    std::map<LinkType, int> numDownloads;
    std::map<char, std::unique_ptr<Link>> links;
    std::vector<std::unique_ptr<Ability>> abilities;

public:
    virtual ~Player() = default;

    void addAbility(char code, const AbilityFactory &factory);
    // bool useAbility(int index, AbilityContext &ctx, const std::vector<std::string> &args);
    Ability &getAbility(int index) const;
    int getAbilityCount() const;
    std::string printAbilities() const;

    int getId() const;

    Link &getLink(char label) const;
    const std::map<char, std::unique_ptr<Link>> &getLinks() const;
    bool hasLink(char label) const;
    void downloadLink(Link &link);
    int getDownloadCount(LinkType type) const;
    // bool hasWon() const;
};

#endif
