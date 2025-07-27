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

    bool tryDownload(const std::vector<Position> &path,
                     const Position &from,
                     Link &link,
                     const Direction &dir);
    void battle(Link &attacker, Link &defender, const Position &from, const Position &to);
    Link &getUserLink(char label);
    void moveLink(char label, const std::string &direction);


    std::optional<int> getWinnerId() const;
    std::vector<int> getLoserIds() const;
    void endTurn();

public:
    Game();

    Direction parseDirection(const std::string &dirStr);

    void setup(const std::string &abilities1,
               const std::string &abilities2,
               const std::string *linkFile1 = nullptr,
               const std::string *linkFile2 = nullptr);
    void moveLinkHelper(Link &link, const Direction &dir);

    void Move(const std::vector<std::string> &params);
    void Ability(const std::vector<std::string> &params);
    std::string Abilities() const;

    bool isOver() const;
    void printGameOver() const;


    const std::vector<Player> &getPlayers() const;
    Board &getBoard();
    TurnHandler &getTurnHandler();
    Player &getCurrentPlayer();
};

#endif
