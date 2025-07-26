#include "player.h"
#include <sstream>
#include <random>
#include <fstream>
#include <iostream>

int Player::getId() const
{
    return id;
}

Link &Player::getLink(char label) const
{
    std::cout << "finding link" << label << std::endl;
    for (const auto &pair : links)
    {
        std::cout << pair.first << std::endl;
    }

    auto it = links.find(label);
    if (it == links.end())
    {
        throw std::invalid_argument("Link with label '" + std::string(1, label) + "' does not exist.");
    }
    return *(it->second);
}

bool Player::hasLink(char label) const
{
    return links.find(label) != links.end();
}

void Player::downloadLink(Link &link)
{
    LinkType type = link.getType();
    ++numDownloads[type];
    link.markDownloaded(); // tracks that it's been downloaded
}

int Player::getDownloadCount(LinkType type) const
{
    auto it = numDownloads.find(type);
    if (it == numDownloads.end())
        return 0;
    return it->second;
}

std::string Player::printAbilities() const
{
    std::ostringstream oss;
    oss << "Abilities: " << abilities.size() << "\n";
    for (size_t i = 0; i < abilities.size(); ++i)
    {
        // oss << static_cast<char>('a' + i) << ": ";
        oss << abilities[i]->name();
        if (abilities[i]->isUsed())
        {
            oss << "[USED]";
        }
        else
        {
            oss << "[AVAILABLE]";
        }
        oss << "\n";
    }
    return oss.str();
}

Ability &Player::getAbility(int index) const
{
    if (index < 0 || index >= abilities.size())
    {
        throw std::out_of_range("Invalid ability index: " + std::to_string(index));
    }
    return *abilities[index];
}

int Player::getAbilityCount() const
{
    int count = 0;
    for (const auto &ability : abilities)
    {
        if (!ability->isUsed())
        {
            count++;
        }
    }
    return count;
}

const std::map<char, std::unique_ptr<Link>> &Player::getLinks() const
{
    return links;
}

void Player::addAbility(char code, const AbilityFactory &factory)
{
    abilities.emplace_back(factory.createAbility(code));
}

void Player::addLink(char label, std::unique_ptr<Link> link)
{
    if (!link)
    {
        throw std::invalid_argument("Cannot add a null link.");
    }

    if (links.count(label))
    {
        throw std::invalid_argument(std::string("Link with label '") + label + "' already exists.");
    }

    links[label] = std::move(link);
}

void Player::loadLinksFromFile(const std::string &file)
{
    std::ifstream in(file);
    if (!in.is_open())
    {
        throw std::runtime_error("Could not open link file: " + file);
    }

    std::vector<std::string> tokens;
    std::string token;
    while (in >> token)
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 8)
    {
        throw std::runtime_error("Link file must contain exactly 8 tokens.");
    }

    char label = (id == 0) ? 'a' : 'A';
    for (const std::string &t : tokens)
    {
        LinkType type = (t[0] == 'V') ? LinkType::Virus : LinkType::Data;
        int strength = t[1] - '0';
        auto link = std::make_unique<Link>(label++, *this, type, strength);
        addLink(label, std::move(link));
    }
}

void Player::assignRandomLinks()
{
    std::vector<std::pair<LinkType, int>> types;

    for (int i = 1; i <= 4; ++i)
    {
        types.emplace_back(LinkType::Virus, i);
        types.emplace_back(LinkType::Data, i);
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(types.begin(), types.end(), g);

    char label = (id == 0) ? 'a' : 'A';

    for (const auto &[type, strength] : types)
    {
        auto link = std::make_unique<Link>(label, *this, type, strength);
        addLink(label++, std::move(link));
    }
}

void Player::setup(int playerId, const std::string &abilityCode, AbilityFactory &factory, const std::string *linkFileName)
{
    id = playerId;

    if (abilityCode.size() != 5)
    {
        throw std::invalid_argument("Player " + std::to_string(playerId + 1) + " must have exactly 5 abilities.");
    }

    std::unordered_map<char, int> counts;
    for (char c : abilityCode)
    {
        if (++counts[c] > 2)
        {
            throw std::invalid_argument("Player " + std::to_string(playerId + 1) +
                                        " has more than two of ability '" + std::string(1, c) + "'");
        }
        addAbility(c, factory);
    }

    if (linkFileName)
    {
        loadLinksFromFile(*linkFileName);
    }
    else
    {
        assignRandomLinks();
    }
}