#include "player.h"

int Player::getId() const
{
    return id;
}

Link &Player::getLink(char label)
{
    auto it = links.find(label);
    if (it == links.end())
    {
        throw std::invalid_argument("Link with label '" + std::string(1, label) + "' does not exist.");
    }
    return *(it->second);
}

bool Player::hasLink(char label)
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

int Player::getAbilityCount() const
{
    int count = 0;
    for (auto i : abilities)
    {
        if (!i->isUsed)
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