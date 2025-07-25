#include <vector>
#include <map>
#include <utility>
#include "../models/game/link/linkType.h"

class Link;
class Player;
class Board;

struct LinkState
{
    int ownerIndex;
    bool isDownloaded;
    bool isRevealed;
    LinkType type;
    int strength;
    char label;

    LinkState(const Link &link, int ownerIdx);
};

struct PlayerState
{
    int dataDownloads;
    int virusDownloads;
    int abilityCount;

    PlayerState(const Player &player);
};

struct GameState
{
    std::vector<std::vector<char>> boardState;
    std::map<char, LinkState> linkStates;
    std::vector<PlayerState> players;
    int currentPlayer;

    GameState(const Board &board, const std::vector<Player> &playersVec, int currentPlayer);
};