#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include "board/board.h"
#include "../ability/abilitycontextprovider.h"
#include "../ability/abilityfactory.h"
#include "player/player.h"
#include "turnhandler.h"
#include "board/downloadedge.h"
#include "link/link.h"

class Player;
class GameNotification;
class TurnHandler;

class Game
{
    std::vector<Player> players;
    std::unique_ptr<Board> board;
    TurnHandler turnHandler;

    AbilityFactory abilityFactory;
    AbilityContextProvider abilityContextProvider;

    bool handleDownloadEdge(Link &link, const Position &from, const Direction &moveDir);
    void battle(Link &attacker, Link &defender, const Position &from, const Position &to);
    Link &getUserLink(char label);

    Direction parseDirection(const std::string &dirStr);

    void endTurn();

public:
    const std::vector<Player> &getPlayers() const;
    void moveLink(char label, const std::string &direction);
    void moveLinkHelper(Link &link, const Direction &dir);

    void useAbility(int index, const std::vector<std::string> &args);

    bool isOver() const;
    std::optional<int> getWinnerId() const;
    std::vector<int> getLoserIds() const;

    void notifyViews();
    Board &getBoard();
    TurnHandler &getTurnHandler();
    Player &getCurrentPlayer();
};

#endif
