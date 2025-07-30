#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <vector>
#include <map>
#include <utility>
#include "../models/game/link/linkType.h"

class Link;
class Player;
class Board;

// data transfer objects - to decouple models from views


struct LinkState
{
    int ownerIndex;    // which player owns this link (0 or 1)
    bool isDownloaded;
    bool isRevealed;   // whether link type is visible to opponents
    LinkType type;     // Data or Virus
    int strength; 
    char label;        // a-h, A-H
    LinkState(const Link &link, int ownerIdx);
};

struct PlayerState
{
    int dataDownloads; 
    int virusDownloads; 
    int abilityCount;   // number of remaining abilities

    PlayerState(const Player &player);
};

// complete game state snapshot for views
// decouples model classes from views
struct GameState
{
    std::vector<std::vector<char>> boardState; // 2d grid representation
    std::map<char, LinkState> linkStates;      // mapping from link label to Link info
    std::vector<PlayerState> players; 
    int currentPlayer;                         // whose turn it is (0 or 1)

    GameState(const Board &board, const std::vector<Player> &playersVec, int currentPlayer);
};

// passed in view::notifyWin(), similar to GameState
// also decouples models from views
struct WinState
{
    int winnerId;                // player who won
    std::vector<int> loserIds;   // players who lost

    WinState(int winnerId, std::vector<int> loserIds);
};

#endif