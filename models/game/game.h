#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include <optional>
#include "board/board.h"

class Player;
class GameNotification;
class TurnHandler;
class AbilityContext;
class Ability;

class Game
{
    std::vector<Player> players;
    Board board;
    GameNotification *notification;
    TurnHandler *turnHandler;

    std::unique_ptr<AbilityContext> buildAbilityContext(const Ability &ability);

    bool handleDownloadEdge(Link &link, const Position &from, const Position &to);
    void battle(Link &attacker, Link &defender, const Position &from, const Position &to);
    Link &getUserLink(char label);

    std::optional<int> getWinnerId() const;

public:
    Game(GameNotification *notifier, TurnHandler *handler);

    std::vector<Player> &getPlayers() const;
    void moveLink(char label, const std::string &direction);
    void moveLinkHelper(Link &link, const std::string &direction);

    void useAbility(int index, const std::vector<std::string> &args);

    bool isOver() const;

    void notifyViews();
};

#endif
