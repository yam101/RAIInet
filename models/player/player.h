#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <map>
#include <memory>
#include "../ability/ability.h"
#include "../ability/abilityfactory.h"
#include "../game/link/link.h"

class Player
{
    int id;
    std::map<LinkType, int> numDownloads;
    std::map<char, std::unique_ptr<Link>> links;
    std::vector<std::unique_ptr<Ability>> abilities;
    void loadLinksFromFile(const std::string &file);
    void assignRandomLinks();

public:
    void addAbility(char code, const AbilityFactory &factory);
    Ability &getAbility(int index) const;
    int getAbilityCount() const;
    std::string printAbilities() const;

    int getId() const;

    Link &getLink(char label) const;
    const std::map<char, std::unique_ptr<Link>> &getLinks() const;
    void addLink(char label, std::unique_ptr<Link> link);
    bool hasLink(char label) const;
    void downloadLink(Link &link);
    int getDownloadCount(LinkType type) const;

    void setup(int playerId, const std::string &abilityCode, AbilityFactory &factory, const std::string *linkFileName = nullptr);
};

#endif
