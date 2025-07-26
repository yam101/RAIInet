#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include "board/board.h"
#include "../ability/abilitycontextprovider.h"
#include "../ability/abilityfactory.h"
#include "turnhandler.h"
#include "../player/player.h"
#include "board/downloadedge.h"
#include "link/link.h"
#include "link/movementstrategy.h"

class Player;

class Game
{
    std::vector<Player> players;
    std::unique_ptr<Board> board;
    TurnHandler turnHandler;

    AbilityFactory abilityFactory;
    AbilityContextProvider abilityContextProvider; // MUST be last in init order

    bool handleDownloadEdge(Player &user, Link &link, const Position &from, const Direction &moveDir);
    void battle(Link &attacker, Link &defender, const Position &from, const Position &to);
    Link &getUserLink(char label);

    Direction parseDirection(const std::string &dirStr);

    void endTurn();

public:
    Game();

    void setup(const std::string &abilities1,
               const std::string &abilities2,
               const std::string *linkFile1 = nullptr,
               const std::string *linkFile2 = nullptr);

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
