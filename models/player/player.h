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
    std::map<LinkType, int> numDownloads; // tracks num of downloads by link type
    std::map<char, std::unique_ptr<Link>> links; // map of player's links
    std::vector<std::unique_ptr<Ability>> abilities; // vector of player's abilities
    void loadLinksFromFile(const std::string &file); // helper to load links from specified file
    void assignRandomLinks(); // helper to assign random links to player

    // helper called in Player::setup to add abilities
    void addAbility(char code, const AbilityFactory &factory);
    // helper called in Player::setup to add link to player's map
    void addLink(char label, std::unique_ptr<Link> link);

public:
    Ability &getAbility(int index) const; // get ability at specified index in the player's ability vector
    int getAbilityCount() const;          // counts total number of available abilities for this player
    std::string printAbilities() const;  // returns formatted string of all abilities

    int getId() const;
    Link &getLink(char label) const;
    const std::map<char, std::unique_ptr<Link>> &getLinks() const;
    bool hasLink(char label) const;
    void downloadLink(Link &link);
    int getDownloadCount(LinkType type) const;

    // initialize player with abilities and links
    void setup(int playerId, const std::string &abilityCode, AbilityFactory &factory, const std::string *linkFileName = nullptr);
};

#endif
