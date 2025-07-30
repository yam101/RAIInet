#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
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
    std::vector<Player> players; // all players in the game
    std::unique_ptr<Board> board; // game board
    TurnHandler turnHandler; // manages turn order and state

    AbilityFactory abilityFactory; // creates ability instances
    AbilityContextProvider abilityContextProvider; // provides context for abilities (MUST be last in init order)

    // checks if link can be downloaded at board edge
    bool tryDownload(const std::vector<Position> &path,
                     const Position &from,
                     Link &link,
                     const Direction &dir);
    // resolve battle between two links
    void battle(Link &attacker, Link &defender, const Position &from, const Position &to);
    // get current player's link by label
    Link &getUserLink(char label);
    // move link in specified direction
    void moveLink(char label, const std::string &direction);

    // advance to next player's turn
    void endTurn();

public:
    Game();

    // convert string direction to Direction enum
    // has to be public because we use it in Hijack
    Direction parseDirection(const std::string &dirStr);

    // initialize game with players and abilities
    void setup(const std::string &abilities1,
               const std::string &abilities2,
               const std::string *linkFile1 = nullptr,
               const std::string *linkFile2 = nullptr);
    // helper method for moving links
    // also needs to be public because we use it in Hijack
    void moveLinkHelper(Link &link, const Direction &dir);

    // called from Controller to execute a move
    void Move(const std::vector<std::string> &params);
    // called from Controller to execute an ability
    void Ability(const std::vector<std::string> &params);
    // get formatted string of current player's abilities
    std::string Abilities() const;

    // get winner's player id
    int getWinnerId() const;
    // get list of loser player ids
    std::vector<int> getLoserIds() const;
    // check if game has ended
    bool isOver() const;

    // various getters used by Controller to create game state
    // as well as in certain abilities
    const std::vector<Player> &getPlayers() const;
    Board &getBoard();
    TurnHandler &getTurnHandler();
    Player &getCurrentPlayer();
};

#endif
