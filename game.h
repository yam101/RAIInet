#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include <memory>
#include "board.h"

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

public:
    Game(GameNotification *notifier, TurnHandler *handler);

    void moveLink(char label, const std::string &direction);
    void useAbility(int index, const std::vector<std::string> &args);

    bool isOver() const;

    void notifyViews();
};

#endif
