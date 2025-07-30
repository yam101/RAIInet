#include "gameState.h"
#include "../models/game/link/link.h"
#include "../models/player/player.h"
#include "../models/game/board/board.h"

// ctors for easy extraction of model state into GameState and WinState dtos

LinkState::LinkState(const Link &link, int ownerIdx)
    : ownerIndex{ownerIdx},
      isDownloaded{link.isDownloaded()},
      isRevealed{link.isRevealed()},
      type{link.getType()},
      strength{link.getStrength()},
      label{link.getLabel()} {}

PlayerState::PlayerState(const Player &player)
    : dataDownloads{player.getDownloadCount(LinkType::Data)},
      virusDownloads{player.getDownloadCount(LinkType::Virus)},
      abilityCount{player.getAbilityCount()} {}

// create complete game state snapshot from model objects
GameState::GameState(const Board &board, const std::vector<Player> &playersVec, int currentPlayer)
    : boardState{board.getState()}, currentPlayer{currentPlayer}
{
    // set up PlayerState vector
    for (const auto &player : playersVec)
    {
        players.emplace_back(player);
    }
    // set up linkStates
    for (size_t i = 0; i < playersVec.size(); ++i)
    {
        const auto &player = playersVec[i];
        for (const auto &pair : player.getLinks())
        {
            // emplace constructs LinkState in-place, avoiding copy
            linkStates.emplace(pair.first, LinkState(*pair.second, static_cast<int>(i)));
        }
    }
}

// construct win state - std::move avoids copying vector
WinState::WinState(int winnerId, std::vector<int> loserIds)
    : winnerId{winnerId}, loserIds{std::move(loserIds)} {} // move ctor for efficiency
