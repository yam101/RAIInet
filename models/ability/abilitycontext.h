#ifndef ABILITY_CONTEXT_H
#define ABILITY_CONTEXT_H

class Link;
class Board;
class Player;
class TurnHandler;
class Game;

struct AbilityContext
{
    Board *board = nullptr;
    Player *user = nullptr;
    Link *linkA = nullptr;
    Link *linkB = nullptr;
    TurnHandler *turnHandler = nullptr;
    Game *game = nullptr; // only provide this if there are NO other options
};

#endif
