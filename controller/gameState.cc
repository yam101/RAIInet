#include "gameState.h"
#include "../models/game/link/link.h"
#include "../models/player/player.h"
#include "../models/game/board/board.h"


LinkState::LinkState(const Link& link, int ownerIdx)
    : ownerIndex(ownerIdx),
      isDownloaded(link.isDownloaded()),
      isRevealed(link.isRevealed()),
      type(link.getType()),
      strength(link.getStrength()),
      label(link.getLabel()) {}

PlayerState::PlayerState(const Player& player)
    : dataDownloads(player.getDownloadCount(LinkType::Data)),
      virusDownloads(player.getDownloadCount(LinkType::Virus)),
      abilityCount(player.getAbilityCount()) {}

GameState::GameState(const Board& board, const std::vector<Player>& playersVec, int currentPlayer)
    : boardState(board.getState()), currentPlayer(currentPlayer)
{
    // set up PlayerState vector
    for (const auto& player : playersVec) {
        players.emplace_back(player);
    }
    // set up linkStates
    for (size_t i = 0; i < playersVec.size(); ++i) {
        const auto& player = playersVec[i];
        for (const auto& pair : player.getLinks()) {
            linkStates.emplace(pair.first, LinkState(*pair.second, static_cast<int>(i)));
        }
    }
} 